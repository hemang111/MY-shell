#include "commands.h"
#include "shell_util.h"
#include <iostream>
#include <filesystem>
#include <regex>
using namespace std;
void execute_echo(const string &input,const vector<string> &args)
{
    string pr = input.substr(5); 
    string result = "";
    bool in_quotes = false;
    char quote_char = '\0';
    size_t backslash_count = 0; 

    for (size_t i = 0; i < pr.size(); ++i)
    {
        char ch = pr[i];

        if (!in_quotes && (ch == '"' || ch == '\'')) 
        {
            in_quotes = true;
            quote_char = ch;
        }
        else if (in_quotes && ch == quote_char)
        {
            in_quotes = false;
            quote_char = '\0';
        }
        else if(ch == '\\' && i != pr.size()-1){
          backslash_count++;
          result += ch; 
          int k = 0;
          if(backslash_count%2 == 0){
                for(int i = 0; i < result.length();i++){
                   if(result[i] == '\\' && k%2 != 0){
                     k++;
                    result.erase(i, 2);
                   cout << result;
                    i++;
                   }
                   else if(k%2 == 0 && result[i] ==  '\\' && k != 0){
                    result[i] = ' ';
                    cout << result;
                    k = 0;
                   }
                }
            }
        }
        else
        {
            result += ch; 
            int k = 0;
          if(backslash_count%2 == 0){
                for(int i = 0; i < result.length();i++){
                   if(result[i] == '\\' && k%2 != 0){
                    k++;
                    result.erase(i, 2);
                    cout << result;
                    i++;
                   }
                   else if(k%2 == 0 && result[i] ==  '\\' && k != 0){
                    result[i] = ' ';
                    cout << result;
                    k = 0;
                   }
                }
            }
        }
    }

    cout << result << endl; // Print the final result
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
    string pr = input.substr(4); // Everything after "cat "
    string current_filename = "";
    bool in_quotes = false;
    char quote_char = '\0';

    for (size_t i = 0; i < pr.size(); ++i)
    {
        char ch = pr[i];

        if (!in_quotes && (ch == '"' || ch == '\'')) // Start of quoted string
        {
            in_quotes = true;
            quote_char = ch;
        }
        else if (in_quotes && ch == quote_char) // End of quoted string
        {
            in_quotes = false;
            result.push_back(current_filename);
            current_filename = "";
        }
        else if (ch == '\\') // Handle backslash escape
        {
            if (i + 1 < pr.size())
            {
                current_filename += pr[i + 1]; // Preserve the next character
                ++i;
            }
        }
        else
        {
            current_filename += ch; // Regular character
        }
    }

    // Add any remaining unquoted filename
    if (!current_filename.empty())
    {
        result.push_back(current_filename);
    }

    // Call the cat command with parsed filenames
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
