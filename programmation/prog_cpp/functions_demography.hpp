#pragma once
#include <iostream>
#include <cmath>
#include "class_mesh.hpp"

// Maximal age
inline const double a_max = 100.;

// Mortality rate
template<typename T>
T mu(T a)
{
    if(a >= 0. && a < a_max)
    {
        return 3 * std::pow(a, 3) / (std::pow(a_max, 3) - std::pow(a, 3));
    }
    else if(a == a_max)
    {
        std::cout << "The mortality rate is not defined in a = " << a_max << std::endl;
        abort();
    }
    else if(a < 0.)
    {
        std::cout << "The mortality rate is not defined for negatif age !" << std::endl;
        abort();
    }
    else
    {
        return 0.;
    }
};

// Survive probability
template<typename T>
T Pi(T a)
{
    if(a >= 0. && a < a_max)
    {
        return 1 - std::pow(a / a_max, 3);
    }
    else if(a < 0.)
    {
        std::cout << "The survive propability is not defined for negatif age !" << std::endl;
        abort();
    }
    else
    {
        return 0.;
    }
    
};

// Birth rate
double beta_plus = 0.045;
template<typename T>
T beta(T a)
{
    if(a >= 20. && a < 40.)
    {
        return beta_plus; 
    }
    else if(a < 0.)
    {
        std::cout << "The birth rate is not defined for negatif age !" << std::endl;
        abort();
    }
    else
    {
        return 0.;
    }
};

// Maternity
template<typename T>
T K(T a)
{
    return Pi(a) * beta(a);
};

// Initial data
template<typename T>
T x_init(T a)
{
    if(a >= 0. && a < a_max)
    {
        return Pi(a);
    }
    else if(a < 0.)
    {
        std::cout << "The initial data is not defined for negatif age !" << std::endl;
        abort();
    }
    else
    {
        return 0.;
    }
};