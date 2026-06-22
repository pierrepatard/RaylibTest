#include "command.h"
#include "raylib.h"
#include <string>
#include <sstream>


std::unordered_map<std::string, CommandFunc> CommandSystem::consoleCommands;


void CommandSystem::RegisterCommands()
{
    consoleCommands["FPS"] = [](const std::vector<std::string>& args)
        {
            if (args.empty())
                return;

            SetTargetFPS(std::stoi(args[0]));
        };
}


ParsedCommand ParseCommand(const std::string& input)
{
    ParsedCommand result;

    std::stringstream ss(input);
    std::string token;

    bool first = true;

    while (ss >> token)
    {
        if (first)
        {
            result.name = token;
            first = false;
        }
        else
        {
            result.args.push_back(token);
        }
    }

    return result;
}


void CommandSystem::ExecuteCommand(const std::string& command)
{
    std::cout << "Command: " << command << std::endl;

    ParsedCommand cmd = ParseCommand(command);

    auto it = consoleCommands.find(cmd.name);

    if (it != consoleCommands.end())
    {
        it->second(cmd.args);
    }
}