#ifndef READLN_HPP
#define READLN_HPP

#include <string>
#include <utility>
#include <vector>

/**
 * @brief c++-wrapper for GNU-readline
 * @param line a reference to string that will be used to save the read line
 * @param prompt the commandprompt
 * @return false if EOF is reached, true otherwise
 */
bool readln(std::string& line, const std::string& prompt);

/**
 * @brief parse a command
 * @param cmd the command from the commandline
 * @return a pair of the primary command and a list of the arguments
 */
std::pair< std::string, std::vector< std::string > > parse_cmd(const std::string& cmd);

#endif // READLN_HPP
