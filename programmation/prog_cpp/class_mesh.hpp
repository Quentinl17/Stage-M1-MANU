#pragma once
#include <iostream>
#include <vector>

template<typename T>
class mesh
{
    public :
        mesh(T a_max, size_t n_cells);

        ~mesh(){};

        inline const size_t n_vertices() const { return n_vertices_ ;};
        inline const size_t n_cells() const { return n_cells_; };
        inline const T da() const { return da_; };
        inline T cells_centers(size_t ii) const { return cells_centers_[ii]; };
        const std::vector<T>& get_vertices() const { return vertices_coordinates_; };

        void print();

    protected :
        std::vector<T> vertices_coordinates_;
        std::vector<T> cells_centers_;
        size_t n_vertices_{0};
        size_t n_cells_{0};
        T da_;
};

// ===== Definitions ===== //
template<typename T>
mesh<T>::mesh(T a_max, size_t n_cells) : n_cells_(n_cells), n_vertices_(n_cells + 1), vertices_coordinates_(n_cells + 1), cells_centers_(n_cells)
{   
    if(a_max == 0)
    {
        std::cout << "Error : a_max must be different of zero !" << std::endl;
        abort();
    }

    if(n_cells == 0)
    {
        std::cout << "Error : number of cells must be strictly positive !" << std::endl;
        abort();
    }

    da_ = a_max / n_cells;

    for(size_t ii = 0; ii < n_vertices_; ii++)
    {
        vertices_coordinates_[ii] =  ii * da_;
    }

    for(size_t ii = 0; ii < n_cells_; ii++)
    {
        cells_centers_[ii] = (vertices_coordinates_[ii + 1] + vertices_coordinates_[ii]) / (2.);
    }
}

template<typename T>
void mesh<T>::print()
{
    std::cout << "The meshes definitions :" << std::endl;

    std::cout << "- Number of cells : " << n_cells_ << std::endl;
    std::cout << "- Number of vertices : " << n_vertices_ << std::endl;
    std::cout << "- Step : " << da_ << std::endl;

    std::cout << "- Vertices coordinates : [";
    for(size_t ii = 0; ii < n_vertices_ - 1; ii++)
    {
        std::cout << vertices_coordinates_[ii] << ", ";
    }
    std::cout << vertices_coordinates_[n_vertices_ - 1] << "]" << std::endl;

    std::cout << "- Cells centers : ";
    for(size_t ii = 0; ii < n_cells_ - 1; ii++)
    {
        std::cout << cells_centers_[ii] << ", ";
    }
    std::cout << cells_centers_[n_cells_ - 1] << std::endl;
}