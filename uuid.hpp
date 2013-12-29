#ifndef UUID_HPP_
#define UUID_HPP_

#include <string>
#include <random>
#include <chrono>
#include <array>
#include <sstream>
#include <iomanip>

namespace UUID {

class UUID final {
public:
  UUID()
        : bytes_({0}) {

        }
        ~UUID() {

        }
        std::string to_string() const {
        	std::ostringstream oss;
        	for(auto i = 0; i < 16; ++i) {
        		oss << std::setw(2) << std::setfill('0') << std::hex << ((std::uint32_t)bytes_[i]);
        		if(i == 3 or i == 5 or i == 7 or i == 9)
        		        oss << "-";
        	}
            return oss.str();
        }
        static UUID random() {
                UUID uuid;
                auto seed = std::chrono::system_clock::now().time_since_epoch().count();
                std::default_random_engine random_engine(seed);
                std::uniform_int_distribution<uint8_t> random_bits(0,255);
                for(int i = 0; i < 16; ++i) {
                	uuid.bytes_[i] = random_bits(random_engine);
                }

                uuid.bytes_[6] &= 0x0F; // clear version
                uuid.bytes_[6] |= 0x40; // set version
                uuid.bytes_[8] &= 0x3F; // clear variant
                uuid.bytes_[8] |= 0x80; // set variant
           return uuid;
        }
        std::array<unsigned char,16> bytes() const {
        	return bytes_;
        }
private:
        std::array<unsigned char,16> bytes_;
};
}


#endif /* UUID_HPP_ */
