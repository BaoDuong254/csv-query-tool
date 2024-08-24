#include <bits/stdc++.h>
using namespace std;
bool isPrintError = false;
enum class TokenType
{
    Keyword,
    Identifier,
    Number,
    String,
    Comma,
    SemiColon,
    LeftParen,
    RightParen,
    Eq,
    Neq,
    Lt,
    Gt,
    Plus,
    Minus,
    Mul,
    Div,
    GtEq,
    LtEq,
    Whitespace,
    Eof,
    Invalid
};
class Token
{
public:
    TokenType type;
    string value;
    Token(TokenType type, string value)
    {
        this->type = type;
        this->value = value;
    }
};
enum class ErrorKind
{
    UnexpectedOrUnsupportedToken,
    UnexpectedWhileParsingOperator,
    OperatorNotClosed,
    StringNotClosed,
    Other
};

struct Location
{
    size_t line; // Line number starting at 1
    size_t col;  // Column number starting at 1
};

class TokenizerError
{
public:
    ErrorKind kind;
    Location location; // Location of the error
    string input;      // Input string that caused the error
    TokenizerError(ErrorKind kind, Location location, string input)
    {
        this->kind = kind;
        this->location = location;
        this->input = input;
    }
};
TokenizerError unexpectedOrUnsupportedToken(Location, string);
TokenizerError unexpectedWhileParsingOperator(Location, string);
TokenizerError operatorNotClosed(Location, string);
TokenizerError stringNotClosed(Location, string);
TokenizerError other(Location, string);
Token tokenizeKeywordOrIdentifier(string);
Token tokenizeNumber(string);
Token tokenizeString(string);
Token tokenizeOperatorOrSeparator(string);
string tokenToString(Token);
vector<Token> tokenize(string);
void printTokens(vector<Token>);
void printError(TokenizerError, string, Token);