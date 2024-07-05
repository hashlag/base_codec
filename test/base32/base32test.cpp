#include <sstream>
#include <cstring>
#include <gtest/gtest.h>

#include "base32/base32.h"

std::string encode_(const char* data) {
	std::string result;

	base32::Encode(
		data,
		data + std::strlen(data),
		std::back_inserter(result)
  );

	return result;
}

// from RFC 4648
TEST(base32, encoding) {
	ASSERT_EQ(encode_(""),       "");
	ASSERT_EQ(encode_("f"),      "MY======");
	ASSERT_EQ(encode_("fo"),     "MZXQ====");
	ASSERT_EQ(encode_("foo"),    "MZXW6===");
	ASSERT_EQ(encode_("foob"),   "MZXW6YQ=");
	ASSERT_EQ(encode_("fooba"),  "MZXW6YTB");
	ASSERT_EQ(encode_("foobar"), "MZXW6YTBOI======");
}

std::string encode_stream_(const char* data, const size_t buffer_size = 40) {
	std::stringstream in(data);
	std::stringstream out;

	base32::EncodeStream(in, out, buffer_size);

	return out.str();
}

// from RFC 4648
TEST(base32, stream_encoding) {
	ASSERT_EQ(encode_stream_(""),       "");
	ASSERT_EQ(encode_stream_("f"),      "MY======");
	ASSERT_EQ(encode_stream_("fo"),     "MZXQ====");
	ASSERT_EQ(encode_stream_("foo"),    "MZXW6===");
	ASSERT_EQ(encode_stream_("foob"),   "MZXW6YQ=");
	ASSERT_EQ(encode_stream_("fooba"),  "MZXW6YTB");
	ASSERT_EQ(encode_stream_("foobar"), "MZXW6YTBOI======");
}

std::string decode_(const char* data) {
	std::string result;

	base32::Decode(
		data,
	  data + std::strlen(data),
	  std::back_inserter(result)
 	);

	return result;
}

// from RFC 4648
TEST(base32, decoding) {
		ASSERT_EQ(decode_(""),                 "");
		ASSERT_EQ(decode_("MY======"),         "f");
		ASSERT_EQ(decode_("MZXQ===="),         "fo");
		ASSERT_EQ(decode_("MZXW6==="),         "foo");
		ASSERT_EQ(decode_("MZXW6YQ="),         "foob");
		ASSERT_EQ(decode_("MZXW6YTB"),         "fooba");
		ASSERT_EQ(decode_("MZXW6YTBOI======"), "foobar");
}

std::string decode_stream_(const char* data, const size_t buffer_size = 8) {
	std::stringstream in(data);
	std::stringstream out;

	base32::DecodeStream(in, out, buffer_size);

	return out.str();
}

// from RFC 4648
TEST(base32, stream_decoding) {
	ASSERT_EQ(decode_stream_(""),                 "");
	ASSERT_EQ(decode_stream_("MY======"),         "f");
	ASSERT_EQ(decode_stream_("MZXQ===="),         "fo");
	ASSERT_EQ(decode_stream_("MZXW6==="),         "foo");
	ASSERT_EQ(decode_stream_("MZXW6YQ="),         "foob");
	ASSERT_EQ(decode_stream_("MZXW6YTB"),         "fooba");
	ASSERT_EQ(decode_stream_("MZXW6YTBOI======"), "foobar");
}
