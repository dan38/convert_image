#ifndef __CREATE_ACTION_H__
#define __CREATE_ACTION_H__
#include "Action.h"

class CreateAction : public Action
{
public:
    CreateAction();
    CreateAction(const char *cmd_line);
    ~CreateAction();

    const char *name() override
    {
        return "create";
    };

    bool set_command(const char *cmd_line) override;

    void render(std::map<std::string, cv::Mat> &images) override;

protected:
    int columns;
    int rows;
    int b;
    int g;
    int r;
};
#endif // __CREATE_ACTION_H__