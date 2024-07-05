#ifndef BASE32_DECODER_H_
#define BASE32_DECODER_H_

#include <string>
#include <cstdint>

#include "utility/utility.h"

namespace base32 {

template<typename InputIt, typename OutputIt>
std::streamsize Decode(InputIt input_begin, InputIt input_end, OutputIt output_begin) {
	std::streamsize written = 0;
	int8_t buffer_write_bit = 0;

	while (*(input_end - 1) == kPaddingChar) { // max 6 iterations
		--input_end;
	}

	uint8_t group;
	int8_t group_bit = 0;

	uint8_t decoded_byte = 0;

	for (InputIt byte = input_begin; byte != input_end;) {
		group = CharToB32(*byte);
		int8_t bits_to_extract = std::min(8 - buffer_write_bit, 5 - group_bit);

		decoded_byte |= FirstN(group << (3 + group_bit), bits_to_extract, buffer_write_bit);

		buffer_write_bit += bits_to_extract;
		group_bit += bits_to_extract;

		if (buffer_write_bit == 8) {
			buffer_write_bit = 0;
			*output_begin++ = decoded_byte;
			++written;
			decoded_byte = 0;
		}

		if (group_bit == 5) {
			++byte;
			group_bit = 0;
		}
	}

	return written;
}

void DecodeStream(std::istream& in, std::ostream& out, size_t max_buffer_size = 16000);
void DecodeFile(const std::string& input_path, const std::string& output_path, size_t max_buffer_size = 16000);

} // base32

#endif //BASE32_DECODER_H_
