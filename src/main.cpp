#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

int test(const char *str)
{
    char *s = strdup(str);
    char *p = strtok(s, " ");
    while (p)
    {
        printf("%s\n", p);
        p = strtok(NULL, " ");
    }
    free(s);
    return 0;
}

// display the image
void display(cv::Mat &img)
{
    cv::namedWindow("Display Image", CV_WINDOW_AUTOSIZE);
    cv::imshow("Display Image", img);
    cv::waitKey(0);
}

// read configuration from a file
int read_config(const char *filename)
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
        test(buf);
    }
    fclose(fp);
    return 0;
}

int main(int argv, char *args[])
{
    if (argv < 2)
    {
        printf("Usage: %s <file>\n", args[0]);
        return 1;
    }

    read_config(args[1]);
    return 0;
}