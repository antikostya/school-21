
#include <iostream>
#include <map>
#include <cmath>
#include <complex>
#include <numeric>

inline constexpr long double EPS = 1e-6;
int VERBOSE = 0;

struct Parser {
    std::string inp;
    std::map<long long int, long double> powers;
    std::string var;

    struct Pair {
        long long int power;
        long double coeff;
    };

    Parser(const std::string &input) {
        inp = input;
    }

    void parse() {
        size_t start = 0;
        bool invert = false;
        bool negative = false;

        while (start < inp.size()) {
            skip_spaces(start);
            negative = false;
            if (start < inp.size() and inp.at(start) == '-') {
                ++start;
                negative = true;
            } else if (start < inp.size() and inp.at(start) == '+') {
                ++start;
            }
            skip_spaces(start);
            Pair p = parse_term(start);
            if (invert)
                negative = not negative;
            if (negative)
                p.coeff = -p.coeff;
            powers[p.power] += p.coeff;
            if (start < inp.size() and inp.at(start) == '=') {
                if (invert)
                    throw std::invalid_argument("only one '=' can be in equation");
                invert = true;
                ++start;
                skip_spaces(start);
            }
        }
    }

    Pair parse_term(size_t &start) {
        bool was_coeff, was_variable, was_power, waiting_power, waiting_var;
        long double coeff = NAN;
        long long int power = -1;
        std::string variable;

        was_coeff = false;
        was_variable = false;
        was_power = false;
        waiting_power = false;
        waiting_var = false;

        skip_spaces(start);
        coeff = parse_float(start, was_coeff);
        if (VERBOSE) {
            std::cout << "parsed coef " << coeff << std::endl;;
        }
        skip_spaces(start);
        if (was_coeff and start < inp.size() and inp.at(start) == '*') {
            ++start;
            skip_spaces(start);
            waiting_var = true;
        }
        if (not was_coeff)
            coeff = 1.0L;
        variable = parse_string(start, was_variable);
        if (VERBOSE) {
            std::cout << "parsed var " << variable << std::endl;
        }
        if (not was_variable and waiting_var)
            throw std::invalid_argument("expected variable name");
        if (was_variable) {
            if (var.empty()) {
                var = variable;
            } else if (var != variable) {
                throw std::invalid_argument("expected variable name `" + var +
                    "`, got `" + variable + "`");
            }
        }
        skip_spaces(start);
        if (start < inp.size() and inp.at(start) == '^') {
            if (was_variable) {
                ++start;
                waiting_power = true;
            } else {
                throw std::invalid_argument("cannot apply power without variable");
            }
        }
        if (waiting_power) {
            power = parse_int(start, was_power);
            if (VERBOSE) {
                std::cout << "parsed power " << power << std::endl;
            }
            skip_spaces(start);
            if (waiting_power && not was_power)
                throw std::invalid_argument("expected power value");
        }
        if (not was_power) {
            if (not was_variable)
                power = 0;
            else
                power = 1;
        }
        return {power, coeff};
    }

    long long int parse_int(size_t &start, bool &was_number)
    {
        char *end;
        long long int ans;

        if (start >= inp.size()) {
            was_number = false;
            return {};
        }
        ans = std::strtoll(inp.data() + start, &end, 10);
        if (end == inp.data() + start) {
            was_number = false;
            return {};
        }
        start += end - inp.data() - start;
        was_number = true;
        return ans;
    }

    long double parse_float(size_t &start, bool &was_number)
    {
        char *end;
        long double ans;

        if (start >= inp.size()) {
            was_number = false;
            return {};
        }
        ans = std::strtold(inp.data() + start, &end);
        if (end == inp.data() + start) {
            was_number = false;
            return {};
        }
        start += end - inp.data() - start;
        was_number = true;
        return ans;
    }

    std::string parse_string(size_t &start, bool &was_string)
    {
        size_t end = start;
        if (end < inp.size() and std::isalpha(inp.at(end))) {
            ++end;
        }
        while (end < inp.size() and std::isalnum(inp.at(end))) {
            ++end;
        }
        if (start == end) {
            was_string = false;
            return {};
        } else {
            was_string = true;
            std::string ret = inp.substr(start, end - start);
            start += end - start;
            return ret;
        }
    }

    void skip_spaces(size_t &start)
    {
        while (start < inp.size() and std::isspace(inp.at(start)))
            ++start;
    }
};

class Solver
{
public:
    Solver(const std::map<long long int, long double> &powers)
        : powers(powers)
    {}

    void check()
    {
        for (auto it = powers.rbegin(); it != powers.rend(); ++it) {
            if (it->first >= 3 and std::abs(it->second) < 1e-10) {
                std::stringstream ss;
                ss << "cannot solve equation of " << it->first << " order";
                throw std::invalid_argument(ss.str());
            }
        }
    }

    void solve() {
        long double a, b, c;

        a = powers.at(2);
        b = powers.at(1);
        c = powers.at(0);
        std::complex<long double> disk;
        disk = b * b - 4 * a * c;
        ld_disk = disk.real();
        disk = std::sqrt(disk);
        first = -b + disk;
        second = -b - disk;
        denumenator = 2 * a;
    }

    const std::map<long long int, long double> &powers;
    std::complex<long double> first;
    std::complex<long double> second;
    long double denumenator;
    long double ld_disk;
};

class Printer
{
public:

    Printer(std::complex<long double> _x1, std::complex<long double> _x2, long double _disk, long double _den)
    {
        if (std::abs(_disk) < EPS) {
            is_equal_roots = true;
            is_complex_roots = false;
        } else if (_disk < 0) {
            is_equal_roots = false;
            is_complex_roots = true;
        } else {
            is_equal_roots = false;
            is_complex_roots = false;
        }

        disk_str = real2str(_disk, 1);
        if (is_complex_roots) {
            x1_str = comp2str(_x1, _den);
            x2_str = comp2str(_x2, _den);
        } else if (is_equal_roots) {
            x1_str = real2str(_x1.real(), _den);
        } else {
            x1_str = real2str(_x1.real(), _den);
            x2_str = real2str(_x2.real(), _den);
        }
    }

    void print_disk()
    {
        std::cout << "Discriminant: " << disk_str << std::endl;
    }

    void print_roots()
    {
        if (is_equal_roots) {
            std::cout << "single root: " << x1_str << std::endl;
        } else {
            std::cout << "first root: " << x1_str << std::endl;
            std::cout << "second root: " << x2_str << std::endl;
        }
    }

    static std::string comp2str(std::complex<long double> x, long double _den)
    {
        if (std::abs(x.imag()) > EPS and std::abs(x.real()) > EPS) {
            return "(" + real2str(x.real(), _den) + " + " + real2str(x.imag(), _den) + "j)";
        } else if (std::abs(x.real()) > EPS) {
            return real2str(x.real(), _den);
        } else if (std::abs(x.imag()) > EPS) {
            return real2str(x.imag(), _den) + "j";
        } else {
            return "0";
        }
    }

    static std::string real2str(long double x, long double _den)
    {
        if (_den < 0) {
            x = -x;
            _den = -_den;
        }
        if (std::abs(x) < EPS)
            return "0";
        if (std::abs(std::round(x) - x) < EPS and
            std::abs(std::round(_den) - _den) < EPS) {
            return rational2str(x, _den);
        } else {
            std::stringstream ss;
            ss << (x / _den);
            return ss.str();
        }
    }

    static std::string rational2str(long double _x, long double _den)
    {
        auto x = static_cast<long long int>(std::round(_x));
        auto den = static_cast<long long int>(std::round(_den));
        long long int gcd = std::gcd(x, den);
        std::stringstream ss;

        x /= gcd;
        den /= gcd;
        if (den == 1 or x == 0)
            ss << x;
        else
            ss << x << '/' << den;
        return ss.str();
    }

    std::string disk_str;
    std::string x1_str;
    std::string x2_str;
    bool is_complex_roots;
    bool is_rational_roots;
    bool is_equal_roots;
};

void print_reduced_form(long double a, long double b, long double c, std::string var)
{
    if (var.empty()) {
        var = "x";
    }
    std::cout << "Reduced form: ";
    std::cout << Printer::real2str(a, 1) << '*' << var << "^2 ";
    if (b < 0) {
        std::cout << "- ";
    } else {
        std::cout << "+ ";
    }
    std::cout << Printer::real2str(std::abs(b), 1) << '*' << var << "^1 ";
    if (c < 0) {
        std::cout << "- ";
    } else {
        std::cout << "+ ";
    }
    std::cout << Printer::real2str(std::abs(c), 1) << '*' << var << "^0 = 0" << std::endl;
}

bool check_singular(long double a, long double b, long double c)
{
    if (std::abs(a) < EPS) {
        if (std::abs(b) < EPS) {
            if (std::abs(c) < EPS) {
                std::cout << "any number is a sulution\n";
            } else {
                std::cout << "no solutions exists\n";
            }
        } else {
            std::cout << "Linear equation\nsingle root: "
                << Printer::real2str(-c, b) << std::endl;
        }
        return true;
    }
    return false;
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        std::cout << "expected equation argument\n";
        return 1;
    } else if (argc > 2) {
        std::cout << "extra arguments ignored\n";
    }
    Parser p(argv[1]);
    try {
        p.parse();
        if (p.powers.empty()) {
            throw std::invalid_argument("empty request");
            return 0;
        }
        if (p.powers.rbegin()->first > 2 and std::abs(p.powers.rbegin()->second) > EPS) {
            throw std::invalid_argument("only 2nd or lower degree equations are supported");
        }
        print_reduced_form(p.powers[2], p.powers[1], p.powers[0], p.var);
        if (check_singular(p.powers[2], p.powers[1], p.powers[0]))
            return 0;
        Solver s(p.powers);
        s.check();
        s.solve();
        Printer pr(s.first, s.second, s.ld_disk, s.denumenator);
        pr.print_disk();
        pr.print_roots();
    } catch (std::invalid_argument &e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
}
