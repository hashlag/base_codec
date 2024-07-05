#ifndef BASE32_UTILITY_H_
#define BASE32_UTILITY_H_

#include <fstream>
#include <string>
#include <cstdint>

namespace base32 {

static const char kPaddingChar = '=';
static const char kBase32Alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567";

uint8_t CharToB32(char c);

inline uint8_t LastNMask(const uint8_t n) {
	return (1 << n) - 1;
}

inline uint8_t FirstNMask(const uint8_t n) {
	return ~LastNMask(8 - n);
}

inline uint8_t FirstN(const uint8_t v, const uint8_t n, const uint8_t pos) {
	return (v & FirstNMask(n)) >> pos;
}

inline size_t EncodedSize(const size_t input_size) {
	return ((input_size / 5) + (input_size % 5 != 0)) * 8;
}

inline size_t DecodedSize(const size_t input_size) {
	return (input_size * 5 / 8) + ((input_size * 5) % 8 != 0);
}


} // base32

#endif //BASE32_UTILITY_H_
