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
  bool isred;
};

class tree
{
public:
  tree();         //supplied
  //~tree();        //supplied
  void build();   //supplied
  void display(node*, int); //supplied
  void display2(node*, node*, int);
  void add(node*, node*, int, node*&);
  void checkadd(node*, node*&);
  void remove(node*&, node*, int, node*);
  bool search(node *, int, node *&);
  void checkDelete(node *curr, node *&root);
  bool isred;
};
