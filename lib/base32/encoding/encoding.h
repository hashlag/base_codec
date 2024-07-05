#ifndef BASE32_ENCODER_H_
#define BASE32_ENCODER_H_

#include <string>
#include <cstdint>

#include "utility/utility.h"

namespace base32 {

template<typename InputIt, typename OutputIt>
void Encode(InputIt input_begin, InputIt input_end, OutputIt output_begin) {
	int8_t input_bit = 0;
	int8_t group_bit = 0;

	uint8_t group = 0;

	int8_t octets_in_last_block = 0;

	for (InputIt byte = input_begin; byte != input_end;) {
		int8_t bits_to_take = std::min(8 - input_bit, 5 - group_bit);
		group |= FirstN(*byte << input_bit, bits_to_take, group_bit + 3);

		group_bit += bits_to_take;
		input_bit += bits_to_take;

		if (group_bit == 5) {
			*output_begin++ = kBase32Alphabet[group];

			octets_in_last_block = (octets_in_last_block + 1) % 8;
			group_bit = 0;
			group = 0;
		}

		if (input_bit == 8) {
			++byte;
			input_bit = 0;
		}
	}

	if (group_bit != 0) {
		*output_begin++ = kBase32Alphabet[group];
		octets_in_last_block = (octets_in_last_block + 1) % 8;
	}

	if (octets_in_last_block) {
		for (int8_t i = 0; i < 8 - octets_in_last_block; ++i) {
			*output_begin++ = kPaddingChar;
		}
	}
}

void EncodeStream(std::istream& in, std::ostream& out, size_t max_buffer_size = 16000);
void EncodeFile(const std::string& input_path, const std::string& output_path, size_t max_buffer_size = 16000);

} // base32

#endif //BASE32_ENCODER_H_
