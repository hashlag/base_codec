#include <vector>
#include <cassert>

#include "decoding.h"

namespace base32 {

void DecodeStream(std::istream& in, std::ostream& out, const size_t max_buffer_size) {
	assert(max_buffer_size >= 8 && "min required buffer size is 8 bytes");

	size_t buffer_size = max_buffer_size - (max_buffer_size % 8);

	std::vector<char> input_buffer(buffer_size);
	std::vector<char> output_buffer(DecodedSize(buffer_size));

	while (in.good()) {
		in.read(input_buffer.data(), buffer_size);
		std::streamsize extracted = in.gcount();

		std::streamsize written = Decode(
			 input_buffer.begin(),
			 input_buffer.begin() + extracted,
			 output_buffer.begin()
	  );

		out.write(output_buffer.data(), written);
	}
}

void DecodeFile(const std::string& input_path, const std::string& output_path, size_t max_buffer_size) {
	std::ifstream in;
	in.exceptions(std::ios::badbit);
	in.open(input_path, std::ios::binary);

	std::ofstream out;
	out.exceptions(std::ios::badbit);
	out.open(output_path, std::ios::binary);

	DecodeStream(in, out, max_buffer_size);
}

} // base32
