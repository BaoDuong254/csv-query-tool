#include "exql.h"
using namespace std;
TokenizerError unexpectedOrUnsupportedToken(Location location, string input)
{
    return TokenizerError(ErrorKind::UnexpectedOrUnsupportedToken, location, input);
}
TokenizerError unexpectedWhileParsingOperator(Location location, string input)
{
    return TokenizerError(ErrorKind::UnexpectedWhileParsingOperator, location, input);
}
TokenizerError operatorNotClosed(Location location, string input)
{
    return TokenizerError(ErrorKind::OperatorNotClosed, location, input);
}
TokenizerError stringNotClosed(Location location, string input)
{
    return TokenizerError(ErrorKind::StringNotClosed, location, input);
}
TokenizerError other(Location location, string input)
{
    return TokenizerError(ErrorKind::Other, location, input);
}
Token tokenizeKeywordOrIdentifier(string input)
{
    // Logic to tokenize keywords or identifiers
    if (input == "SELECT")
    {
        return Token(TokenType::Keyword, "select");
    }
    else if (input == "FROM")
    {
        return Token(TokenType::Keyword, "from");
    }
    else if (input == "WHERE")
    {
        return Token(TokenType::Keyword, "where");
    }
    else if (input == "ORDER")
    {
        return Token(TokenType::Keyword, "order");
    }
    else if (input == "BY")
    {
        return Token(TokenType::Keyword, "by");
    }
    else if (input == "AND")
    {
        return Token(TokenType::Keyword, "and");
    }
    else if (input == "OR")
    {
        return Token(TokenType::Keyword, "or");
    }
    else if (input == "CREATE")
    {
        return Token(TokenType::Keyword, "create");
    }
    else if (input == "TABLE")
    {
        return Token(TokenType::Keyword, "table");
    }
    else if (input == "INT")
    {
        return Token(TokenType::Keyword, "int");
    }
    else if (input == "PRIMARY")
    {
        return Token(TokenType::Keyword, "primary");
    }
    else if (input == "KEY")
    {
        return Token(TokenType::Keyword, "key");
    }
    else if (input == "VARCHAR")
    {
        return Token(TokenType::Keyword, "varchar");
    }
    else if (input == "BOOL")
    {
        return Token(TokenType::Keyword, "bool");
    }
    else if (input == "UPDATE")
    {
        return Token(TokenType::Keyword, "update");
    }
    else if (input == "SET")
    {
        return Token(TokenType::Keyword, "set");
    }
    else if (input == "INSERT")
    {
        return Token(TokenType::Keyword, "insert");
    }
    else if (input == "INTO")
    {
        return Token(TokenType::Keyword, "into");
    }
    else if (input == "VALUES")
    {
        return Token(TokenType::Keyword, "values");
    }
    else if (input == "TRUE")
    {
        return Token(TokenType::Keyword, "true");
    }
    else if (input == "FALSE")
    {
        return Token(TokenType::Keyword, "false");
    }
    else if (input == "DELETE")
    {
        return Token(TokenType::Keyword, "delete");
    }
    else if (input == "DROP")
    {
        return Token(TokenType::Keyword, "drop");
    }
    return Token(TokenType::Identifier, input);
}
Token tokenizeNumber(string input)
{
    // Logic to tokenize numbers
    return Token(TokenType::Number, input);
}
Token tokenizeString(string input)
{
    // Logic to tokenize strings
    return Token(TokenType::String, input);
}
Token tokenizeOperatorOrSeparator(string input)
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
    else if (input == " ")
    {
        return Token(TokenType::Whitespace, " ");
    }
    else if (input == "\t")
    {
        return Token(TokenType::Whitespace, "\t");
    }
    else if (input == "\n")
    {
        return Token(TokenType::Whitespace, "\n");
    }
    return Token(TokenType::Invalid, input);
}
string tokenToString(Token token)
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
vector<Token> tokenize(string input)
{
    vector<Token> tokens;
    Location location = {1, 1};
    for (int i = 0; i < input.size(); i++)
    {
        char currentChar = input[i];
        if (isspace(currentChar))
        {
            tokens.push_back(tokenizeOperatorOrSeparator(string(1, currentChar)));
        }
        else if (isdigit(currentChar))
        {
            string number = "";
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
            string str = "";
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
            string str = "";
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
            string op = "";
            if(currentChar == '!' || currentChar == '<' || currentChar == '>')
            {
                op += currentChar;
                i++;
                currentChar = input[i];
                if(currentChar == '=')
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
                    printError(error, string(1, input[i + 1]), tokenizeOperatorOrSeparator(op));
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
            string identifier = "";
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
            Token token = tokenizeOperatorOrSeparator(string(1, currentChar));
            TokenizerError error = unexpectedOrUnsupportedToken(location, input);
            printError(error, input, token);
            isPrintError = true;
        }
    }
    tokens.push_back(Token(TokenType::Eof, ""));
    return tokens;
}
void printTokens(vector<Token> tokens)
{
    cout << "Ok({" << endl;
    for (int i = 0; i < tokens.size(); i++)
    {
        Token token = tokens[i];
        if (token.type == TokenType::Keyword)
        {
            if (token.value == "select")
            {
                cout << "    Token::Keyword(Keyword::Select)," << endl;
            }
            else if (token.value == "from")
            {
                cout << "    Token::Keyword(Keyword::From)," << endl;
            }
            else if (token.value == "where")
            {
                cout << "    Token::Keyword(Keyword::Where)," << endl;
            }
            else if (token.value == "order")
            {
                cout << "    Token::Keyword(Keyword::Order)," << endl;
            }
            else if (token.value == "by")
            {
                cout << "    Token::Keyword(Keyword::By)," << endl;
            }
            else if (token.value == "and")
            {
                cout << "    Token::Keyword(Keyword::And)," << endl;
            }
            else if (token.value == "or")
            {
                cout << "    Token::Keyword(Keyword::Or)," << endl;
            }
            else if (token.value == "create")
            {
                cout << "    Token::Keyword(Keyword::Create)," << endl;
            }
            else if (token.value == "table")
            {
                cout << "    Token::Keyword(Keyword::Table)," << endl;
            }
            else if (token.value == "int")
            {
                cout << "    Token::Keyword(Keyword::Int)," << endl;
            }
            else if (token.value == "primary")
            {
                cout << "    Token::Keyword(Keyword::Primary)," << endl;
            }
            else if (token.value == "key")
            {
                cout << "    Token::Keyword(Keyword::Key)," << endl;
            }
            else if (token.value == "varchar")
            {
                cout << "    Token::Keyword(Keyword::Varchar)," << endl;
            }
            else if (token.value == "bool")
            {
                cout << "    Token::Keyword(Keyword::Bool)," << endl;
            }
            else if (token.value == "update")
            {
                cout << "    Token::Keyword(Keyword::Update)," << endl;
            }
            else if (token.value == "set")
            {
                cout << "    Token::Keyword(Keyword::Set)," << endl;
            }
            else if (token.value == "insert")
            {
                cout << "    Token::Keyword(Keyword::Insert)," << endl;
            }
            else if (token.value == "into")
            {
                cout << "    Token::Keyword(Keyword::Into)," << endl;
            }
            else if (token.value == "values")
            {
                cout << "    Token::Keyword(Keyword::Values)," << endl;
            }
            else if (token.value == "true")
            {
                cout << "    Token::Keyword(Keyword::True)," << endl;
            }
            else if (token.value == "false")
            {
                cout << "    Token::Keyword(Keyword::False)," << endl;
            }
            else if (token.value == "delete")
            {
                cout << "    Token::Keyword(Keyword::Delete)," << endl;
            }
            else if (token.value == "drop")
            {
                cout << "    Token::Keyword(Keyword::Drop)," << endl;
            }
        }
        else if (token.type == TokenType::Identifier)
        {
            cout << "    Token::Identifier(\"" << token.value << "\")," << endl;
        }
        else if (token.type == TokenType::Number)
        {
            cout << "    Token::Number(\"" << token.value << "\")," << endl;
        }
        else if (token.type == TokenType::String)
        {
            size_t pos = 0;
            while ((pos = token.value.find("\"", pos)) != string::npos)
            {
                token.value.insert(pos, "\\");
                pos += 2;
            }
            cout << "    Token::String(\"" << token.value << "\")," << endl;
        }
        else if (token.type == TokenType::Comma)
        {
            cout << "    Token::Comma," << endl;
        }
        else if (token.type == TokenType::SemiColon)
        {
            cout << "    Token::SemiColon," << endl;
        }
        else if (token.type == TokenType::LeftParen)
        {
            cout << "    Token::LeftParen," << endl;
        }
        else if (token.type == TokenType::RightParen)
        {
            cout << "    Token::RightParen," << endl;
        }
        else if (token.type == TokenType::Eq)
        {
            cout << "    Token::Eq," << endl;
        }
        else if (token.type == TokenType::Neq)
        {
            cout << "    Token::Neq," << endl;
        }
        else if (token.type == TokenType::Lt)
        {
            cout << "    Token::Lt," << endl;
        }
        else if (token.type == TokenType::Gt)
        {
            cout << "    Token::Gt," << endl;
        }
        else if (token.type == TokenType::Plus)
        {
            cout << "    Token::Plus," << endl;
        }
        else if (token.type == TokenType::Minus)
        {
            cout << "    Token::Minus," << endl;
        }
        else if (token.type == TokenType::Mul)
        {
            cout << "    Token::Mul," << endl;
        }
        else if (token.type == TokenType::Div)
        {
            cout << "    Token::Div," << endl;
        }
        else if (token.type == TokenType::GtEq)
        {
            cout << "    Token::GtEq," << endl;
        }
        else if (token.type == TokenType::LtEq)
        {
            cout << "    Token::LtEq," << endl;
        }
        else if (token.type == TokenType::Whitespace)
        {
            if (token.value == " ")
            {
                cout << "    Token::Whitespace(Whitespace::Space)," << endl;
            }
            else if (token.value == "\t")
            {
                cout << "    Token::Whitespace(Whitespace::Tab)," << endl;
            }
            else if (token.value == "\n")
            {
                cout << "    Token::Whitespace(Whitespace::Newline)," << endl;
            }
        }
        else if (token.type == TokenType::Eof)
        {
            cout << "    Token::Eof" << endl;
        }
    }
    cout << "})" << endl;
}
void printError(TokenizerError error, string input, Token token)
{
    cout << "Err({" << endl;
    if (error.kind == ErrorKind::UnexpectedOrUnsupportedToken)
    {
        cout << "    ErrorKind::UnexpectedOrUnsupportedToken(\'" << token.value << "\')," << endl;
    }
    else if (error.kind == ErrorKind::UnexpectedWhileParsingOperator)
    {
        cout << "    ErrorKind::UnexpectedWhileParsingOperator('" << input << "', Token::" << tokenToString(token) << ")," << endl;
    }
    else if (error.kind == ErrorKind::OperatorNotClosed)
    {
        cout << "    ErrorKind::OperatorNotClosed(Token::" << tokenToString(token) << ")," << endl;
    }
    else if (error.kind == ErrorKind::StringNotClosed)
    {
        cout << "    ErrorKind::StringNotClosed," << endl;
    }
    else if (error.kind == ErrorKind::Other)
    {
        cout << "    ErrorKind::Other,";
    }
    cout << "    Location{" << error.location.line << ", " << error.location.col << "}," << endl;
    size_t pos = 0;
    while ((pos = error.input.find("\"", pos)) != string::npos)
    {
        error.input.insert(pos, "\\");
        pos += 2;
    }
    pos = 0;
    while ((pos = error.input.find("\'", pos)) != string::npos)
    {
        error.input.insert(pos, "\\");
        pos += 2;
    }
    cout << "    \"" << error.input << "\"" << endl;
    cout << "})" << endl;
}
int main(int argc, char *argv[])
{
    string input;
    for (int i = 1; i < argc; i++)
    {
        if (i >= 3)
        {
            input += " ";
        }
        input += argv[i];
    }
    while (input.find("\\") != string::npos)
    {
        input.replace(input.find("\\"), 1, "\"");
    }
    while (input.find("\\") != string::npos)
    {
        input.erase(input.find("\\"), 1);
    }
    vector<Token> tokens = tokenize(input);
    if (isPrintError)
    {
        return 0;
    }
    printTokens(tokens);
    return 0;
}