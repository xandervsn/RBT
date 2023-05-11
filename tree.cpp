#include "tree.h"

int tree::find(int input, node* &current, int& tester){
  if(input == current->data || tester > 0){
    cout << tester << endl;
    tester++;
    return tester;
  }
  if(input < current->data){
    //less, left
    if(current->left->data != 0){
      find(input, current->left, tester);
    }
  }else if(input > current->data){
    //high, right
    if(current->right->data != 0){
      find(input, current->right, tester);
    }
  }
  if(current->left->data != 0 && current->right->data != 0){
    cout << tester << endl;
    return tester;
  }
  return tester;
}

void tree::checkadd(node* current, node*& root) {
  node* parent = NULL;
  node* grandparent = NULL;
  node* uncle = NULL;
  if (current->parent != NULL) {
    parent = current->parent;
    if (parent->parent != NULL) {
      grandparent = parent->parent;
      if (grandparent->left == parent) {
    	uncle = grandparent->right;
      } else if (grandparent->right == parent) {
    	uncle = grandparent->left;
      }
    }
  }
  //case 1a
  if(current == root) {
    current->isred = false;
    return;
  }
  //case 1b
  else if(parent != NULL && !parent->isred) {
    return;
  }
  //triangle case
  else if(uncle != NULL && parent->isred && uncle->isred) {
    parent->isred = false;
    uncle->isred = false;
    grandparent->isred = true;
    checkadd(grandparent, root);
  }
  //triangle case 2
  else if(uncle == NULL || !uncle->isred) {
    //case 2a
    if(parent == grandparent->right && current == parent->left) {
      grandparent->right = current;
      current->parent = grandparent;
      node *temp = current->right;
      current->right = parent;
      parent->parent = current;
      if(temp != NULL){
    	temp->parent = parent;
      }
      parent->left = temp;
      parent = current;
      current = parent->right;
      current->parent = parent;
    }else if(parent == grandparent->left && current == parent->right) {
      //cast 2b
      grandparent->left = current;
      current->parent = grandparent;
      node *temp = current->left;
      current->left = parent;
      parent->parent = current;
      if(temp != NULL) {
    	temp->parent = parent;
      }
      parent->right = temp;
      parent = current;
      current = parent->left;
      current->parent = parent;
    }
    if(parent->isred && current->isred) {
      //line case
      node* greatgrandparent = NULL;
      if(grandparent->left == parent && parent->left == current) {
	//case 3a
	node* temp = parent->right;
    	parent->right = grandparent;
    	if(grandparent != root){
	  greatgrandparent = grandparent->parent;
	  if(greatgrandparent->left == grandparent) {
	    greatgrandparent->left = parent;
	  }else{
	    greatgrandparent->right = parent;
	  }
	  parent->parent = greatgrandparent;
    	}else{
	  parent->parent = NULL;
	  root = parent;
    	}
    	grandparent->parent = parent;
    	if(temp != NULL) {
	  temp->parent = grandparent;
    	}
    	grandparent->left = temp;
    	parent->isred = false;
    	grandparent->isred = true;
      }else if(grandparent->right == parent && parent->right == current) {
	//case 3b
	node* temp = parent->left;
    	parent->left = grandparent;
    	if(grandparent != root) {
	  greatgrandparent = grandparent->parent;
	  if(greatgrandparent->left == grandparent) {
	    greatgrandparent->left = parent;
	  }else{
	    greatgrandparent->right = parent;
	  }
	  parent->parent = greatgrandparent;
    	}else{
	  parent->parent = NULL;
	  root = parent;
    	}
    	grandparent->parent = parent;
    	if(temp != NULL){
	  temp->parent = grandparent;
    	}
    	grandparent->right = temp;
    	parent->isred = false;
    	grandparent->isred = true;
      }
    }
  }
}

void tree::add(node* current, node* n, int input, node*& root) { //bst add
  if(current->right != NULL && input > current->data) {
    add(current->right, n, input, root);
  }else if (current->left != NULL && input <= current->data) {
    add(current->left, n, input, root);
  } else {
    if (input > current->data) {
      n->parent = current;
      current->right = n;
      checkadd(current->right, root);
    }
    if (input <= current->data) {
      n->parent = current;
      current->left = n;
      checkadd(current->left, root);
    }
  }
}

void tree::display(node* root, int buffer){
  //buffer is the space between nodes when printed out
  //some of this is taken from the final practice display functions
  if(root == NULL){
    return;
  }
  buffer += 5;
  display(root->right, buffer);
  cout << endl;
  for (int i = 5; i < buffer; i++){
    cout << " ";
  }
  if(root->isred){
    cout << "R" << root->data << endl;
  }else{
    cout << "B" << root->data << endl;
  }
  display(root->left, buffer);
}

void tree::display2(node* current, node* root, int buffer){
  //covering bases
  if(current == NULL){
    return;
  }
  buffer += 5;
  display2(current->right, root, buffer);
  checkadd(current, root);
  display2(current->left, root, buffer);
}

tree::tree() {
  root = NULL;
}

