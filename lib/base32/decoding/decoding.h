#ifndef BASE32_DECODER_H_
#define BASE32_DECODER_H_

#include <string>
#include <cstdint>

#include "utility/utility.h"

namespace base32 {

/**
 * Decodes an entire [input_begin, input_end) range of bytes into [output_begin, DecodedSize(input_size) + output_begin).
 * @tparam InputIt input iterator type
 * @tparam OutputIt output iterator type
 * @param input_begin iterator pointing to the first element of the input range
 * @param input_end iterator pointing right after the last element of the input range
 * @param output_begin iterator pointing to the first element of the output range
 * @throws std::runtime_error when encountering a character which is not a valid Base32 alphabet entry
 * @return number of bytes written to the output range
 */
template<typename InputIt, typename OutputIt>
std::streamsize Decode(InputIt input_begin, InputIt input_end, OutputIt output_begin) {
	std::streamsize written = 0;

	while (*(input_end - 1) == kPaddingChar) { // max 6 iterations
		--input_end;
	}

	int8_t decoded_group_bit = 0;

	uint8_t decoded_byte = 0;
	int8_t decoded_byte_bit = 0;

	for (InputIt group = input_begin; group != input_end;) {
		uint8_t decoded_group = CharToB32(*group);
		int8_t bits_to_extract = std::min(kBitsInByte - decoded_byte_bit, kBitsInGroup - decoded_group_bit);

		decoded_byte |= FirstNBits(decoded_group << (kGroupStartingBit + decoded_group_bit), bits_to_extract) >> decoded_byte_bit;

		decoded_byte_bit += bits_to_extract;
		decoded_group_bit += bits_to_extract;

		if (decoded_byte_bit == kBitsInByte) {
			*output_begin++ = decoded_byte;
			++written;
			decoded_byte = 0;
			decoded_byte_bit = 0;
		}

		if (decoded_group_bit == kBitsInGroup) {
			++group;
			decoded_group_bit = 0;
		}
	}

	return written;
}

/**
 * Decodes an entire 'in' stream into 'out'.
 * @param in input stream
 * @param out output stream
 * @param max_buffer_size maximum buffer size (can't be less than 8, default = 4096)
 * @throws std::runtime_error when encountering a character which is not a valid Base32 alphabet entry
 */
void DecodeStream(std::istream& in, std::ostream& out, size_t max_buffer_size = 4096);

/**
 * Decodes the entire file into another one.
 * @param input_path path to the input file
 * @param output_path path to the output file
 * @param max_buffer_size maximum buffer size (can't be less than 8, default = 4096)
 * @throws std::runtime_error when encountering a character which is not a valid Base32 alphabet entry
 * @throws std::system_error I/O exceptions
 */
void DecodeFile(const std::string& input_path, const std::string& output_path, size_t max_buffer_size = 4096);

} // base32

#endif //BASE32_DECODER_H_
