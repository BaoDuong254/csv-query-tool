#include "exql.h"
bool isPrintError = false;
Token::Token(TokenType type, std::string value) : type(type), value(value) {}
TokenizerError::TokenizerError(ErrorKind kind, Location location, std::string input)
    : kind(kind), location(location), input(input) {}
TokenizerError unexpectedOrUnsupportedToken(const Location location, const std::string input)
{
    return TokenizerError(ErrorKind::UnexpectedOrUnsupportedToken, location, input);
}
TokenizerError unexpectedWhileParsingOperator(const Location location, const std::string input)
{
    return TokenizerError(ErrorKind::UnexpectedWhileParsingOperator, location, input);
}
TokenizerError operatorNotClosed(const Location location, const std::string input)
{
    return TokenizerError(ErrorKind::OperatorNotClosed, location, input);
}
TokenizerError stringNotClosed(const Location location, const std::string input)
{
    return TokenizerError(ErrorKind::StringNotClosed, location, input);
}
TokenizerError other(const Location location, const std::string input)
{
    return TokenizerError(ErrorKind::Other, location, input);
}
Token tokenizeKeywordOrIdentifier(const std::string input)
{
    // Logic to tokenize keywords or identifiers
    std::string inputTemp = input;
    for (int i = 0; i < inputTemp.size(); i++)
    {
        inputTemp[i] = toupper(inputTemp[i]);
    }
    if (inputTemp == "SELECT")
    {
        return Token(TokenType::Keyword, "select");
    }
    else if (inputTemp == "FROM")
    {
        return Token(TokenType::Keyword, "from");
    }
    else if (inputTemp == "WHERE")
    {
        return Token(TokenType::Keyword, "where");
    }
    else if (inputTemp == "ORDER")
    {
        return Token(TokenType::Keyword, "order");
    }
    else if (inputTemp == "BY")
    {
        return Token(TokenType::Keyword, "by");
    }
    else if (inputTemp == "AND")
    {
        return Token(TokenType::Keyword, "and");
    }
    else if (inputTemp == "OR")
    {
        return Token(TokenType::Keyword, "or");
    }
    else if (inputTemp == "CREATE")
    {
        return Token(TokenType::Keyword, "create");
    }
    else if (inputTemp == "TABLE")
    {
        return Token(TokenType::Keyword, "table");
    }
    else if (inputTemp == "INT")
    {
        return Token(TokenType::Keyword, "int");
    }
    else if (inputTemp == "PRIMARY")
    {
        return Token(TokenType::Keyword, "primary");
    }
    else if (inputTemp == "KEY")
    {
        return Token(TokenType::Keyword, "key");
    }
    else if (inputTemp == "VARCHAR")
    {
        return Token(TokenType::Keyword, "varchar");
    }
    else if (inputTemp == "BOOL")
    {
        return Token(TokenType::Keyword, "bool");
    }
    else if (inputTemp == "UPDATE")
    {
        return Token(TokenType::Keyword, "update");
    }
    else if (inputTemp == "SET")
    {
        return Token(TokenType::Keyword, "set");
    }
    else if (inputTemp == "INSERT")
    {
        return Token(TokenType::Keyword, "insert");
    }
    else if (inputTemp == "INTO")
    {
        return Token(TokenType::Keyword, "into");
    }
    else if (inputTemp == "VALUES")
    {
        return Token(TokenType::Keyword, "values");
    }
    else if (inputTemp == "TRUE")
    {
        return Token(TokenType::Keyword, "true");
    }
    else if (inputTemp == "FALSE")
    {
        return Token(TokenType::Keyword, "false");
    }
    else if (inputTemp == "DELETE")
    {
        return Token(TokenType::Keyword, "delete");
    }
    else if (inputTemp == "DROP")
    {
        return Token(TokenType::Keyword, "drop");
    }
    return Token(TokenType::Identifier, input);
}
Token tokenizeNumber(const std::string input)
{
    // Logic to tokenize numbers
    return Token(TokenType::Number, input);
}
Token tokenizeString(const std::string input)
{
    // Logic to tokenize strings
    return Token(TokenType::String, input);
}
Token tokenizeOperatorOrSeparator(const std::string input)
{
    // Logic to tokenize operators and separators
    if (input == ",")
    {
        return Token(TokenType::Comma, ",");
    }
    else if (input == ";")
    {
        return Token(TokenType::SemiColon, ";");
    }
    else if (input == "(")
    {
        return Token(TokenType::LeftParen, "(");
    }
    else if (input == ")")
    {
        return Token(TokenType::RightParen, ")");
    }
    else if (input == "=")
    {
        return Token(TokenType::Eq, "=");
    }
    else if (input == "!=")
    {
        return Token(TokenType::Neq, "!=");
    }
    else if (input == "<")
    {
        return Token(TokenType::Lt, "<");
    }
    else if (input == ">")
    {
        return Token(TokenType::Gt, ">");
    }
    else if (input == "+")
    {
        return Token(TokenType::Plus, "+");
    }
    else if (input == "-")
    {
        return Token(TokenType::Minus, "-");
    }
    else if (input == "*")
    {
        return Token(TokenType::Mul, "*");
    }
    else if (input == "/")
    {
        return Token(TokenType::Div, "/");
    }
    else if (input == ">=")
    {
        return Token(TokenType::GtEq, ">=");
    }
    else if (input == "<=")
    {
        return Token(TokenType::LtEq, "<=");
    }
    return Token(TokenType::Invalid, input);
}
std::string tokenToString(const Token token)
{
    if (token.type == TokenType::Comma)
    {
        return "Comma";
    }
    else if (token.type == TokenType::SemiColon)
    {
        return "SemiColon";
    }
    else if (token.type == TokenType::LeftParen)
    {
        return "LeftParen";
    }
    else if (token.type == TokenType::RightParen)
    {
        return "RightParen";
    }
    else if (token.type == TokenType::Eq)
    {
        return "Eq";
    }
    else if (token.type == TokenType::Neq)
    {
        return "Neq";
    }
    else if (token.type == TokenType::Lt)
    {
        return "Lt";
    }
    else if (token.type == TokenType::Gt)
    {
        return "Gt";
    }
    else if (token.type == TokenType::Plus)
    {
        return "Plus";
    }
    else if (token.type == TokenType::Minus)
    {
        return "Minus";
    }
    else if (token.type == TokenType::Mul)
    {
        return "Mul";
    }
    else if (token.type == TokenType::Div)
    {
        return "Div";
    }
    else if (token.type == TokenType::GtEq)
    {
        return "GtEq";
    }
    else if (token.type == TokenType::LtEq)
    {
        return "LtEq";
    }
    else if (token.type == TokenType::Invalid)
    {
        return "Neq";
    }
    return token.value;
}
std::vector<Token> tokenize(const std::string input)
{
    std::vector<Token> tokens;
    Location location = {1, 1};
    for (int i = 0; i < input.size(); i++)
    {
        char currentChar = input[i];
        if (isspace(currentChar))
        {
            tokens.push_back(tokenizeOperatorOrSeparator(std::string(1, currentChar)));
        }
        else if (isdigit(currentChar))
        {
            std::string number = "";
            while (isdigit(currentChar))
            {
                number += currentChar;
                i++;
                currentChar = input[i];
            }
            i--;
            tokens.push_back(tokenizeNumber(number));
        }
        else if (currentChar == '"')
        {
            std::string str = "";
            i++;
            currentChar = input[i];
            while (currentChar != '"' && i < input.size())
            {
                str += currentChar;
                i++;
                currentChar = input[i];
            }
            if (currentChar != '"')
            {
                location.col = i + 1;
                TokenizerError error = stringNotClosed(location, input);
                printError(error, input, Token(TokenType::String, str));
                isPrintError = true;
            }
            tokens.push_back(tokenizeString(str));
        }
        else if (currentChar == '\'')
        {
            std::string str = "";
            i++;
            currentChar = input[i];
            while (currentChar != '\'' && i < input.size())
            {
                str += currentChar;
                i++;
                currentChar = input[i];
            }
            if (currentChar != '\'')
            {
                location.col = i + 1;
                TokenizerError error = stringNotClosed(location, input);
                printError(error, input, Token(TokenType::String, str));
                isPrintError = true;
            }
            tokens.push_back(tokenizeString(str));
        }
        else if (currentChar == ',' || currentChar == ';' || currentChar == '(' || currentChar == ')' || currentChar == '=' || currentChar == '!' || currentChar == '<' || currentChar == '>' || currentChar == '+' || currentChar == '-' || currentChar == '*' || currentChar == '/')
        {
            std::string op = "";
            if (currentChar == '!' || currentChar == '<' || currentChar == '>')
            {
                op += currentChar;
                i++;
                currentChar = input[i];
                if (currentChar == '=')
                {
                    op += currentChar;
                }
                else
                {
                    i--;
                }
            }
            else
            {
                op += currentChar;
            }
            if (tokenizeOperatorOrSeparator(op).type == TokenType::Invalid && op != "!")
            {
                location.col = i - op.length() + 2;
                TokenizerError error = unexpectedOrUnsupportedToken(location, input);
                printError(error, input, tokenizeOperatorOrSeparator(op));
                isPrintError = true;
            }
            else if (op == "!")
            {
                if (i != input.size() - 1)
                {
                    location.col = i + 2;
                    TokenizerError error = unexpectedWhileParsingOperator(location, input);
                    printError(error, std::string(1, input[i + 1]), tokenizeOperatorOrSeparator(op));
                    isPrintError = true;
                }
                else
                {
                    location.col = i + 2;
                    TokenizerError error = operatorNotClosed(location, input);
                    printError(error, input, tokenizeOperatorOrSeparator(op));
                    isPrintError = true;
                }
            }
            tokens.push_back(tokenizeOperatorOrSeparator(op));
        }
        else if (isalpha(currentChar))
        {
            std::string identifier = "";
            while (isalpha(currentChar) || isdigit(currentChar) || currentChar == '_')
            {
                identifier += currentChar;
                i++;
                currentChar = input[i];
            }
            i--;
            tokens.push_back(tokenizeKeywordOrIdentifier(identifier));
        }
        else
        {
            location.col = i + 1;
            Token token = tokenizeOperatorOrSeparator(std::string(1, currentChar));
            TokenizerError error = unexpectedOrUnsupportedToken(location, input);
            printError(error, input, token);
            isPrintError = true;
        }
    }
    tokens.push_back(Token(TokenType::Eof, ""));
    return tokens;
}
void printTokens(std::vector<Token> tokens)
{
    std::cout << "Ok({" << std::endl;
    for (int i = 0; i < tokens.size(); i++)
    {
        Token token = tokens[i];
        if (token.type == TokenType::Keyword)
        {
            if (token.value == "select")
            {
                std::cout << "    Token::Keyword(Keyword::Select)," << std::endl;
            }
            else if (token.value == "from")
            {
                std::cout << "    Token::Keyword(Keyword::From)," << std::endl;
            }
            else if (token.value == "where")
            {
                std::cout << "    Token::Keyword(Keyword::Where)," << std::endl;
            }
            else if (token.value == "order")
            {
                std::cout << "    Token::Keyword(Keyword::Order)," << std::endl;
            }
            else if (token.value == "by")
            {
                std::cout << "    Token::Keyword(Keyword::By)," << std::endl;
            }
            else if (token.value == "and")
            {
                std::cout << "    Token::Keyword(Keyword::And)," << std::endl;
            }
            else if (token.value == "or")
            {
                std::cout << "    Token::Keyword(Keyword::Or)," << std::endl;
            }
            else if (token.value == "create")
            {
                std::cout << "    Token::Keyword(Keyword::Create)," << std::endl;
            }
            else if (token.value == "table")
            {
                std::cout << "    Token::Keyword(Keyword::Table)," << std::endl;
            }
            else if (token.value == "int")
            {
                std::cout << "    Token::Keyword(Keyword::Int)," << std::endl;
            }
            else if (token.value == "primary")
            {
                std::cout << "    Token::Keyword(Keyword::Primary)," << std::endl;
            }
            else if (token.value == "key")
            {
                std::cout << "    Token::Keyword(Keyword::Key)," << std::endl;
            }
            else if (token.value == "varchar")
            {
                std::cout << "    Token::Keyword(Keyword::Varchar)," << std::endl;
            }
            else if (token.value == "bool")
            {
                std::cout << "    Token::Keyword(Keyword::Bool)," << std::endl;
            }
            else if (token.value == "update")
            {
                std::cout << "    Token::Keyword(Keyword::Update)," << std::endl;
            }
            else if (token.value == "set")
            {
                std::cout << "    Token::Keyword(Keyword::Set)," << std::endl;
            }
            else if (token.value == "insert")
            {
                std::cout << "    Token::Keyword(Keyword::Insert)," << std::endl;
            }
            else if (token.value == "into")
            {
                std::cout << "    Token::Keyword(Keyword::Into)," << std::endl;
            }
            else if (token.value == "values")
            {
                std::cout << "    Token::Keyword(Keyword::Values)," << std::endl;
            }
            else if (token.value == "true")
            {
                std::cout << "    Token::Keyword(Keyword::True)," << std::endl;
            }
            else if (token.value == "false")
            {
                std::cout << "    Token::Keyword(Keyword::False)," << std::endl;
            }
            else if (token.value == "delete")
            {
                std::cout << "    Token::Keyword(Keyword::Delete)," << std::endl;
            }
            else if (token.value == "drop")
            {
                std::cout << "    Token::Keyword(Keyword::Drop)," << std::endl;
            }
        }
        else if (token.type == TokenType::Identifier)
        {
            std::cout << "    Token::Identifier(\"" << token.value << "\")," << std::endl;
        }
        else if (token.type == TokenType::Number)
        {
            std::cout << "    Token::Number(\"" << token.value << "\")," << std::endl;
        }
        else if (token.type == TokenType::String)
        {
            size_t pos = 0;
            std::string valueTemp = token.value;
            while ((pos = valueTemp.find("\"", pos)) != std::string::npos)
            {
                valueTemp.insert(pos, "\\");
                pos += 2;
            }
            std::cout << "    Token::String(\"" << valueTemp << "\")," << std::endl;
        }
        else if (token.type == TokenType::Comma)
        {
            std::cout << "    Token::Comma," << std::endl;
        }
        else if (token.type == TokenType::SemiColon)
        {
            std::cout << "    Token::SemiColon," << std::endl;
        }
        else if (token.type == TokenType::LeftParen)
        {
            std::cout << "    Token::LeftParen," << std::endl;
        }
        else if (token.type == TokenType::RightParen)
        {
            std::cout << "    Token::RightParen," << std::endl;
        }
        else if (token.type == TokenType::Eq)
        {
            std::cout << "    Token::Eq," << std::endl;
        }
        else if (token.type == TokenType::Neq)
        {
            std::cout << "    Token::Neq," << std::endl;
        }
        else if (token.type == TokenType::Lt)
        {
            std::cout << "    Token::Lt," << std::endl;
        }
        else if (token.type == TokenType::Gt)
        {
            std::cout << "    Token::Gt," << std::endl;
        }
        else if (token.type == TokenType::Plus)
        {
            std::cout << "    Token::Plus," << std::endl;
        }
        else if (token.type == TokenType::Minus)
        {
            std::cout << "    Token::Minus," << std::endl;
        }
        else if (token.type == TokenType::Mul)
        {
            std::cout << "    Token::Mul," << std::endl;
        }
        else if (token.type == TokenType::Div)
        {
            std::cout << "    Token::Div," << std::endl;
        }
        else if (token.type == TokenType::GtEq)
        {
            std::cout << "    Token::GtEq," << std::endl;
        }
        else if (token.type == TokenType::LtEq)
        {
            std::cout << "    Token::LtEq," << std::endl;
        }
        else if (token.type == TokenType::Eof)
        {
            std::cout << "    Token::Eof" << std::endl;
        }
    }
    std::cout << "})" << std::endl;
}
void printError(const TokenizerError error, const std::string input, const Token token)
{
    std::cout << "Err({" << std::endl;
    if (error.kind == ErrorKind::UnexpectedOrUnsupportedToken)
    {
        std::cout << "    ErrorKind::UnexpectedOrUnsupportedToken(\'" << token.value << "\')," << std::endl;
    }
    else if (error.kind == ErrorKind::UnexpectedWhileParsingOperator)
    {
        std::cout << "    ErrorKind::UnexpectedWhileParsingOperator('" << input << "', Token::" << tokenToString(token) << ")," << std::endl;
    }
    else if (error.kind == ErrorKind::OperatorNotClosed)
    {
        std::cout << "    ErrorKind::OperatorNotClosed(Token::" << tokenToString(token) << ")," << std::endl;
    }
    else if (error.kind == ErrorKind::StringNotClosed)
    {
        std::cout << "    ErrorKind::StringNotClosed," << std::endl;
    }
    else if (error.kind == ErrorKind::Other)
    {
        std::cout << "    ErrorKind::Other,";
    }
    std::cout << "    Location{" << error.location.line << ", " << error.location.col << "}," << std::endl;
    size_t pos = 0;
    std::string inputCopy = error.input;
    while ((pos = inputCopy.find("\"", pos)) != std::string::npos)
    {
        inputCopy.insert(pos, "\\");
        pos += 2;
    }
    pos = 0;
    while ((pos = inputCopy.find("\'", pos)) != std::string::npos)
    {
        inputCopy.insert(pos, "\\");
        pos += 2;
    }
    std::cout << "    \"" << inputCopy << "\"" << std::endl;
    std::cout << "})" << std::endl;
}