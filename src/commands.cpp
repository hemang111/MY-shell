#include "commands.h"
#include "shell_util.h"
#include <iostream>
#include <filesystem>
#include <regex>
using namespace std;
void execute_echo(const string &input, const vector<string> &args)
{
    string pr = input.substr(5); // Everything after "echo "
    if (args.size() > 1)
    {
        vector<string> rs;
        stringstream ss(pr);
        string word;
        while (ss >> word)
        {
            if (word[0] == '"' && word[word.length() - 1] == '"')
            {
                word = word.substr(1, word.length() - 2);s
            }
            else if (word[0] == '\'' && word[word.length() - 1] == '\'')
            {
                word = word.substr(1, word.length() - 2);
            }

            rs.push_back(word);
        }

        // If the entire string is quoted with single or double quotes
        if ((pr[0] == '\'' && pr[pr.size() - 1] == '\'') || (pr[0] == '"' && pr[pr.size() - 1] == '"'))
        {
            pr = pr.substr(1, pr.size() - 2); // Remove surrounding quotes
            cout << pr;
        }
        else
        {
            // Output parsed words
            for (size_t i = 0; i < rs.size(); ++i)
            {
                cout << rs[i] << (i < rs.size() - 1 ? " " : "");
            }
        }

        cout << "\n";
    }
}
void execute_pwd()
{
    try
    {
        string currentpath = filesystem::current_path().string();
        if (currentpath.empty())
        {
            cerr << "Error: Current path is empty." << endl;
        }
        else
        {
            cout << currentpath << endl;
        }
    }
    catch (const filesystem::filesystem_error &e)
    {
        cerr << "Filesystem error: " << e.what() << endl;
    }
}

void execute_cd(const vector<string> &args)
{
    string maini = "";
    for (const auto &arg : args)
    {
        if (arg != "cd")
        {
            maini += arg;
        }
    }
    if (maini == "~")
    {
        change_to_home_directory();
    }
    else
    {
        bool valid_path = check_path(maini);
        if (valid_path)
        {
            filesystem::current_path(maini);
        }
    }
}

void execute_cat(const string &input)
{
    vector<string> result;
    string main = input.length() > 3 ? input.substr(4) : "";
    regex quote_regex("'([^']*)'");
    smatch matches;

    while (regex_search(main, matches, quote_regex))
    {
        string word = matches[1];
        result.push_back(word);
        main = matches.suffix().str();
    }

    cat_command(result);
    cout << endl;
}

void execute_type(const vector<string> &args, const vector<string> &builtins)
{
    if (args.size() < 2)
    {
        cerr << "Usage: type <command>" << endl;
        return;
    }

    string cmd = args[1];
    bool is_builtin = false;

    for (const auto &builtin : builtins)
    {
        if (builtin == cmd)
        {
            is_builtin = true;
            break;
        }
    }

    if (is_builtin)
    {
        cout << cmd << " is a shell builtin" << endl;
    }
    else
    {
        string path = get_path(cmd);
        if (path.empty())
        {
            cout << cmd << ": not found" << endl;
        }
        else
        {
            cout << cmd << " is " << path << endl;
        }
    }
}
