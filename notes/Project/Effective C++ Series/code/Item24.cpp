class Rational {
    public:
        Rational(int numerator=0, int denominator=1); // 允許 int-to-Rational 的隱式轉換
        int numerator(); // 分子
        int denominator(); // 分母
        const Rational operator*(const Rational rhs) const;
}

Rational oneEight(1, 8);
Rational oneHalf(1, 2);

Rational res = oneEight*oneHalf; // OK
res = res*oneEight; // OK
res = oneHalf*2; // OK: oneHalf.operator*(2)
res = 2*oneHalf; // Error: 2.operator*(oneHalf)


class Rational {
    ...
};

const Rational operator*(const Rational& lhs, const Rational& rhs) {
    return Rational(lhs.numerator()*rhs.numerator(), lhs.denominator()*rhs.denominator());
}
