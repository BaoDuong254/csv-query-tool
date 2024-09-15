#include "exql.h"

// * Token definition
std::vector<Token> tokens;
int current = 0;
Token current_token()
{
    return tokens[current];
}
void next_token()
{
    if (current < tokens.size() - 1)
    {
        current++;
    }
}

// * Column class
std::string Column::getName() const
{
    return name;
}

DataType Column::getDataType() const
{
    return dataType;
}

std::vector<Constraint> Column::getConstraints() const
{
    return constraints;
}

std::string Column::ConstraintToString() const
{
    for (int i = 0; i < constraints.size(); ++i)
    {
        if (constraints[i] == Constraint::PrimaryKey)
        {
            return "Constraint::PrimaryKey";
        }
        else if (constraints[i] == Constraint::Unique)
        {
            return "Constraint::Unique";
        }
    }
    return "";
}

Column::Column(const std::string &name, DataType dataType, std::vector<Constraint> constraints)
{
    this->name = name;
    this->dataType = dataType;
    this->constraints = constraints;
}

Column Column::newColumn(const std::string &name, DataType dataType)
{
    return Column(name, dataType, {});
}

Column Column::primaryKey(const std::string &name, DataType dataType)
{
    return Column(name, dataType, {Constraint::PrimaryKey});
}

Column Column::unique(const std::string &name, DataType dataType)
{
    return Column(name, dataType, {Constraint::Unique});
}

// * Assignment class
std::string Assignment::getName() const
{
    return identifier;
}

Expression *Assignment::getValue() const
{
    return value;
}

// * DataType class
std::string DataType::toString() const
{
    switch (type)
    {
    case Type::Int:
        return "DataType::Int";
    case Type::Bool:
        return "DataType::Bool";
    case Type::Varchar:
        return "DataType::Varchar";
    }
    return "";
}

// ! Statement classes
// * Create class
std::string Create::toString() const
{
    std::string str = "Statement::Create {\n";
    str += "    name: " + name + ",\n";
    str += "    columns: [\n";
    for (int i = 0; i < columns.size(); ++i)
    {
        str += "        Column {\n";
        str += "            name: " + '"' + columns[i].getName() + '"' + ",\n";
        str += "            type: " + '"' + columns[i].getDataType().toString() + '"' + ",\n";
        str += "            constraints: [\n";
        for (int j = 0; j < columns[i].getConstraints().size(); ++j)
        {
            str += "                " + columns[i].ConstraintToString();
            if (j != columns[i].getConstraints().size() - 1)
            {
                str += ",";
            }
            str += "\n";
        }
        str += "            ]\n";
        if (i != columns.size() - 1)
        {
            str += "        },\n";
        }
        else
        {
            str += "        }\n";
        }
    }
    str += "    ]\n";
    str += "}\n";
    return str;
}

// * Select class

std::string Select::toString() const
{
    std::string str = "Statement::Select {\n";
    str += "    columns: [\n";
    for (int i = 0; i < columns.size(); ++i)
    {
        str += "        " + columns[i]->toString();
        if (i != columns.size() - 1)
        {
            str += ",";
        }
        str += "\n";
    }
    str += "    ],\n";
    str += "    from: " + from + ",\n";
    str += "    where: " + where->toString() + "\n";
    str += "    OrderBy: [\n";
    for (int i = 0; i < orderBy.size(); ++i)
    {
        str += "        " + orderBy[i]->toString();
        if (i != orderBy.size() - 1)
        {
            str += ",";
        }
        str += "\n";
    }
    str += "    ]\n";
    str += "}\n";
    return str;
}

// * Delete class
std::string Delete::toString() const
{
    std::string str = "Statement::Delete {\n";
    str += "    from: " + from + ",\n";
    str += "    where: " + where->toString() + "\n";
    str += "}\n";
    return str;
}

// * Update class
std::string Update::toString() const
{
    std::string str = "Statement::Update {\n";
    str += "    table: " + table + ",\n";
    str += "    columns: [\n";
    for (int i = 0; i < columns.size(); ++i)
    {
        str += "        Assignment {\n";
        str += "            column: " + '"' + columns[i]->getName() + '"' + ",\n";
        str += "            value: " + columns[i]->getValue()->toString() + "\n";
        if (i != columns.size() - 1)
        {
            str += "        },\n";
        }
        else
        {
            str += "        }\n";
        }
    }
    str += "    ],\n";
    str += "    where: " + where->toString() + "\n";
    str += "}\n";
    return str;
}

// * Insert class

std::string Insert::toString() const
{
    std::string str = "Statement::Insert {\n";
    str += "    into: " + into + ",\n";
    str += "    columns: [\n";
    for (int i = 0; i < columns.size(); ++i)
    {
        str += "        " + '"' + columns[i] + '"';
        if (i != columns.size() - 1)
        {
            str += ",";
        }
        str += "\n";
    }
    str += "    ],\n";
    str += "    values: [\n";
    for (int i = 0; i < values.size(); ++i)
    {
        str += "        " + values[i]->toString();
        if (i != values.size() - 1)
        {
            str += ",";
        }
        str += "\n";
    }
    str += "    ]\n";
    str += "}\n";
    return str;
}

// * Drop class

std::string Drop::toString() const
{
    std::string str = "Statement::Drop(\"" + name + "\")";
    return str;
}

// ! Expression classes
// * Identifier class
Identifier::Identifier(std::string ident)
{
    this->ident = ident;
}

std::string Identifier::toString() const
{
    return "Expression::Identifier(\"" + ident + "\")";
}

// * Wildcard class
std::string Wildcard::toString() const
{
    return "Expression::Wildcard";
}

// * Value class
std::string Value::toString() const
{
    switch (type)
    {
    case Type::String:
        return "Expression::Value(Value::String(" + str_val + "))";
    case Type::Bool:
        return "Expression::Value(Value::Bool(" + std::string(bool_val ? "true" : "false") + "))";
    case Type::Number:
        return "Expression::Value(Value::Number(" + std::to_string(num_val) + "))";
    }
    return "";
}

Value::Value(std::string str_val)
{
    this->str_val = str_val;
    this->type = Type::String;
}

Value::Value(bool bool_val)
{
    this->bool_val = bool_val;
    this->type = Type::Bool;
}

Value::Value(int64_t num_val)
{
    this->num_val = num_val;
    this->type = Type::Number;
}

// * BinaryOperation class
std::string BinaryOperation::toString() const
{
    std::string opString;
    std::string str;
    switch (op)
    {
    case BinaryOperator::Eq:
        opString = "BinaryOperator::Eq";
        break;
    case BinaryOperator::Neq:
        opString = "BinaryOperator::Neq";
        break;
    case BinaryOperator::Lt:
        opString = "BinaryOperator::Lt";
        break;
    case BinaryOperator::LtEq:
        opString = "BinaryOperator::LtEq";
        break;
    case BinaryOperator::Gt:
        opString = "BinaryOperator::Gt";
        break;
    case BinaryOperator::GtEq:
        opString = "BinaryOperator::GtEq";
        break;
    case BinaryOperator::Plus:
        opString = "BinaryOperator::Plus";
        break;
    case BinaryOperator::Minus:
        opString = "BinaryOperator::Minus";
        break;
    case BinaryOperator::Mul:
        opString = "BinaryOperator::Mul";
        break;
    case BinaryOperator::Div:
        opString = "BinaryOperator::Div";
        break;
    case BinaryOperator::And:
        opString = "BinaryOperator::And";
        break;
    case BinaryOperator::Or:
        opString = "BinaryOperator::Or";
        break;
    }
    str = "Expression::BinaryOperation {\n";
    str += "    left: " + left->toString() + ",\n";
    str += "    op: " + opString + ",\n";
    str += "    right: " + right->toString() + "\n";
    str += "}\n";
    return str;
}

BinaryOperation::BinaryOperation(Expression *left, BinaryOperator op, Expression *right)
{
    this->left = left;
    this->op = op;
    this->right = right;
}

BinaryOperator BinaryOperation::getOperator() const
{
    return op;
}

// * UnaryOperation class
std::string UnaryOperation::toString() const
{
    std::string opString;
    std::string str;
    switch (op)
    {
    case UnaryOperator::Plus:
        opString = "UnaryOperator::Plus";
        break;
    case UnaryOperator::Minus:
        opString = "UnaryOperator::Minus";
        break;
    }
    str = "Expression::UnaryOperation {\n";
    str += "    op: " + opString + ",\n";
    str += "    expr: " + expr->toString() + "\n";
    str += "}\n";
    return str;
}

// * Nested class
std::string Nested::toString() const
{
    return "Expression::Nested(" + expr->toString() + ")";
}

// * Get the precedence of the operators

BinaryOperator tokenTypeToBinaryOperator(TokenType type)
{
    switch (type)
    {
    case TokenType::Eq:
        return BinaryOperator::Eq;
    case TokenType::Neq:
        return BinaryOperator::Neq;
    case TokenType::Lt:
        return BinaryOperator::Lt;
    case TokenType::LtEq:
        return BinaryOperator::LtEq;
    case TokenType::Gt:
        return BinaryOperator::Gt;
    case TokenType::GtEq:
        return BinaryOperator::GtEq;
    case TokenType::Plus:
        return BinaryOperator::Plus;
    case TokenType::Minus:
        return BinaryOperator::Minus;
    case TokenType::Mul:
        return BinaryOperator::Mul;
    case TokenType::Div:
        return BinaryOperator::Div;
    }
    return BinaryOperator::Invalid;
}

// Mark the precedence of the operators
int get_precedence(BinaryOperator op)
{
    switch (op)
    {
    case BinaryOperator::Or:
        return 1;
    case BinaryOperator::And:
        return 2;
    case BinaryOperator::Eq:
    case BinaryOperator::Neq:
    case BinaryOperator::Lt:
    case BinaryOperator::LtEq:
    case BinaryOperator::Gt:
    case BinaryOperator::GtEq:
        return 3;
    case BinaryOperator::Plus:
    case BinaryOperator::Minus:
        return 4;
    case BinaryOperator::Mul:
    case BinaryOperator::Div:
        return 5;
    default:
        return 0;
    }
    return 0;
}

// Get next precedence
int get_next_precedence()
{
    return get_precedence(tokenTypeToBinaryOperator(current_token().type));
}

// * Parse functions
// parse expr expression
Expression *parse_expr(int precedence)
{
    Expression *expr = parse_prefix();
    int next_precedence = get_next_precedence();
    while (precedence < next_precedence)
    {
        expr = parse_infix(expr, next_precedence);
        next_precedence = get_precedence(dynamic_cast<BinaryOperation *>(expr)->getOperator());
    }
    return expr;
}

// parse prefix expression
Expression *parse_prefix()
{
    Token token = current_token();
    next_token();
    if (token.type == TokenType::Identifier)
    {
        return new Identifier(token.value);   
    }
    else if (token.type == TokenType::Number)
    {
        return new Value(token.value);
    }
    else if (token.type == TokenType::String)
    {
        return new Value(token.value);
    }
    return nullptr;
}

// parse infix expression
Expression *parse_infix(Expression *left, int precedence)
{
    Token token = current_token();
    next_token();
    Expression *right = parse_prefix();
    int next_precedence = get_next_precedence();
    if (precedence < next_precedence)
    {
        right = parse_infix(right, next_precedence);
    }
    return new BinaryOperation(left, tokenTypeToBinaryOperator(token.type), right);
}

int main(int argc, char *argv[])
{
    std::string input;
    for (int i = 1; i < argc; i++)
    {
        input += argv[i];
    }
    tokens = tokenize(input);
}