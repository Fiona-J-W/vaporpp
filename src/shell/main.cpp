#include <cstdint>
#include <iostream>
#include <stdexcept>

#include <boost/algorithm/string.hpp>
#include <boost/program_options.hpp>

#include "../lib/client.hpp"

#include "console.hpp"
#include "commands.hpp"

int main(int argc, char**argv){
	using std::string;
	namespace bpo = boost::program_options;
	
	string server;
	string token;
	uint16_t port;
	
	bpo::options_description desc;
	desc.add_options()
			("help,h", "print this help")
			("verbose,v", "be verbose")
			("token,t", bpo::value<std::string>(&token), "sets the authentication-token" )
			("server,s", bpo::value<std::string>(&server), "sets the servername")
			("port, p", bpo::value<uint16_t>(&port)->default_value(vlpp::client::DEFAULT_PORT), "sets the server-port");
	
	bpo::variables_map vm;
	bpo::store(bpo::parse_command_line(argc, argv, desc) ,vm);
	bpo::notify(vm);
	if(vm.count("help")){
		std::cout << desc << std::endl;
		return 0;
	}
	
	if(vm.count("verbose")){
		std::cout << "server = “" << server << "”\n"
			  << "token = “" << token << "”\n"
			  << "port = " << port << std::endl;
	}
	
	vlpp::client client(server, token, port);
	
	string line;
	while(readln(line, "-> ")){
		boost::algorithm::trim(line);
		if(line.empty()){
			continue;
		}
		auto cmd = parse_cmd(line);
		
		if(cmd.first == "set"){
			if(cmd.second.size() != 2){
				std::cerr << "Error: “set” takes exactly two arguments" << std::endl;
				continue;
			}
			try{
				set_leds(client, cmd.second[0], cmd.second[1]);
			}
			catch(std::invalid_argument& e){
				std::cerr << "Error: " << e.what() << std::endl;
				continue;
			}
			catch(std::runtime_error& e){
				std::cerr << "Error: " << e.what() << std::endl;
				break;
			}
		}
		else if(cmd.first == "quit"){
			break;
		}
		else{
			std::cerr << "Error: unknown command: “" << cmd.first << "”" << std::endl;
		}
	}
	
	return 0;
}
