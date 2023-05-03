#include "Fraction.hpp"
#include <iostream>
#include <numeric>

using namespace std;
namespace ariel {
    Fraction::Fraction(int numerator, int denominator) : numerator(numerator), denominator(denominator) {
        if (denominator == 0) {
            throw ("Cant divide by zero!");
        }
        this->numerator = numerator;
        this->denominator = denominator;

    }

    Fraction::Fraction(float num) :numerator(1),denominator(1){
        int top = int(num * 1000);
        int bottom = 1000;
        this->denominator = bottom;
        this->numerator = top;
        simplify(*this);
    }

    Fraction::Fraction():numerator(1),denominator(1) {
    }

    Fraction operator+(const Fraction &fraction1, const Fraction &fraction2) {
        int num1 = fraction1.getNumerator(), num2 = fraction2.getNumerator();
        int den1 = fraction1.getDenominator(), den2 = fraction2.getDenominator();
        int tmpDen1 = den1;
        num1 = den2 * num1;
        den1 = den2 * den1;
        num2 = num2 * tmpDen1;
        Fraction result(num1 + num2, den1);
        simplify(result);
        return result;
    }

    Fraction operator-(const Fraction &fraction1, const Fraction &fraction2) {
        int num1 = fraction1.getNumerator(), num2 = fraction2.getNumerator();
        int den1 = fraction1.getDenominator(), den2 = fraction2.getDenominator();
        int tmpDen1 = den1;
        num1 = den2 * num1;
        den1 = den2 * den1;
        num2 = num2 * tmpDen1;
        den2 = den2 * tmpDen1;
        Fraction result(num1 - num2, den1);
        simplify(result);
        return result;
    }

    Fraction operator*(const Fraction &fraction1, const Fraction &fraction2) {
        int num = fraction1.getNumerator() * fraction2.getNumerator();
        int den = fraction1.getDenominator() * fraction2.getDenominator();
        Fraction result(num, den);
        simplify(result);
        return result;
    }

    Fraction operator/(const Fraction &fraction1, const Fraction &fraction2) {
        if (fraction2.getNumerator() == 0) {
            throw ("Cant divide by zero!");
        }
        int num = fraction1.getNumerator() * fraction2.getDenominator();
        int den = fraction1.getDenominator() * fraction2.getNumerator();
        Fraction result(num, den);
        simplify(result);
        return result;
    }

    bool operator==(const Fraction &fraction1, const Fraction &fraction2) {
        return (!(fraction2 != fraction1));
    }

    bool operator>=(const Fraction &fraction1, const Fraction &fraction2) {
        return (!(fraction1 < fraction2));
    }

    bool operator<=(const Fraction &fraction1, const Fraction &fraction2) {
        return (!(fraction1 > fraction2));
    }

    bool operator!=(const Fraction &fraction1, const Fraction &fraction2) {
        return (fraction1 > fraction2 || fraction2 > fraction1);
    }

    bool operator<(const Fraction &fraction1, const Fraction &fraction2) {
        return (fraction2 > fraction1);
    }

    bool operator>(const Fraction &fraction1, const Fraction &fraction2) {
        int num1 = fraction1.getNumerator() * fraction2.getDenominator();
        int num2 = fraction2.getNumerator() * fraction1.getDenominator();
        return (num1 > num2);
    }

    int Fraction::getNumerator() const {
        return numerator;
    }


    std::ostream &operator<<(std::ostream &os, const Fraction &fraction) {
        return os << fraction.numerator << '/' << fraction.denominator;
    }

    std::istream &operator>>(std::istream &input, Fraction &fraction) {
        int num ,den;
        if(!(input >> num)){
            throw ("error");
        }
        if(!(input >> den)){
            throw ("error");
        }
        if(den==0){
            throw ("error");
        }
        fraction.setNumerator(num);
        fraction.setDenominator(den);
        return input;
    }

    // prefix increment:
    Fraction &Fraction::operator++() {
        increment();
        return *this;
    }

    //not working right
    // postfix increment:
    const Fraction Fraction::operator++(int) {
        Fraction copy(*this);
        increment();
        return copy;
    }

    // prefix decrement:
    Fraction &Fraction::operator--() {
        decrement();
        return *this;
    }

    // postfix decrement:
    const Fraction Fraction::operator--(int) {
        Fraction copy(*this);
        decrement();
        return copy;
    }

    int Fraction::getDenominator() const {
        return denominator;
    }

    void simplify(Fraction &fraction) {
        int num = fraction.getNumerator();
        int den = fraction.getDenominator();
        int divisor = std::gcd(num, den);
        num = fraction.getNumerator() / divisor;
        den = fraction.getDenominator() / divisor;
        fraction.setDenominator(den);
        fraction.setNumerator(num);
    }

    void Fraction::setNumerator(int num) {
        this->numerator = num;
    }

    void Fraction::setDenominator(int den) {
        this->denominator = den;
    }

    void Fraction::increment() {
        this->numerator += this->denominator;
    }

    void Fraction::decrement() {
        this->numerator -= this->denominator;
    }

}

