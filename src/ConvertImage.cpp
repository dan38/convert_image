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

// display the image
void ConvertImage::display(cv::Mat &img)
{
    cv::namedWindow("Display Image", WINDOW_AUTOSIZE);
    cv::imshow("Display Image", img);
    cv::waitKey(0);
}

// read configuration from a file
int ConvertImage::read_config(const char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (!fp)
    {
        printf("failed to open file %s\n", filename);
        return -1;
    }
    char buf[1024];
    while (fgets(buf, 1024, fp))
    {
        // test(buf);
    }
    fclose(fp);
    return 0;
}

// create test image
int ConvertImage::create_test_image(const char *filename)
{
    cv::Mat img(100, 100, CV_8UC3, cv::Scalar(0, 0, 0));
    display(img);
    cv::imwrite(filename, img);
    return 0;
}

// rotate an image at a point
void ConvertImage::rotate_image(cv::Mat src, cv::Mat &dest, uint16_t degrees, cv::Point2f point)
{
    /*
    cv::Mat img = cv::imread(filename, CV_LOAD_IMAGE_COLOR);
    if (!img.data)
    {
        printf("failed to open file %s\n", filename);
        return -1;
    }
    cv::Point2f center(img.cols / 2.0, img.rows / 2.0);
    */
    cv::Mat rot_mat = cv::getRotationMatrix2D(point, degrees, 1.0);

    cv::warpAffine(src, dest, rot_mat, src.size());
}

bool ConvertImage::do_command(commands_t *cmd)
{
    bool success = true;
    if (cmd->get_command() == eSAVE)
    {
        cv::imwrite(filename, img);
        printf("save\n");
    }
    else if (cmd->get_command() == eLOAD)
    {
        printf("load\n");
    }
    else if (cmd->get_command() == eCREATE)
    {
        cv::Mat img(100, 100, CV_8UC3, cv::Scalar(0, 0, 0));
        images.insert(std::pair<std::string, cv::Mat>(cmd->get_target_name(), img));
        printf("create\n");
    }
    else if (cmd->get_command() == eROTATE)
    {
        std::string src = cmd->items.front();
        printf("Name of the source image is %s\n", src.c_str());
        // need to check if src is in the map
        if (images.find(src) == images.end())
        {
            printf("Image %s not found\n", src.c_str());
            success = false;
        }
        else
        {
            cv::Mat result;
            rotate_image(images.find(src)->second, result, 90, cv::Point2f(0, 0));
            // cv::Mat rot_mat = cv::getRotationMatrix2D(point, degrees, 1.0);
            // cv::warpAffine(src, dest, rot_mat, src.size());
            images.insert(std::pair<std::string, cv::Mat>(cmd->get_target_name(), result));
            printf("rotate\n");
        }
    }
    else
    {
        printf("command not found in line\n");
        success = false;
    }
    return success;
} // ConvertImage::do_command
