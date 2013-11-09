#ifndef UUID_HPP_
#define UUID_HPP_

#include <string>
#include <random>
#include <chrono>
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
                auto seed = std::chrono::system_clock::now().time_since_epoch().count();
                std::default_random_engine random_engine(seed);
                std::uniform_int_distribution<int8_t> index(0,15);


                auto random_char = [&random_engine,&index]() {

                	return hex_chars[index(random_engine)];
                };
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
