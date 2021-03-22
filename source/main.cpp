/*
  Name: Ryan Kilkenney
  Date: 10/1/2020
  Purpose: It's the main file needed to make and run an AVL Tree
*/

#include <iostream>
#include "avl_tree.h"
using namespace std;

int main(int argc, char** argv) {

  AVLTree tree;

  char option;
  int key;

  do {
    cin >> option;
    switch(option) {
      case 'i':
        cin >> key;
        tree.insert(key);
        break;
      case 'r':
        cin >> key;
          tree.deleteNode(key);
        break;
      case 'h':
        tree.print('h');
        break;
      case 'p':
        tree.print('p');
        break;
      default:
        break;
    }
  } while(option != 'q');
}
