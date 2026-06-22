#pragma once
#include <unordered_map>
#include <functional>
#include <iostream>


using CommandFunc = std::function<void(const std::vector<std::string>&)>;


struct ParsedCommand
{
    std::string name;
    std::vector<std::string> args;
};

class CommandSystem
{
public:
    static void RegisterCommands();
    static void ExecuteCommand(const std::string& command);
private:
    static std::unordered_map<std::string, CommandFunc> consoleCommands;
};