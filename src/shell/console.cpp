#include "console.hpp"

#include <cstring>
#include <sstream>
#include <stdexcept>

#include <readline/readline.h>
#include <readline/history.h>

void init_readln(){
	using_history();
}

bool readln(std::string& line,const std::string& prompt) {
	static char * last_cmd = nullptr;
	char * tmp = readline(prompt.c_str());
	if(!tmp){
		return false;
	}
	
	line = tmp;
	
	if(*tmp && last_cmd){
		//don't safe duplicates:
		if(strcmp(tmp, last_cmd)){
			add_history(tmp);
		}
	}
	else if(!last_cmd){
		add_history(tmp);
	}
	if(last_cmd){
		free(last_cmd);
	}
	last_cmd = tmp;
	
	return true;
}


std::pair< std::string, std::vector< std::string > > parse_cmd(const std::string& cmd){
	using std::string;
	std::istringstream stream(cmd);
	string primary_command;
	if(!stream.good()){
		throw std::invalid_argument("empty commandline cannot be parsed");
	}
	stream >> primary_command;
	
	std::vector<std::string> args;
	std::string tmp;
	while(stream.good()){
		stream >> tmp;
		args.push_back(tmp);
	}
	
	return std::make_pair(primary_command, args);
}
