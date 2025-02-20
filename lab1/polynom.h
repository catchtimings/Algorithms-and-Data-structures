#pragma once
#include <stdexcept>
#include <iostream>
#include <cmath>
#define EPSILON 0.0000001

template <typename T>
class Polynom
{
private:
    T* _coeffs;
    size_t _degree;

public:

    Polynom(const size_t& degree) : _degree(degree) 
    {
        _coeffs = new T[_degree + 1];
        for (size_t i = 0; i <= _degree; ++i) _coeffs[i] = 0;
    }


    Polynom(const T* coeffs, const size_t& degree) : _degree(degree) 
    {
        _coeffs = new T[_degree + 1];
        for (size_t i = 0; i <= _degree; ++i) _coeffs[i] = coeffs[i];
    }


    Polynom(const Polynom<T>& other) : _degree(other._degree) 
    {
        _coeffs = new T[_degree + 1];
        for (size_t i = 0; i <= _degree; ++i) _coeffs[i] = other._coeffs[i];
    }


    ~Polynom() {
        delete[] _coeffs;
    }


    size_t degree() const noexcept { return _degree; }

    T* coeffs() const noexcept { return _coeffs; }

    T& operator[](const size_t& index) const 
    {
        if (index < 0 || index > _degree) throw std::out_of_range("Invalid degree value");
        return _coeffs[index];
    }


    void set(const T& value, const size_t& degree) 
    {
        if (degree < 0 || degree > _degree) throw std::out_of_range("Invalid degree value");
        _coeffs[degree] = value;
    }


    T calculate(const T& x) const 
    {
        T result = 0;
        for (size_t i = 0; i <= _degree; ++i) 
        {
            result += _coeffs[i] * T(pow(x,i));
        }
        return result;
    }


    void shrink_to_fit() 
    {
        int deg = static_cast<int>(_degree);
        size_t max_degree = 0;
        for (int i = deg; i >= 0; --i) 
        {
            if (_coeffs[i] != 0) 
            {
                max_degree = static_cast<size_t>(i);
                break;
            }
        }

        //if (max_degree == 0) throw std::invalid_argument("Degree must be greater than 0");

        T* new_coeffs = new T[max_degree + 1];

        for (size_t i = 0; i <= max_degree; ++i) 
        {
            new_coeffs[i] = _coeffs[i];
        }
        delete[] _coeffs;
        _coeffs = new_coeffs;
        _degree = max_degree;
    }


    void expand(const size_t& new_degree) 
    {
        if (new_degree <= _degree) throw std::invalid_argument("New degree must be greater than old");

        T* new_coeffs = new T[new_degree + 1];
        for (size_t i = 0; i <= new_degree; ++i) 
        {
            T value = (i > _degree) ? 0 : _coeffs[i];
            new_coeffs[i] = value;
        }
        delete[] _coeffs;
        _coeffs = new_coeffs;
        _degree = new_degree;
    }


    Polynom& operator=(const Polynom& other) 
    {
        if (this != &other) 
        {
            delete[] _coeffs;
            _degree = other._degree;
            _coeffs = new T[_degree + 1];
            for (size_t i = 0; i <= _degree; ++i) 
            {
                _coeffs[i] = other._coeffs[i];
            }
        }
        return *this;
    }


    Polynom& operator +=(const Polynom& other) 
    {
        if (_degree != other._degree) throw std::logic_error("Max degree must be the same");

        for (size_t i = 0; i <= _degree; ++i)
        {
            _coeffs[i] += other._coeffs[i];
        }
        return *this;
    }


    Polynom& operator -=(const Polynom& other) 
    {
        if (_degree != other._degree) throw std::logic_error("Max degree must be the same");

        for (size_t i = 0; i <= _degree; ++i)
        {
            _coeffs[i] -= other._coeffs[i];
        }
        return *this;
    }


    Polynom& operator *=(const T& value) 
    {
        for (size_t i = 0; i <= _degree; ++i) {
            _coeffs[i] *= value;
        }
        return *this;
    }


    bool operator==(const Polynom& other) const 
    {
        if (_degree != other._degree) return false;

        for (size_t i = 0; i <= _degree; ++i) {
            if (std::fabs(_coeffs[i] - other._coeffs[i]) > EPSILON) return false;
        }

        return true;
    }


    bool operator!=(const Polynom& other) const 
    {
        return !(*this == other);
    }

};


template <class T>
Polynom<T> operator+(Polynom<T> lhs, const Polynom<T>& rhs)
{
    return lhs += rhs;
}

template <class T>
Polynom<T> operator*(Polynom<T> lhs, const T& value) 
{
    return lhs *= value;
}

template <class T>
Polynom<T> operator-(Polynom<T> lhs, const Polynom<T>& rhs) 
{
    return lhs -= rhs;
}

template <class T>
Polynom<T> operator*(const T& value, Polynom<T> lhs) 
{
    return lhs *= value;
}

template <class T>
std::ostream& operator<<(std::ostream& os, const Polynom<T>& p) 
{
    T* coeffs = p.coeffs();
    int deg = static_cast<int>(p.degree());
    for (int i = deg; i >= 0; --i)
    {
        os << "(" << coeffs[i] << ")" << "x^" << i << " ";
        if (i > 0) os << "+ ";
    }
    return os;
}