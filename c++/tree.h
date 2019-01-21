#include <iostream>
#include <memory>
#include <cassert>
#include <algorithm>

//Create a function which stops you from defining Tkey as non-number

//----------------TREE CLASS-------------------------------
template <class Tkey, class Tval>
class Tree {
  std::size_t _size{0};
  
  struct Node {
    std::pair<Tkey,Tval> _leaf;
    std::unique_ptr<Node> _next[2];
    Node* _parent;

  Node(const std::pair<Tkey,Tval>& leaf, Node* par)
  : _leaf{leaf}, _parent{par} {
  }

    ~Node() = default;
    //~Node() { std::cout << "Ciao " << _leaf.first << std::endl;} //to check deallocation

    //find the next key
    Node* plus();
  };
  
  std::unique_ptr<Node> root;

  //Stop when you find key or when you find an empty slot
  Node* _find(const Tkey& key){
    Node* ptr = root.get();
    while(key!=ptr->_leaf.first && ptr->_next[bool{key>ptr->_leaf.first}].get() )
      ptr = ptr->_next[bool{key>ptr->_leaf.first}].get();
    return ptr;
  }

  //initialize graph
  //copying from another (sub-)graph
  //whose (local-)root is 'loc_root'
  void copy_graph( const Node* loc_root );

  //Find the extrema of the graph
  Node* _extremum(bool b) const {
    Node* ptr = root.get();
    while( ptr->_next[b] )
      ptr = ptr->_next[b].get();
    if(b) ptr = ptr->_next[b].get();
    return ptr;
  }

 public:  
  Tree() = default;

  void insert(const Tkey& key, const Tval& val);
  std::size_t size(){return _size;}

  class Iterator;
  class ConstIterator;
  
  Iterator head() { return Iterator{root.get()}; }
  Iterator begin() { return Iterator{_extremum(0)}; }
  Iterator end() { return Iterator{_extremum(1)}; }

  ConstIterator head() const { return ConstIterator{root.get()}; }
  ConstIterator begin() const { return ConstIterator{_extremum(0)}; }
  ConstIterator end() const { return ConstIterator{_extremum(1)}; }
  
  ConstIterator cbegin() const { return ConstIterator{_extremum(0)}; }
  ConstIterator cend() const { return ConstIterator{_extremum(1)}; }
  ConstIterator cbegin() { return ConstIterator{_extremum(0)}; }
  ConstIterator cend() { return ConstIterator{_extremum(1)}; }
  
  Iterator find(const Tkey& key){
    Node* ptr = _find(key);
    if(key!=ptr->_leaf.first) return end();
    return Iterator{ptr};
  }
  
  void balance(const Iterator& loc_begin, const std::size_t loc_size, Tree<Tkey,Tval>& t);
  void self_balance(){
    Tree<Tkey,Tval> tmp;
    balance(begin(), size(), tmp);
    *this = tmp;
    tmp.clear();
  }

  void clear(){ root.reset(); _size = 0; }

  //[] non-const version
  Tval& operator[](const Tkey& key){
    Node* ptr = _find(key);
    if(key == ptr->_leaf.first)
      return ptr->_leaf.second;
    //else allocate node with value = default
    ptr->_next[bool{key>(ptr->_leaf.first)}].reset(new Node{std::pair<Tkey,Tval>{key,Tval{}},ptr});
    _size++;
    return (ptr->_next[bool{key>(ptr->_leaf.first)}].get())->_leaf.second;
  }

  //[] const version
  const Tval& operator[] (const Tkey& key) const {
    Node* ptr = _find(key);
    if(key == ptr->_leaf.first)
      return ptr->_leaf.second;
    return end();
  }
  
  //COPY & MOVE SEMANTICS
  Tree( const Tree& t ){ copy_graph(t.root.get()); } //copy ctr

  Tree& operator=(const Tree& t){ //copy assignment
    clear();
    auto tmp = t;
    (*this) = std::move(tmp);
    return *this;
  }

  Tree(Tree&& t) noexcept //move ctr
    : _size{std::move(t._size)}, root{std::move(t.root)} {}

  Tree& operator=(Tree&& t) noexcept{ //move assignment
    _size = std::move(t._size);
    root = std::move(t.root);
    return *this;
  }

};

//------------CLASS ITERATOR-----------------
template <class Tkey, class Tval>
	class Tree<Tkey,Tval>::Iterator{

	using Node = Tree<Tkey,Tval>::Node;
	Node *current;

 public:
	Iterator(Node* n): current{n} {}
	
	std::pair<Tkey,Tval> operator*() const {
		return std::pair<Tkey,Tval>{ current->_leaf.first,current->_leaf.second };
	}

	Iterator& operator++() {
		current = current->plus();
		return *this;
	}
	
	bool operator==(const Iterator& other) { return current == other.current; }
	bool operator!=(const Iterator& other) { return !(*this == other); }
};

template <class Tkey, class Tval>
class Tree<Tkey, Tval>::ConstIterator : public Tree<Tkey, Tval>::Iterator {
 public:
	using parent = Tree<Tkey,Tval>::Iterator;
	using parent::Iterator;
	const std::pair<Tkey,Tval> operator*() const { return parent::operator*(); }
};

//----------------NODE PLUS-------------
template <class Tkey, class Tval>
  class Tree<Tkey,Tval>::Node* Tree<Tkey,Tval>::Node::plus(){
  Node* tmp;
  if( _next[1].get() ){
    tmp = _next[1].get();
    while( tmp->_next[0].get() )
      tmp = tmp->_next[0].get();
    return tmp;
  }
  Tkey key = _leaf.first;
  tmp = _parent;
  while( tmp && key>(tmp->_leaf.first) )
    tmp = tmp->_parent;
  if( !tmp ) //this can happen IFF the root is the only node
    return _next[1].get();
  return tmp;
};

//--------------TREE INSERT--------------
template <class Tkey,class Tval>
  void Tree<Tkey,Tval>::insert(const Tkey& key, const Tval& val){
  if(root==nullptr){
    root.reset(new Node{std::pair<Tkey,Tval>{key,val},nullptr});
    _size++;
    return;
  }
  Node* ptr = _find(key);
  if(key!=(ptr->_leaf.first)){
     ptr->_next[bool{key>(ptr->_leaf.first)}].reset(new Node{std::pair<Tkey,Tval>{key,val},ptr});
    _size++;
  }
  else
    std::cout << "Warning: you tried to insert an already existing key! Val is not allocated." << std::endl;
}

//-------------------PRINT TREE-------------------
//auxiliary: print std::pair
template <class Tkey, class Tval>
std::ostream& operator<<(std::ostream& os, std::pair<Tkey,Tval> obj) {
	os << "(" << obj.first << ":" << obj.second << ")";
	return os;
};
//print tree
template <class Tkey, class Tval>
std::ostream& operator<<(std::ostream& os , const Tree<Tkey,Tval>& t){
  /* for(auto& it: t) */
  /*     os << it << " "; */
 for(auto it=t.begin(); it!=t.end(); ++it)
    std::cout << *it << " ";
 return os;
};

//--------------------BALANCE TREE----------------
//recursive
template <class Tkey, class Tval>
  void Tree<Tkey,Tval>::balance(const class Tree<Tkey,Tval>::Iterator& loc_begin, const std::size_t loc_size, Tree<Tkey,Tval>& t){

  if(loc_size==1)
    t.insert((*loc_begin).first,(*loc_begin).second);
  else{
    std::size_t median = loc_size/2 + 1;
    Iterator ptr = loc_begin;
    for(std::size_t i=1; i<median; i++) ++ptr;
    t.insert((*ptr).first,(*ptr).second);

    Iterator loc_begin_1 = loc_begin;
    std::size_t loc_size_1 = median -1;
    balance(loc_begin_1,loc_size_1,t);

    if(median != loc_size){
      Iterator loc_begin_2 = ++ptr;
      std::size_t loc_size_2 = median -2 + (loc_size % 2);
      balance(loc_begin_2, loc_size_2, t);
    }   
  }
};

//--------------COPY SEMANTICS------------------
//recursive
template <class Tkey, class Tval>
void Tree<Tkey,Tval>::copy_graph( const Tree<Tkey,Tval>::Node* loc_root ){
	if(loc_root){
		insert( loc_root->_leaf.first, loc_root->_leaf.second );
		if( loc_root->_next[0].get() )
		copy_graph( loc_root->_next[0].get() );
		if( loc_root->_next[1].get() )
			copy_graph( loc_root->_next[1].get() );
	}
};
