#include "shell_util.h"
#include <iostream>
#include <sstream>
#include <filesystem>
#include <fstream>
#include <unistd.h>
#include <sys/wait.h>
#include <regex>
using namespace std;

std::string get_path(std::string command)
{
    string path_env = getenv("PATH");
    stringstream ss(path_env);
    string path;
    while (!ss.eof())
    {
        getline(ss, path, ':');
        string abs_path = path + '/' + command;
        if (filesystem::exists(abs_path))
        {
            return abs_path;
        }
    }
    return "";
}

void cat_command(const std::vector<std::string> &args)
{
    if (args.empty())
    {
        cerr << "Usage: cat <filename>" << endl;
        return;
    }

    for (const auto &file_name : args)
    {
        if (!filesystem::exists(file_name))
        {
            cerr << file_name << ": No such file" << endl;
            continue;
        }

        if (!filesystem::is_regular_file(file_name))
        {
            cerr << file_name << ": Not a regular file" << endl;
            continue;
        }

        ifstream file(file_name);
        if (file.is_open())
        {
            string line;
            while (getline(file, line))
            {
                cout << line ;
            }
            file.close();
        }
        else
        {
            cerr << file_name << ": Could not open file" << endl;
        }
    }
}

std::vector<std::string> parse_command(std::string input)
{
    stringstream ss(input);
    string word;
    vector<string> args;
    while (ss >> word)
    {
        args.push_back(word);
    }
    return args;
}

bool check_path(std::string path)
{
    if (filesystem::exists(path) && filesystem::is_directory(path))
    {
        return true;
    }
    else
    {
        cout << path << ": No such file or directory" << endl;
        return false;
    }
}

void change_to_home_directory()
{
    const char *home = getenv("HOME");
    if (!home)
    {
        home = getenv("USERPROFILE");
    }

    if (home)
    {
        try
        {
            filesystem::current_path(home);
        }
        catch (const filesystem::filesystem_error &e)
        {
            cerr << "Error: " << e.what() << '\n';
        }
    }
    else
    {
        cerr << "Home directory could not be found.\n";
    }
}
