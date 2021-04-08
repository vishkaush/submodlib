#include <pybind11/pybind11.h>
#include<pybind11/stl.h>
#include "wrapper.h"
namespace py = pybind11;

PYBIND11_MODULE(submodlib_cpp, m) 
{
    cl_FacilityLocation(m);
    cl_FeatureBased(m);
    cl_DisparitySum(m);
    cl_DisparityMin(m);
    cl_GraphCut(m);
    cl_SetCover(m);
    cl_LogDeterminant(m);
    cl_ProbabilisticSetCover(m);
    cl_FacilityLocationMutualInformation(m);
    cl_helper(m);
    cl_sparse_utils(m);
    cl_Clustered(m);
    //cl_set(m);
    //cl_NaiveGreedyOptimizer(m);
}
