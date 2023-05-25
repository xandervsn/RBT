#include "tree.h"

void tree::add(node*& root, node* curr, int value, node*& n){ //basically bst add
  if(curr->data >= value && curr->left == NULL){
    curr->left = new node();
    curr->left->data = value;
    curr->left->parent = curr;
    n = curr;
    checkadd(root, curr->left);
  }else if(curr->data < value && curr->right == NULL){
    curr->right = new node();
    curr->right->data = value;
    curr->right->parent = curr;
    n = curr;
    checkadd(root, curr->right);
  }else if(curr->data >= value){
    add(root, curr->left, value, n);
  } else if(curr->data < value){
    add(root, curr->right, value, n);
  }
}

void tree::checkadd(node* &root, node* curr){
  node* parent = NULL;
  node* grandparent = NULL;
  node* uncle = NULL;
 
  //init
  if(curr->parent != NULL){
    parent = curr->parent;
    if(parent->parent != NULL){
      grandparent = parent->parent;   
      if(grandparent->left == parent){
	uncle = grandparent->right;
      }else if(grandparent->right == parent){
	uncle = grandparent->left;
      }
    }
  }
  if(curr->isred && curr == root){
    //CASE 1
    //cout << "A" << endl;
    root->isred = false;
    return;
  }else if(curr->parent != NULL && curr->parent->isred == false){
    //CASE 2
    //cout << "B" << endl;
    return;
  }else if(uncle != NULL && parent->isred == true && uncle->isred == true){
    //CASE 3
    //cout << "C" << endl;
    parent->isred = false;
    uncle->isred = false;
    grandparent->isred = true;
    checkadd(root, grandparent);
  }else if(uncle == NULL || uncle->isred == false){
    //============================================================BLACK UNCLE
    if(parent == grandparent->right && curr == parent->left){
      //CASE 4
      //cout << "D" << endl;
      grandparent->right = curr;
      curr->parent = grandparent;
      node* temp = curr->right;
      curr->right = parent;
      parent->parent = curr;
      if(temp != NULL){
	temp->parent = parent;
      }
      parent->left = temp;
      parent = curr;
      curr = parent->right;
    }else if(parent == grandparent->left && curr == parent->right){
      //CASE 5
      //cout << "E" << endl;
      grandparent->left = curr;
      curr->parent = grandparent;
      node* temp = curr->left;
      curr->left = parent;
      parent->parent = curr;
      if(temp != NULL){
	temp->parent = parent;
      }
      parent->right = temp;
      parent = curr;
      curr = parent->left;
    }
    if(parent->isred == true && curr->isred == true){
      //CASE 6
      node* greatgrandparent = NULL;
      if(grandparent->left == parent && parent->left == curr){
	//================================================================LEFT LINE
	node* temp = parent->right;
	parent->right = grandparent;
	if(grandparent != root){
	  greatgrandparent = grandparent->parent;
	  parent->parent = greatgrandparent;
	  if(grandparent == greatgrandparent->left){
	    greatgrandparent->left = parent;
	  }else {
	    greatgrandparent->right = parent;
	  }
	}else {
	  parent->parent = NULL;
	  root = parent;
	}
	grandparent->parent = parent;
	if(temp != NULL){
	  temp->parent = grandparent;
	}
	grandparent->left = temp;
	parent->isred = false;
	grandparent->isred = true;
      }else if(grandparent->right == parent && parent->right == curr){
	//=====================================================================RIGHT LINE
	node* temp = parent->left;
	parent->left = grandparent;
	if(grandparent != root){
	  greatgrandparent = grandparent->parent;
	  parent->parent = greatgrandparent;
	  if(grandparent == greatgrandparent->left){
	    greatgrandparent->left = parent;
	  }else {
	    greatgrandparent->right = parent;
	  }
	}else {
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


bool tree::find(node* curr, int num, node* &n){
  //basically bst search, just figured out returns
  bool b = false;
  if(curr->data == num){
    n = curr;
    return true;
  }else {
    if(curr->data > num && curr->left != NULL){
      b = find(curr->left, num, n);
    }else if(curr->data < num && curr->right != NULL){
      b = find(curr->right, num, n);
    }
    if(b){
      return true;
    }
  }
  return false;
}

void tree::checkdelete(node* curr, node* &root){
  //case 5 rewrite
  if(!needsr(curr)){
    cout << "cur:" << curr->data << endl;
    curr->parent->right = NULL;
    if(curr->isred && !curr->left && !curr->right){
      if(!curr->parent->left){
      	recolor(root, 0);
      }
    }else if(curr->left){
      if(curr->left->isred){
        cout << "hww" << endl;
        curr->left->isred = false;
        curr->parent->right = curr->left;
      }
    }else if(!curr->left && !curr->right){
      if(!curr->isred && curr->parent->left){
	if(!curr->parent->left->isred){
	  cout << "awoo:" << curr->parent->right->data << endl;
	  curr->parent->right->isred = true;
	  curr->parent->isred = false;
	}
      }
    }
    return;
  }
  
  //double black finder
  node* sibling = NULL;
  if(!curr->parent){
    //ROOT CASE
    //cout << "case 1" << endl;
    return;
  }else {
    node* parent = curr->parent;
    if(curr == curr->parent->right){
      sibling = curr->parent->left;
    }else if(curr == curr->parent->left){
      sibling = curr->parent->right;
    }

    if(sibling != NULL){
      //SIBLING CASE
      if(sibling->isred == true && curr == curr->parent->left && curr->isred == false && parent->isred == false){
	node* siblingLeft = sibling->left;
	sibling->parent = parent->parent;
	if(parent != root){
	  if(parent == parent->left){
	    parent->parent->left = sibling;
	  }else {
	    parent->parent->right = sibling;
	  }
	}else {
	  cout << root->data << endl;
	  root = sibling;
	}
	sibling->left = parent;
	parent->parent = sibling;
	parent->isred = true;//changes isreds
	sibling->isred = false;
	parent->right = siblingLeft;
	if(siblingLeft != NULL){
	  siblingLeft->parent = parent;
	}
	sibling = parent->right;//Resets sibling
      }else if(sibling->isred == true && curr == curr->parent->right && curr->isred == false && parent->isred == false){//Rotates sibling through parent
	node* siblingRight = sibling->right;
	sibling->parent = parent->parent;
	if(parent != root){
	  if(parent == parent->left){
	    parent->parent->left = sibling;
	  }else {
	    parent->parent->right = sibling;
	  }
	}else {
	  root = sibling;
	}
	sibling->right = parent;
	parent->parent = sibling;
	parent->isred = true;//Changes isreds
	sibling->isred = false;
	parent->left = siblingRight;
	if(siblingRight != NULL){
	  siblingRight->parent = parent;
	}
	node* temporary = sibling;
	sibling = parent->left;//Resets sibling
      }
	 
      if(sibling->isred == false && curr->isred == false && parent->isred == false && (sibling->left == NULL || sibling->left->isred == false) && (sibling->right == NULL || sibling->right->isred == false)){
	//CASE 3
	sibling->isred = true;
	checkdelete(parent, root);
      }else if(parent->isred == true && sibling->isred == false && (sibling->left == NULL || sibling->left->isred == false) && (sibling->right == NULL || sibling->right->isred == false)){
	//CASE 4
	parent->isred = false;
	sibling->isred = true;
	return;
      }else if(parent->left == sibling && (sibling->left == NULL || sibling->left->isred == false)){
	//==============================================================================================CASE 5 (ROTATION CASE)
	if(sibling->right != NULL){
	  if(sibling->right->isred == true){
	    node* siblingRight = sibling->right;
	    //RIGHT ROTATE
	    parent->left = siblingRight;
	    siblingRight->parent = parent;
	    node* temp = siblingRight->left;
	    siblingRight->left = sibling;
	    sibling->parent = siblingRight;
	    sibling->right = temp;
	    temp->parent = sibling;
	    sibling->isred = true;
	    siblingRight->isred = false;
	    sibling = siblingRight;
	  }
	}
      }else if(parent->right == sibling && (sibling->right == NULL || sibling->right->isred == false)){
	if(sibling->left != NULL){
	  if(sibling->left->isred == true){
	    node* siblingLeft = sibling->left;
	    //LEFT ROTATE
	    parent->right = siblingLeft;
	    siblingLeft->parent = parent;
	    node* temp = siblingLeft->right;
	    siblingLeft->right = sibling;
	    sibling->parent = siblingLeft;
	    sibling->left = temp;
	    temp->parent = sibling;
	    sibling->isred = true;//Sets isreds
	    siblingLeft->isred = false;
	    sibling = siblingLeft;//Resets sibling
	  }
	}
      }
      if(sibling->isred == false && parent->left == sibling && sibling->left != NULL && curr->isred == false){
	//CASE 6 (FAKE ROTATION CASE)
	if(sibling->left->isred == true){
	  node* temp = sibling->right;
	  sibling->right = parent;
	  if(parent->parent != NULL){
	    if(parent == parent->parent->right){
	      parent->parent->right = sibling;
	      sibling->parent = parent->parent;
	    }else {
	      parent->parent->left = sibling;
	      sibling->parent = parent->parent;
	    }
	  }else {
	    sibling->parent = NULL;
	    root = sibling;
	  }
	  parent->parent = sibling;
	  parent->left = temp;
	  if(temp != NULL){
	    temp->parent = parent;
	  }
	  sibling->left->isred = false;
	  sibling->isred = parent->isred;
	  parent->isred = false;
	  return;
	}
      }else if(sibling->isred == false && parent->right == sibling && sibling->right != NULL && curr->isred == false){
	if(sibling->right->isred == true){
	  node* temp = sibling->left;
	  sibling->left = parent;
	  if(parent->parent != NULL){
	    if(parent == parent->parent->right){
	      parent->parent->right = sibling;
	      sibling->parent = parent->parent;
	    }else {
	      parent->parent->left = sibling;
	      sibling->parent = parent->parent;
	    }
	  }else {
	    sibling->parent = NULL;
	    root = sibling;
	  }
	  parent->parent = sibling;
	  parent->right = temp;
	  if(temp != NULL){
	    temp->parent = parent;
	  }
	  sibling->right->isred = false;
	  sibling->isred = parent->isred;
	  parent->isred = false;
	  return;
	}
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
  if(root->parent){
    if(root->isred){
      cout << "R" << root->data << endl;
    }else{
      cout << "B" << root->data << endl;
    }
  }else{
    cout << "B" << root->data << endl;
  }
  display(root->left, buffer);
}

void tree::recolor(node* curr, int steps){
  if(curr->right){
    steps++;
    recolor(curr->right, steps);
    steps--;
  }
  if(curr->left){
    steps++;
    recolor(curr->left, steps);
    steps--;
  }
  if(steps % 2 != 0){
    //cout << "R" << curr->data << endl;
    curr->isred = true;
  }else{
    curr->isred = false;
    //cout << "B" << curr->data << endl;
  }
}


tree::tree(){
 
}
