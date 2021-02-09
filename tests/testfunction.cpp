#include "testfunction.h"



const std::string &TestFunction::get_expression() const
{
    return this->expression;
}

const Function<double>::RPN &TestFunction::get_RPN() const
{
    return this->m_rpn_expr;
}

std::string TestFunction::call_simplify(const std::string &source)
{
    return this->simplify(source);
}

Function<double>::RPN TestFunction::call_convert(const std::string &simplified_source)
{
    return this->convert(simplified_source);
}
