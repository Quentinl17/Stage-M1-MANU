#pragma once
#include "class_mesh.hpp"
#include "class_field.hpp"

// McKendrick-Lotka flux
template<typename T>
T flux(T const& u)
{
    return u;
};

// class residual
template<typename T>
class residual 
{
    public :
        residual(mesh<T> const& mesh): mesh_(mesh), values_(mesh.n_cells()) {};

        ~residual(){};

        inline void clear() { values_.clear(); };
        void assemble_from_field(field<T> const& uh, T birth_rate);

        const mesh<T>& get_mesh() const { return mesh_; };
        inline const size_t n_cells() const { return mesh_.n_cells(); };

        T operator()(size_t ii) const { return values_[ii]; };
        T& operator()(size_t ii) { return values_[ii]; };

        template <typename S>
        friend residual<S> operator*(S lambda, residual<S> const& res);
        template<typename S>
        friend residual<S> operator-(residual<S> const& res1, residual<S> const& res2);
    
    protected :
        mesh<T> const& mesh_;
        std::vector<T> values_;
};

// ===== Definitions ===== //
template<typename T>
void residual<T>::assemble_from_field(field<T> const& uh, T birth_rate)
{
    for(size_t i = 0; i < mesh_.n_cells(); i++)
    {
        if(i == 0)
        {
            values_[i] = - 1. / mesh_.da() * (uh(i) - birth_rate);
        }
        else
        {
            values_[i] = - 1. / mesh_.da() * (uh(i) - uh(i - 1));
        }
    }
};

template<typename T>
residual<T> operator*(T lambda, residual<T> const& res)
{
    residual<T> result = res;
    for(size_t ii = 0; ii < res.mesh_.n_cells(); ii++)
    {
        result.values_[ii] *= lambda;
    }
    
    return result;
};

template<typename T>
residual<T> operator-(residual<T> const& res1, residual<T> const& res2)
{
    residual<T> res(res1.get_mesh());
    for(size_t ii = 0; ii < res.mesh_.n_cells(); ii++)
    {
        res.values_[ii] = res1(ii) - res2(ii);
    }
    
    return res;
};