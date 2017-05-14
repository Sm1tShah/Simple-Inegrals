//Smit Shah sss160030
#include "node.h"
#include <iostream>
#include <vector>
using namespace std;

class bst
{
    node* root;//private by default root node
    vector<node> v;//will store the trig in here
public:
    bst(){root = nullptr;}//default constructor taking no parameters
    bst(node* r) {root = r;}//overloaded constructor where it takes the node passed in and makes it the root
    bst(const bst& b) {root = b.getRoot();}//a copy constructor where we just make the new tree's root be the old tree's
    node* getRoot()const{return root;}//Returns the root and takes no parameter
    void setRoot(node* r) {root = r;}//Takes a parameter of node* r and sets it to the root variable and then returns nothing
    ~bst();//Returns nothing and calls the recursive delete function using the root which will eventually
    void recursivedelete(node*);//store the node in a temp node then call recursivedelete function on node->getleft and node->get right and then delete the temp variable
    void in(int,int,node*);//parameters are the two ints which are the coefficient and exponent and returns nothing. This is the recursive helper method
    void insertN(int,int);//parameters are the two doubles which are the coefficient and exponent and returns nothing
    bool se(int,node*);//the helper method to search and will do the actual recursion
    bool searchN(int);//takes an int to search it and will return if it's found or not.
    void preorder(bst&,node*);//prints the preorder, was used for debugging
    void inorder(node*);//used for debugging
    void trig();//prints the trig vector, was used for debugging
    double evaluate(double, double, node*);//evaluates the non trig nodes recursively and takes two bounds
    string print(node*);//will give the list as a string
    string printTrig();//will print the trig vector
    void insertTrig(int,int,int);//inserts a trig node into the vector
    double evaluateTrig(double,double);//evaluates the trig
    void clearTrig();//clears the vector for a new expression to begin
};
