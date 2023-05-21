#include "tree.h"
#include <fstream>
#include <math.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <cstring>

using namespace std;

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

tree::tree() {
}

