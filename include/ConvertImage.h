#ifndef __CONVERT_IMAGE_H__
#define __CONVERT_IMAGE_H__
#include <map>
#include "commands.h"

class ConvertImage
{
public:
    ConvertImage(){};
    ~ConvertImage();
    int read_config(const char *filename);
    int create_test_image(const char *filename);
    void rotate_image(cv::Mat src, cv::Mat &dest, uint16_t degrees, cv::Point2f point);
    void display(cv::Mat &img);
    void debug_dump();
    bool do_command(commands_t *cmd);

private:
    std::map<std::string, cv::Mat> images;
};

#endif // __CONVERT_IMAGE_H__