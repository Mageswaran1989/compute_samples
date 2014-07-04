////---------------------------------------------------------------------------//
//// Copyright (c) 2013-2014 Mageswaran.D <mageswaran1989@gmail.com>
////
//// Distributed under the Boost Software License, Version 1.0
//// See accompanying file LICENSE_1_0.txt or copy at
//// http://www.boost.org/LICENSE_1_0.txt
////
//// See http://kylelutz.github.com/compute for more information.
////---------------------------------------------------------------------------//

//#include <random>
//#include <algorithm>
//#include <iterator>
//#include <iostream>

//#include <boost/compute/system.hpp>
//#include <boost/compute/container/vector.hpp>
//#include <boost/compute/source.hpp>
//#include <boost/compute/random/mersenne_twister.hpp>
//#include <boost/compute/random/default_random_engine.hpp>
//#include <boost/compute/random/uniform_int_distribution.hpp>

//#include "shuffle.hpp"

//namespace compute = boost::compute;

//const char shuffle_source[] =
//        BOOST_COMPUTE_STRINGIZE_SOURCE(
//            __kernel void gpu_shuffle(__global float *in_data,
//                                      __global const unsigned int *rand_data)
//            {
//                int i = get_global_id(0);
//                int shuffle_index = rand_data[i];
//                float temp = in_data[shuffle_index];
//                barrier(CLK_GLOBAL_MEM_FENCE);
//                in_data[i] = temp;
//            }
//    );

////http://en.cppreference.com/w/cpp/algorithm/random_shuffle

//template<class RandomIt, class UniformRandomNumberGenerator>
//void test_shuffle(RandomIt first, RandomIt last,
//             UniformRandomNumberGenerator&& g)
//{
//    typedef typename std::iterator_traits<RandomIt>::difference_type diff_t;
//    typedef typename std::make_unsigned<diff_t>::type udiff_t;
//    typedef typename std::uniform_int_distribution<udiff_t> distr_t;
//    typedef typename distr_t::param_type param_t;

//    distr_t D;
//    diff_t n = last - first;
//    //>>>>>Added
//    std::cout<<" g(0,i) : ";
//    //<<<<<Added
//    for (diff_t i = n-1; i > 0; --i) {
//        using std::swap;
//        swap(first[i], first[D(g, param_t(0, i))]);
//        std::cout << D(g, param_t(0, i)) << " ";
//    }
//    //>>>>>Added
//    std::cout<< std::endl;
//    //<<<<<Added
//}


//void std_shuffle()
//{

//    //Testing shuffle
//    std::vector<int> v = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

//    std::random_device rd;
//    std::mt19937 g(rd());

//    std::cout<<"std::Shuffle"<< std::endl;
//    std::shuffle(v.begin(), v.end(), g);
//    copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
//    std::cout << "\n";

//    std::cout<<"test_shuffle :"<< std::endl;
//    test_shuffle(v.begin(), v.end(), g);
//    copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
//    std::cout << "\n";

//    std::cout<<"Testing uniform_int_distribution generator:"
//             << std::endl;
//    std::mt19937 mt(rd());
//    std::uniform_int_distribution<uint> dist(0, 10);
//    for (int i=0; i<10; ++i)
//        std::cout << dist(mt) << " ";
//}

//int compute_shufle(compute::command_queue &queue,
//                   compute::context &context)
//{
//    compute::program program = compute::program::create_with_source(
//                                                    shuffle_source,
//                                                    context);
//    try
//    {
//        program.build();
//    }
//    catch(compute::opencl_error e)
//    {
//        std::cout<<e.error_string()
//                <<std::endl
//               <<program.build_log();
//        return -1;
//    }

//    std::vector<float> host_in(128);
//    for(int i=0; i<128; i++)
//        host_in[i] = i * i;

//    std::cout<< std::endl <<"Data Before Shuffle :>>>>>>>>>>>" << std::endl;
//    for(int i=0; i<128; i++)
//        std::cout <<host_in[i] <<" ";


//    compute::uniform_int_distribution<unsigned int> random_distribution(0, 127);
//    random_distribution.generate(gpu_rand.begin(),
//                                    gpu_rand.end(), random_engine, queue);


//    // device vectors
//    compute::vector<float> d_input(128, context);

//    // copy input data
//     compute::copy(host_in.begin(), host_in.end(), d_input.begin(), queue);

//    compute::kernel shuffle_kernel(program, "gpu_shuffle");

//    shuffle_kernel.set_arg(0, d_input);
//    shuffle_kernel.set_arg(1, gpu_rand);
//    size_t global_size = 128;
//    size_t local_size = NULL;

//    queue.enqueue_nd_range_kernel(shuffle_kernel,
//                                  1,
//                                  0,
//                                  &global_size,
//                                  0);

//    compute::copy(d_input.begin(), d_input.end(), host_in.begin(), queue);

//    //Results
//    std::cout<< std::endl << "Shuffle Index: >>>>>>>>>>>" << std::endl;
//    for (int i=0; i<128; ++i)
//        std::cout << gpu_rand[i] << " ";

//    std::cout<< std::endl <<"Data After Shuffle :>>>>>>>>>>>" <<std::endl;
//    for(int i=0; i<128; i++)
//        std::cout <<host_in[i]<<" ";

//}

///***
// *  Shuffle OpenCL Algorithm:
// *  1. Get the user data for shuffle
// *  2. Generate random index using the rng
// *  3. Map the user data and random index to kernel
// *  4. Run the kernel
// */
//int main(int arc, char* argv[])
//{
//    //OpenCL Setup
//    compute::device cl_device = compute::system::default_device();
//    compute::context cl_context(cl_device);
//    compute::command_queue cl_command_queue(
//                cl_context,
//                cl_device,
//                compute::command_queue::enable_profiling);

//    std_shuffle();
//    compute_shufle(cl_command_queue, cl_context);

//    compute::vector<float> user_data(1024);

//    for(int i=0; i<1024; i++)
//        user_data[i] = i;

//    std::cout<< std::endl <<"user_data Before Shuffle :>>>>>>>>>>>" <<std::endl;
//    for(int i=0; i<1024; i++)
//        std::cout <<user_data[i]<<" ";

//    boost::compute::shuffle(user_data.begin(), user_data.end());

//    std::cout<< std::endl <<"user_data After Shuffle :>>>>>>>>>>>" <<std::endl;
//    for(int i=0; i<1024; i++)
//        std::cout <<user_data[i]<<" ";

//    return 0;
//}














