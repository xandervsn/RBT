#include "tree.h"

void tree::checkdlt(node *curr, node *&root, node *&goaln) {
  node *sibling = NULL;
  node *parent = NULL;
  node *grandparent = NULL;
  if (curr->parent != NULL) {
    parent = curr->parent;
    if (parent->left == curr && parent->right != NULL) {
      sibling = parent->right;
    } else if (parent->right == curr && parent->left != NULL) {
      sibling = parent->left;
    }
    if (parent->parent != NULL) {
      grandparent = parent->parent;
    }
  }
  // CASE 1
  if (curr == root) {
    if (curr->right == NULL) {
      root = curr->left;
      delete goaln;
    } else {
      root = curr->right;
      delete goaln;
    }
  }
  // CASE 2
  if (sibling->color) {
    if (parent->right == curr) {
      sibling->color = false;
      parent->color = true;
      parent->right = sibling->left;
      sibling->left->parent = parent;
      sibling->left = parent;
      parent->parent = sibling;
      if (grandparent != NULL) {
	if (grandparent->right == parent) {
	  grandparent->right = sibling;
	} else {
	  grandparent->left = sibling;
	}
	sibling->parent = grandparent;
      } else {
	root = sibling;
      }
    } else {
      sibling->color = false;
      parent->color = true;
      parent->left = sibling->right;
      sibling->right->parent = parent;
      sibling->right = parent;
      parent->parent = sibling;
      if (grandparent != NULL) {
	if (grandparent->right == parent) {
	  grandparent->right = sibling;
	} else {
	  grandparent->left = sibling;
    }
	sibling->parent = grandparent;
      } else {
	root = sibling;
      }
    }
    if (curr->parent != NULL) {
      parent = curr->parent;
      if (parent->left == curr && parent->right != NULL) {
	sibling = parent->right;
      } else if (parent->right == curr && parent->left != NULL) {
	sibling = parent->left;
      }
      if (parent->parent != NULL) {
	grandparent = parent->parent;
      }
    }
    
    // CASE 3
    if (!sibling->color) {
      sibling->color = true;
      checkdlt(parent, root, goaln);
    }
    // CASE 4
    else if (
	     parent->color && !sibling->color &&
	     (sibling->left == NULL || !sibling->left->color) &&
	     (sibling->right == NULL || !sibling->right->color)) {
      parent->color = false;
      sibling->color = true;
    }
    // Case 5
    else if (
	     (!sibling->color &&
	      (sibling->left == NULL || !sibling->left->color) &&
	      sibling->right->color && parent->right == curr) ||
	     (!sibling->color &&
	      (sibling->right == NULL || !sibling->right->color) &&
	      sibling->left->color && parent->left == curr)) {
      if (parent->right == curr) {
	node *temp = sibling->right->left;
	sibling->right->color = false;
	sibling->color = true;
	parent->left = sibling->right;
	sibling->right->parent = parent;
	sibling->right->left = sibling;
	sibling->parent = sibling->right;
	sibling->right = temp;
      } else {
	node *temp = sibling->left->right;
	sibling->right->color = false;
	sibling->color = true;
	parent->right = sibling->left;
	sibling->left->parent = parent;
	sibling->left->right = sibling;
	sibling->parent = sibling->left;
	sibling->left = temp;
      }
    }
    // CASE 6
    else {
      if ((!sibling->color && sibling->left->color &&
	   parent->right == curr) ||
	  (!sibling->color && sibling->right->color &&
	   parent->left == curr)) {
	sibling->color = parent->color;
	parent->color = false;
	if (parent->right == curr) {
	  node *temp = sibling->right;
	  sibling->left->color = false;
	  sibling->right = parent;
	  parent->parent = sibling;
	  parent->left = temp;
	  if (temp != NULL) {
	    temp->parent = parent;
	  }
	  if (grandparent != NULL) {
	    if (grandparent->right == parent) {
	      grandparent->right = sibling;
	    } else {
	      grandparent->left = sibling;
	    }
	    sibling->parent = grandparent;
	  } else {
	    root = sibling;
	  }
	} else {
	  node *temp = sibling->left;
	  sibling->right->color = false;
	  sibling->left = parent;
	  parent->parent = sibling;
	  parent->right = temp;
	  if (temp != NULL) {
	    temp->parent = parent;
	  }
	  if (grandparent != NULL) {
	    if (grandparent->right == parent) {
	      grandparent->right = sibling;
	    } else {
	      grandparent->left = sibling;
	    }
	    sibling->parent = grandparent;
	  } else {
	    root = sibling;
	  }
	}
      }
      delete goaln;
    }
  }
}


void tree::dlt(node * &root, node * &todelete) {
  bool n;
  node *parent = todelete->parent;
  if (todelete !=
      root) { // If the node that is to be removed is the not the root
    if (parent->left == todelete) {
      n = true;
    } else {
      n = false;
    } // If n is ture curr is left of parent
  }
  if (todelete == root) { // If there is nothing but the root remove the root
    if (todelete->right == NULL && todelete->left == NULL) {
      delete todelete;
      return;
    } else if (todelete->right != NULL && todelete->left != NULL) { // If
      // there is
      // a right
      // and left
      node* temp = todelete->right;
      while (temp->left != NULL) {
	temp = temp->left;
      }
      todelete->value = temp->value;
      if(temp->right != NULL && temp != todelete->right){
	temp->parent->left = temp->right;
	if(temp->parent->color){
	  temp->right->color = false;
	}
      }
      if (temp->parent->left == temp) {
	temp->parent->left = NULL;
      }
      if(temp == todelete->right && temp->right != NULL){
	todelete->right = temp->right;
	temp->right->parent = todelete;
      }
      delete temp;
      return;
    }
    if (root->right == NULL) { // If there only is a right
      node *temp = root;
      delete temp;
      root = root->left;
    } else { // If there only is a left
      node *temp = root;
      delete temp;
      root = root->right;
    }
    root->color = false;
  } else { // If the goal node is not the root
    if (todelete->right == NULL &&
	todelete->left ==
	NULL) { // If both are null set the parents pointer that
      // would point to the goal node to NULL
      if (todelete->color) {
	if (n) {
	  delete todelete;
	  parent->left = NULL;
	} else {
	  delete todelete;
	  parent->right = NULL;
	}
	return;
      }
      if (n) {
	checkdlt(todelete, root, todelete);
	parent->left = NULL;
      } else {
	checkdlt(todelete, root, todelete);
	parent->right = NULL;
      }
      return;
    } else if (
	       todelete->right != NULL &&
	       todelete->left != NULL) { // If there is a both right and left
      node *temp = todelete->right;
      while (temp->left != NULL) {
	temp = temp->left;
      }
      todelete->value = temp->value;
      checkdlt(temp, root, temp);
      if (temp == todelete->right) {
	todelete->right = todelete->right->right;
      }
      if (temp->parent->left == temp) {
	temp->parent->left = NULL;
      }
      return;
    } else { // If there is only one child
      if (n) {
	if (todelete->left == NULL) {
	  if (todelete->right->color == !todelete->color) {
	    delete todelete;
	    parent->left = todelete->right;
	    if (todelete->right->color) {
	      todelete->color = false;
	    }
	    return;
	  }
	  parent->left = todelete->right;
	  checkdlt(todelete, root, todelete);
	} else {
	  if (todelete->left->color == !todelete->color) {
	    delete todelete;
	    parent->left = todelete->left;
	    if (todelete->left->color) {
	      todelete->color = false;
	    }
	    return;
	  }
	  parent->left = todelete->left;
	  checkdlt(todelete, root, todelete);
	}
      } else {
	if (todelete->left == NULL) {
	  if (todelete->right->color == !todelete->color) {
	    delete todelete;
	    parent->right = todelete->right;
	    if (todelete->right->color) {
	      todelete->color = false;
	    }
	    return;
	  }
	  parent->right = todelete->right;
	  checkdlt(todelete, root, todelete);
	} else {
	  if (todelete->left->color == !todelete->color) {
	    delete todelete;
	    parent->right = todelete->left;
	    if (todelete->left->color) {
	      todelete->color = false;
	    }
	    return;
	  }
	  parent->right = todelete->left;
	  checkdlt(todelete, root, todelete);
	}
      }
      return;
    }
  }
}


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

