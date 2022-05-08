#include "LineAction.h"

LineAction::LineAction() : sx(0), sy(0), ex(0), ey(0),
                           b(0), g(0), r(0), thickness(1)
{
    target_name.clear();
}

LineAction::LineAction(const char *cmd_line)
{
    set_command(cmd_line);
}

LineAction::~LineAction()
{
}

bool LineAction::set_command(const char *cmd_line)
{
    bool success = true;

    char *s = strdup(cmd_line);
    char *p = strtok(s, " ,");

    src_line = std::string(cmd_line);
    target_name.clear();

    if (p == NULL)
        success = false;
    else
    {
        target_name = std::string(p);
        if (target_name.compare(name()) != 0)
        {
            p = strtok(NULL, " ");

            if ((p == NULL) || (p[0] != '='))
                success = false;

            if (success)
                p = strtok(NULL, " ,");

            if ((p == NULL) || (0 != strcmp(p, name())))
                success = false;

            if (success)
                p = strtok(NULL, " ,");

            if (success && p != NULL)
                img = std::string(p);
            else
                success = false;
        }
        else
        {
            target_name = "";
            p = strtok(NULL, " ,");
            if (p != NULL)
                img = std::string(p);
            else
                success = false;
        }
    }

    printf("The image name is :%s\n", img.c_str());
    if (success)
        p = strtok(NULL, " ,");

    if (p == NULL)
        success = false;

    if (success)
    {
        sx = atoi(p);
        p = strtok(NULL, " ,");
    }
    if (p == NULL)
        success = false;

    if (success)
    {
        sy = atoi(p);
        p = strtok(NULL, " ,");
    }
    if (p == NULL)
        success = false;

    if (success)
    {
        ex = atoi(p);
        p = strtok(NULL, " ,");
    }
    if (p == NULL)
        success = false;

    if (success)
    {
        ey = atoi(p);
        p = strtok(NULL, " ,");
    }
    if (p == NULL)
        success = false;

    if (p == NULL)
        success = false;
    if (success)
    {
        // do something fancy here with the color
        b = atoi(p);
        p = strtok(NULL, " ,");

        // or not
        if (p != NULL)
        {
            g = atoi(p);
            p = strtok(NULL, " ,");
        }
        if (p != NULL)
        {
            r = atoi(p);
            p = strtok(NULL, " ,");
        }
        else
            success = false;
    } // end read color

    if (success)
    {
        thickness = atoi(p);
        p = strtok(NULL, " ,");
    }
    if (p == NULL)
        success = false;

    // what do we do with the rest if p is not null?
    // items.push_back(std::string(p));
    // p = strtok(NULL, " ,");
    free(s);
    return success;
}

std::string LineAction::get_command()
{
    std::string cmd_line;
    if (target_name.length() > 0)
        cmd_line = target_name + " = " + name() + " " + img;
    else
        cmd_line = name() + std::string(" ") + img;

    cmd_line += " " + std::to_string(sx);
    cmd_line += " " + std::to_string(sy);
    cmd_line += " " + std::to_string(ex);
    cmd_line += " " + std::to_string(ey);
    cmd_line += " " + std::to_string(b);
    cmd_line += " " + std::to_string(g);
    cmd_line += " " + std::to_string(r);
    cmd_line += " " + std::to_string(thickness);
    return cmd_line;
}

void LineAction::render(std::map<std::string, cv::Mat> &images)
{
    // TBD do some error input checking
    /*
    int columns = stoi(items[0]);
    int rows = stoi(items[1]);
    int b = stoi(items[2]);
    int g = stoi(items[3]);
    int r = stoi(items[4]);
    */
    // TBD write something fancy to pull apart color
    //

    // Need to work out BGR vs RGB
    // also need to work out how to handle alpha
    // and bit depth?

    cv::line(images.find(img)->second, cv::Point(sx, sy), cv::Point(ex, ey), cv::Scalar(b, g, r), thickness);
    printf("Line not fully implemented %s:%d\n", __FILE__, __LINE__);
    // we need to implement this if it's an assignment?
    // images.insert(std::pair<std::string, cv::Mat>(get_target_name(), img));
}
