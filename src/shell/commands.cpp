#include "commands.hpp"

#include "../lib/rgba_color.hpp"

#include "ids.hpp"

void set_leds(vlpp::client& cl, const std::string& leds, const std::string& color){
	vlpp::rgba_color col(color);
	cl.set_leds(str_to_ids(leds), col);
}
