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
  tree bst;
  node* newptr = NULL;
  srand(time(0));

  while(true){
    cout << "Please enter a valid command (ADD, READ, PRINT, QUIT, FIND, DLT)." << endl;
    char command[10];
    int input = 0;
    cin >> command;
    if(strcmp(command, "PRINT") == 0){
      bst.display2(bst.root, bst.root, 0);
      bst.display(bst.root, 0);
    }else if(strcmp(command, "FIND") == 0){
      cout << "Input number to find:" << endl;
      int input = 0;
      cin >> input;
      if(bst.search(bst.root, input, newptr)){
	cout << "Input found!" << endl;
      }else{
	cout << "Input NOT found." << endl;
      }
    }if(strcmp(command, "ADD") == 0){
      cout << "Input number to add:" << endl;
      int in2 = 0;
      cin >> in2;
      node* n = new node();
      n->data = in2;
      n->isred = true;
      if(bst.root == NULL){
	bst.root = n;
	bst.checkadd(n, bst.root);
      }else{
	bst.add(bst.root, n, in2, bst.root);
      }
    }else if(strcmp(command, "READ") == 0){
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
      cin >> input;
      cout << "In what order? (FRONT, BACK, RAND)" << endl;
      cin >> command;
      if(strcmp(command, "FRONT") == 0){
	for(int i = 0; i < input; i++){
	  int random = numbers[i];
	  node* n = new node();
	  n->data = random;
	  n->isred = true;
	  if(bst.root == NULL){
	    bst.root = n;
	    bst.checkadd(n, bst.root);
	  }else{
	    bst.add(bst.root, n, random, bst.root);
	  }
	}
      }else if(strcmp(command, "BACK") == 0){
	for(int i = numbers.size(); i > numbers.size() - input; i--){
	  int random = numbers[i];
          node* n = new node();
          n->data = random;
          n->isred = true;
          if(bst.root == NULL){
            bst.root = n;
            bst.checkadd(n, bst.root);
          }else{
            bst.add(bst.root, n, random, bst.root);
          }
	}
      }else if(strcmp(command, "RAND") == 0){
        for(int i = 0; i < input; i++){
	  int rnd = rand() % 999;
          int random = numbers[rnd];
          node* n = new node();
          n->data = random;
          n->isred = true;
          if(bst.root == NULL){
            bst.root = n;
            bst.checkadd(n, bst.root);
          }else{
            bst.add(bst.root, n, random, bst.root);
          }
        }
      }
    }else if(strcmp(command, "QUIT") == 0){
      break;
    }else if(strcmp(command, "DLT") == 0){
      cout << "Input number to remove:" << endl;
      int input = 0;
      cin >> input;
      bst.remove(bst.root, bst.root, input, newptr);
    }
  }
  return 0;
}
