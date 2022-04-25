#include <iostream>
#include <initializer_list>
#include <cmath>
#include "gtest/gtest.h"

using namespace std;

struct monomial {
    int degree;
    int coef;
};


template<int len>
class Polynomial {
public:
    constexpr Polynomial(initializer_list<monomial> &monomials) {
        int count = 0;
        for (auto &i: monomials) {
            poly[count++] = i;
        }
    }

    constexpr int val_at_point(const int x_value) {
        int result(0);
        for (auto &i: poly) {
            result += pow(x_value, i.degree) * i.coef;
        }
        return result;
    }

    friend ostream &operator<<(ostream &out, const Polynomial &polyn) {
        for (int i = 0; i < len; i++) {
            char sign = '+';
            if (polyn.poly[i].coef < 0) {
                sign = '-';
            }
            out << sign << ' ' <<  polyn.poly[i].coef << "x^" << polyn.poly[i].degree << " ";
        }
        return out;
    }
protected:
    monomial poly[len];
};

template <int n>
struct Test{
    int val = n;
};

TEST(VALUE_TEST, TEST){
    initializer_list<monomial> a{monomial{2, 5}, monomial{1, 3}, monomial{3, 1}, monomial{4, 1}};
    Polynomial<4> pol(a);
    int res = pol.val_at_point(1);
    ASSERT_TRUE(res == 10);
};


int main() {
    RUN_ALL_TESTS();
    return 0;
}
