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

void ConvertImage::save_image(cv::Mat &img, const char *cmd, const char *prefix, const char *target)
{
    if (strlen(prefix) > 0)
    {
        char filename[1024] = {};
        snprintf(filename, sizeof(filename) - 1, "%s-%s-%s.jpg", prefix, cmd, target);
        filename[1023] = '\0';
        cv::imwrite(filename, img);
    }
}

bool ConvertImage::do_command(commands_t *cmd, const char *prefix)
{
    bool success = true;
    if (cmd->get_command() == eSAVE)
    {
        std::string img = cmd->items.front();
        printf("Saving img to %s\n", cmd->items[1].c_str());
        cv::imwrite(cmd->items[1], images.find(img)->second);
        printf("save\n");
    }
    else if (cmd->get_command() == eLOAD)
    {
        printf("Load not implemented %s:%d\n", __FILE__, __LINE__);
        cmd->debug_dump();
        printf("load\n");
    }
    else if (cmd->get_command() == eCREATE)
    {
        // TBD do some error input checking
        int columns = stoi(cmd->items[0]);
        int rows = stoi(cmd->items[1]);
        int b = stoi(cmd->items[2]);
        int r = stoi(cmd->items[3]);
        int g = stoi(cmd->items[4]);

        // TBD write something fancy to pull apart color
        //

        // Need to work out BGR vs RGB
        // also need to work out how to handle alpha
        // and bit depth?

        cv::Mat img(columns, rows, CV_8UC3, cv::Scalar(b, r, g));
        printf("Create not fully implemented %s:%d\n", __FILE__, __LINE__);
        images.insert(std::pair<std::string, cv::Mat>(cmd->get_target_name(), img));
        // cv::imwrite("create.jpg", img);
        save_image(img, "create", prefix, cmd->get_target_name().c_str());
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
            printf("Rotate not fully implemented %s:%d\n", __FILE__, __LINE__);
            rotate_image(images.find(src)->second, result, 45, cv::Point2f(0, 0));
            // cv::Mat rot_mat = cv::getRotationMatrix2D(point, degrees, 1.0);
            // cv::warpAffine(src, dest, rot_mat, src.size());
            images.insert(std::pair<std::string, cv::Mat>(cmd->get_target_name(), result));
            save_image(result, "rotate", prefix, cmd->get_target_name().c_str());
            printf("rotate\n");
        }
    }
    else if (cmd->get_command() == eLINE)
    {
        std::string src = cmd->items.front();
        // need to check if src is in the map
        if (images.find(src) == images.end())
        {
            printf("Image %s not found\n", src.c_str());
            success = false;
        }
        else
        {
            printf("Line not fully implemented %s:%d\n", __FILE__, __LINE__);
            cv::line(images.find(src)->second, cv::Point(0, 0), cv::Point(100, 100), cv::Scalar(0, 255, 255), 5);
            // images.insert(std::pair<std::string, cv::Mat>(cmd->get_target_name(), result));
            save_image(images.find(src)->second, "line", prefix, cmd->get_target_name().c_str());
            printf("line\n");
        }
    }
    else if (cmd->get_command() == eCIRCLE)
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
            printf("Circle not fully implemented %s:%d\n", __FILE__, __LINE__);
            cv::circle(images.find(src)->second, cv::Point(50, 50), 40, cv::Scalar(255, 255, 255), 5);
            // images.insert(std::pair<std::string, cv::Mat>(cmd->get_target_name(), result));
            save_image(images.find(src)->second, "circle", prefix, cmd->get_target_name().c_str());
            printf("circle\n");
        }
    }
    else if (cmd->get_command() == eRECTANGLE)
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
            printf("Rectangle not fully implemented %s:%d\n", __FILE__, __LINE__);
            cv::rectangle(images.find(src)->second, cv::Point(0, 0), cv::Point(100, 100), cv::Scalar(255, 255, 255), 5);
            // images.insert(std::pair<std::string, cv::Mat>(cmd->get_target_name(), result));
            save_image(images.find(src)->second, "rectangle", prefix, cmd->get_target_name().c_str());
            printf("rectangle\n");
        }
    }
    else
    {
        printf("unknown command\n");
        success = false;
    }
    return success;
} // ConvertImage::do_command
