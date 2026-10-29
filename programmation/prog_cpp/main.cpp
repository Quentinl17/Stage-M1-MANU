#include "class_mesh.hpp"
#include "class_residual.hpp"
#include "class_field.hpp"
#include "class_output_writer.hpp"
#include "class_time_loop.hpp"
#include "functions_demography.hpp"
#include "class_renewal_solver.hpp"

int main()
{
    // MCKENDRICK-LOTKA MODEL SOLVING
    // Needed initialization parameters
    size_t Ne = 1000;
    size_t Nt = 2000;
    double final_time = 3.;

    // Mesh construction
    mesh<double> msh(a_max, Ne);
    // Print of mesh if needed
    // msh.print();

    // Initial field defined and initialized on mesh
    field<double> xh(msh);

    // Initialize writer
    output_writer<double> out_stream(msh, "mckendrick_lotka_solution");

    // Write initial field
    out_stream.write_solution(xh, "initial");

    // Initialize time-loop
    time_loop<double> loop_in_time(msh, final_time);

    // Lauch time-loop
    loop_in_time.run(xh);

    // Write final field
    out_stream.write_solution(xh, "final");

    // RENEWAL EQUATION SOLVING
    // Initialize writer
    output_writer<double> out_renewal(msh, "renewal");

    // Write renewal solution by FV
    out_renewal.write_birth(loop_in_time.get_times(), loop_in_time.get_B(), "B_FV"); 

    // Initialize solver of renewal equation
    renewal_solver<double> renewal_equation(final_time, Nt, msh);

    // Solving
    renewal_equation.solve();

    // Write renewal solution by Volterra
    out_renewal.write_birth(renewal_equation.get_times_Volterra(), renewal_equation.get_B_Volterra(), "B_Volterra");

    // REPRODUCTION NUMBER
    double R{0.};
    for(size_t ii = 0; ii < msh.n_cells(); ii++)
    {
        R += K(msh.cells_centers(ii));
    }
    R = msh.da() * R;

    std::cout << "The net reproduction rate is R = " << R << "." << std::endl;

    return 0;
}