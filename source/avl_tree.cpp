/*
  Name: Ryan Kilkenney
  Date: 10/1/2020
  Purpose: It's the .ccp file needed to make an AVL Tree
*/

#include <iostream>
#include "avl_tree.h"

void AVLTree::insert(const int key) {
  //all of this creates the node and submits it to the next insert function
  bool isTaller = false;
  BinaryNode *node = new BinaryNode(0);
  node->key = key;
  node->height = 0;
  node->bfactor = 0;
  node->left = NULL;
  node->right = NULL;

  insert(node, root, isTaller);
}

void AVLTree::insert(BinaryNode* node, BinaryNode* &root, bool& isTaller) {

  //checks if this is the first node being submitted 
  if (root == NULL) {
    root = node;
    isTaller = true;
  }
  //this runs if the the key value is already in the tree
  else if(root->key == node->key) {
    cout << "No duplicates allowed" << endl;
  } //this runs if the key value needs to be placed left of the root value 
  else if(root->key > node->key) {
    insert(node, root->left, isTaller);

    //checks if the tree needs to be rebalanced
    if(isTaller) {
      switch(root->bfactor) {
        case -1:
          balanceLeft(root);
          isTaller = false;
          break;
        case 0:
          root->bfactor = -1;
          isTaller = true;
          break;
        case 1:
          root->bfactor = 0;
          isTaller = false;
      }
    }
  }
  else { //this runs if the key value needs to be placed right of the root value
    insert(node, root->right, isTaller);

    //checks if the tree needs to be rebalanced
    if(isTaller) {
      switch(root->bfactor) {
        case -1:
          root->bfactor = 0;
          isTaller = false;
          break;
        case 0:
          root->bfactor = 1;
          isTaller = true;
          break;
        case 1:
          balanceRight(root);
          isTaller = false;
      }
    }
  } 
  //finds the height of the root node
  root->height = 1+findMax(setHeight(root->left), setHeight(root->right));
}

int AVLTree::setHeight(BinaryNode* root) {
  //this just returns the height of a node
  if(root == NULL)
    return 0;

  return root->height;
}

int AVLTree::findMax(int a, int b){
  //just finds the max between two numbers
  if(a >= b)
    return a;
  else
    return b;
}

void AVLTree::print(const char c) {
  //checks the value of c to pick which print function to run
  if(c == 'p') {
    pprint(root);
    cout << endl;
  } else if (c == 'h') {
    hprint(root);
    cout << endl;
  }

}

void AVLTree::pprint(BinaryNode* node) const {  
  //prints all key values using inorder traversal
  if (node != NULL) {
    pprint(node->left);
    cout << node->key << " ";
    pprint(node->right);
  }
}

void AVLTree::hprint(BinaryNode* root) {
  //prints all heights and also rechecks the height values using inorder traversal
  if (root != NULL) {
    hprint(root->left);
    root->height = 1+findMax(setHeight(root->left), setHeight(root->right));
    cout << root->height << " ";
    hprint(root->right);
  }
}

BinaryNode* AVLTree::balanceLeft(BinaryNode* &root) {
  //this code is from the textbook
  //this code rebalances the tree after insertion 
  BinaryNode *p;
  BinaryNode *w;

  p = root->left;

  switch (p->bfactor)
  {
  case -1:
    root->bfactor = 0;
    p->bfactor = 0;
    return rotateRight(root, 'i');
    break;

  case 0:
    cout << "Can't balance from left" << endl;
    break;

  case 1:
    w = p->right;
    switch (w->bfactor)
    {
    case -1:
      root->bfactor = 1;
      p->bfactor = -1;
      break;
    
    case 0:
      root->bfactor = 0;
      p->bfactor = 0;
      break;

    case 1:
      root->bfactor = 0;
      p->bfactor = -1;
    }
  
  w->bfactor = 0;
  rotateLeft(p, 'i');
  root->left = p;
  return rotateRight(root, 'i');
  
  }
  return root;
}

BinaryNode* AVLTree::balanceRight(BinaryNode* &root) {
  //this code is from the textbook
  //this code rebalances the tree after insertion 
  BinaryNode *p;
  BinaryNode *w;

  p = root->right;
  switch (p->bfactor)
  {
  case -1:
    w = p->left;
    switch (w->bfactor)
    {
    case -1:
      root->bfactor = 0;
      p->bfactor = 1;
      break;
    
    case 0:
      root->bfactor = 0;
      p->bfactor = 0;
      break;

    case 1:
      root->bfactor = -1;
      p->bfactor = 0;
    }

    w->bfactor = 0;
    rotateRight(p, 'i');
    root->right = p;
    return rotateLeft(root, 'i');
    break;

    case 0:
      cout << "Can't balance from left" << endl;
      break;
    
    case 1:
      root->bfactor = 0;
      p->bfactor = 0;
      return rotateLeft(root, 'i');
  }
  return root;
}

BinaryNode* AVLTree::rotateLeft(BinaryNode* root, char c) {
  BinaryNode *p;
  BinaryNode *w;
  
  if(c == 'i') {
    if (root == NULL) {
      cout << "Error in tree" << endl;
    } else if (root->right == NULL) {
      cout << "Error in tree" << endl;
      cout << "No right subtree to rotate" << endl;
    } else {
      p = root->right;
      root->right = p->left;

      p->left = root;
      root = p;
      return p;
    }
  } else {
      p = root->right;  
      w = p->left;  
    
      p->left = root;  
      root->right = w;  
    
      root->height = findMax(setHeight(root->left), setHeight(root->right)) + 1;  
      p->height = findMax(setHeight(p->left), setHeight(p->right)) + 1;  
  
      return p; 
  }
  return root;
}

BinaryNode* AVLTree::rotateRight(BinaryNode* root, char c) {
  BinaryNode *p;
  BinaryNode *w;

  if(c == 'i') {
      if(root == NULL) {
      cout << "Error in tree" << endl;
      } else if(root->left == NULL) {
        cout << "Error in tree" << endl;
        cout << "No left subtree to rotate" << endl;
        } else {
          p = root->left;
          root->left = p->right;

          p->right = root;
          root = p;
          return p;
    }
  } else {
    p = root->left;  
    w = p->right;  
  
    p->right = root;  
    root->left = w;  
  
    root->height = findMax(setHeight(root->left), setHeight(root->right)) + 1;  
    p->height = findMax(setHeight(p->left), setHeight(p->right)) + 1;  
 
    return p;  
  }
  return root;
}

void AVLTree::deleteNode(const int key) {
  //this takes in input and resubmits it to the second delete function 
  root = deleteNode(key, root);
  root->height = root->height-1;
}

BinaryNode* AVLTree::deleteNode(const int key, BinaryNode* &root) {
  if(root == NULL) {
    return root;
  }

  //this searches the tree and finds the node that needs to be deleted 
  if (key < root->key) {
    deleteNode(key, root->left);
  } else if(key > root->key) {
    deleteNode(key, root->right);
  } else {
    //case 1/2/3
    //if the node that needs to be deleted has one or no children, run this 
    if((root->left == NULL) || (root->right == NULL)) {  
      BinaryNode *temp = root->left ? root->left : root->right;  

        //if the node has no children run this and delete the node 
        if (temp == NULL) {  
          temp = root;  
          root = NULL;  
        } else 
          *root = *temp; 
                            
          free(temp); 
  } else {
    //case 4
    //if node has two children, run this by finding the correct sucessor and deleting the node/replacing it with the sucessor 
    BinaryNode* temp = root->right;

    while (temp->left != NULL) {
      temp = temp->left;
    }

    root->key = temp->key;

    root->right = deleteNode(temp->key, root->right);
    
  }
    } 

  if (root == NULL) {
    return root; 
  }
  
  //find the bf of the root
  root->bfactor = setHeight(root->left) - setHeight(root->right);

  //checks if the tree needs to be rebalanced
  if(root->bfactor > 1) {
    int temp = setHeight(root->left->left) - setHeight(root->left->right);

    if (temp >= 0) {
      return rotateRight(root,'d');
    } else {
      root->left = rotateLeft(root->left, 'd');
      return rotateRight(root,'d');
    }
  }

  if(root->bfactor < -1) {
    int temp = setHeight(root->right->left) - setHeight(root->right->right);

    if(temp <= 0) {
      return rotateLeft(root, 'd');
    } else {
        root->right = rotateRight(root->right, 'd');
        return rotateLeft(root, 'd');
    }
  }
  return root;
}

