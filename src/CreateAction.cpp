#include "CreateAction.h"

CreateAction::CreateAction() : columns(0),
                               rows(0), b(0), g(0), r(0)
{
    target_name.clear();
}

CreateAction::CreateAction(const char *cmd_line)
{
    set_command(cmd_line);
}

CreateAction::~CreateAction()
{
}

bool CreateAction::set_command(const char *cmd_line)
{
    bool success = true;

    char *s = strdup(cmd_line);
    char *p = strtok(s, " ,");

    src_line = std::string(cmd_line);
    target_name.clear();

    if (p == NULL)
        success = false;
    else
        target_name = std::string(p);

    if (success)
        p = strtok(NULL, " ");

    if ((p == NULL) || (p[0] != '='))
        success = false;
    if (success)
        p = strtok(NULL, " ,");

    if ((p == NULL) || (0 != strcmp(p, name())))
        success = false;
    if (success)
        p = strtok(NULL, " ,");

    if (p == NULL)
        success = false;
    if (success)
    {
        columns = atoi(p);
        p = strtok(NULL, " ,");
    }

    if (p == NULL)
        success = false;
    if (success)
    {
        rows = atoi(p);
        p = strtok(NULL, " ,");
    }

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

        // what do we do with the rest if p is not null?
        // items.push_back(std::string(p));
        // p = strtok(NULL, " ,");
    }
    free(s);
    return success;
}

std::string CreateAction::get_command()
{
    std::string cmd_line = target_name + " = " + name();
    cmd_line += " " + std::to_string(columns);
    cmd_line += " " + std::to_string(rows);
    cmd_line += " " + std::to_string(b);
    cmd_line += " " + std::to_string(g);
    cmd_line += " " + std::to_string(r);
    return cmd_line;
}

void CreateAction::render(std::map<std::string, cv::Mat> &images)
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

    cv::Mat img(columns, rows, CV_8UC3, cv::Scalar(b, g, r));
    printf("Create not fully implemented %s:%d\n", __FILE__, __LINE__);
    images.insert(std::pair<std::string, cv::Mat>(get_target_name(), img));
}
