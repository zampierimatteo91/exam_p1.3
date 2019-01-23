#include <iostream>
#include <chrono>
#include <cstdlib>
#include <map>
#include "tree.h"
#include <thread>
#include <vector>


int main(int, char const *argv[]) {

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
	//Initialization
	/*tree.insert(8,8);
	tree.insert(3,3);
	tree.insert(10,10);
	tree.insert(3,3);
	tree.insert(14,14);
	tree.insert(1,1);
	tree.insert(6,6);
	tree.insert(4,4);
	tree.insert(7,7);
	tree.insert(13,13);*/

	//std::cout << "Begin value is: " << *tree.begin() << std::endl;

	//int key = 669;

	//std::cout << "Elapsed times for finding a key.\n";
	
	//std::cout << "Elapsed time before balancing: " << time_1.count() / num_keys_to_find << "s\n";
	/*std::cout << "\n\nPrint with iterator: *tree.find(" << key << ") = " << *tree.find(key) << std::endl;
	std::cout << "\n\nPrint with operator: tree[" << key << "] = " << tree[669] << std::endl; 
	
	std::cout << "\n\nFind of non-existing key returns end(): "
				<< (bool{tree.find(5)==tree.end()} ? "true" : "false")
				<< std::endl;
	
	std::cout << "\n\nFind of existing key returns end(): "
				<< (bool{++tree.find(key)==tree.end()} ? "true" : "false")
				<< std::endl;*/
	
	/*std::cout << "\n\nPrint element example: " << *(++tree.find(key)) << std::endl;

	std::cout << "\n\nPrint graph in (key:val) format:" << std::endl;
	std::cout << tree << std::endl;*/

	Tree<int,int> t2;
	tree.balance(tree.begin(), tree.size(), t2);
	
	std::chrono::duration<double> time_1{};
	std::chrono::duration<double> time_2{};
	std::chrono::duration<double> time_3{};

	srand(time(NULL));
	for( std::size_t i = 0;  i < num_keys_to_find; i++) {
		int k = rand()%N_nodes;
		auto n = t2.begin();
		auto m = map_tree.begin();
		auto l = tree.begin();
		
		auto start = std::chrono::system_clock::now();
			l = tree.find(k);
		auto end = std::chrono::system_clock::now();
		time_1 += end-start;

		if( l != tree.end() ) {
			v1.push_back((*l).second);
			std::cout << (*l).second;
		}	
		
		auto start_balanced = std::chrono::system_clock::now();
		n = t2.find(k);
		auto end_balanced = std::chrono::system_clock::now();

		auto start_map = std::chrono::system_clock::now();
		m = map_tree.find(k);
		auto end_map = std::chrono::system_clock::now();
		
		time_2 += end_balanced-start_balanced;
		time_3 += end_map-start_map;

		if( n != t2.end() ){
			v2.push_back((*n).second);
			std::cout << (*n).second;
		}

		if( n != t2.end() ){
			v3.push_back((*m).second);
			std::cout << (*m).second;
		}
	}

	/*std::cout << "Elapsed time after self-balancing: " << elapsed_seconds_balanced.count() / num_keys_to_find << "s\n";
	std::cout << "Elapsed time with std::map: " << elapsed_seconds_map.count() / num_keys_to_find << "s\n";*/

	std::cout << N_nodes << "\t" << time_1.count()*1e+6/ num_keys_to_find << "\t"\
						<< (time_2.count()*1e+6 / num_keys_to_find) << "\t"\
						<< (time_3.count()*1e+6 / num_keys_to_find) << "\n";

	//std::cout << N_nodes << *tree.head() << "\t" << *tree.begin() << "\t" << tree.size() << "\t" << comp_tree.size() << std::endl;

	if( v1.size() != v2.size() || v1.size() != v3.size() || v2.size() != v3.size() ) {
		std::cout << "Error" << std::endl;
	}
	/*std::cout << "\n\nSize of the balanced tree: " << tree.size() << std::endl;*/
	/*std::cout << "\n\nRoot of the balanced tree: " << *tree.head() << std::endl;
	std::cout << tree << std::endl;*/

	tree.clear();
	/*std::cout << "\n\nSize of tree after deletion: " << tree.size() << std::endl;*/

	/*std::chrono::duration<double> elapsed_seconds_map;
	for( std::size_t i = 0;  i < num_keys_to_find; i++) {
		int k = rand()%1000;
		
		auto start_map = std::chrono::system_clock::now();
		comp_tree.find(k);
		auto end_map = std::chrono::system_clock::now();
				
		elapsed_seconds_map += end_map-start_map;
	}

	std::cout << "Elapsed time with std::map: " << elapsed_seconds_map.count() / num_keys_to_find << "s\n";*/

	return 0;
}