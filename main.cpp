/* Xander Siruno-Nebel
   C++/Data Structures
   Galbraith
   BST: implementation of a binary search tree in C++
 */

#include "tree.h"
#include <fstream>
#include <cstring>
#include <vector>

int main(){
  tree bst;
  srand(time(0));

  while(true){
    cout << "Please enter a valid command (PRINT, ADD, DEL, FIND)." << endl;
    char command[10];
    int input = 0;
    cin >> command;
    if(strcmp(command, "PRINT") == 0){
      bst.display(bst.root, 0);
    }else if(strcmp(command, "DEL") == 0){
      cout << "What number to delete?" << endl;
      cin >> input;
      bst.del(input, bst.root, NULL);
    }else if(strcmp(command, "FIND") == 0){
      cout << "What number to find?" << endl;
      cin >> input;
      bst.find(input, bst.root);
    }else if(strcmp(command, "ADD") == 0){
      cout << "Input by console (C) or file (F)?" << endl;
      cin >> command;
      cout << "How many numbers would you like to add?" << endl;
      cin >> input;
      if(strcmp(command, "C") == 0){
	for(int i = 0; i < input; i++){
	  cout << "Input number to add:" << endl;
	  int in2 = 0;
	  cin >> in2;
	  bst.add(in2, bst.root);
	}
      }else if(strcmp(command, "F") == 0){
	ifstream File;
	File.open("nums.txt");
	vector<int>numbers;
	int number;
	while(File >> number){
	  numbers.push_back(number);
	}
	for(int i = 0; i < input; i++){
	  int random = rand() % 999;
	  bst.add(numbers[random], bst.root);
	}
      }
    }
  }
  return 0;
}
