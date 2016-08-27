#include <iostream>
#include "binary_tree.h"
#include "test_tree_binary.h"
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
  BinaryTree< TraitGreatest<int> > tree;
  tree.insert(6);
  tree.insert(10);
  tree.insert(2);
  tree.insert(1);
  tree.insert(5);
  tree.insert(11);
  tree.insert(9);

  Node<int> *head = tree.root_;
  tree.to_linked_list(head);
  tree.print_tree_in_png("outputDAC");


  TestBinaryTree a;
  a.run_tests();

  return 0;
}

