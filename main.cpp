/* Xander Siruno-Nebel
   C++/Data Structures, Galbraith
   4/29/23
   RBT: implementation of a red black tree in C++
 */

#include "tree.h"
#include <fstream>
#include <cstring>
#include <vector>

int main(){
  int count = 1;
  tree bst;
  node* root = NULL;
  node* newptr = NULL;
  srand(time(0));

  while(true){
    cout << "Please enter a valid command (ADD, READ, PRINT, QUIT, FIND, DLT)." << endl;
    char command[10];
    int input = 0;
    cin >> command;
    if(strcmp(command, "PRINT") == 0){
      bst.display(root, 0);
    }else if(strcmp(command, "FIND") == 0){
      cout << "Input number to find:" << endl;
      int input = 0;
      cin >> input;
      if(bst.search(root, input, newptr)){
	cout << "Input found!" << endl;
      }else{
	cout << "Input NOT found." << endl;
      }
    }if(strcmp(command, "ADD") == 0){
      cout << "Input number to add:" << endl;
      int in2 = 0;
      cin >> in2;

      if(root == NULL){
	root = new node();
	root->data = in2;
	bst.check(root, root);
      }else{
	bst.recurciveAdd(root, root, in2, newptr);
      }

    }else if(strcmp(command, "READ") == 0){
      char command[100];
      cout << "Enter file name (include file extension):" << endl;
      cin >> command;
      ifstream File;
      File.open(command);
      vector<int>numbers;
      int number;
      while(File >> number){
	numbers.push_back(number);
      }
      cout << "How many numbers to read in?" << endl;
      int input = 0;
      cin >> input;
      cout << "In what order (FRONT, BACK, RAND)?" << endl;
      cin >> command;
      if(strcmp(command, "FRONT") == 0){
	for(int i = 0; i < input; i++){
	  int random = numbers[i];
	  node* n = new node();
	  n->data = random;
	  if(root == NULL){
	    root = new node();
	    root->data = random;
	    bst.check(root, root);
	  }else{
	    bst.recurciveAdd(root, root, random, newptr);
	  }
	}
      }else if(strcmp(command, "BACK") == 0){
	for(int i = input-1; i >= 0; i--){
	  int random = numbers[i];
	  node* n = new node();
	  n->data = random;
	  if(root == NULL){
	    root = new node();
	    root->data = random;
	    bst.check(root, root);
	  }else{
	    bst.recurciveAdd(root, root, random, newptr);
	  }
	}      
      }else if(strcmp(command, "RAND") == 0){
	for(int i = 0; i < input; i++){
	  int rnd = rand() % input;
          int random = numbers[rnd];
	  node* n = new node();
          n->data = random;
          if(root == NULL){
            root = new node();
            root->data = random;
            bst.check(root, root);
          }else{
            bst.recurciveAdd(root, root, random, newptr);
          }
        }
      }
    }else if(strcmp(command, "QUIT") == 0){
      break;
    }else if(strcmp(command, "DLT") == 0){
      cout << "Input number to remove:" << endl;
      int input = 0;
      cin >> input;
      bst.remove(root, root, input, newptr);
    }
  }
  return 0;
}

void tree::recurciveAdd(node* &root, node* curr, int value, node* &newptr) {//Adds recurcivly to the tree
  if (curr->data >= value && curr->left == NULL) {
    curr->left = new node();
    curr->left->data = value;
    curr->left->parent = curr;
    newptr = curr;
    check(root, curr->left);//Check function
  }
  else if (curr->data < value && curr->right == NULL) {
    curr->right = new node();
    curr->right->data = value;
    curr->right->parent = curr;
    newptr = curr;
    check(root, curr->right);//check function
  }
  else if (curr->data >= value) {//Recurcive Call
    recurciveAdd(root, curr->left, value, newptr);
  }
  else if (curr->data < value) {//Recurcive Call
    recurciveAdd(root, curr->right, value, newptr);
  }
}

void tree::check(node* &root, node* curr) {
  node* parent = NULL;
  node* grandparent = NULL;
  node* uncle = NULL;
  
  //Makes the node pointers if they exit in the tree
  if (curr->parent != NULL) {
    parent = curr->parent;
    if (parent->parent != NULL) {
      grandparent = parent->parent;   
      if (grandparent->left == parent) {
	uncle = grandparent->right;
      }
      else if (grandparent->right == parent) {
	uncle = grandparent->left;
      }
    }
  }
  if (curr->isred && curr == root) {//Case 1
    cout << "A" << endl;
    root->isred = false;
    return;
  }
  else if (curr->parent != NULL && curr->parent->isred == false) {//Case 2
    return;
  }
  else if (uncle != NULL && parent->isred == true && uncle->isred == true) {//Case 3
    parent->isred = false;
    uncle->isred = false;
    grandparent->isred = true;
    check(root, grandparent);//Recurcive Call on Grandparent
  }
  else if (uncle == NULL || uncle->isred == false) {//If the uncle is black
    if (parent == grandparent->right && curr == parent->left) {//Case 4
      grandparent->right = curr;
      curr->parent = grandparent;
      node* temp = curr->right;
      curr->right = parent;
      parent->parent = curr;
      if (temp != NULL) {
	temp->parent = parent;
      }
      parent->left = temp;
      parent = curr;
      curr = parent->right;
    }
    else if (parent == grandparent->left && curr == parent->right) {//Case 4
      grandparent->left = curr;
      curr->parent = grandparent;
      node* temp = curr->left;
      curr->left = parent;
      parent->parent = curr;
      if (temp != NULL) {
    	temp->parent = parent;
      }
      parent->right = temp;
      parent = curr;
      curr = parent->left;
    }
    if (parent->isred == true && curr->isred == true) {//Case 5
      node* greatgrandparent = NULL;
      if (grandparent->left == parent && parent->left == curr) {//If parent is a left child and curr is a left child
	node* temp = parent->right;
	parent->right = grandparent;
	if (grandparent != root) {
	  greatgrandparent = grandparent->parent;
	  parent->parent = greatgrandparent;
	  if (grandparent == greatgrandparent->left) {
	    greatgrandparent->left = parent;
	  }
	  else {
	    greatgrandparent->right = parent;
	  }
	}
	else {
	  parent->parent = NULL;
	  root = parent;
	}
	grandparent->parent = parent;
	if (temp != NULL) {
	  temp->parent = grandparent;
	}
	grandparent->left = temp;
	parent->isred = false;
	grandparent->isred = true;
      }
      else if (grandparent->right == parent && parent->right == curr) {//If parent is a right child and curr is a right child
	node* temp = parent->left;
    	parent->left = grandparent;
    	if (grandparent != root) {
	  greatgrandparent = grandparent->parent;
	  parent->parent = greatgrandparent;
	  if (grandparent == greatgrandparent->left) {
	    greatgrandparent->left = parent;
	  }
	  else {
	    greatgrandparent->right = parent;
	  }
    	}
    	else {
	  parent->parent = NULL;
	  root = parent;
    	}
    	grandparent->parent = parent;
	if (temp != NULL) {
	  temp->parent = grandparent;
    	}
    	grandparent->right = temp;
	parent->isred = false;
    	grandparent->isred = true;
      }
    }
  }
}


bool tree::search(node* curr, int num, node* &newptr) {//Search Function
  bool b = false;
  if (curr->data == num) {
    newptr = curr;
    return true;
  }
  else {
    if (curr->data > num && curr->left != NULL) {
      b = search(curr->left, num, newptr);
    }
    else if (curr->data < num && curr->right != NULL) {
      b = search(curr->right, num, newptr);
    }
    if(b) {
      return true;
    }
  }
  return false;
}

void tree::checkDelete(node* curr, node* &root) {//Check delete function which has cases for double blacks
  node* sibling = NULL;
  if (!curr->parent) {//CASE 1
    cout << "case 1" << endl;
    return;
  }
  else {
    //Sets up varubles
    node* parent = curr->parent;
    if (curr == curr->parent->right) {
      sibling = curr->parent->left;
    }
    else if (curr == curr->parent->left) {
      sibling = curr->parent->right;
    }

    if (sibling != NULL) {
      //CASE 2
      if (sibling->isred == true && curr == curr->parent->left && curr->isred == false && parent->isred == false) {
	node* siblingLeft = sibling->left;
	sibling->parent = parent->parent;
	if (parent != root) {
	  if (parent == parent->left) {
	    parent->parent->left = sibling;
	  }
	  else {
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
	if (siblingLeft != NULL) {
	  siblingLeft->parent = parent;
	}
	sibling = parent->right;//Resets sibling
      }
      else if (sibling->isred == true && curr == curr->parent->right && curr->isred == false && parent->isred == false) {//Rotates sibling through parent
	node* siblingRight = sibling->right;
	sibling->parent = parent->parent;
	if (parent != root) {
	  if (parent == parent->left) {
	    parent->parent->left = sibling;
	  }
	  else {
	    parent->parent->right = sibling;
	  }
	}
	else {
	  root = sibling;
	}
	sibling->right = parent;
	parent->parent = sibling;
	parent->isred = true;//Changes isreds
	sibling->isred = false;
	parent->left = siblingRight;
	if (siblingRight != NULL) {
	  siblingRight->parent = parent;
	}
	node* temporary = sibling;
	sibling = parent->left;//Resets sibling
      }
      
      //CASE 3
      if (sibling->isred == false && curr->isred == false && parent->isred == false && (sibling->left == NULL || sibling->left->isred == false) && (sibling->right == NULL || sibling->right->isred == false)) {//Sets siblings isred to red then recurcive call on parent
	sibling->isred = true;
	checkDelete(parent, root);
      }
      
      //CASE 4
      else if (parent->isred == true && sibling->isred == false && (sibling->left == NULL || sibling->left->isred == false) && (sibling->right == NULL || sibling->right->isred == false)) {//Sets parent to black and sibling to red
	parent->isred = false;
	sibling->isred = true;
	return;
      }
      //CASE 5
      else if (parent->left == sibling && (sibling->left == NULL || sibling->left->isred == false)) {//Rotates through sibling
	if (sibling->right != NULL) {
	  if (sibling->right->isred == true) {//If siblings right is red
	    node* siblingRight = sibling->right;//Rotates trhough sibling
	    parent->left = siblingRight;
	    siblingRight->parent = parent;
	    node* temp = siblingRight->left;
	    siblingRight->left = sibling;
	    sibling->parent = siblingRight;
	    sibling->right = temp;
	    temp->parent = sibling;
	    sibling->isred = true;//Sets isreds
	    siblingRight->isred = false;
	    sibling = siblingRight;//Resets sibling
	  }
	}
      }
      else if (parent->right == sibling && (sibling->right == NULL || sibling->right->isred == false)) {
	if (sibling->left != NULL) {
	  if (sibling->left->isred == true) {
	    node* siblingLeft = sibling->left;//Rotates through sibling
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
      //CASE 6
      if (sibling->isred == false && parent->left == sibling && sibling->left != NULL && curr->isred == false) {//Rotates through parent and switchs parent and siblings isreds
	if (sibling->left->isred == true) {
	  node* temp = sibling->right;
	  sibling->right = parent;
	  if (parent->parent != NULL) {//Checks if parent is NULL
	    if (parent == parent->parent->right) {
	      parent->parent->right = sibling;
	      sibling->parent = parent->parent;
	    }
	    else {
	      parent->parent->left = sibling;
	      sibling->parent = parent->parent;
	    }
	  }
	  else {
	    sibling->parent = NULL;
	    root = sibling;
	  }
	  parent->parent = sibling;
	  parent->left = temp;
	  if (temp != NULL) {
	    temp->parent = parent;
	  }
	  //Sets isreds
	  sibling->left->isred = false;
	  sibling->isred = parent->isred;
	  parent->isred = false;
	  return;
	}
      }
      else if (sibling->isred == false && parent->right == sibling && sibling->right != NULL && curr->isred == false) {
	if (sibling->right->isred == true) {
	  node* temp = sibling->left;
	  sibling->left = parent;
	  if (parent->parent != NULL) {
	    if (parent == parent->parent->right) {
	      parent->parent->right = sibling;
	      sibling->parent = parent->parent;
	    }
	    else {
	      parent->parent->left = sibling;
	      sibling->parent = parent->parent;
	    }
	  }
	  else {
	    sibling->parent = NULL;
	    root = sibling;
	  }
	  parent->parent = sibling;
	  parent->right = temp;
	  if (temp != NULL) {
	    temp->parent = parent;
	  }
	  //Sets isreds
	  sibling->right->isred = false;
	  sibling->isred = parent->isred;
	  parent->isred = false;
	  return;
	}
      }
    }
  }
}


void tree::remove(node* &root, node* curr, int num, node* newptr) {//Removes the number from the binary search tree
  if (search(curr, num, newptr) == true) {//If the number is in the tree
    node* temp = newptr;
    node* newPos = NULL;
    node* x = NULL;
    if (temp == root) {//If thr root is the number to be deleted
      if (temp->left == NULL && temp->right == NULL) {//If it is a leaf
	root = NULL;
	newptr = NULL;
      }
      else if (temp->left != NULL && temp->right == NULL) {//If it only has a left child
	root = root->left;
	root->parent = NULL;
	newptr = NULL;
	newPos = root;
      }
      else if (temp->left == NULL && temp->right != NULL) {//If it only has a right child
	root = root->right;
	root->parent = NULL;
	newptr = NULL;
	newPos = root;
      }
      else {//If it has two children
	node* newnode = temp->right;
    	while (newnode->left != NULL) {//Goes to inorder sucser
	  newnode = newnode->left;
    	}
    	temp->data = newnode->data;
	checkDelete(newnode, root);//Calls check delete
    	if (newnode == temp->right) {
	  temp->right = temp->right->right;
    	}
	else if(newnode->right != NULL){
	  newnode->parent->left = newnode->right;
	  newnode->right->parent = newnode->parent;
	  if(newnode->parent->isred){
	    newnode->right->isred = false;
	  }
	}
	if (newnode->parent->left == newnode) {
	  newnode->parent->left = NULL;
	}
	newptr = NULL;
	newPos = root;
      }
    }
    else {
      if (temp->left == NULL && temp->right == NULL) {//If it is a leaf
	if (temp->isred == true) {
	  if (temp->parent->left == temp) {
	    temp->parent->left = NULL;
	    delete temp;
	  }
	  else {
	    temp->parent->right = NULL;
	    delete temp;
	  }
	  return;
	}
	if (temp->parent->left == temp) {//Calls check delete then deletes
	  checkDelete(temp, root);
	  temp->parent->left = NULL;
	}
	else {//Calls check delete then delets
	  checkDelete(temp, root);
	  temp->parent->right = NULL;
	}
	newptr = NULL;
      }
      else if (temp->left != NULL && temp->right == NULL) {//If temp only has a left child
	//MAKEs THE PARENTS POINTER POINT TO THE CHILD (EASIER)
	node* tempParent = temp->parent;
	if (tempParent->left == temp) {
	  if (temp->left->isred == !temp->isred) {//If isreds are diffrent
	    tempParent->left = temp->left;
	    temp->left->parent = tempParent;
	    if (temp->left->isred) {//Sets temps left new isred based on what the isred variations are
	      temp->left->isred = false;
	    }
	    else {
	      temp->left->isred = true;
	    }
	    delete temp;
	    return;
	  }
	  //Deletes temp
	  tempParent->left = temp->left;
	  temp->left->parent = tempParent;
	  delete temp;
	}
	else {
	  if (temp->left->isred == !temp->isred) {//If the isreds are diffrent
	    tempParent->right = temp->left;
	    temp->left->parent = tempParent;
	    if (temp->left->isred) {//Sets temps left new isred based on the diffre isred variations
	      temp->left->isred = false;
	    }
	    else {
	      temp->left->isred = true;
	    }
	    delete temp;
	    return;
	  }
	  //Deletes temp
	  tempParent->right = temp->left;
	  temp->left->parent = tempParent;
	  checkDelete(temp, root);
	}
	newptr = NULL;
      }
      else if (temp->left == NULL && temp->right != NULL) {//If temp only has a right child
	node* tempParent = temp->parent;
	if (tempParent->right == temp) {
	  if (temp->right->isred == !temp->isred) {//If isreds are diffrent
	    tempParent->right = temp->right;
	    temp->right->parent = tempParent;
	    if (temp->right->isred) {//Sets temp left based off isred varients
	      temp->right->isred = false;
	    }
	    else {
	      temp->right->isred = true;
	    }
	    delete temp;
	    return;
	  }
	  //deletes temp then runs check delete
	  tempParent->right = temp->right;
	  temp->right->parent = tempParent;
	  delete temp;
	  checkDelete(temp, root);
	}
	else {
	  if (temp->right->isred == !temp->isred) {
	    tempParent->left = temp->right;
	    temp->right->parent = tempParent;
	    if (temp->right->isred) {
	      temp->right->isred = false;
	    }
	    else {
	      temp->right->isred = true;
	    }
	    delete temp;
	    return;
	  }
	  tempParent->left = temp->right;
	  temp->right->parent = tempParent;
	  delete temp;
	  checkDelete(temp, root);
	}
	newptr = NULL;
      }
      else {//If it has two children
	node* newnode = temp->right;
	while (newnode->left != NULL) {//Finds in order sucser
	  newnode = newnode->left;
	}
	temp->data = newnode->data;

	cout << newnode->isred << endl;
	
	checkDelete(newnode, root);//Checks
	if (newnode == temp->right) {
	  temp->right = temp->right->right;
	}
	if (newnode->parent->left == newnode) {
	  newnode->parent->left = NULL;
	}
      }
    }
  }
}
