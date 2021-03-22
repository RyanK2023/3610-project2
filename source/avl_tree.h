/*
  Name: Ryan Kilkenney
  Date: 10/1/2020
  Purpose: It's the .h file needed to make an AVL Tree
*/

#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <cstddef>

using namespace std;

struct BinaryNode {
  //constructor for the BinaryNode struct
  BinaryNode(const int key) : key(key), left(NULL), right(NULL), height(0) {}

  //deconstructor for the BinaryNode struct
  ~BinaryNode() {
    delete left;
    delete right;
    left = right = NULL;
  }

  int key; //the key data for the struct
  int height; //the node's space in the tree
  int bfactor;//balance factor for the node
  BinaryNode *left, *right;//pointers to the left and right nodes 
};

class AVLTree {

public:
  //constructor for the AVLTree class
  AVLTree() : root(NULL) {}
  ~AVLTree() { 
    delete root;
  }

  //this insert function takes in a int, makes it into a node, and submits it to the second insert function
  void insert(const int key);

  //this delete function takes in an int, makes it into a node, and submits it to the second delete function
  void deleteNode(const int key);

  //this function takes in a char, and determines the next print function to use 
  void print(const char c);

private:
  //this is the second insert, it takes in a node, finds its space in the tree, inserts it, and rebalances the tree
  //uses code from the text book
  void insert(BinaryNode* node, BinaryNode* &root, bool& isTaller);

  //this is the second delete, it finds the node in the tree, deletes it, and rebalances the tree
  //uses some code from the source in READEME.txt
  BinaryNode* deleteNode(const int key, BinaryNode* &root);

  //this returns the height of a node
  int setHeight(BinaryNode* root);

  //this balances the tree after inserting a node
  //code is used from the textbook
  BinaryNode* balanceLeft(BinaryNode* &root);

  //this balances the tree after inserting a node
  //code is used from the textbook
  BinaryNode* balanceRight(BinaryNode* &root);

  //this rotates the tree after inserting a node
  //code is used from the textbook
  BinaryNode* rotateLeft(BinaryNode* root, char c);

  //this rotates the tree after inserting a node
  //code is used from the textbook
  BinaryNode* rotateRight(BinaryNode* root, char c);

  //this prints out all of the key values of each node
  void pprint(BinaryNode* node) const;

  //this prints out the heights of each node
  void hprint(BinaryNode* root);
  
  //finds the max of two numbers, used to find the height of a node
  int findMax(int a, int b);

  BinaryNode* root; //the top value in the AVL Tree
};

#endif
