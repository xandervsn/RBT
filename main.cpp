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
	  int rnd = rand() % input;
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
