#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <string>

#include "../lib/client.hpp"

/**
 * @brief set_leds
 * @param cl A refercence to the conncection-client
 * @param leds a string that contains describes the leds to be set
 * @param color a string that describes a color
 */
void set_leds(vlpp::client& cl, const std::string& leds, const std::string& color);

#endif // COMMANDS_HPP
