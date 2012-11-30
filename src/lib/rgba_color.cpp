#include "rgba_color.hpp"

#include <stdexcept>
#include <cctype>

//private function to convert two hex-characters to a byte:
uint8_t hex_to_byte(char highbyte, char lowbyte);

vlpp::rgba_color::rgba_color(uint8_t R, uint8_t G, uint8_t B, uint8_t A):
	r(R), g(G), b(B), alpha(A)
{}

vlpp::rgba_color::rgba_color(std::string colorcode) {
	if (!colorcode.empty() && colorcode[0] == '#') {
		colorcode.erase(0,1);
	}
	switch (colorcode.length()) {
		case 8:
			alpha = hex_to_byte(colorcode[6], colorcode[7]);
			//fallthrough
		case 6:
			r = hex_to_byte(colorcode[0], colorcode[1]);
			g = hex_to_byte(colorcode[2], colorcode[3]);
			b = hex_to_byte(colorcode[4], colorcode[5]);
			break;
		default
				:
			throw std::invalid_argument("invalid colorcode");
	}
}



uint8_t hex_to_byte(char highbyte, char lowbyte) {
	if (!isxdigit(highbyte) || !isxdigit(lowbyte)) {
		throw std::invalid_argument("invalid colorcode");
	}
	uint8_t returnval = 0;
	
	if (isdigit(highbyte)) {
		returnval = ((unsigned char)highbyte - '0') * 0x10;
	}
	else {
		returnval = (10 + (unsigned char)highbyte -'a') * 0x10;
	}
	
	if (isdigit(lowbyte)) {
		returnval += (lowbyte - '0');
	}
	else {
		returnval += (10 + lowbyte -'a');
	}
	
	return returnval;
}
