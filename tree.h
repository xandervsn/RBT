//doubly linked list

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
  void remove(node*&, node*, int, node*);
  void checkdelete(node*, node*&);
  bool find(node*, int, node*&);
  void add(node*&, node*, int, node*&);
  void checkadd(node*&, node*);
};


