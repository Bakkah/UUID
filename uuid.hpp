#ifndef UTILITY_UUID_HPP_
#define UTILITY_UUID_HPP_

#include <array>
#include <string>
#include <cinttypes>
#include <random>
#include <chrono>
#include "hexchars.hpp"

namespace Utility {

using UUIDBytes = std::array<std::int32_t, 16>;
using UUIDString = std::array<char, 37>;

class UUID final {
public:
	UUID()
	: bytes_({0}) {

	}
	UUID(const UUIDBytes &bytes)
	: bytes_(bytes) {

	}
	UUID(const std::string &str) {
		set(str);
	}
	static UUID from_string(const std::string &str) {
		return UUID(str);
	}
	static UUID from_bytes(const UUIDBytes &bytes) {
		return UUID(bytes);
	}
	void set(const UUIDBytes &bytes) {
		bytes_ = bytes;
	}
	void set(const std::string &uuid) {
		char s[2] = {0};
		constexpr int string_index[] = {0,2,4,6,9,11,14,16,19,21,24,26,28,30,32,34};
		for(size_t i = 0; i < 16; ++i) {
			auto index = string_index[i];
			s[0] = uuid.at(index);
			s[1] = uuid.at(index+1);
			bytes_.at(i) = (std::int32_t)std::strtol(s,nullptr,16);
		}
	}
	template<HexCharType Type = HexCharType::Lower>
	std::string to_string() const {
		return c_str().data();
	}
	template<HexCharType Type = HexCharType::Lower>
	UUIDString c_str() const {
		UUIDString str{"00000000-0000-0000-0000-000000000000"};
		constexpr int string_indexes[]{0,2,4,6,9,11,14,16,19,21,24,26,28,30,32,34};
		for(std::int32_t i = 0; i < 16; ++i) {
			auto string_index = string_indexes[i];
			std::int32_t dec = bytes_[i];
			str[string_index] = HexCharacters<Type>::chars[(dec >> 4)&(0xF)];
			str[string_index+1] = HexCharacters<Type>::chars[(dec & 0xF)];
		}
		return str;
	}
	UUIDBytes bytes() const {
		return bytes_;
	}
	bool compare(const UUID &other) const {
		for(std::int32_t i = 0; i < 16; ++i) {
			if(bytes_[i] not_eq other.bytes_[i])
				return false;
		}
		return true;
	}
	bool operator==(const UUID &other) const {
		return compare(other);
	}
	static UUID random() {
		static std::mt19937 random_engine(std::chrono::high_resolution_clock::now().time_since_epoch().count());
		std::uniform_int_distribution<std::int32_t> bits(0,255);
		UUIDBytes bytes;
		for(std::int32_t i = 0; i < 16; ++i) {
			bytes[i] = bits(random_engine);
		}

        bytes[6] &= 0x0F; // clear version
        bytes[6] |= 0x40; // set version 4

        bytes[8] &= 0x3F; // clear variant
        bytes[8] |= 0x80; // set variant current

		return bytes;
	}
private:
	UUIDBytes bytes_;
};

}


#endif /* UTILITY_UUID_HPP_ */
