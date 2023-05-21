//doubly linked list
#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <cstring>
#include <cctype>
#include <cstdlib>

using namespace std;

struct node
{
  int data;		//some questions use a char * data;
  node* left;
  node* right;
  node* parent;
  bool isred = true;
};

class tree
{
public:
  tree();         //supplied
  //~tree();        //supplied
  void build();   //supplied
  void display(node*, int); //supplied
  void remove(node* &root, node* curr, int num, node* newptr);
  void checkDelete(node* curr, node* &root);
  bool search(node* curr, int num, node* &newptr);
  void recurciveAdd(node*&, node*, int, node*&);
  void addFile(node*&, node*&, int&);
  void check(node*&, node*);
};

#endif
