#ifndef RGBA_COLOR_HPP
#define RGBA_COLOR_HPP

#include <cstdint>
#include <string>

namespace vlpp{

/**
 * @brief The rgba_color class
 */
class rgba_color
{
	public:
		/**
		 * @brief default-ctor; will initialize #000000ff
		 */
		rgba_color() = default;
		
		/**
		 * @brief the default copy-ctor
		 * @param other an already existing instance that will be copied
		 */
		rgba_color(const rgba_color& other) = default;
		
		/**
		 * @brief the default assignement-function
		 * @param other an already existing instance that will be copied
		 */
		rgba_color& operator=(const rgba_color& other) = default;
		
		/**
		 * @brief Constructs an rgba-color from the provided arguments
		 * @param r the red-value
		 * @param g the green-value
		 * @param b the blue-value
		 * @param alpha the alpha-value
		 */
		rgba_color(uint8_t r, uint8_t g, uint8_t b, uint8_t alpha = UINT8_MAX);
		
		/**
		 * @brief rgba_color
		 * @param colorcode
		 * @throws std::invalid_argument if the string cannot be converted to a color
		 */
		rgba_color(std::string colorcode);
		
		/**
		 * @brief the red-value
		 */
		uint8_t r = 0;
		
		/**
		 * @brief the green-value
		 */
		uint8_t g = 0;
		
		/**
		 * @brief the blue-value
		 */
		uint8_t b = 0;
		
		/**
		 * @brief the alpha-value
		 */
		uint8_t alpha = UINT8_MAX;
};

}
#endif // RGBA_COLOR_HPP
