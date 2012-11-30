#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <vector>
#include <string>
#include <cstdint>
#include <memory>

#include "rgba_color.hpp"

namespace vlpp {


/**
 * @brief The client class, used to connect to the server.
 *
 * This class provides the usual interface used to communicate with the server.
 */
class client {
	public:
		
		/**
		 * @brief the default port
		 */
		enum: uint16_t{ DEFAULT_PORT = 7534 };
		
		/**
		 * @brief Constructs an instance, connects to the specified server and authenticates there.
		 * @param server the servername; this might be an ip-address or an hostname,
		 *               eg "192.168.23.44" or "example.com"
		 * @param token the authentication-token
		 * @param port the server-port
		 * @throws std::runtime_error if no connection could be created or a write fails
		 */
		client(const std::string& server, const std::string& token, uint16_t port = DEFAULT_PORT);
		
		/**
		 * @brief cleans up the object.
		 */
		~client();
		
		/**
		 * @brief Sets a rgb-LED to a specific rgba-color.
		 * @param led_id the ID of the led
		 * @param col the new color of the LED
		 * @throws std::runtime_error if the write fails
		 */
		void set_led(uint16_t led_id, const rgba_color& col);
		
		/**
		 * @brief Sets a list of LEDs to a specific color.
		 * @param led_ids the IDs of the LEDs
		 * @param col the new color of the LEDs
		 * @throws std::runtime_error if a write fails
		 */
		void set_leds(const std::vector<uint16_t>& led_ids, const rgba_color& col);
		
		/**
		 * @brief execute the sent commands
		 * @throws std::runtime_error if the write fails
		 */
		void execute();
		
		
	private:
		// we are using the pimpl-idiom to decrease the
		// compiletime and dependencies for users of this class:
		class client_impl;
		std::unique_ptr<client_impl> _impl;
};

}


#endif // CLIENT_HPP
