#pragma once
#include <cmath>
#include "class_mesh.hpp"
#include "functions_demography.hpp"

template<typename T>
class residual;

// Definition of class field
template<typename T>
class field
{
    public :
        field(mesh<T> const& msh);

        ~field(){};

        inline const size_t n_cells() const { return n_cells_; };
        inline const std::vector<T>& operator()() const { return values_; };
        
        inline T operator()(size_t ii) const { return values_[ii]; };
        
        field<T>& operator+=(residual<T> res);

    protected :
        size_t n_cells_{0};
        std::vector<T> values_;
};

// ===== Definitions ===== //
template<typename T>
field<T>::field(mesh<T> const& msh): n_cells_(msh.n_cells()), values_(n_cells_)
{
    for(size_t ii = 0; ii < n_cells_; ii++)
    {
        values_[ii] = x_init(msh.cells_centers(ii));
    }
}

template<typename T>
field<T>& field<T>::operator+=(residual<T> res)
{
    for(size_t ii = 0; ii < res.n_cells(); ii++)
    {
        values_[ii] += res(ii);
    }

    return *this;
}