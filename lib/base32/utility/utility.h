#ifndef BASE32_UTILITY_H_
#define BASE32_UTILITY_H_

#include <fstream>
#include <string>
#include <cstdint>
#include <format>

namespace base32 {

inline constexpr int8_t kGroupStartingBit = 3;
inline constexpr int8_t kGroupsInBlock = 8;
inline constexpr int8_t kBitsInByte = 8;
inline constexpr int8_t kBitsInGroup = 5;

inline constexpr char kPaddingChar = '=';
inline constexpr char kBase32Alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567";

/**
 * Converts a char from Base32 alphabet to the corresponding 5-bit group. Expected to be optimized out, e.g. with jump table.
 * @param c character to decode
 * @throws std::runtime_error when character is not a valid Base32 alphabet entry
 * @return unsigned 8-bit integer containing decoded group in the 5 least significant bits, remaining 3 are zeroes
 */
inline uint8_t CharToB32(char c) {
	switch (c) {
		case 'A': return 0;
		case 'B': return 1;
		case 'C': return 2;
		case 'D': return 3;
		case 'E': return 4;
		case 'F': return 5;
		case 'G': return 6;
		case 'H': return 7;
		case 'I': return 8;
		case 'J': return 9;
		case 'K': return 10;
		case 'L': return 11;
		case 'M': return 12;
		case 'N': return 13;
		case 'O': return 14;
		case 'P': return 15;
		case 'Q': return 16;
		case 'R': return 17;
		case 'S': return 18;
		case 'T': return 19;
		case 'U': return 20;
		case 'V': return 21;
		case 'W': return 22;
		case 'X': return 23;
		case 'Y': return 24;
		case 'Z': return 25;
		case '2': return 26;
		case '3': return 27;
		case '4': return 28;
		case '5': return 29;
		case '6': return 30;
		case '7': return 31;
		default:
			throw std::runtime_error(
				std::format(
					"'{}' ({:#x}) is not a valid Base32 character",
					c, c
				)
			);
	}
}

/**
 * Generates a bitmask with 'n' least significant bits set to 1 and other zeroed.
 * @param n number of bits to set
 * @return generated bitmask
 */
inline uint8_t LastNBitsMask(const uint8_t n) {
	return (1 << n) - 1;
}

/**
 * Generates a bitmask with 'n' most significant bits set to 1 and other zeroed.
 * @param n number of bits to set
 * @return generated bitmask
 */
inline uint8_t FirstNBitsMask(const uint8_t n) {
	return ~LastNBitsMask(8 - n);
}

/**
 * Preserves first 'n' bits of a given byte and zeroes other.
 * @param v byte to apply the bitmask to
 * @param n number of bits to preserve
 * @return given byte with the bitmask applied
 */
inline uint8_t FirstNBits(const uint8_t v, const uint8_t n) {
	return v & FirstNBitsMask(n);
}

/**
 * Calculates the number of bytes to be produced as a result of encoding byte sequence of length 'input_size' bytes using Base32.
 * @param input_size length of input sequence in bytes
 * @return length of encoded sequence in bytes
 */
inline size_t EncodedSize(const size_t input_size) {
	return ((input_size / 5) + (input_size % 5 != 0)) * 8;
}

/**
 * Calculates the number of bytes to be produced as a result of decoding Base32 sequence of length 'input_size' bytes.
 * @param input_size length of input sequence in bytes
 * @return length of decoded sequence in bytes
 */
inline size_t DecodedSize(const size_t input_size) {
	return input_size * 5 / 8;
}

} // base32

#endif //BASE32_UTILITY_H_
