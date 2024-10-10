#ifndef FUNCTION_COMPILER_H
#define FUNCTION_COMPILER_H
#include <string>
#include <vector>
#include <cmath>
#include <stack>
#include <limits>
#include <stdexcept>

enum UnitType{
    NUMBER,
    VARIABLE,
    FUNCTION,
    OPERATOR,
    UNDEFINED __attribute__((unused))
};

namespace {

template<typename T>
T sgn(T val)
{
    static_assert(std::is_arithmetic<T>::value, "T must be an arithmetic type");
    if (std::isnan(val))
        return std::numeric_limits<T>::quiet_NaN();
    return (T(0) < val) - (val < T(0));
}

}

template<class T>
class Function
{
public:
    Function() = default;
    explicit Function(const std::string& source);
    virtual ~Function() = default;

    int set_function(const std::string& source);
    T run(T xvalue) const;

    Function& operator=(const std::string& source);
    T operator()(T xvalue) const;

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

template<class T>
struct Function<T>::Unit
{
    typedef double (*TFunction)(double);

    UnitType type{UNDEFINED};
    T value;
    TFunction function{};
    char operation{};

    Unit() = default;
    explicit Unit(const T& x) : type(NUMBER), value(x) {}
    explicit Unit(const std::string& s) {
        if (s == "x") {
            type = VARIABLE;
        } else {
            type = FUNCTION;
            if (s == "sin")
                function = sin;
            else if (s == "cos")
                function = cos;
            else if (s == "tan")
                function = tan;
            else if (s == "asin")
                function = asin;
            else if (s == "acos")
                function = acos;
            else if (s == "sgn")
                function = sgn;
            else if (s == "floor")
                function = floor;
            else if (s == "exp")
                function = exp;
            else if (s == "log10")
                function = log10;
            else
                throw std::invalid_argument("Invalid function name: " + s);
        }
    }
    explicit Unit(char c) {
        type = OPERATOR;
        if (Function<T>::is_operator(c))
            operation = c;
        else
            operation = '*';
    }
};


template<class T>
Function<T>::Function(const std::string &source)
{
    set_function(source);
}

template<class T>
int Function<T>::set_function(const std::string& source)
{
    expression = source;
    m_rpn_expr = convert(simplify(expression));
    return 0;
}

template<class T>
std::string Function<T>::simplify(const std::string& source)
{
    std::string result;

    for (size_t i = 0; i < source.size(); ++i)
    {
        if (isspace(source[i])) continue;

        if (is_operator(source[i]) && source[i] != '(' && source[i] != ')')
            if (i == 0 || source[i - 1] == '(')
                result += '0';

        result += source[i];
        if (!isalpha(source[i]) || source[i] == 'x') { continue; }

        size_t j;
        for (j = i + 1; j < source.size() && (isalpha(source[j]) || isdigit(source[j])); ++j)
            result += source[j];
        result += '#';
        i = j - 1;
    }

    return result;
}

template<class T>
bool Function<T>::is_operator(char c)
{
    return (
        c == '*' || c == '/' || c == '%' ||
        c == '+' || c == '-' ||
        c == '^' || c == '#' ||
        c == '(' || c == ')'
        );
}

template<class T>
int Function<T>::priority(char c) const
{
    if (c == '#')
        return 5;
    if (c == '^')
        return 4;
    if (c == '*' || c == '/' || c == '%')
        return 3;
    if (c == '+' || c == '-')
        return 2;
    if (c == '(')
        return 1;
    return 0;
}

template<class T>
T Function<T>::run(T xvalue) const
{
    std::stack<Unit> st;
    T result = 0;

    for (size_t i = 0; i < m_rpn_expr.size(); ++i)
    {
        Unit cur = m_rpn_expr[i];

        if (cur.type == OPERATOR)
        {
            if (st.size() < 2) {
                throw std::runtime_error("Ill-formed function");
            }

            Unit val2 = st.top(); st.pop();
            Unit val1 = st.top(); st.pop();

            if (cur.operation == '#') {
                if (val1.type != FUNCTION || val2.type != NUMBER) {
                    throw std::runtime_error("Ill-formed function");
                }
            } else {
                if (val1.type != NUMBER || val2.type != NUMBER) {
                    throw std::runtime_error("Ill-formed function");
                }
            }

            switch (cur.operation)
            {
            case '+':
                result = val1.value + val2.value;
                break;
            case '-':
                result = val1.value - val2.value;
                break;
            case '*':
                result = val1.value * val2.value;
                break;
            case '/':
                result = val1.value / val2.value;
                break;
            case '%':
                result = static_cast<long long>(val1.value) %
                         static_cast<long long>(val2.value);
                break;
            case '^':
                result = pow(val1.value, val2.value);
                break;
            case '#':
                result = val1.function(val2.value);
                break;
            default:
                result = 0;
            }

            st.push(Unit(result));
        } else {
            if (cur.type == VARIABLE)
                st.push(Unit(xvalue));
            else
                st.push(cur);
        }
    }
    return result;
}

template<class T>
Function<T>& Function<T>::operator=(const std::string &source)
{
    set_function(source);
    return *this;
}

template<class T>
T Function<T>::operator()(T xvalue) const
{
    return run(xvalue);
}


template<class T>
typename Function<T>::RPN Function<T>::convert(const std::string& s)
{
    std::stack<Unit> st;
    Function<T>::RPN result;
    std::string buffer;

    const auto processBuffer = [&result](std::string &buffer) -> void
    {
        if (!buffer.empty()) {
            if (isdigit(buffer[0]))
                result.push_back(Unit(T(std::stod(buffer))));
            else if (buffer == "x")
                result.push_back(Unit("x"));
            else
                result.push_back(Unit(buffer));
            buffer.clear();
        }
    };

    for (char c : s)
    {
        if (c == '(') {
            st.push(Unit('('));
            continue;
        }

        if (c == ')') {
            processBuffer(buffer);
            while (!st.empty() && st.top().operation != '(')
            {
                result.push_back(st.top());
                st.pop();
            }

            if (!st.empty() && st.top().operation == '(')
                st.pop();

            continue;
        }

        if (is_operator(c)) {
            processBuffer(buffer);
            while (!st.empty() && priority(st.top().operation) >= priority(c))
            {
                result.push_back(st.top());
                st.pop();
            }
            st.push(Unit(c));
            buffer.clear();
        } else {
            buffer += c;
        }
    }

    processBuffer(buffer);
    while (!st.empty())
    {
        result.push_back(st.top());
        st.pop();
    }
    return result;
}


#endif // FUNCTION_COMPILER_H
