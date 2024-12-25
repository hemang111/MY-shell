#include <iostream>
#include <vector>
#include <string>
#include "commands.h"
#include "shell_util.h"

using namespace std;

int main()
{
    cout << unitbuf;
    cerr << unitbuf;
    vector<string> inshell = {"echo", "type", "exit", "pwd", "cd"};

    while (true)
    {
        cout << "$ ";
        string input;
        getline(cin, input);

        if (input == "exit 0")
        {
            return 0;
        }

        vector<string> args = parse_command(input);
        if (args.empty())
            continue;

        string command = args[0];

        if (command == "type")
        {
            execute_type(args, inshell);
        }
        else if (command == "echo")
        {
            execute_echo(input, args);
        }
        else if (command == "pwd")
        {
            execute_pwd();
        }
        else if (command == "cd")
        {
            execute_cd(args);
        }
        else if (command == "cat")
        {
            execute_cat(input);
        }
        else
        {
            string path = get_path(command);
            if (path.empty())
            {
                cout << command << ": command not found" << endl;
            }
            else
            {
                vector<char *> c_args;
                for (auto &arg : args)
                {
                    c_args.push_back(&arg[0]);
                }
                c_args.push_back(nullptr);

                pid_t pid = fork();
                if (pid == 0)
                {
                    execvp(path.c_str(), c_args.data());
                    perror("execvp");
                    exit(EXIT_FAILURE);
                }
                else if (pid > 0)
                {
                    int status;
                    waitpid(pid, &status, 0);
                }
                else
                {
                    perror("fork");
                }
            }
        }
    }
}
