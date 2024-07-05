#include <vector>
#include <cassert>

#include "encoding.h"

namespace base32 {

//void EncodeToStream(const char* data, const size_t size, std::ostream& out_stream, const size_t buffer_size) {
//	std::vector<char> buffer(buffer_size);
//	size_t buffer_write_ix = 0;
//
//	int8_t input_bit = 0;
//	int8_t group_bit = 0;
//
//	uint8_t group = 0;
//
//	int8_t octets_in_last_block = 0;
//
//	for (size_t byte_ix = 0; byte_ix < size;) {
//		int8_t bits_to_take = std::min(8 - input_bit, 5 - group_bit);
//		group |= FirstN(data[byte_ix] << input_bit, bits_to_take, group_bit + 3);
//
//		group_bit += bits_to_take;
//		input_bit += bits_to_take;
//
//		if (group_bit == 5) {
//			buffer[buffer_write_ix++] = kBase32Alphabet[group];
//
//			if (buffer_write_ix == buffer.size()) {
//				out_stream.write(buffer.data(), buffer.size());
//				buffer_write_ix = 0;
//			}
//
//			octets_in_last_block = (octets_in_last_block + 1) % 8;
//			group_bit = 0;
//			group = 0;
//		}
//
//		if (input_bit == 8) {
//			++byte_ix;
//			input_bit = 0;
//		}
//	}
//
//	if (group_bit != 0) {
//		buffer[buffer_write_ix++] = kBase32Alphabet[group];
//		octets_in_last_block = (octets_in_last_block + 1) % 8;
//	}
//
//	out_stream.write(buffer.data(), buffer_write_ix);
//
//	if (octets_in_last_block) {
//		out_stream.write(kBase32Alphabet + 32, 8 - octets_in_last_block);
//	}
//}

void EncodeStream(std::istream& in, std::ostream& out, size_t max_buffer_size) {
	assert(max_buffer_size >= 40 && "min required buffer size is 40 bytes");

	size_t buffer_size = max_buffer_size - (max_buffer_size % 40);
	std::vector<char> input_buffer(buffer_size);

	std::vector<char> output_buffer(EncodedSize(buffer_size));

	while (in.good()) {
		in.read(input_buffer.data(), buffer_size);
		std::streamsize extracted = in.gcount();

		Encode(input_buffer.begin(), input_buffer.begin() + extracted, output_buffer.begin());

		out.write(output_buffer.data(), EncodedSize(extracted));
	}
}

void EncodeFile(const std::string& input_path, const std::string& output_path, size_t max_buffer_size) {
	std::ifstream in;
	in.exceptions(std::ios::badbit);
	in.open(input_path, std::ios::binary);

	std::ofstream out;
	out.exceptions(std::ios::badbit);
	out.open(output_path, std::ios::binary);

	EncodeStream(in, out, max_buffer_size);
}

} // base32