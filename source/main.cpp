#include "exql.h"
int main(int argc, char *argv[])
{
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
    if (isPrintError)
    {
        return 0;
    }
    printTokens(tokens);
    return 0;
}