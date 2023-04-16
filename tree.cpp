#include "tree.h"

void tree::find(int input, node* &current){
  if(input == current-> data){
    cout << "Input found!" << endl;
    return;
  }else if(root == NULL){
    cout << "This BST is empty! " << endl;
    return;
  }
  if(input < current->data){
    //less, left
    if(current->left->data != 0){
      find(input, current->left);
    }
  }else if(input > current->data){
    //high, right
    if(current->right->data != 0){
      find(input, current->right);
    }
  }
  if(current->left->data != 0 && current->right->data != 0){
    cout << "Input NOT found." << endl;
    return;
  }
}

void tree::checkadd(node* &current){
  if(current == root){
    //current is root
    return;
  }else if(!current->parent || !current->parent->parent){
    //current does not have an uncle
    return;
  }else{
    //sees if parent is left or right child, sets unc as opposite
    current->grandparent = current->parent->parent;
    if(current->parent == current->grandparent->left){
      current->uncle = current->right;
    }else if(current->parent == current->grandparent->right){
      current->uncle = current->left;
    }

    if(current->uncle->isred){
      
    }else if(!current->uncle->isred){
      cout << "a" << endl;
      if((current->parent->left == current && current->grandparent->right == current->parent) ||
	 (current->parent->right == current && current->grandparent->left == current->parent)){
	int temp = current->data;
	current->data = current->parent->data;
	current->parent->data = temp;
      }
    }
  }
}

void tree::add(int input, node* &current){
  node* n = new node();
  n->data = input;
  n->parent = current;
  n->isred = true;
  n->left = new node();
  n->left->isred = false;
  n->right = new node();
  n->right->isred = false;
  //slightly tweaked code from find
  if(root == NULL){
    root = n;
    n->isred = false;
  }else{
    if(input < current->data){
      if(current->left->data == 0){
	current->left = n;
	checkadd(current->left);
      }else{
	add(input, current->left);
      }
    }else if(input > current->data){
      if(current->right->data == 0){
	current->right = n;
      }else{
	add(input, current->right);
      }
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
  cout << root->data << "\n";
  display(root->left, buffer);
}

tree::tree() {
  root = NULL;
}
