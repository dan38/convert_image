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
    cv::Mat img(100, 100, CV_8UC3, cv::Scalar(0, 0, 0));
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
    ConvertImage *ci = new ConvertImage();

    const char *line = "src = create 100, 100";
    commands_t *cmd = new commands_t(line);
    printf("%s\n", line);
    cmd->debug_dump();
    ci->do_command(cmd);
    printf("==================\n");

    line = "result = rotate src, 90, (0, 0)";
    printf("%s\n", line);
    cmd->set_command(line);
    cmd->debug_dump();
    ci->do_command(cmd);
    printf("==================\n");

    line = "save result test.jpg";
    printf("%s\n", line);
    cmd->set_command(line);
    cmd->debug_dump();
    ci->do_command(cmd);
    printf("==================\n");
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