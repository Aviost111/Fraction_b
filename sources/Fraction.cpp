#include "Fraction.hpp"
#include <iostream>
#include <cmath>
#include <climits>
#include <numeric>

using namespace std;
namespace ariel {
    void checkTooBig(long num1,long num2){
        if(num1>INT_MAX||num2>INT_MAX||num1<INT_MIN||num2<INT_MIN){
            throw overflow_error("The numbers are too big!");
        }
    }

    Fraction::Fraction(int numerator, int denominator) : numerator(numerator), denominator(denominator) {
        if (denominator == 0) {
            throw invalid_argument("Cant divide by zero!");
        }
        this->numerator = numerator;
        this->denominator = denominator;

    }

    Fraction::Fraction(float num) : numerator(1), denominator(1) {
        int top = int(num * 1000);
        int bottom = 1000;
        this->denominator = bottom;
        this->numerator = top;
        simplify(*this);
    }

    Fraction::Fraction() : numerator(1), denominator(1) {
    }

    Fraction operator+(const Fraction &fraction1, const Fraction &fraction2) {
        long num1 = fraction1.getNumerator(), num2 = fraction2.getNumerator();
        long den1 = fraction1.getDenominator(), den2 = fraction2.getDenominator();
        long tmpDen1 = den1;
        num1 = den2 * num1;
        den1 = den2 * den1;
        num2 = num2 * tmpDen1;
        checkTooBig(num1+num2,den1);
        Fraction result(int(num1 + num2), int(den1));
        simplify(result);
        return result;
    }

    Fraction operator-(const Fraction &fraction1, const Fraction &fraction2) {
        long num1 = fraction1.getNumerator(), num2 = fraction2.getNumerator();
        long den1 = fraction1.getDenominator(), den2 = fraction2.getDenominator();
        long tmpDen1 = den1;
        num1 = den2 * num1;
        den1 = den2 * den1;
        num2 = num2 * tmpDen1;
        den2 = den2 * tmpDen1;
        checkTooBig(num1-num2,den1);
        Fraction result(int(num1 - num2), int(den1));
        simplify(result);
        return result;
    }

    Fraction operator*(const Fraction &fraction1, const Fraction &fraction2) {
        Fraction a(fraction1.getNumerator(), fraction1.getDenominator());
        Fraction b(fraction2.getNumerator(), fraction2.getDenominator());
        simplify(a);
        simplify(b);
        //need to deal with long
        long bigNum = long(a.getNumerator()) * b.getNumerator();
        long bigDen = long(a.getDenominator()) * b.getDenominator();
        checkTooBig(bigDen,bigNum);
        int num = a.getNumerator() * b.getNumerator();
        int den = a.getDenominator() * b.getDenominator();
        Fraction result(num, den);
        simplify(result);
        return result;
    }

    Fraction operator/(const Fraction &fraction1, const Fraction &fraction2) {
        if (fraction2.getNumerator() == 0) {
            throw runtime_error("Cant divide by zero!");
        }
        Fraction a(fraction1.getNumerator(), fraction1.getDenominator());
        Fraction b(fraction2.getNumerator(), fraction2.getDenominator());
        simplify(a);
        simplify(b);
        long bigNum = long(a.getNumerator()) * b.getNumerator();
        long bigDen = long(a.getDenominator()) * b.getDenominator();
        checkTooBig(bigDen,bigNum);
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
        int den1 = fraction1.getDenominator(), den2 = fraction2.getDenominator();
        int numa1 = fraction1.getNumerator(), numa2 = fraction2.getNumerator();
        double num1 =int((double(numa1)/den1)*1000);
        num1=num1/1000;
        double num2 =int((double(numa2)/den2)*1000);
        num2=num2/1000;
//        bool positive1, positive2;
//        if (((den1 < 0) && (numa1 < 0)) || ((den1 > 0) && (numa1 > 0))) {
//            positive1 = true;
//        } else {
//            positive1 = false;
//        }
//        if (((den2 < 0) && (numa2 < 0)) || ((den2 > 0) && (numa2 > 0))) {
//            positive2 = true;
//        } else {
//            positive2 = false;
//        }
//        int num1 = abs(numa1 * den2);
//        int num2 = abs(numa2 * den1);
//        if (!positive1) {
//            num1 = (-num1);
//        }
//        if (!positive2) {
//            num2 = (-num2);
//        }
        return (num1 > num2);
    }

    int Fraction::getNumerator() const {
        return numerator;
    }


    std::ostream &operator<<(std::ostream &os, const Fraction &fraction) {
        Fraction fraction1(fraction.numerator,fraction.denominator);
        simplify(fraction1);
        if((fraction1.numerator<0&&fraction1.denominator>0)||fraction1.numerator>0&&fraction1.denominator<0){
            return os <<"-"<<abs(fraction1.numerator) << '/' << abs(fraction1.denominator);
        }
        return os << abs(fraction1.numerator) << '/' << abs(fraction1.denominator);
    }

    std::istream &operator>>(std::istream &input, Fraction &fraction) {
        int num, den;
        if (!(input >> num)) {
            throw runtime_error("error");
        }
        if (!(input >> den)) {
            throw runtime_error("error");
        }
        if (den == 0) {
            throw runtime_error("error");
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

