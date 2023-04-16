//doubly linked list
#include <iostream>
#include <cstring>
#include <cctype>
#include <cstdlib>
using namespace std;

struct node
{
  int data;		//some questions use a char * data;
  node * left;
  node * right;
};

class tree
{
public:
  tree();         //supplied
  //~tree();        //supplied
  void build();   //supplied
  void display(node*, int); //supplied
  void add(int, node*&);
  void find(int, node*&);
  void del(int, node*&, node*);
  node* getNextHighest(node*, node*);
  node* root;   
};
