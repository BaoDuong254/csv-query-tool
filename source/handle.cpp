#include "exql.h"

std::string handleFile(const std::string &filename, int type)
{
    std::ifstream file;
    std::string filePath = "../data/" + filename + ".csv";
    file.open(filePath);
    if (file.is_open())
    {
        std::string line;
        std::vector<std::string> data;
        while (getline(file, line))
        {
            data.push_back(line);
        }
        if (type == 0)
        {
            for (int i = 1; i < data.size(); i++)
            {
                std::cout << data[i] << std::endl;
            }
        }
        else if(type==1)
        {
            for (int i = 1; i < data.size(); i++)
            {
                std::istringstream ss(data[i]);
                std::string id, first_name, last_name;
                getline(ss, id, ',');
                getline(ss, first_name, ',');
                getline(ss, last_name, ',');
                std::cout << id << "," << first_name << "," << last_name << std::endl;
            }
        }
        file.close();
    }
    else
    {
        throw std::runtime_error("File not found");
    }
    return "";
}

int main(int argc, char *argv[])
{
    std::string fileName;
    std::string input;
    for (int i = 1; i < argc; i++)
    {
        if (i >= 3)
        {
            input += " ";
        }
        input += argv[i];
    }
    while (input.find("\\") != std::string::npos)
    {
        input.replace(input.find("\\"), 1, "\"");
    }
    while (input.find("\\") != std::string::npos)
    {
        input.erase(input.find("\\"), 1);
    }
    std::vector<Token> tokens = tokenize(input);
    for (int i = 0; i < tokens.size(); i++)
    {
        if (tokens[i].value == "from")
        {
            i += 2;
            fileName = tokens[i].value;
            break;
        }
    }
    for (int i = 0; i < tokens.size(); i++)
    {
        if (tokens[i].value == "select")
        {
            i += 2;
            if (tokens[i].value == "*")
            {
                i += 2;
                handleFile(fileName, 0);
                break;
            }
            else if (tokens[i].type == TokenType::Identifier)
            {
                if (tokens[i].value == "id")
                {
                    handleFile(fileName, 1);
                    break;
                }
                else
                {
                    throw std::runtime_error("Invalid SQL statement");
                }
            }
        }
        else
        {
            throw std::runtime_error("Invalid SQL statement");
        }
    }
    return 0;
}