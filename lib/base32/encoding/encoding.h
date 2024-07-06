#ifndef BASE32_ENCODER_H_
#define BASE32_ENCODER_H_

#include <string>
#include <cstdint>

#include "utility/utility.h"

namespace base32 {

/**
 * Encodes an entire [input_begin, input_end) range of bytes into [output_begin, EncodedSize(input_size) + output_begin).
 * @tparam InputIt input iterator type
 * @tparam OutputIt output iterator type
 * @param input_begin iterator pointing to the first element of the input range
 * @param input_end iterator pointing right after the last element of the input range
 * @param output_begin iterator pointing to the first element of the output range
 * @return number of bytes written to the output range
 */
template<typename InputIt, typename OutputIt>
std::streamsize Encode(InputIt input_begin, InputIt input_end, OutputIt output_begin) {
	std::streamsize written = 0;

	int8_t input_bit = 0;
	int8_t current_group_bit = 0;

	uint8_t current_group = 0;

	int8_t groups_in_current_block = 0;

	for (InputIt byte = input_begin; byte != input_end;) {
		int8_t bits_to_take = std::min(kBitsInByte - input_bit, kBitsInGroup - current_group_bit);
		current_group |= FirstNBits(*byte << input_bit, bits_to_take) >> (kGroupStartingBit + current_group_bit);

		current_group_bit += bits_to_take;
		input_bit += bits_to_take;

		if (current_group_bit == kBitsInGroup) {
			*output_begin++ = kBase32Alphabet[current_group];
			++written;

			groups_in_current_block = (groups_in_current_block + 1) % kGroupsInBlock;
			current_group_bit = 0;
			current_group = 0;
		}

		if (input_bit == kBitsInByte) {
			++byte;
			input_bit = 0;
		}
	}

	if (current_group_bit != 0) {
		*output_begin++ = kBase32Alphabet[current_group];
		++written;
		groups_in_current_block = (groups_in_current_block + 1) % kGroupsInBlock;
	}

	if (groups_in_current_block) {
		for (int8_t i = 0; i < kGroupsInBlock - groups_in_current_block; ++i) {
			*output_begin++ = kPaddingChar;
		}

		written += kGroupsInBlock - groups_in_current_block;
	}

	return written;
}

/**
 * Encodes an entire 'in' stream into 'out'.
 * @param in input stream
 * @param out output stream
 * @param max_buffer_size maximum buffer size (can't be less than 40, default = 4096)
 */
void EncodeStream(std::istream& in, std::ostream& out, size_t max_buffer_size = 4096);

/**
 * Encodes the entire file into another one.
 * @param input_path path to the input file
 * @param output_path path to the output file
 * @param max_buffer_size maximum buffer size (can't be less than 40, default = 4096)
 * @throws std::system_error I/O exceptions
 */
void EncodeFile(const std::string& input_path, const std::string& output_path, size_t max_buffer_size = 4096);

} // base32

#endif //BASE32_ENCODER_H_
