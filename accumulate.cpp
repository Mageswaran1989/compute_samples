//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Mageswaran.D <mageswaran1989@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://kylelutz.github.com/compute for more information.
//---------------------------------------------------------------------------//

#include <iostream>
#include <boost/compute/core.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/algorithm/accumulate.hpp>

#define DATA_LENGTH 10000
namespace compute = boost::compute;

int main()
{
    compute::device compute_device = compute::system::default_device();

    std::cout<<"Hey you goona test on me : "<<compute_device.name()<<std::endl;

    compute::context compute_context(compute_device);
    compute::command_queue compute_queue(compute_context, compute_device);

    int *some_int_ptr;
    some_int_ptr = new int[DATA_LENGTH];

    for(int i=0; i<DATA_LENGTH; i++)
        some_int_ptr[i] = i;

    compute::vector<int> compute_vec(some_int_ptr, some_int_ptr+DATA_LENGTH, compute_queue);


    std::cout << " Tadaaa.... " << std::endl;
    std::cout << "Sum : "
              << compute::accumulate(compute_vec.begin(), compute_vec.end(), 0, compute_queue)
              << std::endl;

    some_int_ptr[0] = 1;

    std::cout << "With binary function: product of array items : "
              << compute::accumulate(compute_vec.begin(), compute_vec.end(), 1, boost::compute::multiplies<int>(), compute_queue)
              << std::endl;
    delete[] some_int_ptr;
    return 0;
}










