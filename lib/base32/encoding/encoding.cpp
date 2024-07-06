#include <vector>
#include <cassert>

#include "encoding.h"

namespace base32 {

void EncodeStream(std::istream& in, std::ostream& out, size_t max_buffer_size) {
	max_buffer_size = std::max(40ull, max_buffer_size);

	size_t buffer_size = max_buffer_size - (max_buffer_size % 40);
	std::vector<char> input_buffer(buffer_size);

	std::vector<char> output_buffer(EncodedSize(buffer_size));

	while (!in.eof()) {
		in.read(input_buffer.data(), buffer_size);
		std::streamsize extracted = in.gcount();

		std::streamsize written = Encode(
			input_buffer.begin(),
			input_buffer.begin() + extracted,
			output_buffer.begin()
		);

		out.write(output_buffer.data(), written);
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