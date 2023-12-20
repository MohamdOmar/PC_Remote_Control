#include "executer.hpp"
#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <cstdlib>
#include <thread>

Command::Command(): command_lst{
    {"calculator","gnome-calculator"},
    {"terminal","gnome-terminal"},    
    {"VScode","code"},
    {"home","xdg-open /home/mohamed/"},
    {"firefox","firefox"},
    {"camera","cheese"},
}{}

void Command::trim(std::string& order)
{
    // Trim leading and trailing whitespaces
    order.erase(order.begin(), std::find_if(order.begin(), order.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
    order.erase(std::find_if(order.rbegin(), order.rend(), [](unsigned char ch) {return !std::isspace(ch);}).base(), order.end());
}

void Command::command_execute(std::string& order)
{
    //Execute the command
    auto it = command_lst.find(order.data());
    if (it != command_lst.end()) {
        //Run system func on another thread 
        std::thread commandThread([&]() {
            system(it->second.c_str());
            std::cout << "Command Executed Successfully" << std::endl;
        });
        commandThread.detach();       
    } 
    else {
        std::cout << "Unknown command: " << order << std::endl;
    }

}