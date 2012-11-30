#include "client.hpp"

#include <cassert>

#include <boost/asio.hpp>
#include <array>

using boost::asio::io_service;
using boost::asio::ip::tcp;


class vlpp::client::client_impl {
public:
	client_impl(const std::string& servername, const std::string& token, uint16_t port);
	void authenticate(const std::string& token);
	void set_led(uint16_t led, rgba_color col);
	void execute();
	io_service _io_service;
	tcp::socket _socket;
};

///////////


vlpp::client::client(const std::string &server, const std::string &token, uint16_t port):
	_impl(new vlpp::client::client_impl(server, token, port)) {
}

vlpp::client::~client() {
	
}

void vlpp::client::set_led(uint16_t led_id, const rgba_color &col) {
	_impl->set_led(led_id, col);
}

void vlpp::client::set_leds(const std::vector<uint16_t> &led_ids, const rgba_color &col) {
	for(auto led: led_ids) {
		set_led(led, col);
	}
}

void vlpp::client::execute() {
}


///////// now: the private stuff


vlpp::client::client_impl::client_impl(const std::string &servername, const std::string &token, uint16_t port):
	_socket(_io_service) {
	//first check the token:
	if( token.length() != 16 ) {
		throw std::invalid_argument("invalid token (wrong size)");
	}
	
	tcp::resolver _resolver(_io_service);
	tcp::resolver::query q(servername, std::to_string(port));
	auto endpoints = _resolver.resolve(q);
	boost::asio::connect(_socket, endpoints);
	if(!_socket.is_open()) {
		throw std::runtime_error("cannot open socket");
	}
	authenticate(token);
}

void vlpp::client::client_impl::authenticate(const std::string &token) {
	assert(token.length() == 16);
	std::array<char,17> auth_data;
	auth_data[0] = 0x02;
	for(size_t i = 0; i<16; ++i) {
		auth_data[i+1] = (char)token[i];
	}
	boost::system::error_code e;
	boost::asio::write(_socket, boost::asio::buffer(&(auth_data[0]), auth_data.size()) , e);
	if(e){
		throw std::runtime_error("write failed");
	}
}

void vlpp::client::client_impl::set_led(uint16_t led, rgba_color col) {
	boost::system::error_code e;
	std::array<char, 7> data;
	data[0] = 0x01;
	data[1] = (char)(led >> 8);
	data[2] = (char)(led & 0xff);
	data[3] = (char)(col.r);
	data[4] = (char)(col.g);
	data[5] = (char)(col.b);
	data[6] = (char)(col.alpha);
	boost::asio::write(_socket, boost::asio::buffer(&(data[0]), data.size()), e);
	if(e){
		throw std::runtime_error("write failed");
	}
}

void vlpp::client::client_impl::execute() {
	const char opcode = (char)0xff;
	boost::system::error_code e;
	boost::asio::write(_socket, boost::asio::buffer(&opcode, 1), e);
	if(e){
		throw std::runtime_error("write failed");
	}
}
