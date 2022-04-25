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

protected:
    char *name;
    enum enum_commands command;
    const char *target_name;
    std::list<std::string> items;
    int parse(const char *line);
    int (*func)(int argc, char **argv);
};

#endif // __COMMANDS_H__