#include "tree.h"

void tree::del(int input, node* &current, node* previous){
  if(input == current-> data){
    node* temp = current;
    if(!current->left && !current->right){
      //leaf
      previous->left = NULL;
      previous->right = NULL;
    }else if(!current->left){
      //1 right child
      if(current == previous->left){
	//current IS the left child
	previous->left = current->right;
      }else if(current == previous->right){
	//current is the right child
	previous->right = current->right;
      }
      delete temp;
    }else if(!current->right){
      //1 left child
      if(current == previous->left){
	//current IS the left child
	previous->left = current->left;
      }else if(current == previous->right){
	//current is the right child
	previous->right = current->left;
      }
      delete temp;
    }else{
      //2 children
      int nexthigh = getNextHighest(current, previous)->data;
      del(nexthigh, root, NULL);
      current->data = nexthigh;
    }
    return;
  }else if(root == NULL){
    cout << "This BST is empty! " << endl;
    return;
  }
  if(input < current->data){
    if(current->left != NULL){
      del(input, current->left, current);
    }
  }else if(input > current->data){
    if(current->right != NULL){
      del(input, current->right, current);
    }
  }
}

node* tree::getNextHighest(node* current, node* previous){
  node* temp = current;
  if(current->right == NULL){
    //only left tree (less)
    while(previous != NULL && temp->data > previous->data){
      current = previous;
    }
    return previous;
  }else{
    current = current->right;
    while (current->left != NULL && current->left->data > temp->data){
      current = current->left;
    }
    return current;
  }
}
  
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
    if(current->left != NULL){
      find(input, current->left);
    }
  }else if(input > current->data){
    //high, right
    if(current->right != NULL){
      find(input, current->right);
    }
  }
  if(!current->left && !current->right){
    cout << "Input NOT found." << endl;
    return;
  }
}

void tree::add(int input, node* &current){
  node* n = new node();
  n->data = input;
  n->left = NULL;
  n->right = NULL;
  //slightly tweaked code from find
  if(root == NULL){
    root = n;
  }else{
    if(input < current->data){
      if(current->left == NULL){
	current->left = n;
      }else{
	add(input, current->left);
      }
    }else if(input > current->data){
      if(current->right == NULL){
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
