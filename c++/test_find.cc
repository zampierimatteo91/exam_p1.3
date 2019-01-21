#include <iostream>
#include <chrono>
#include <cstdlib>
#include <map>
#include "tree.h"
#include <thread>

int main(int, char const *argv[]) {

	const std::size_t N_nodes = atoi(argv[1]);
	const std::size_t num_keys_to_find = N_nodes / 2;

	Tree<int,int> tree;
	std::map<int, int> comp_tree;

	srand(time(NULL));
	for( std::size_t i = 0; i < N_nodes; i++ ) {
		int k = rand()%N_nodes;
		tree.insert(k, k);
		comp_tree.insert({k, k});
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

	std::chrono::duration<double> elapsed_seconds{};
	std::cout << elapsed_seconds.count() << "\n";
	for( std::size_t i = 0;  i < num_keys_to_find; i++) {
		int k = rand()%N_nodes;
		
		auto start = std::chrono::system_clock::now();
				tree.find(k);
		auto end = std::chrono::system_clock::now();
		elapsed_seconds += end-start;
		
	}

	//std::cout << "Elapsed time before balancing: " << elapsed_seconds.count() / num_keys_to_find << "s\n";
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

	//Balance the tree
	Tree<int,int> tnew;
	tree.balance(tree.begin(), tree.size(), tnew);
	/*std::cout << "\n\nSize of the balanced tree: " << tnew.size() << std::endl;
	std::cout << "\n\nRoot of the balanced tree: " << *tnew.head() << std::endl;
	std::cout << tnew << std::endl;*/

	//t2.copy_graph(tree.root.get()); //error!
	//Tree<int,int> t2{tree}; //copy ctr
	//Tree<int,int> t2 = tree; //copy assignment
	//Tree<int,int> t2{std::move(tree)}; //move ctr
	//Tree<int,int> t2 = std::move(tree); //move assignment
	//t2[4]=0;
	/*std::cout << "\n\nCopy tree in t2 and modify an element.\n"
			<< "\nNew tree:\n\n" << t2 << std::endl;

	std::cout << "\n\nOriginal tree:" << std::endl;
	for(auto it=tree.cbegin(); it!=tree.cend(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;*/

	Tree<int,int> t2;
	tree.balance(tree.begin(), tree.size(), t2);

	std::chrono::duration<double> elapsed_seconds_balanced{};
	std::chrono::duration<double> elapsed_seconds_map{};

	srand(time(NULL));
	for( std::size_t i = 0;  i < num_keys_to_find; i++) {
		int k = rand()%N_nodes;
		
		auto start_balanced = std::chrono::system_clock::now();
		t2.find(k);
		auto end_balanced = std::chrono::system_clock::now();

		auto start_map = std::chrono::system_clock::now();
		comp_tree.find(k);
		auto end_map = std::chrono::system_clock::now();
		
		elapsed_seconds_balanced += end_balanced-start_balanced;
		elapsed_seconds_map += end_map-start_map;
	}

	/*std::cout << "Elapsed time after self-balancing: " << elapsed_seconds_balanced.count() / num_keys_to_find << "s\n";
	std::cout << "Elapsed time with std::map: " << elapsed_seconds_map.count() / num_keys_to_find << "s\n";*/

	std::cout << N_nodes << "\t" << elapsed_seconds.count()*1e+6/ num_keys_to_find << "\t"\
						<< (elapsed_seconds_balanced.count()*1e+6 / num_keys_to_find) << "\t"\
						<< (elapsed_seconds_map.count()*1e+6 / num_keys_to_find) << "\n";

	//std::cout << N_nodes << *tree.head() << "\t" << *tree.begin() << "\t" << tree.size() << "\t" << comp_tree.size() << std::endl;


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