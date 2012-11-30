#ifndef IDS_HPP
#define IDS_HPP

#include <vector>
#include <cstdint>
#include <string>

/**
 * @brief converts a string to a list of uint16_t
 * @param str the string
 * @return a vector of the numbers
 */
std::vector<uint16_t> str_to_ids(const std::string& str);

#endif // IDS_HPP
