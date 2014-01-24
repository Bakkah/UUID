#ifndef UTILITY_HEXCHARS_HPP_
#define UTILITY_HEXCHARS_HPP_


namespace Utility {

enum class HexCharType {
	Lower = 0,
	Upper = 1
};

template<HexCharType Type>
struct HexCharacters {

};
template<>
struct HexCharacters<HexCharType::Lower> {
	static constexpr const char *chars = "0123456789abcdef";
};
template<>
struct HexCharacters<HexCharType::Upper> {
	static constexpr const char *chars = "0123456789ABCDEF";
};

}



#endif /* UTILITY_HEXCHARS_HPP_ */
