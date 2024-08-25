#include <iostream>
#include <string>
#include <vector>
extern bool isPrintError;
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
    const TokenType type;
    const std::string value;
    Token(TokenType type, std::string value);
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
    const ErrorKind kind; // Kind of the error
    const Location location; // Location of the error
    const std::string input;      // Input string that caused the error
    TokenizerError(ErrorKind kind, Location location, std::string input);
};
TokenizerError unexpectedOrUnsupportedToken(const Location, const std::string);
TokenizerError unexpectedWhileParsingOperator(const Location, const std::string);
TokenizerError operatorNotClosed(const Location, const std::string);
TokenizerError stringNotClosed(const Location, const std::string);
TokenizerError other(const Location, const std::string);
Token tokenizeKeywordOrIdentifier(const std::string);
Token tokenizeNumber(const std::string);
Token tokenizeString(const std::string);
Token tokenizeOperatorOrSeparator(const std::string);
std::string tokenToString(const Token);
std::vector<Token> tokenize(const std::string);
void printTokens(std::vector<Token>);
void printError(const TokenizerError, const std::string, const Token);