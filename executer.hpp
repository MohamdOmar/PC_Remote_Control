#include <string>
#include <map>

class Command {
public:
    Command();

    void trim(std::string& order);
    void command_execute(std::string& order);
  
private:
    std::map<std::string  ,std::string> command_lst;
};
