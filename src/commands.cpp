#include "commands.h"
#include "shell_util.h"
#include <iostream>
#include <filesystem>
#include <regex>
using namespace std;
void execute_echo(const string &input, const vector<string> &args)
{
    string pr = input.substr(5); // Everything after "echo "
    vector<string> parsed_words;
    string current_word = "";
    bool in_quotes = false;
    char quote_char = '\0';

    // Parse input, respecting quotes
    for (size_t i = 0; i < pr.size(); ++i)
    {
        char ch = pr[i];

        if ((ch == '"' || ch == '\'') && !in_quotes)
        {
            in_quotes = true;
            quote_char = ch;
        }
        else if (ch == quote_char && in_quotes)
        {
            in_quotes = false;
            quote_char = '\0';
        }
        else if (ch == ' ' && !in_quotes)
        {
            if (!current_word.empty())
            {
                parsed_words.push_back(current_word);
                current_word = "";
            }
        }
        else
        {
            current_word += ch;
        }
    }

    // Add the last word if not empty
    if (!current_word.empty())
    {
        parsed_words.push_back(current_word);
    }

    // Print the parsed words
    for (size_t i = 0; i < parsed_words.size(); ++i)
    {
        cout << parsed_words[i];
        if (i < parsed_words.size() - 1)
            cout << " ";
    }
    cout << endl;
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

    // Adjust regex to match either single or double quotes
    regex quote_regex(R"(['"]([^'"]*)['"])");
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
