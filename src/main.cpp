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

#ifdef __cplusplus
extern "C"
{
#endif

    void test_lines();

#ifdef __cplusplus
}
#endif

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
    /*
    ConvertImage *ci = new ConvertImage();

    commands_t *cmd = new commands_t("src = create 100, 100");
    cmd->debug_dump();
    ci->do_command(cmd);

    cmd->set_command("result = rotate src, 90, (0, 0)");
    cmd->debug_dump();
    ci->do_command(cmd);

    cmd->set_command("save result");
    cmd->debug_dump();
    ci->do_command(cmd);
    */
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