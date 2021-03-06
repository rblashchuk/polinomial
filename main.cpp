#include <iostream>
#include <initializer_list>
#include <cmath>
#include "gtest/gtest.h"

using namespace std;

constexpr long long pow(int x, int p) {
    if (x) {
        if (p == 0) return 1;
        else return x * pow(x, p - 1);
    }
    else{
        if (p) return 0;
        else return 1;
    }
}

struct monomial {
    int degree;
    int coef;
};

template<int len>
class Polynomial {
public:
    constexpr Polynomial(initializer_list<monomial> monomials) {
        int ind = 0;
        for (auto &elem: monomials) {
            poly[ind] = elem;
            ind++;
        }
    }

    constexpr int val_at_point(const int x_value) const{
        int ans(0);
        for (auto &elem: poly) {
            ans += pow(x_value, elem.degree) * elem.coef;
        }
        return ans;
    }

    friend ostream &operator<<(ostream &out, const Polynomial &polynomial) {
        for (int i = 0; i < len; i++) {
            char s = '+';
            if (polynomial.poly[i].coef < 0) {
                s = '-';
            }

            if(polynomial.poly[i].coef == 1) {
                if (i || s == '-')
                    out << s << ' ' << "x^" << polynomial.poly[i].degree << " ";
                else out << "x^" << polynomial.poly[i].degree << " ";
            }

            else {
                if (i || s == '-')
                    out << s << ' ' << polynomial.poly[i].coef << "x^" << polynomial.poly[i].degree << " ";
                else out << polynomial.poly[i].coef << "x^" << polynomial.poly[i].degree << " ";
            }


        }
        out << "\n";

        return out;
    }
protected:
    monomial poly[len]{};
};



TEST(VALUE_TEST, TEST){
    initializer_list<monomial> a{monomial{2, 5}, monomial{1, 3}, monomial{3, 1}, monomial{4, 1}};
    Polynomial<4> pol(a);
    int res = pol.val_at_point(2);
    ASSERT_TRUE(res == 50);
};

int main() {
    constexpr Polynomial<4> pol = {monomial{2, 5}, monomial{1, 3}, monomial{3, 1}, monomial{4, 1}};
    cout << pol;

    RUN_ALL_TESTS();
    return 0;
}
