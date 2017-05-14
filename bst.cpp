//Smit Shah, sss160030
//TRIG FUNCTIONS
#include "bst.h"
#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <string>
#include <sstream>//including all the good libraries and the bst.h which included the node.h already
using namespace std;//because it's easier to do this
void bst::insertTrig(int s,int co,int ex)//will insert a node into the vector that stores the trig
{
    if(v.size() == 0)
        v.push_back(node(s,co,ex,nullptr,nullptr));//you just include the new trig function if the vector is empty
    else
    {
        unsigned int count = 0;
        bool found = false;
        while(count < v.size())//iterating through the whole vector
        {
            if(v[count].getS() == s && v[count].getEx() == ex)//will see if its the same trig function and also has the same inside coefficient
            {
                v[count] = node(s,v[count].getCo() + co,ex,nullptr,nullptr);//combine like terms
                found = true;
                break;
            }
            count++;
        }
        if(!found)
        {
            v.push_back(node(s,co,ex,nullptr,nullptr));//if didn't find a like term then add normally
        }
    }
}
int GCD(int x, int y)//greatest common divisor recursive method
{
    return y == 0 ? x : GCD(y, x % y);//Euclid's algorithm, self explanatory.
}
template <typename T>
string NumberToString(T pNumber)// a handy function to convert ints or doubles to strings
{
 ostringstream o;
 o << pNumber;
 return o.str();
}
bst::~bst()//Returns nothing and calls the recursive delete function using the root which will eventually
{
    recursivedelete(root);//will call the recursive function on the root
}
void bst::recursivedelete(node* n)//store the node in a temp node then call recursivedelete function on node->getleft and node->get right and then delete the temp variable
{
    if(n)//base case where if the pointer is pointing to nothing then we dont' delete anything
    {
        recursivedelete(n->getLeft());//recursing on the left subtree
        recursivedelete(n->getRight());//recursing on the right subtree
        delete n;//actually deleting the node we're on
    }
}
void bst::in(int c,int e,node* r)//parameters are the two ints which are the coefficient and exponent and returns nothing. This is the recursive helper method
{
    if(r == nullptr)//here we add recursively and it will add a new node only if it's a unique exponent and if it isn't then it'll add the coefficient to the existing node with that exponent
    {
        r = new node(c,e,nullptr,nullptr);//we found the right spot to insert the new node
    }
    else
    {
        if(e == r->getEx())//if a node with that same exponent is found then we just add the new exponent
        {
            r->setCo(r->getCo() + c);//here we just add the coefficients if they have the same exponent
        }
        else if(e > r->getEx())
        {
            //in(num,r->getRight());
            if(r->getRight() == nullptr)
                r->setRight(new node(c,e,nullptr,nullptr));
            else
                in(c,e,r->getRight());

        }
        else
        {
            if(r->getLeft() == nullptr)
                r->setLeft(new node(c,e,nullptr,nullptr));
            else
                in(c,e,r->getLeft());
        }
    }//In all this we are just recursively going through and using the properties of binary trees that if the current node is not equal then if the search var is bigger then the nodes to the right have to be the only ones that can have it
}
void bst::insertN(int c ,int e)//parameters are the two doubles which are the coefficient and exponent and returns nothing
{
    if(root == nullptr)//if root is null means tree is empty
    {
        root = new node(c,e,nullptr,nullptr);//insert is a non recursive method if the tree is empty but it is recursive if it has to traverse
    }
    else
    {
        in(c,e,root);//if there's atleast a root then we can call the recursive helper insert function
    }
}
bool bst::se(int n,node* r)//the helper method to search and will do the actual recursion
{
    if(r == nullptr)//if the node is empty then we didn't find it
    {
        return false;//we didn't find it so ret false
    }
    else
    {
        if(n == r->getCo())//we found it
            return true;
        else if(n > r->getEx())//using tree properties, going to the correct subtree
        {
            if(r->getRight() == nullptr)
                return false;
            else
                se(n,r->getRight());
        }
        else//using tree properties, going to the correct subtree
        {
            if(r->getLeft() == nullptr)
                return false;
            else
                se(n,r->getLeft());
        }
    }
    return false;//necessary for it to compile
}
bool bst::searchN(int n)//takes an int to search it and will return if it's found or not.
{
    if(root == nullptr)//if tree is empty we return false
    {
        return false;//search is a non recursive method if the tree is empty but it is recursive if it has to traverse
    }
    else
    {
        return se(n,root);//call the recursive search method
    }
}
double bst::evaluate(double a, double b, node* n)//recursive method that will give the value of the bounded integral
{
    if(n != nullptr)//go until base case hits that n is null
    {
        double newexp = n->getEx() + 1;
        double newco = n->getCo() / (newexp * 1.0);//finding the integral
        double val = newco * pow(b,newexp);//plugging in
        double val2 = newco * pow(a,newexp);//plugging in
        return val - val2 + evaluate(a, b,n->getLeft()) + evaluate(a, b, n->getRight());//recursing
    }
    return 0;
}
double bst::evaluateTrig(double a, double b)//will take two bounds and evaluate the trig vector
{
    double ret;
    unsigned int i = 0;
    if(v.size() == 0)//obviously if it's empty then it will be 0
        return 0;
    while(i < v.size())//go until we run out of nodes in the vector
    {//cout << "EVALUATE TRIG ITERATES" << endl;
        node temp = v[i];//storing the node in a temp for ease
        double c = temp.getCo() / temp.getEx();//chain rule
        double val, val2;
        if(temp.getS() == 1)//if it's SIN
        {
            val = -1 * cos(b*temp.getEx());
            val2 = -1 * cos(a*temp.getEx());
            ret += c * (val - val2);//plugging in and using chain rule to get an answer
        }
        else if(temp.getS() == 2)//if its COS
        {
            val = sin(b*temp.getEx());
            val2 = sin(a*temp.getEx());
            ret += c * (val - val2);//plugging in and using chain rule to get an answer
        }
        else// if its SEC^2
        {
            val = tan(b*temp.getEx());
            val2 = tan(a*temp.getEx());
            ret += c * (val - val2);//plugging in and using chain rule to get an answer
        }
        i++;//traversing through the vector
    }
    return ret;
}
string bst::print(node* n)//will print the non trig nodes of the tree
{
    if(n)
    {
        string ret = print(n->getRight());//post order traversal
        double newco = 0, newexp = 0;
        newexp = n->getEx() + 1;
        newco = n->getCo() / (newexp * 1.0);//integrating
        string add;
        if(floor(newco) == newco)//deciding if it's a fraction or not
        {
            if(newco == -1)
                add = "-x";
            else if(newco < 0)//if it's negative then it'll have a minus in it anyways
                add = NumberToString(newco) + "x";// + NumberToString(newexp) + " ";
            else if(newco != 1)//if it's not 1 then we put a plus in front
                add = "+" + NumberToString(newco) + "x";// + NumberToString(newexp) + " ";
            else//this is if it's just a 1 then we just put x
                add = "+x";
        }
        else
        {
            int gcd = GCD(abs(n->getCo()),abs(newexp));//finding the gct
            if((n->getCo() <0 && newexp>0) || (n->getCo()>0 && newexp<0))
                add = "-(" + NumberToString(abs(n->getCo()/gcd)) + "/" + NumberToString(abs(newexp/gcd)) +")x";
            else if(n->getCo() < 0 && newexp < 0)
                add = "+(" + NumberToString(abs(n->getCo()/gcd)) + "/" + NumberToString(abs(newexp/gcd)) +")x";
            else
                add = "+(" + NumberToString(n->getCo()/gcd) + "/" + NumberToString(newexp/gcd) +")x";
        }//outputting correct signs based on if the denominator is what and numerator is what
        if(newexp == 1)//making the output prettier
            add += " ";
        else//putting the exponent in there
            {add += "^" + NumberToString(newexp) + " ";}//string add = atof(newco.c_str()) + "x^" + atof(newexp.c_str());ret += add;
        ret += add;
        ret += print(n->getLeft());//part of the postorder traversal
        return ret;//returning it which builds our string representation
    }
    return "";
}
string bst::printTrig()
{
    string ret;
    unsigned int i= 0;
    while(i < v.size())//going through the vector
    {
        node temp = v[i];
        double newexp = temp.getEx();
        double newco = temp.getCo() / newexp;//integrating//cout << "newexp:" << newexp << "newco: " << newco << endl;
        if(temp.getS() == 1)//making it negative if we're integrating sin x
            newco *= -1;//cout << "newco: " << newco << endl;
        string add;
        if(floor(abs(newco)) == abs(newco))//if its not a fraction
        {//cout <<"print trig If" << endl;
            if(newco == -1)
                add = "-";
            else if(newco < 0)//if its negative we don't need a sign
                add = NumberToString(newco);// + NumberToString(newexp) + " ";
            else if(newco == 1)//pretty formatting
                add = "+";
            else
                add = "+" + NumberToString(newco);// + NumberToString(newexp) + " ";
        }
        else
        {//outputting correct signs based on if the denominator is what and numerator is what//cout <<"print trig else" << endl;
            int gcd = GCD(abs(temp.getCo()),abs(newexp));
            if(temp.getS() == 1)//we do it differently if it's a sin x
            {
                if((temp.getCo() <0 && newexp>0) || (temp.getCo()>0 && newexp<0))
                    add = "+(" + NumberToString(abs(temp.getCo()/gcd)) + "/" + NumberToString(abs(newexp/gcd)) +")";
                else if(temp.getCo() < 0 && newexp < 0)
                    add = "-(" + NumberToString(abs(temp.getCo()/gcd)) + "/" + NumberToString(abs(newexp/gcd)) +")";
                else
                    add = "-(" + NumberToString(temp.getCo()/gcd) + "/" + NumberToString(newexp/gcd) +")";
            }
            else if(newco < 0)// if its negative we pull the negative to the outside
            {
                add = "-(" + NumberToString(abs(temp.getCo()/gcd)) + "/" + NumberToString(abs(newexp/gcd)) +")";
            }
            else
            {
                add = "+(" + NumberToString(abs(temp.getCo()/gcd)) + "/" + NumberToString(abs(newexp/gcd)) +")";
            }
        }
        if(temp.getS() == 1)//just putting the trig function in there and the inner coefficient
        {
            if(temp.getEx() != 1)
                add += "cos("+NumberToString(temp.getEx()) + "x) ";
            else
                add += "cos(x) ";
        }
        else if(temp.getS() == 2)//just putting the trig function in there and the inner coefficient
        {
            if(temp.getEx() != 1)
                add += "sin("+NumberToString(temp.getEx()) + "x) ";
            else
                add += "sin(x) ";
        }
        else if(temp.getS() == 3)//just putting the trig function in there and the inner coefficient
        {
            if(temp.getEx() != 1)
                add += "tan("+NumberToString(temp.getEx()) + "x) ";
            else
                add += "tan(x) ";
        }//        add += NumberToString(temp->getEx()) + "x ";
        ret += add;
        i++;
    }
    return ret;
}
void bst::inorder(node* n)//used for debugging
{//    cout << "Inside inorder" << endl;
    if(n != nullptr)
    {//        cout << "inside inorder if" << endl;
        inorder(n->getLeft());
        cout << n->getS() << " " << n->getCo() << " " << n->getEx() << ",";
        inorder(n->getRight());
    }//    cout<<endl;
}
void bst::trig()//used for debugging
{
    unsigned int count = 0;
    while(count < v.size())
    {
        node n = v[count];
        cout << n.getS() << " " << n.getCo() << " " << n.getEx() << ",";
        count++;
    }
    cout << endl;
}
void bst::clearTrig()//clears the vector
{
    v.clear();
}
