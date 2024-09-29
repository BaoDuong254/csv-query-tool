#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include <fstream>
#include <sstream>

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
    Eof,
    Invalid
};

enum class ErrorKind
{
    UnexpectedOrUnsupportedToken,
    UnexpectedWhileParsingOperator,
    OperatorNotClosed,
    StringNotClosed,
    // AST error kinds
    TokenizerError,
    Expected,
    ExpectedOneOf,
    UnexpectedOrUnsupported,
    UnexpectedEof,
    IntegerOutOfRange,
    Other,
};

// Enum class for SQL binary operators
enum class BinaryOperator
{
    Eq,
    Neq,
    Lt,
    LtEq,
    Gt,
    GtEq,
    Plus,
    Minus,
    Mul,
    Div,
    And,
    Or,
    Invalid
};

// Enum class for SQL unary operators
enum class UnaryOperator
{
    Plus,
    Minus
};

// Enum class for SQL constraints
enum class Constraint
{
    PrimaryKey,
    Unique
};

struct Location
{
    size_t line; // Line number starting at 1
    size_t col;  // Column number starting at 1
};

class Token
{
public:
    const TokenType type;
    const std::string value;
    Token(TokenType type, std::string value);
};

class TokenizerError
{
public:
    const ErrorKind kind;    // Kind of the error
    const Location location; // Location of the error
    const std::string input; // Input string that caused the error
    TokenizerError(ErrorKind kind, Location location, std::string input);
};

// Base class for SQL Statements
class Statement
{
public:
    virtual ~Statement() = default;
    virtual std::string toString() const = 0;
};

// Base class for all expressions
class Expression
{
public:
    virtual ~Expression() = default;
    virtual std::string toString() const = 0;
};

// Class for SQL data types
class DataType
{
private:
    enum class Type
    {
        Int,
        Bool,
        Varchar
    };
    Type type;
    size_t size; // Used for VARCHAR, example: VARCHAR(50), VARCHAR(100), VARCHAR(255)
public:
    std::string toString() const;
};

// Class to represent an Assignment in SQL
class Assignment
{
private:
    std::string identifier; // The column name or identifier
    Expression *value;      // The expression assigned to the column
public:
    // Get methods
    std::string getName() const;
    Expression *getValue() const;
    // constructor
    Assignment(std::string identifier, Expression *value);
    // dtor
    ~Assignment()
    {
        delete value;
    }
};

// Class to represent a Column in SQL
class Column
{
private:
    std::string name;                    // The name of the column
    DataType dataType;                   // The data type of the column
    std::vector<Constraint> constraints; // Constraints on the column
    Column(const std::string &name, DataType dataType, std::vector<Constraint> constraints);

public:
    // Get methods
    std::string getName() const;
    DataType getDataType() const;
    std::vector<Constraint> getConstraints() const;
    // To_string method
    std::string ConstraintToString() const;
    // Static method to create a new Column without constraints
    static Column newColumn(const std::string &name, DataType dataType);
    // Static method to create a Column with PrimaryKey constraint
    static Column primaryKey(const std::string &name, DataType dataType);
    // Static method to create a Column with Unique constraint
    static Column unique(const std::string &name, DataType dataType);
    // dtor
    ~Column()
    {
        constraints.clear();
    }
};

// Derived class for CREATE statements
class Create : public Statement
{
private:
    std::string name;            // table name
    std::vector<Column> columns; // table columns
public:
    std::string toString() const;
    // dtor
    ~Create()
    {
        columns.clear();
    }
};

// Derived class for SELECT statements
class Select : public Statement
{
private:
    std::vector<Expression *> columns;
    std::string from;
    Expression *where;
    std::vector<Expression *> orderBy;

public:
    friend class Parser;
    std::string toString() const;
    // dtor
    ~Select()
    {
        for (auto &column : columns)
        {
            delete column;
        }
        delete where;
        for (auto &order : orderBy)
        {
            delete order;
        }
    }
};

// Derived class for DELETE statements
class Delete : public Statement
{
private:
    std::string from;
    Expression *where;

public:
    friend class Parser;
    std::string toString() const;
    // dtor
    ~Delete()
    {
        delete where;
    }
};

// Derived class for UPDATE statements
class Update : public Statement
{
private:
    std::string table;
    std::vector<Assignment *> columns;
    Expression *where;

public:
    friend class Parser;
    std::string toString() const;
    // dtor
    ~Update()
    {
        for (auto &column : columns)
        {
            delete column;
        }
        delete where;
    }
};

// Derived class for INSERT statements
class Insert : public Statement
{
private:
    std::string into;
    std::vector<std::string> columns;
    std::vector<Expression *> values;

public:
    friend class Parser;
    std::string toString() const;
    // dtor
    ~Insert()
    {
        for (auto &value : values)
        {
            delete value;
        }
    }
};

// Derived class for DROP statement
class Drop : public Statement
{
private:
    std::string name; // table name
public:
    friend class Parser;
    std::string toString() const;
};

// Derived class for identifiers
class Identifier : public Expression
{
private:
    std::string ident;

public:
    Identifier(std::string ident);
    std::string toString() const;
};

// Derived class for values
class Value : public Expression
{
private:
    enum class Type
    {
        String,
        Bool,
        Number
    };
    Type type;
    std::string str_val;
    bool bool_val;
    int64_t num_val;

public:
    Value(std::string str_val);
    Value(bool bool_val);
    Value(int64_t num_val);
    std::string toString() const;
};

// Derived class for wildcards
class Wildcard : public Expression
{
public:
    std::string toString() const;
};

// Derived class for binary operations
class BinaryOperation : public Expression
{
private:
    Expression *left;
    BinaryOperator op;
    Expression *right;

public:
    std::string toString() const;
    BinaryOperator getOperator() const;
    BinaryOperation(Expression *left, BinaryOperator op, Expression *right);
    // dtor
    ~BinaryOperation()
    {
        delete left;
        delete right;
    }
};

// Derived class for unary operations
class UnaryOperation : public Expression
{
private:
    UnaryOperator op;
    Expression *expr;

public:
    std::string toString() const;
    // dtor
    ~UnaryOperation()
    {
        delete expr;
    }
};

// Derived class for nested expressions
class Nested : public Expression
{
private:
    Expression *expr;

public:
    std::string toString() const;
    //dtor
    ~Nested()
    {
        delete expr;
    }
};

// Define a class for ParserError
class ParserError
{
public:
    ErrorKind kind;
    Location location; // Location class from Lexer phase
    std::string input;
};

template <typename T>
struct ParseResult
{
    bool success; // Flag indicating if the parsing was successful
    // T result;     // Holds the result if successful
    // ParserError error; // Holds the error details if unsuccessful
};
class Parser
{
private:
    std::string input; // Original string input
    Token *token;      // Token class from Lexer phase
    Location location; // Location class from Lexer phase
public:
    Parser(std::string input);
    // Parser methods
    ParseResult<Statement> parseStatement();
    ParseResult<Expression> parseExpression();
    // dtor
    ~Parser()
    {
        delete token;
    }
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
std::vector<Token> tokenize(const std::string);
std::string tokenToString(const Token);
void printTokens(std::vector<Token>);
void printError(const TokenizerError, const std::string, const Token);
BinaryOperator tokenTypeToBinaryOperator(TokenType);
int getPrecedence(BinaryOperator);
int getNextPrecedence();
Expression *parseExpr(int);
Expression *parsePrefix();
Expression *parseInfix(Expression *, int);
Token currentToken();
int nextTokenIndex();
std::string handleFile(const std::string&, int);