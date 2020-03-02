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

    int set_function(const std::string& source);
    double run(double xvalue) const;

    Function& operator=(const std::string& source);
    double operator()(double xvalue) const;

protected:

    struct Unit;
    typedef std::vector<Unit> RPN;


    std::string expression;
    RPN m_rpn_expr;

    static bool is_operator(char c);
    int priority(char c) const;

    RPN convert(const std::string& source);
    std::string simplify(const std::string& source);
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
    Unit(double x) : value(x), type(NUMBER) {}
    Unit(const std::string& s) {
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
    Unit(char c) {
        type = OPERATOR;
        if (Function::is_operator(c))
            operation = c;
        else
            operation = '*';
    }
};

#endif // FUNCTION_COMPILER_H
