#ifndef COMMANDS_H
#define COMMANDS_H

#include <vector>
#include <string>

void execute_echo(const std::string &input, const std::vector<std::string> &args);
void execute_pwd();
void execute_cd(const std::vector<std::string> &args);
void execute_cat(const std::string &input);
void execute_type(const std::vector<std::string> &args, const std::vector<std::string> &builtins);

#endif // COMMANDS_H
