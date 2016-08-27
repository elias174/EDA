#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

//macro to cast for a string
#define SSTR( x ) dynamic_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()

template <class T>
class Node{
 public:
  Node(T data_){
    this->b_data_ = data_;
    this->b_leaf_[0] = NULL;
    this->b_leaf_[1] = NULL;
  }
  Node(){
    this->b_leaf_[0] = NULL;
    this->b_leaf_[1] = NULL;
  }
  T b_data_;
  Node<T>*b_leaf_[2];
  string getNodeInfo(){
    string ret;
    if( !(this->b_leaf_[0]) && !(this->b_leaf_[1])){
      return "";
    }
    else{
      if( !(this->b_leaf_[0]) ){
        ret += SSTR(this->b_data_);
        ret += "->";
        ret += SSTR(this->b_leaf_[1]->b_data_);
      }
      else if( !(this->b_leaf_[1]) ){
        ret += SSTR(this->b_data_);
        ret += "->";
        ret += SSTR(this->b_leaf_[0]->b_data_);
      }
      else{
        ret += SSTR(this->b_data_);
        ret += "->";
        ret += SSTR(this->b_leaf_[0]->b_data_);
        ret += '\n';
        ret += SSTR(this->b_data_);
        ret += "->";
        ret += SSTR(this->b_leaf_[1]->b_data_);
      }
    }
    return ret;
  }

};


#endif // NODE_H
