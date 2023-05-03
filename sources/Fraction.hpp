#ifndef FRACTION_A_FRACTION_HPP
#define FRACTION_A_FRACTION_HPP

#include <iostream>
#include <string>

namespace ariel {

    class Fraction {
    private:
        int numerator;
        int denominator;
        void increment();
        void decrement();

    public:
        explicit Fraction(int numerator, int denominator);

        Fraction();

//        Fraction(const Fraction &fraction);
//
        Fraction(float num);

        void setNumerator(int num);

        void setDenominator(int den);

        int getDenominator() const;

        friend void simplify(Fraction &fraction);


        friend Fraction operator+(const Fraction &fraction1, const Fraction &fraction2);

        friend Fraction operator-(const Fraction &fraction1, const Fraction &fraction2);

        friend Fraction operator*(const Fraction &fraction1, const Fraction &fraction2);

        friend Fraction operator/(const Fraction &fraction1, const Fraction &fraction2);

        friend bool operator==(const Fraction &fraction1, const Fraction &fraction2);

        friend bool operator>=(const Fraction &fraction1, const Fraction &fraction2);

        friend bool operator<=(const Fraction &fraction1, const Fraction &fraction2);

        friend bool operator!=(const Fraction &fraction1, const Fraction &fraction2);

        friend bool operator<(const Fraction &fraction1, const Fraction &fraction2);

        int getNumerator() const;

        friend bool operator>(const Fraction &fraction1, const Fraction &fraction2);

        friend std::ostream &operator<<(std::ostream &osStream, const Fraction &fraction);

        friend std::istream &operator>>(std::istream &input, Fraction fraction);

        // prefix increment:
        Fraction &operator++();

        // postfix increment:
        const Fraction operator++(int);

        // prefix decrement:
        Fraction &operator--();

        // postfix decrement:
        const Fraction operator--(int);

    };

}


#endif //FRACTION_A_FRACTION_HPP
