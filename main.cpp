/* Xander Siruno-Nebel
   C++/Data Structures
   Galbraith
   RBT: implementation of a red black tree in C++
 */

#include "tree.h"
#include <fstream>
#include <cstring>
#include <vector>

int main(){
  tree bst;
  srand(time(0));

  while(true){
    cout << "Please enter a valid command (ADD, READ, PRINT, QUIT)." << endl;
    char command[10];
    int input = 0;
    cin >> command;
    if(strcmp(command, "PRINT") == 0){
      bst.display2(bst.root, bst.root, 0);
      bst.display(bst.root, 0);
    }else if(strcmp(command, "FIND") == 0){
      cout << "What number to find?" << endl;
      cin >> input;
      bst.find(input, bst.root);
    }if(strcmp(command, "ADD") == 0){
      cout << "Input number to add:" << endl;
      int in2 = 0;
      cin >> in2;
      node* n = new node();
      n->data = in2;
      if(bst.root == NULL){
	bst.root = n;
	bst.checkadd(n, bst.root);
      }else{
	bst.add(bst.root, n, in2, bst.root);
      }
    }else if(strcmp(command, "READ") == 0){
      ifstream File;
      File.open("nums.txt");
      vector<int>numbers;
      int number;
      while(File >> number){
	numbers.push_back(number);
      }
      cout << "How many numbers to read in?" << endl;
      cin >> input;
      for(int i = 0; i < input; i++){
	int random = numbers[i];
	node* n = new node();
	n->data = random;
	if(bst.root == NULL){
	  bst.root = n;
	  bst.checkadd(n, bst.root);
	}else{
	  bst.add(bst.root, n, random, bst.root);
	}	
      }
    }else if(strcmp(command, "QUIT") == 0){
      break;
    }
  }
  return 0;
}
