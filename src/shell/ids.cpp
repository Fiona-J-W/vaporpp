#include "ids.hpp"

#include <cctype>
#include <stdexcept>

std::vector<uint16_t> str_to_ids(const std::string& str){
	using std::vector;
	using std::string;
	
	vector<uint16_t> returnlist;
	string current_word;
	uint16_t tmp_id = 0;
	bool in_range = false;
	for(auto c: str){
		if(isdigit(c)){
			current_word += c;
		}
		else if(c==',') {
			if(in_range){
				uint16_t upper_bound =  (uint16_t)std::stoul(current_word);
				if(upper_bound < tmp_id){
					throw std::invalid_argument("invalid range");
				}
				for(uint16_t i = tmp_id; i <= upper_bound; ++i){
					returnlist.push_back(i);
				}
			}
			else{
				returnlist.push_back( (uint16_t)std::stoul(current_word) );
			}
			current_word.clear();
		}
		else if(c == '-') {
			if(in_range){
				throw std::invalid_argument("invalid range");
			}
			in_range = true;
			tmp_id = (uint16_t)std::stoul(current_word);
			current_word.clear();
		}
		else{
			throw std::invalid_argument("invalid range");
		}
	}
	
	return returnlist;
}
