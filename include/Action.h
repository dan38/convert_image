#ifndef __ACTION_H__
#define __ACTION_H__
#include <map>
#include <string>
#include <opencv2/opencv.hpp>

class Action
{
public:
    Action(){};
    virtual ~Action(){};

    virtual const char *name() = 0;
    virtual bool set_command(const char *line) = 0;
    void debug_dump();
    std::string get_target_name() { return target_name; };
    virtual void render(std::map<std::string, cv::Mat> &images) = 0;

    // temporary, need to figure out a better way to do this
    // Just don't do it std::vector<std::string> items;

protected:
    std::string target_name;
    std::string src_line;
};
#endif // __ACTION_H__