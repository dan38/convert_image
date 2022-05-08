#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <map>
#include <unistd.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "commands.h"
#include "ConvertImage.h"
#include "Action.h"
#include "CreateAction.h"
#include "LineAction.h"

using namespace cv;
using namespace std;
/*
#ifdef __cplusplus
extern "C"
{
#endif
*/
/*
#ifdef __cplusplus
}
#endif
*/
void map_sample()
{
    std::map<std::string, int> m;
    m.insert(std::pair<std::string, int>("one", 1));
    m.insert(std::pair<std::string, int>("two", 2));
    m.insert(std::pair<std::string, int>("three", 3));

    auto a = m.find("one");
    printf("%d\n", a->second);
}

void test_do_it_with_ascii_lines()
{
    std::map<std::string, cv::Mat> images;
    // create a 100 x 100 image called src
    // line could be src = create 100, 100
    cv::Mat img(100, 100, CV_8UC3, cv::Scalar(0, 255, 0));
    images.insert(std::pair<std::string, cv::Mat>("src", img));
    // hmm how do we handle result?
    // line could be result = rotate img, 90, (0, 0)
    cv::Mat result;
    // rotate_image(images.find("src")->second, result, 90, cv::Point2f(0, 0));
    images.insert(std::pair<std::string, cv::Mat>("result", result));

    // display the image
    // display(images.find("result")->second);
    imshow("display", images.find("result")->second);
    // waitKey(0);
    //  read command
    //  image list

    // switch on command
    // do command
    // repeat
}

void test_lines()
{
    // create height x width image
    // color is BGR
    const char *lines[] = {
        "srcb = create 400, 100, 255, 0, 0",
        "srcg = create 100, 200, 0, 255, 0",
        "srcr = create 300, 200, 0, 0, 255",
        "line srcb, 20, 30, 100, 50, 255, 255, 0, 4",
        "rotate srcb, 45, 10, 20",
        "display result",
        "exit"};

    ConvertImage *ci = new ConvertImage();

    commands_t *cmd = new commands_t();
    char step[100] = {};

    for (int ii = 0; ii < 6; ii++)
    {
        printf("%s\n", lines[ii]);
        cmd->set_command(lines[ii]);
        // cmd->debug_dump();
        snprintf(step, 99, "%d", ii);
        ci->do_command(cmd, step);
        printf("==================\n");
    }
}

Action *create_action(char const *line)
// Action *create_action()
{
    // const char *line = "blah";
    Action *action = NULL;
    char *s = strdup(line);
    char *p = strtok(s, " ,");
    enum enum_commands command;
    // std::string target_name;
    // std::vector<std::string> items;
    // items.clear();
    // target_name.clear();

    if (p[0] == '#')
    {
        command = eCOMMENT;
    }
    else
    {
        // I don't like how this "knows" the format of the line
        // but it works for now
        // todo make it better in future
        while (p)
        {
            // printf("Testing |%s|\n", p);
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
                // TODO what if two commands on a line?
                action = new CreateAction();
                action->name();
                action->set_command(line);
                //  func = create;
            }
            else if (strcmp(p, "rotate") == 0)
            {
                command = eROTATE;
                // func = rotate;
            }
            else if (strcmp(p, "line") == 0)
            {
                command = eLINE;
                action = new LineAction();
                action->name();
                action->set_command(line);
            }
            else if (strcmp(p, "circle") == 0)
            {
                command = eCIRCLE;
            }
            else if (strcmp(p, "rectangle") == 0)
            {
                command = eRECTANGLE;
            }
            else if (p[0] == '=')
            {
                // target_name = items.front().c_str();
                // items.clear();
                // assert(items.size() == 0);
            }
            else
            {
                // items.push_back(std::string(p));
            }

            p = strtok(NULL, " ,");
        }
    }
    free(s);
    return action;
}

void test_lines_2()
{
    // create height x width image
    // color is BGR
    const char *lines[] = {
        "srcb = create 400, 100, 255, 0, 0",
        "srcg = create 100, 200, 0, 255, 0",
        "srcr = create 300, 200, 0, 0, 255",
        "line srcb, 20, 30, 100, 50, 255, 255, 0, 4",
        "rotate srcb, 45, 10, 20",
        "display result",
        "exit"};
    std::map<std::string, cv::Mat> images;
    char step[100] = {};
    Action *action = NULL;

    for (int ii = 0; ii < sizeof(lines) / sizeof(char *); ii++)
    {
        printf("%s\n", lines[ii]);
        action = create_action(lines[ii]);
        // action = create_action();
        //  cmd->set_command(lines[ii]);
        //   cmd->debug_dump();
        snprintf(step, 99, "%d", ii);
        // ci->do_command(cmd, step);
        if (action)
        {
            // this is kinda silly to allocate and then delete the action
            // must be a better way to do it
            // maybe don't delete the action?
            std::cout << action->get_command() << std::endl;
            action->render(images);
            delete (action);
        }
        else
        {
            std::cout << "no action" << std::endl;
        }
        printf("==================\n");
    }
}

int main(int argv, char *args[])
{
    test_lines_2();
    if (argv < 2)
    {
        printf("Usage: %s <file>\n", args[0]);
    }

    // read_config(args[1]);
    return 0;
}