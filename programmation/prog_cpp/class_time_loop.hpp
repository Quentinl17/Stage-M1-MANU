#pragma once
#include "class_mesh.hpp"
#include "class_field.hpp"
#include "class_residual.hpp"
#include "functions_demography.hpp"

template<typename T>
class time_loop
{
    public :
        time_loop(mesh<T> const& msh, T final_time);

        ~time_loop(){};

        inline const T final_time() const { return final_time_; };
        inline const T get_dt() const { return dt_; };
        const std::vector<T>& get_times() const { return times_; };
        const std::vector<T>& get_B() const { return B_; };

        T birth_rate(field<T> const& uh) const;
        void run(field<T>& uh);

    protected :
        T dt_{0.};
        T physical_time_{0.};
        T final_time_{0.};
        T max_mu_{0.};
        bool last_iteration_{false};
        double cfl_number_{0.4};

        std::vector<T> B_;
        std::vector<T> times_;
        residual<T> residual_;
        mesh<T> const& mesh_;
};

// ===== Definitions ===== //
template<typename T>
time_loop<T>::time_loop(mesh<T> const& msh, T final_time) : mesh_(msh), final_time_(final_time), residual_(residual<T>(msh))
{
    for(size_t i = 0; i < msh.n_cells(); i++)
    {
        max_mu_   = std::max(max_mu_, mu(msh.cells_centers(i)));
    }

    dt_ = cfl_number_ * mesh_.da() / (1 + max_mu_ * mesh_.da());
};

template<typename T>
T time_loop<T>::birth_rate(field<T> const& uh) const
{
    T B{0.};

    for(size_t ii = 0; ii < mesh_.n_cells(); ii++)
    {
        B += beta(mesh_.cells_centers(ii)) * uh(ii);
    }

    return B * mesh_.da();
};

template<typename T>
void time_loop<T>::run(field<T>& uh)
{
    while(std::abs(physical_time_ - final_time()) > 1e-6)
    {
        if(physical_time_ + dt_ > final_time())
        {
            dt_ = final_time() - physical_time_;
            last_iteration_ = true;
        }

        times_.push_back(physical_time_);
        
        residual<T> source_term(mesh_);
        for(size_t ii = 0; ii < mesh_.n_cells(); ii++)
        {
            source_term(ii) = mu(mesh_.cells_centers(ii)) * uh(ii);
        }

        const T B = birth_rate(uh);
        B_.push_back(B);

        residual_.assemble_from_field(uh, B);

        uh += dt_ * (residual_ - source_term);

        physical_time_ += dt_;
    }
}