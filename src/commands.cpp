#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "commands.h"

commands_t::commands_t()
{
    // target_name = NULL;
    command = eNULL;
    func = NULL;
};

commands_t::commands_t(const char *line)
{
    // target_name = NULL;
    command = eNULL;
    func = NULL;
    set_command(line);
};

commands_t::~commands_t(){};

void commands_t::set_command(const char *line)
{
    target_name.clear();
    command = eNULL;
    func = NULL;
    // should free args too
    items.clear();
    parse(line);
};

// rudementary command parser
int commands_t::parse(const char *line)
{
    char *s = strdup(line);
    char *p = strtok(s, " ,");
    while (p)
    {
        if (strcmp(p, "save") == 0)
        {
            command = eSAVE;
            // func = save;
        }
        else if (strcmp(p, "load") == 0)
        {
            command = eLOAD;
            // func = load;
        }
        else if (strcmp(p, "create") == 0)
        {
            command = eCREATE;
            // func = create;
        }
        else if (strcmp(p, "rotate") == 0)
        {
            command = eROTATE;
            // func = rotate;
        }
        else if (p[0] == '=')
        {
            target_name = items.front().c_str();
            items.pop_front();
            assert(items.size() == 0);
        }
        else
        {
            items.push_back(std::string(p));
        }

        p = strtok(NULL, " ,");
    }
    free(s);
    return 0;
};

void commands_t::debug_dump()
{
    printf("command: %d\n", command);

    printf("target_name: %s\n", target_name.c_str());

    printf("args: %lu\n", items.size());

    for (std::list<std::string>::iterator it = items.begin(); it != items.end(); it++)
    {
        printf("  %s\n", it->c_str());
    }
    printf("\n");
};