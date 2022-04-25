#ifndef __COMMANDS_H__
#define __COMMANDS_H__
#include <list>
#include <string>

enum enum_commands
{
    eNULL,
    eSAVE,
    eLOAD,
    eCREATE,
    eROTATE,
};

class commands_t
{
public:
    commands_t();
    commands_t(const char *line);
    ~commands_t();

    void set_command(const char *line);
    enum_commands get_command() { return command; };
    void debug_dump();
    std::string get_target_name() { return target_name; };

    // temporary, need to figure out a better way to do this
    std::list<std::string> items;

protected:
    enum enum_commands command;
    std::string target_name;
    int parse(const char *line);
    int (*func)(int argc, char **argv);
};

#endif // __COMMANDS_H__