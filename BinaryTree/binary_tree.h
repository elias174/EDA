#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <iostream>
#include "node.h"
#include "function_object.h"
#include <time.h>
#include <stdlib.h>
#include <fstream>
#include <string>

using namespace std;

template <typename T>
struct TraitLess{
  typedef T DataType;
  typedef Less<DataType> cmp_Type;
};

template <typename T>
struct TraitGreatest{
  typedef T DataType;
  typedef Greatest<DataType> cmp_Type;
};

template <typename Tr>
class BinaryTree
{
 private:
  typedef typename Tr::DataType T;
  typedef typename Tr::cmp_Type C;
  C cmp_;
 public:
  Node<T>* root_;
  BinaryTree();
  ~BinaryTree();
  bool find(T /*n*/, Node<T>** &/*p_ */);
  bool insert(T /*n*/);
  bool remove(T /*n*/);
  void liberate_memory(Node<T>* /*p*/);
  void print_inorder(Node<T>* /*p*/);
  void inorder_to_string(Node<T>* /*p*/, string &/*ret*/);
  void print_tree_in_png(string /*filename_*/);
  void rotation_simple(Node<T> **&/*p_*/, bool /*left*/);
  Node<T>** get_replace(Node<T>**/*p*/);
  void to_linked_list(Node<T> *tmp);
  string string_to_export_in_dot();
};

template <typename Tr>
BinaryTree<Tr>::BinaryTree()
{
  this->root_ = 0;
}

template <typename Tr>
void BinaryTree<Tr>::liberate_memory(Node<T> *p){
  if(!p)return;
  liberate_memory(p->b_leaf_[0]);
  delete p;
  liberate_memory(p->b_leaf_[1]);
}


template <typename Tr>
void BinaryTree<Tr>::to_linked_list(Node<T>* tmp){
  Node<T>* N = tmp;
  Node<T>* leaf_zero = (N)->b_leaf_[0];
  Node<T>* leaf_one = (N)->b_leaf_[1];
//  if (!!(*N)->b_leaf_[0] && !!(*N)->b_leaf_[1]){
  if ( !!(N)->b_leaf_[0] && !!(N)->b_leaf_[1] ){
      to_linked_list(leaf_one);
      to_linked_list(leaf_zero);
      Node<T>* prev = NULL;
      Node<T>* current = N->b_leaf_[1];
      while(current){
          prev = current;
          current = current->b_leaf_[1];
      }
      prev->b_leaf_[1] = N->b_leaf_[0];
      N->b_leaf_[0] = NULL;
  }
  return;
}

template <typename Tr>
void BinaryTree<Tr>::rotation_simple(Node<T>** &p_, bool pos){
  Node<T>* N = *p_;
  *p_ = (*p_)->b_leaf_[pos];
  if( (*p_)->b_leaf_[!pos] ){
    N->b_leaf_[pos] = (*p_)->b_leaf_[!pos];
  }
  else{
    N->b_leaf_[pos] = NULL;
  }
  (*p_)->b_leaf_[!pos] = N;
  N = NULL;
}

template <typename Tr>
BinaryTree<Tr>::~BinaryTree(){
  Node<T>* p = this->root_;
  this->liberate_memory(p);
}

template <typename Tr>
bool BinaryTree<Tr>::find(T n, Node<T>** &p)
{
  p=& root_;
  while (*p) {
    if ((*p)->b_data_==n) {
      return 1;
    }
    p=&(*p)->b_leaf_[cmp_((*p)->b_data_,n)];
  }
  return 0;
}

template<typename Tr>
Node<typename Tr::DataType>** BinaryTree<Tr>::get_replace(Node<T>** p_){
  srand(time(NULL) );
  bool change_ = rand()%2;
  Node<T>** temp_ = &(*p_)->b_leaf_[change_];
  while ( (*temp_)->b_leaf_[!change_] )
      temp_ = &(*temp_)->b_leaf_[!change_];
  return temp_;
}

template<typename Tr>
bool BinaryTree<Tr>::remove(T n){
  /* To remove elements from a tree
   * we have 3 cases
   * when the node does not have leaf (Case 0)
   * when the node does not have 1 leaf (Case 1)
   * and when the node have the 2 leafs (Case 2)
  */
  Node<T>** p;
  Node<T>** q;
  if(!find(n,p)) return 0;
  bool left = !!(*p)->b_leaf_[0];
  bool right = !!(*p)->b_leaf_[1];
  //Case 2
  if(left & right){
    q = get_replace(p);
    (*p)->b_data_ = (*q)->b_data_;
    p = q;
    left = !!(*p)->b_leaf_[0];
    right = !!(*p)->b_leaf_[1];
  }
  //Case 1
  if(left | right){
    Node<T>* t = *p;
    *p = (*p)->b_leaf_[right];
    delete t;
    return 1;
  }
  else{
    //Otherwise Case 0
    delete *p;
    *p = 0;
    return 1;
  }
}


template <typename Tr>
bool BinaryTree<Tr>::insert(T n){
  Node<T>** p;
  if( find(n,p) ) return 0;
  //Node<T>* q = new Node<T>(n);
  (*p) = new Node<T>(n);
  return 1;
}

template <typename Tr>
void BinaryTree<Tr>::print_inorder(Node<T>* p){
  if(!p){
    return;
  }
  print_inorder(p->b_leaf_[0]);
  cout << p->b_data_ << endl;
  print_inorder(p->b_leaf_[1]);

}

template <typename Tr>
void BinaryTree<Tr>::inorder_to_string(Node<T>* p,string &ret){
  if(!p){
    return;
  }
  inorder_to_string(p->b_leaf_[0],ret);
  if(p->getNodeInfo()!=""){
    ret += p->getNodeInfo();
    ret += '\n';
  }
  inorder_to_string(p->b_leaf_[1],ret);

}

template <typename Tr>
string BinaryTree<Tr>::string_to_export_in_dot(){
    string ret;
    ret += "digraph treeBinary {";
    ret += '\n';
    ret += "node [color=lightblue2, style=filled];";
    ret += '\n';
    string tmp;
    inorder_to_string(this->root_,tmp);
    ret += tmp;
    ret += '\n';
    ret += "}";
    return ret;
}

template <typename Tr>
void BinaryTree<Tr>::print_tree_in_png(string filename_){
  string extDot= filename_+".dot";
  string extPNG = filename_+".dot";
  string genDot = "dot -Tpng "+filename_+".dot > "+filename_+".png";
  string seePNG = "gwenview "+filename_+".png";
  ofstream out(extDot.c_str());
  //in the function tree.string_to_export_in_dot is the magic
  out << this->string_to_export_in_dot();
  out.close();
  //its time to generate the png
  system(genDot.c_str());
  //this is optional, if you dont like, only remove
  system(seePNG.c_str());

}




#endif // BINARY_TREE_H
