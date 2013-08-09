#ifndef UUID_HPP_
#define UUID_HPP_

#include <string>
#include <random>
#include <array>

namespace UUID {

class UUID final {
public:
  UUID()
	: uuid_({
		'0','0','0','0','0','0','0','0','-',
		'0','0','0','0','-',
		'0','0','0','0','-',
		'0','0','0','0','-',
		'0','0','0','0','0','0','0','0','0','0','0','0',
	}) {

	}
	~UUID() {

	}
	std::string to_string() const {
		return uuid_.data();
	}
	static UUID new_uuid() {
		UUID uuid;
		auto random_char = []() { return hex_chars[rand() % 15 + 1];};
		uuid.uuid_ = {
				random_char(), random_char(), random_char(), random_char(),
				random_char(), random_char(), random_char(), random_char(), '-',
				random_char(), random_char(), random_char(), random_char(), '-',
				random_char(), random_char(), random_char(), random_char(), '-',
				random_char(), random_char(), random_char(), random_char(), '-',
				random_char(), random_char(), random_char(), random_char(),
				random_char(), random_char(), random_char(), random_char(),
				random_char(), random_char(), random_char(), random_char(),
				'\0'
		};
		return uuid;
	}
private:
	static constexpr const char *hex_chars = "0123456789abcdef";
	std::array<char,37> uuid_;
};

}


#endif /* UUID_HPP_ */
