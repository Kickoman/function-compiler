#ifndef FUNCTION_COMPILER_H
#define FUNCTION_COMPILER_H
#include <string>
#include <vector>
#include <math.h>

enum UnitType{NUMBER, VARIABLE, FUNCTION, OPERATOR, UNDEFINED};

class Function
{
public:
    Function();
    virtual ~Function();

    int set_function(std::string const& source);
    double run(double const& xvalue) const;

    Function& operator=(const std::string& source);
    double operator()(double const& xvalue) const;

protected:

    struct Unit;
    typedef std::vector<Unit> RPN;


    std::string expression;
    RPN m_rpn_expr;

    static bool is_operator(char const& c);
    int priority(char const& c) const;

    RPN convert(std::string const& source);
    std::string simplify(std::string const& source);
private:
};


struct Function::Unit
{
    typedef double (*_Function)(double);

    UnitType type;
    double value;
    _Function function;
    char operation;

    Unit() {}
    Unit(double const& x) : value(x), type(NUMBER) {}
    Unit(std::string const& s) {
        if (s == "x") {
            type = VARIABLE;
        } else {
            type = FUNCTION;
            if (s == "sin")
                function = sin;
            else if (s == "cos")
                function = cos;
            else
                function = tan;
        }
    }
    Unit(char const& c) {
        type = OPERATOR;
        if (Function::is_operator(c))
            operation = c;
        else
            operation = '*';
    }
};

#endif // FUNCTION_COMPILER_H
