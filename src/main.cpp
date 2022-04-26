#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <map>
#include <unistd.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "commands.h"
#include "ConvertImage.h"

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

int main(int argv, char *args[])
{
    test_lines();
    if (argv < 2)
    {
        printf("Usage: %s <file>\n", args[0]);
    }

    // read_config(args[1]);
    return 0;
}