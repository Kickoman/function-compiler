#ifndef TESTFUNCTION_H
#define TESTFUNCTION_H

#include "kfunction.h"

class TestFunction : public Function<double>
{
public:
    const std::string & get_expression() const;
    const RPN & get_RPN() const;

    std::string call_simplify(const std::string &source);
    RPN call_convert(const std::string &simplified_source);
};

#endif // TESTFUNCTION_H
