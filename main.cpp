/* Xander Siruno-Nebel
   C++/Data Structures, Galbraith
   5/21/23
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
  node* n = NULL;
  srand(time(0));

  //command setup, pretty self explanatory
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
      if(bst.find(root, input, n)){
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
	bst.checkadd(root, root);
      }else{
	bst.add(root, root, in2, n);
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
	  if(root == NULL){
	    root = new node();
	    root->data = random;
	    bst.checkadd(root, root);
	  }else{
	    bst.add(root, root, random, n);
	  }
	}
      }else if(strcmp(command, "BACK") == 0){
	for(int i = input-1; i >= 0; i--){
	  int random = numbers[i];
	  if(root == NULL){
	    root = new node();
	    root->data = random;
	    bst.checkadd(root, root);
	  }else{
	    bst.add(root, root, random, n);
	  }
	} 	 
      }else if(strcmp(command, "RAND") == 0){
	for(int i = 0; i < input; i++){
	  int rnd = rand() % numbers.size();
	  int random = numbers[rnd];
	  if(root == NULL){
	    root = new node();
	    root->data = random;
	    bst.checkadd(root, root);
	  }else{
	    bst.add(root, root, random, n);
	  }
    	}
      }
    }else if(strcmp(command, "QUIT") == 0){
      break;
    }else if(strcmp(command, "DLT") == 0){
      cout << "Input number to remove:" << endl;
      int input = 0;
      cin >> input;
      bst.remove(root, root, input, n);
    }
  }
  return 0;
}

void tree::remove(node* &root, node* curr, int num, node* n){
  if(find(curr, num, n) == true){
    node* temp = n;
    node* newPos = NULL;
    node* x = NULL;
    if(temp == root){
      //ROOT CASE
      if(temp->left == NULL && temp->right == NULL){
        root = NULL;
        n = NULL;
      }else if(temp->left != NULL && temp->right == NULL){
        //LEFT CHILD
        root = root->left;
        root->parent = NULL;
        n = NULL;
        newPos = root;
      }else if(temp->left == NULL && temp->right != NULL){
        //RIGHT CHILD
        root = root->right;
        root->parent = NULL;
        n = NULL;
        newPos = root;
      }else {
        //2 CHILDREN
        node* newnode = temp->right;
        while (newnode->left != NULL){
          newnode = newnode->left;
        }
        temp->data = newnode->data;
        checkdelete(newnode, root);
        if(newnode == temp->right){
          temp->right = temp->right->right;
        }else if(newnode->right != NULL){
          newnode->parent->left = newnode->right;
          newnode->right->parent = newnode->parent;
          if(newnode->parent->isred){
            newnode->right->isred = false;
          }
        }
        if(newnode->parent->left == newnode){
          newnode->parent->left = NULL;
        }
        n = NULL;
        newPos = root;
      }
    }else {
      if(temp->left == NULL && temp->right == NULL){
        //LEAF
        if(temp->isred == true){
          if(temp->parent->left == temp){
            temp->parent->left = NULL;
            delete temp;
          }else {
            temp->parent->right = NULL;
            delete temp;
          }
          return;
        }
        if(temp->parent->left == temp){
          checkdelete(temp, root);
          temp->parent->left = NULL;
        }else {
          checkdelete(temp, root);
          temp->parent->right = NULL;
        }
        n = NULL;
      }else if(temp->left != NULL && temp->right == NULL){
        //swaps parent, bit hacky (supposed to rotate) but i cba
        //kinda just bst add but weirder
        node* tempParent = temp->parent;
        if(tempParent->left == temp){
          if(temp->left->isred == !temp->isred){
            tempParent->left = temp->left;
            temp->left->parent = tempParent;
            if(temp->left->isred){
              temp->left->isred = false;
            }else {
              temp->left->isred = true;
            }
            delete temp;
            return;
          }
          tempParent->left = temp->left;
          temp->left->parent = tempParent;
          delete temp;
        }else {
          if(temp->left->isred == !temp->isred){
            tempParent->right = temp->left;
            temp->left->parent = tempParent;
            if(temp->left->isred){
              temp->left->isred = false;
            }else {
              temp->left->isred = true;
            }
            delete temp;
            return;
          }
          tempParent->right = temp->left;
          temp->left->parent = tempParent;
          checkdelete(temp, root);
        }
        n = NULL;
      }else if(temp->left == NULL && temp->right != NULL){
        node* tempParent = temp->parent;
        if(tempParent->right == temp){
          if(temp->right->isred == !temp->isred){
            tempParent->right = temp->right;
            temp->right->parent = tempParent;
            if(temp->right->isred){
              temp->right->isred = false;
            }else {
              temp->right->isred = true;
            }
            delete temp;
            return;
          }
          tempParent->right = temp->right;
          temp->right->parent = tempParent;
          delete temp;
          checkdelete(temp, root);
        }else {
          if(temp->right->isred == !temp->isred){
            tempParent->left = temp->right;
            temp->right->parent = tempParent;
            if(temp->right->isred){
              temp->right->isred = false;
            }else {
              temp->right->isred = true;
            }
            delete temp;
            return;
          }
          tempParent->left = temp->right;
          temp->right->parent = tempParent;
          delete temp;
          checkdelete(temp, root);
        }
        n = NULL;
      }else {
        node* newnode = temp->left;
        while(newnode->right != NULL){
          newnode = newnode->right;
        }

        if(!needsr(newnode)){
	  checkdelete(newnode, root);
	  cout << "woo:" << newnode->data << endl;
	  temp->data = newnode->data;
	  delete newnode;
	}else{
          cout << "a2" << endl;
          newnode = temp->right;
          while(newnode->left != NULL){
            newnode = newnode->left;
          }
          temp->data = newnode->data;
          checkdelete(newnode, root);
          if(newnode == temp->right){
            temp->right = temp->right->right;
          }
          if(newnode->parent->left == newnode){
            newnode->parent->left = NULL;
          }
        }
      }
    }
  }
}

bool tree::needsr(node* curr){
  cout << "HERE" << endl;
  if(curr->isred && !curr->left && !curr->right){
    return false;
  }else if(curr->left){
    if(curr->left->isred){
      return false;
    }
  }else if(!curr->left && !curr->right){
    if(!curr->isred && curr->parent->left){
      if(!curr->parent->left->isred){
	return false;
      }
    }
  }
  return true;
}
