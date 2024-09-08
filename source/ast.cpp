#include "exql.h"

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

int main(int argc, char *argv[])
{
    std::string input;
    for (int i = 1; i < argc; i++)
    {
        input += argv[i];
    }
    std::vector<Token> tokens = tokenize(input);
}