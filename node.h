//Smit Shah
#ifndef NODE_H
#define NODE_H
class node
{
    private:
    int coef,exp, spec; //spec is an identifier as to whether it is a trig function and which one it is
    node* left, *right;//all the private components of the node class
    public:
    node(){coef = exp = 0; spec = -1; left = right = nullptr;}//Default constructor takes nothing and sets doubles to 0 and pointers to null
    node(int c, int e,node* l, node* r){coef = c;exp = e;left =l; right = r; spec = -1;}//And stores it appropriately//Overloaded constructor takes
    node(int s, int c, int e,node* l, node* r){spec = s;coef = c;exp = e;left =l; right = r;}//other overloaded constructor that takes a spec that will be stored to identify the trig
    node(node* n) {coef = n->getCo(); exp = n->getEx(); left = n->getLeft(); right = n->getRight(); spec = n->getS();}//the copy constructor that will do member wise copying
    //Copy constructor takes a const &node And copies each member into the appropriate var
    int getCo () {return coef;}//Takes no parameter and returns coef
    int getEx () {return exp;}//Takes no parameter and returns exp
    int getS() {return spec;}//returns the spec
    node* getLeft() {return left;}//Takes no parameter and returns left
    node* getRight() {return right;}//Takes no parameter and returns right
    void setCo(int c){coef =c;}//Returns nothing and takes as parameter coef
    void setEx(int e){exp = e;}//Returns nothing and takes as parameter exp
    void setS(int s){spec = s;}//will take a new spec and save that in
    void setLeft(node* l){left = l;}//Returns nothing and takes as parameter left
    void setRight(node* r){right = r;}//Returns nothing and takes as parameter right
};
#endif // NODE_H
