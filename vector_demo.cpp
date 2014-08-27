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
#include <vector>

#include <boost/compute/core.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/algorithm/fill.hpp>
#include <boost/compute/algorithm/copy.hpp>
#include <boost/compute/system.hpp>

using namespace std;
namespace compute = boost::compute;

int main()
{
	cout << "!!!Hello Compute Vector!!!" << endl;

	///>>>>>>>>	OpenCL Device setup
	// get the default device
	compute::device device_1 = compute::system::default_device();

	// print the device's name
	std::cout << "hello from " << device_1.name() << std::endl;

	compute::context device_1_context(device_1);
	compute::command_queue device_1_command_queue_1(device_1_context, device_1);
	//<<<<<<<<<<

	///>>>>>>>>> Different ways of creating compute::vector
	//Creation 1:
	compute::vector<int> huge_vector(100, device_1_context);

	/// Creation 2:
	std::vector<int> host_vector;
	host_vector.push_back(10);
	host_vector.push_back(20);
	host_vector.push_back(30);
	host_vector.push_back(40);

	compute::vector<int> device_vector(host_vector.begin(), host_vector.end(), device_1_command_queue_1);

	//Creation 3:
	int data[] = { 1, 5, 10, 15 };
	compute::vector<int> a(data, data + 4);


	///>>>>>>>>> Different operations on compute vector:
	cout<<"Size of compute vector :"<<huge_vector.size()<<endl;

	huge_vector.resize(10000);

	cout<<"Size of compute vector after resize :"<<huge_vector.size()<<endl;

	//Array operation on vector
	compute::fill(huge_vector.begin(), huge_vector.end(), 0, device_1_command_queue_1);
	///@Tips: While using any algorithm pass the command queue/context that you have created

	///@Error:
	///	vector_demo: /usr/local/include/compute/boost/compute/command_queue.hpp:348:
	/// void boost::compute::command_queue::enqueue_write_buffer(
	///					const boost::compute::buffer&, 
	/// 					size_t, size_t, const void*,
	///					const boost::compute::wait_list&): 
	/// Assertion `buffer.get_context() == this->get_context()' failed.


	//[print_vector_example
	std::cout << "value huge_vector after fill operation : [ ";
	boost::compute::copy(
			huge_vector.begin(), huge_vector.end(),
			std::ostream_iterator<int>(std::cout, ", "),
			device_1_command_queue_1
	);
	std::cout << "]" << std::endl;
	//]

	huge_vector[5678] = 5678;
	huge_vector[0] = 10000;

	cout<<"Value of huge_vector at(5678) :"<<huge_vector.at(5678)<<endl;
	cout<<"Value of huge_vector.front :"<<huge_vector.front()<<endl;
	cout<<"Value of huge_vector.back :"<<huge_vector.back()<<endl;

	int host_array[] = { 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };

	compute::copy(host_array, host_array + 10, huge_vector.begin(), device_1_command_queue_1);
	compute::system::finish(); /// == clFinish(queue);

	//[print_vector_example
	std::cout << "value of huge_vector after copy operation: [ ";
	boost::compute::copy(
			huge_vector.begin(), huge_vector.end(),
			std::ostream_iterator<int>(std::cout, ", "),
			device_1_command_queue_1
	);
	std::cout << "]" << std::endl;
	//]

	//[print_vector_example
	std::cout << "Copied host vector: [ ";
	boost::compute::copy(
			device_vector.begin(), device_vector.end(),
			std::ostream_iterator<int>(std::cout, ", "),
			device_1_command_queue_1
	);
	std::cout << "]" << std::endl;
	//]


	//[print_vector_example
	std::cout << "device_iterator_constructor: [ ";
	boost::compute::copy(
			device_vector.begin(), device_vector.end(),
			std::ostream_iterator<int>(std::cout, ", "),
			device_1_command_queue_1
	);
	std::cout << "]" << std::endl;
	//]

	huge_vector.push_back(10001);

	///@Tips: No need of device_1_command_queue_1 as a parameter as huge_vector is created with device_1_command_queue_1
	cout<<"Size of compute vector after resize :"<<huge_vector.size()<<endl;

	cout<<"Value of huge_vector[10000] :"<<huge_vector.at(10000)<<endl;

	huge_vector.erase(huge_vector.begin() + 10000);
	cout<<"Size of compute vector after erase :"<<huge_vector.size()<<endl;

	if(device_1.supports_extension("cl_khr_fp64"))
	{
		///@Error: compute::vector<double> double_vector;
		compute::vector<double> double_vector(device_1_context);
		double_vector.push_back(1.21);
		double_vector.push_back(3.14);
		double_vector.push_back(7.89);
		//Creation 4:
		compute::vector<double> other = double_vector;

		//[print_vector_example
		std::cout << "double_vector: [ ";
		boost::compute::copy(
				other.begin(), other.end(),
				std::ostream_iterator<double>(std::cout, ", "),
				device_1_command_queue_1
		);
		std::cout << "]" << std::endl;
		//]

	}

	 std::vector<int> host_vec;
	 host_vec.push_back(1);
	 host_vec.push_back(9);
	 host_vec.push_back(7);
	 host_vec.push_back(9);

	huge_vector.assign(host_vec.begin(), host_vec.end(), device_1_command_queue_1);

	//[print_vector_example
	std::cout << "value of huge_vector after assign operation: [ ";
	boost::compute::copy(
			huge_vector.begin(), huge_vector.end(),
			std::ostream_iterator<int>(std::cout, ", "),
			device_1_command_queue_1
	);
	std::cout << "]" << std::endl;
	//]

	return 0;
}

/// TODO: Vector swap

