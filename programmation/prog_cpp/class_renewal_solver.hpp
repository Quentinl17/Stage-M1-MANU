#pragma once
#include <vector>
#include "class_mesh.hpp"
#include "functions_demography.hpp"

template<typename T>
class renewal_solver 
{
    public :
        renewal_solver(T final_time, size_t Nt, mesh<T> const& msh) : final_time_(final_time), Nt_(Nt), mesh_(msh) {};

        ~renewal_solver(){};

        const std::vector<T>& get_times_Volterra() const { return times_; };
        const std::vector<T>& get_B_Volterra() const { return B_Volterra_; };

        void solve();

    protected :
        T final_time_;
        size_t Nt_;
        std::vector<T> times_;

        mesh<T> const& mesh_;

        std::vector<T> B_Volterra_;
};

// ===== Definitions ===== //
template<typename T>
void renewal_solver<T>::solve()
{
    T da = mesh_.da();
    const std::vector<T>& vertices = mesh_.get_vertices();

    for(size_t ii = 0; ii <= Nt_; ii++)
    {
        times_.push_back(ii * final_time_ / Nt_);
    }

    T dt = final_time_ / Nt_;

    B_Volterra_.resize(times_.size());

    for(size_t ii = 0; ii < times_.size(); ii++)
    {
        // Calcul of F by trapezoidal method
        T F{0.};
        for(size_t jj = 0; jj < mesh_.n_vertices() - 1; jj++)
        {
            if(jj + 1 == mesh_.n_vertices() - 1)
            {
                T m = (vertices[jj] + vertices[jj + 1]) / 2.;
                F += 0.5 * K(m + ii * dt) * x_init(m) / Pi(m);
            }
            else
            {
                F += 0.5 * (K(vertices[jj] + ii * dt) * x_init(vertices[jj]) / Pi(vertices[jj]) + K(vertices[jj + 1] + ii * dt) * x_init(vertices[jj + 1]) / Pi(vertices[jj + 1]));
            }
        }
        F = da * F;

        // Renewal
        if(ii == 0)
        {
            B_Volterra_[ii] = F;
        }
        else
        {
            T sum{0.};
            for(size_t jj = 0; jj < ii; jj++)
            {
                if(jj == 0)
                {
                    sum += 0.5 * (K((jj + 1) * dt) * B_Volterra_[ii - jj - 1]);
                }
                else
                {
                    sum += 0.5 * (K(jj * dt) * B_Volterra_[ii - jj] + K((jj + 1) * dt) * B_Volterra_[ii - jj - 1]);
                }
            }
            sum = dt * sum;

            B_Volterra_[ii] = F + sum;
        }
    }
};