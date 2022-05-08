#ifndef __LINE_ACTION_H__
#define __LINE_ACTION_H__
#include "Action.h"

class LineAction : public Action
{
public:
    LineAction();
    LineAction(const char *cmd_line);
    ~LineAction();

    const char *name() override
    {
        return "line";
    };

    bool set_command(const char *cmd_line) override;

    std::string get_command() override;

    void render(std::map<std::string, cv::Mat> &images) override;

protected:
    std::string img;
    int sx;
    int sy;
    int ex;
    int ey;
    int b;
    int g;
    int r;
    int thickness;
};
#endif // __LINE_ACTION_H__
