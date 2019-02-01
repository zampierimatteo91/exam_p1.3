#include <iostream>
#include <chrono>
#include <cstdlib>
#include <map>
#include "tree.h"
#include <thread>
#include <vector>
#include <thread>


int main(int, char const *argv[]) {

	using namespace std::chrono;

	// double time_try{};

	// auto start_try = high_resolution_clock::now();
	
	// // std::this_thread::sleep_for(std::chrono::seconds(2));

	// auto end_try = high_resolution_clock::now();

	// time_try = duration_cast<nanoseconds> (end_try - start_try).count();

	// std::cout << time_try << std::endl;

	// return 1;


    //std::this_thread::sleep_for(std::chrono::seconds(2));

	const std::size_t N_nodes = atoi(argv[1]);
	const std::size_t num_keys_to_find = N_nodes / 2;



	Tree<int,int> tree;
	std::map<int, int> map_tree;

	// Vectors for dummy computations
	std::vector<int> v1, v2, v3;

	srand(time(NULL));
	for( std::size_t i = 0; i < N_nodes; i++ ) {
		int k = rand()%N_nodes;
		tree.insert(k, k);
		map_tree.insert({k, k});
	}

	Tree<int,int> t2;
	tree.balance(tree.begin(), tree.size(), t2);

	double time_1{};
	double time_2{};
	double time_3{};

	// auto start = high_resolution_clock::now();
	srand(time(NULL));
	for( std::size_t i = 0;  i < num_keys_to_find; i++) {
		int k = rand()%N_nodes;
		auto n = t2.begin();
		auto m = map_tree.begin();
		auto l = tree.begin();
		
		auto start = high_resolution_clock::now();
		l = tree.find(k);
		auto end = high_resolution_clock::now();
		time_1 += duration_cast<nanoseconds> (end-start).count();

		if( l != tree.end() ) {
			v1.push_back((*l).second);
			//std::cout << (*l).second;
		}	
		
		auto start_balanced = high_resolution_clock::now();
		n = t2.find(k);
		auto end_balanced = high_resolution_clock::now();

		auto start_map = high_resolution_clock::now();
		m = map_tree.find(k);
		auto end_map = high_resolution_clock::now();
		
		time_2 += duration_cast<nanoseconds> (end_balanced-start_balanced).count();
		time_3 += duration_cast<nanoseconds> (end_map-start_map).count();

		if( n != t2.end() ){
			v2.push_back((*n).second);
			// std::cout << (*n).second;
		}

		if( m != map_tree.end() ){
			v3.push_back((*m).second);
			// std::cout << (*m).second;
		}
	}

	std::cout << N_nodes << "\t" << time_1/ num_keys_to_find << "\t"\
						<< time_2 / num_keys_to_find << "\t"\
						<< time_3 / num_keys_to_find << "\n";

	if( v1.size() != v2.size() || v1.size() != v3.size() || v2.size() != v3.size() ) {
		std::cout << "Error" << std::endl;
	}
	else 
	std::cout << v1.size() << std::endl;

	tree.clear();

	return 0;
}