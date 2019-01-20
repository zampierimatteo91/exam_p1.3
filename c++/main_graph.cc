#include <iostream>
#include "tree.h"

int main(){
  Tree<int,int> tree;
  //Initialization
  tree.insert(8,8);
  tree.insert(3,3);
  tree.insert(10,10);
  tree.insert(3,3);
  tree.insert(14,14);
  tree.insert(1,1);
  tree.insert(6,6);
  tree.insert(4,4);
  tree.insert(7,7);
  tree.insert(13,13);

  std::cout << "Begin value is: " << *tree.begin() << std::endl;
  int key = 4;
  std::cout << "Print with iterator: *tree.find(" << key << ") = " << *tree.find(key) << std::endl;
  std::cout << "Print with operator: tree[" << key << "] = " << tree[4] << std::endl; 
  std::cout << "Find of non-existing key returns end(): "
  	    << (bool{tree.find(5)==tree.end()} ? "true" : "false")
  	    << std::endl;
  std::cout << "Find of existing key returns end(): "
  	    << (bool{++tree.find(key)==tree.end()} ? "true" : "false")
  	    << std::endl;
  std::cout << "Print element example: " << *(++tree.find(key)) << std::endl;

  std::cout << "Print graph in (key:val) format:" << std::endl;
  std::cout << tree << std::endl;

  //Balance the tree
  Tree<int,int> tnew;
  tree.balance(tree.begin(), tree.size(), tnew);
  std::cout << "Size of the balanced tree: " << tnew.size() << std::endl;
  std::cout << "Root of the balanced tree: " << *tnew.head() << std::endl;
  std::cout << tnew << std::endl;


  //t2.copy_graph(tree.root.get()); //error!
  Tree<int,int> t2{tree}; //copy ctr
  //Tree<int,int> t2 = tree; //copy assignment
  //Tree<int,int> t2{std::move(tree)}; //move ctr
  //Tree<int,int> t2 = std::move(tree); //move assignment
  t2[4]=0;
  std::cout << "Copy tree in t2 and modify an element.\n"
	    << "New tree:\n" << t2 << std::endl;

  std::cout << "Original tree:" << std::endl;
  for(auto it=tree.cbegin(); it!=tree.cend(); ++it)
    std::cout << *it << " ";
  std::cout << std::endl;

  tree.self_balance();
  std::cout << "Size of the balanced tree: " << tree.size() << std::endl;
  std::cout << "Root of the balanced tree: " << *tree.head() << std::endl;
  std::cout << tree << std::endl;
  
  tree.clear();
  std::cout << "Size of tree after deletion: " << tree.size() << std::endl;

  return 0;
}
