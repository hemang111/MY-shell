#ifndef SHELL_UTIL_H
#define SHELL_UTIL_H

#include <vector>
#include <string>

std::string get_path(std::string command);
void cat_command(const std::vector<std::string> &args);
std::vector<std::string> parse_command(std::string input);
bool check_path(std::string path);
void change_to_home_directory();

#endif // SHELL_UTIL_H
