#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include "class_mesh.hpp"
#include "class_field.hpp"

template<typename T>
class output_writer
{
    public :
        output_writer(mesh<T> const& msh, std::string filename): mesh_(msh), radical_name_(filename){};

        ~output_writer(){};

        void write_solution(field<T> const& solution, std::string const& loop_counter);
        void write_birth(std::vector<T> const& times, std::vector<T> const& B, std::string const& suffix = "B");

        inline const mesh<T>& get_mesh() const { return mesh_; };

    protected :
        mesh<T> const& mesh_;
        std::string radical_name_;
};

// ===== Definitions ===== //
template<typename T>
void output_writer<T>::write_solution(field<T> const& solution, std::string const& loop_counter)
{
    std::string filename = radical_name_ + "_" + loop_counter + ".txt";
    std::ofstream my_file(filename);

    for(size_t ii = 0; ii < mesh_.n_cells(); ii++)
    {
        my_file << mesh_.cells_centers(ii) << " " << solution(ii) << std::endl;
    }
    
    my_file.close();
}

template<typename T>
void output_writer<T>::write_birth(std::vector<T> const& times, std::vector<T> const& B, std::string const& suffix)
{
    if(times.size() != B.size())
    {
        std::cout << "Error : times and B must have the same size !" << std::endl;
        abort();
    }

    std::string filename = radical_name_ + "_" + suffix + ".txt";
    std::ofstream my_file(filename);

    for(size_t ii = 0; ii < times.size(); ii++)
    {
        my_file << times[ii] << " " << B[ii] << std::endl;
    }

    my_file.close();
}