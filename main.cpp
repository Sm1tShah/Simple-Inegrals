//Smit Shah
//TRIG FUNCTIONS
#include <iostream>
#include "bst.h"
#include <fstream>
#include <iomanip>
#include <cmath>
#include <stdlib.h>
#include <string>
#include <sstream>
using namespace std;
template <typename T>
string NumberToString(T pNumber)//handy way to convert ints and doubles to strings
{
 ostringstream o;
 o << pNumber;
 return o.str();
}
void setup(string all, int &p, int &m)//will process where the next valid plus or minus is
{//cout << "setup line: " << all << endl;
    p = all.find("+");//    cout << "p in setup:" << p << endl;
    m = all.find("-");
    if(m == 0)//if it's for example "-x"
    {
        int ef = all.substr(1).find("-");//then we find the next minus
        if(ef == -1)//if we didn't find a new minus then it means
        {
            m = -1;//no more minuses in the expression
        }
        else//means there's more minuses in the expression
        {
            int c = m+1, allofit = all.length() -1;
            bool done = false;
            while(!done && c < allofit)//we loop through the expression until
            {
                if(all[c] == '-')//we find a minus so we store it and end the loop
                {m = c; done = true;}
                c = c + 1;
            }
        }
    }
        string s = NumberToString(all[m-1]) + NumberToString(all[m]);//        cout << "THIS IS THE S:" << s << endl;
        if(s == "^-" || s == "n-" || s=="s-" || (s=="2-" && all[m-3] == 'c'))//we see if the exponent is negative or if a trig function has a negative argument
        {
            int ef = all.substr(m+1).find("-");//if we don't find it in the rest of the string
            if(ef == -1)
            {
                m = -1;//then it's not in the expression
            }
            else
            {
                int c = m+1, allofit = all.length() -1;
                bool done = false;
                while(!done && c < allofit)//and if we do find it in the rest of the expression then we loop to find it and set it
                {
                    if(all[c] == '-')
                    {m = c; done = true;}
                    c = c + 1;
                }
            }
        }

}
int main()
{
    bst tree;
    ifstream inputfile("integralsXC.txt");//Make an input file that reads from integrals.txt
    ofstream outputfile("results.txt");//Make an output file that outputs to results.txt
    if (inputfile.is_open())//Use file.is_open() to make sure that the file is open
    {
        string all;
        bool done = false, i = false;
        int p =-1, m =-1, co=-1, ex=-1, old =1;//p and m stand for plus or minus
        int spec = -1, s = -1, c = -1, e = -1;//trig variables
        double a, b;//bounds for the integral
        while(!inputfile.eof())//no specified number of integrals so we will go till the end of the file
        {
            getline(inputfile,all);//reading the whole line as each line represents an integralcout << "whole line read: " << all << "ended" << endl;
            if(all == "")
            break;
            outputfile << showpoint << fixed <<  setprecision(3);//setting up the correct output format
            if(all.substr(0,1) == "|") //basically this would show that it's an anti derivative and has no bounds
            {//cout << "It's an antiderivative" << endl;
                i = false;
                all = all.substr(2,all.length()-5);//This just trims the whole line into just the expression that we need to integrate

            }
            else//has bounds in it
            {
                i = true;//cout <<"It's an integral" << endl;
                a = atof(all.substr(0,all.find("|")).c_str());//this will convert the first bound as a string into a double
                b = atof(all.substr(all.find("|")+1,all.find(" ")).c_str());//this will convert the second bound as a string into a doublecout << "a: " << a << " b: " << b << endl;
                all = all.substr(all.find(" ")+1);
                all = all.substr(0,all.length()-3);//This just trims the whole line into just the expression that we need to integrate
            }
                done = false;
                p = m = co = ex = s = c = e = spec = -1; //resetting variables before we read each term of the expression
                while(!done)//each iteration will deal with one term at a time
                {
                    string newall;
                    unsigned int index = 0;
                    int goalong = 0;
                    while(index < all.length())//going through the whole expression and removing spaces
                    {
                        if(all[index] != ' ')//will only add non space chars
                        {
                            newall += all[index];
                            goalong++;
                        }
                        index++;
                    }
                    all = newall;//we have an expression with no spacescout << "trimmed line: " << all << endl;cout << "Plus: " << p << " Minus: " << m << endl;
                    setup(all,p,m);//cout << "Plus: " << p << " Minus: " << m << endl;
                    s = all.find("i"); if(s!= -1)s--;//setting appropriate trig variables
                    c = all.find("c");
                    e = all.find("e"); if(e != -1)e--;//cout << "s:" << s << " c:" << c << " e:" << e << endl;//                    cout << ((p<0 || s < p) && (c<0 || s < c) && (e<0 ||s < e) && s!= -1) << endl;//                    cout << ((p<0 || s < m) && (c<0 || s < c) && (e<0 ||s < e) && s!= -1) << endl;
                    if(m==-1 || (p!= -1 &&p < m))//a plus occurs before a minus does
                    {
                        int expsign = all.find("^");
                        if(all[expsign-1] == 'c')//if it's a sec^2 then it doesn't count so we have to loop to find the next one
                        {
                            int c = expsign+1, allofit = all.length() -1;
                            bool d = false;
                            while(!d && c < allofit)
                            {
                                if(all[c] == '^')
                                {expsign = c; done = true;}
                                c = c + 1;
                            }
                        }
                        int xindex = all.find("x");//cout << "expsign: " << expsign << " xindex: " << xindex << endl;
                        if(xindex ==0)//check this because an X is the same as 1x and if x is the first thing then the coefficient has to be 1
                        {//cout <<"ENTERING IF" << endl;
                            co=1;//Coefficient defaults to 1 if no coefficient is there
                            if(expsign != -1 && (p ==-1 || expsign < p))//means the current term has an exponent sign in it
                            {//CHECKcout << "10p IF" << endl;//                                cout << "find ^ " << all.find("^") << " find empty space " << all.find(" ") << endl;//                                cout << all.substr(all.find("^"),all.find(" ")) << endl;
                                ex = atof(all.substr(all.find("^")+1,p).c_str());//cout << "EX HERE" << ex << endl;
                            }
                            else
                            {//cout << "10p ELSE" << endl;
                                ex = 1;//if nothing is there then we default to 1
                            }
                        }
                        else if((p<0 || s < p) && (c<0 || s < c) && (e<0 ||s < e) && s!= -1)//if a SIN IS UP NEXT
                        {
                            spec = 1;//cout << "SIN IS UP NEXT" << endl;
                            int f = all.find("i"); if(f != -1)f--;
                            int findx = all.find("x");//we find the appropriate symbols cout << "f: " << f << " findx" << findx << endl;
                            if(f == 0)//if there's no coefficients
                            {//cout <<"SIN IF" << endl;
                                co = 1;
                                if(all[findx-1] != 'n')//we check if there's anything between the x and the sin
                                    ex = atof(all.substr(f+3,findx).c_str());
                                else
                                    ex = 1;
                            }
                            else
                            {//cout <<"SIN ELSE" << endl;
                                co = atof(all.substr(0,f).c_str());
                                if(all[findx-1] == 'n')//we check if there's anything between the x and the sin
                                {//cout << "SIN ELSE, IF" << endl;
                                    ex = 1;
                                }
                                else
                                {//cout << "SIN ELSE ELSE" << endl;
                                    if(all[findx-1] == '-' && all[findx-2] == 'n')//we check if there's anything between the x and the sin
                                        ex = -1;
                                    else
                                        ex = atof(all.substr(f+3,findx).c_str());
                                }
                            }
                        }
                        else if((p<0 || c < p) && (s<0 || c < s) && (e<0 ||c < e) && c!= -1)//if a cos is up next
                        {
                            spec = 2;//setting it to 2 so we can add that into the vector later//cout << "COS IS UP NEXT" << endl;
                            int f = all.find("c");
                            int findx = all.find("x");//cout << "f: " << f << " findx" << findx << endl;
                            if(f == 0)
                            {//cout <<"COS IF" << endl;
                                co = 1;
                                if(all[findx-1] != 's')//we check if there's anything between the x and the cos
                                    ex = atof(all.substr(f+3,findx).c_str());
                                else
                                    ex = 1;//default of 1
                            }
                            else
                            {//cout <<"COS ELSE" << endl;
                                co = atof(all.substr(0,f).c_str());
                                if(all[findx-1] == 's')//we check if there's anything between the x and the cos
                                {//cout << "COS ELSE, IF" << endl;
                                    ex = 1;
                                }
                                else
                                {//cout << "COS ELSE ELSE" << endl;
                                    if(all[findx-1] == '-' && all[findx-2] == 's')//we check if there's anything between the x and the sin
                                        ex = -1;
                                    else
                                        ex = atof(all.substr(f+3,findx).c_str());//otherwise we read whatever is there
                                }
                            }
                        }
                        else if((p<0 || e < p) && (s<0 || e < s) && (c<0 ||e < c) && e!= -1)//if a sec^2 is up next
                        {
                            spec = 3;//we store that in here so we can add it to the vector latercout << "sec IS UP NEXT" << endl;
                            int f = all.find("e");if(f != -1)f--;
                            int findx = all.find("x");//cout << "f: " << f << " findx" << findx << endl;
                            if(f == 0)
                            {//cout <<"sec IF" << endl;
                                co = 1;
                                if(all[findx-3] != 'c')//we check if there's anything between the x and the sec
                                    ex = atof(all.substr(f+5,findx).c_str());
                                else
                                    ex = 1;//defaults to 1 if nothing is there
                            }
                            else
                            {//cout <<"sec ELSE" << endl;
                                co = atof(all.substr(0,f).c_str());
                                if(all[findx-3] == 'c')//we check if there's anything between the x and the sec
                                {//cout << "sec ELSE, IF" << endl;
                                    ex = 1;//defaults to 1 if nothing is there
                                }
                                else
                                {//cout << "sec ELSE ELSE" << endl;
                                    if(all[findx-1] == '-' && all[findx-4] == 'c')//we check if there's anything between the x and the sec
                                        ex = -1;//defaults to -1 if - is there
                                    else
                                        ex = atof(all.substr(f+5,findx).c_str());//we get whatever is there otherwise
                                }
                            }
                        }
                        else
                        {//cout <<"ENTERING ELSE" << endl;
                            if(expsign != -1 &&(p == -1 || expsign < p))//means the current term has an exponent sign in it//cout <<"1p IF" << endl;//atof(line.substr(0,comma).c_str())
                            {
                                co = atof(all.substr(0,all.find("x")).c_str());
                                ex = atof(all.substr(all.find("^")+1,p).c_str());//we read the things before the x and things after the exponent sign
                            }
                            else if(xindex != -1 &&(p == -1 || xindex < p))//means the term has an x in it
                            {//cout <<"1p ELSE IF" << endl;
                                co = atof(all.substr(0,all.find("x")).c_str());//we get the stuff between the start and the x
                                ex = 1; //it's 1 because the term has no ^ but has an x
                            }
                            else//it means its just a lone number
                            {//cout <<"1p ELSE" << endl;
                                co = atof(all.substr(0,p).c_str());//we get the stuff between the start and the x
                                ex = 0;//default of 0 if its a lone number
                            }

                        }
                        all = all.substr(p+1);//we processed the current term so we will move along the iteration
                        while(all[0] == ' ')
                        {
                            all = all.substr(1);
                        }//just trimming
                        co *= old;
                        old = 1;//this is what remembers if the next term should be positive or negative
                    }
                    else//p > m
                    {
                        int expsign = all.find("^");
                        if(all[expsign-1] == 'c')
                        {
                            int c = expsign+1, allofit = all.length() -1;
                            bool d = false;
                            while(!d && c < allofit)//making sure that the ^ is not the one inside sec^2 so we need a loop to find the next one
                            {
                                if(all[c] == '^')
                                {expsign = c; done = true;}
                                c = c + 1;
                            }
                        }
                        int xindex = all.find("x");//cout << "expsign: " << expsign << " xindex: " << xindex << endl;
                        if(xindex ==0)//check this because an X is the same as 1x and if x is the first thing then the coefficient has to be 1
                        {//cout <<"ENTERING IF m" << endl;
                            co=1;//Coefficient defaults to 1 if no coefficient is there
                            if(expsign != -1 && (m == -1 || expsign < m))//means the current term has an exponent sign in it
                            {
                                ex = atof(all.substr(all.find("^")+1,m).c_str());//we get whatever is there otherwise
                            }
                            else
                            {
                                ex = 1;//defaults to 1 if nothing is there
                            }
                        }
                        else if((m<0 || s < m) && (c<0 || s < c) && (e<0 ||s < e) && s!= -1)//SIN IS UP NEXT
                        {
                            spec = 1;//we store that in here so we can add it to the vector latercout << "SIN IS UP NEXTx" << endl;
                            int f = all.find("i"); f--;
                            int findx = all.find("x");
                            if(f == 0)//if the sin is the first term
                            {
                                co = 1;//default of 1
                                if(all[findx-1] != 'n')//we check if there's anything between the x and the sin
                                    ex = atof(all.substr(f+3,findx).c_str());//we get whatever is there otherwise
                                else
                                    ex = 1;//defaults to 1 if nothing is there
                            }
                            else
                            {//cout <<"SIN ELSE" << endl;
                                co = atof(all.substr(0,f).c_str());//we get what's between the start and the sin
                                if(all[findx-1] == 'n')
                                {//cout << "SIN ELSE, IF" << endl;
                                    ex = 1;//defaults to 1 if nothing is there
                                }
                                else
                                {//cout << "SIN ELSE ELSE" << endl;
                                    if(all[findx-1] == '-' && all[findx-2] == 'n')//we get what's there
                                        ex = -1;//defaults to -1 if - is there
                                    else
                                        ex = atof(all.substr(f+3,findx).c_str());//we get whatever is there otherwise
                                }
                            }
                        }
                        else if((m<0 || c < m) && (s<0 || c < s) && (e<0 ||c < e) && c!= -1)//COS IS UP NEXT
                        {
                            spec = 2;//we store that in here so we can add it to the vector later//cout << "COS IS UP NEXT m" << endl;
                            int f = all.find("c");
                            int findx = all.find("x");//cout << "f: " << f << " findx" << findx << endl;
                            if(f == 0)
                            {//cout <<"COS IF" << endl;
                                co = 1;//defaults to 1 if nothing is there
                                if(all[findx-1] != 's')//we check if there's anything between the x and the cos
                                    ex = atof(all.substr(f+3,findx).c_str());//we get whatever is there otherwise
                                else
                                    ex = 1;//defaults to 1 if nothing is there
                            }
                            else
                            {//cout <<"COS ELSE" << endl;
                                co = atof(all.substr(0,f).c_str());
                                if(all[findx-1] == 's')//we check if there's anything between the x and the cos
                                {//cout << "COS ELSE, IF" << endl;
                                    ex = 1;//defaults to 1 if nothing is there
                                }
                                else
                                {//cout << "COS ELSE ELSE" << endl;
                                    if(all[findx-1] == '-' && all[findx-2] == 's')//we check if there's anything between the x and the cos
                                        ex = -1;//defaults to -1 if - is there
                                    else
                                        ex = atof(all.substr(f+3,findx).c_str());//we get whatever is there otherwise
                                }
                            }
                        }
                        else if((m<0 || e < m) && (s<0 || e < s) && (c<0 ||e < c) && e!= -1)//sec2 is up next
                        {
                            spec = 3;//we store that in here so we can add it to the vector later cout << "sec IS UP NEXT" << endl;
                            int f = all.find("e");if(f != -1)f--;
                            int findx = all.find("x");//cout << "f: " << f << " findx" << findx << endl;
                            if(f == 0)
                            {//cout <<"sec IF" << endl;
                                co = 1;//defaults to 1 if nothing is there
                                if(all[findx-3] != 'c')//we check if there's anything between the x and the sec
                                    ex = atof(all.substr(f+5,findx).c_str());//we get whatever is there otherwise
                                else
                                    ex = 1;//defaults to 1 if nothing is there
                            }
                            else
                            {//cout <<"sec ELSE" << endl;
                                co = atof(all.substr(0,f).c_str());
                                if(all[findx-3] == 'c')//we check if there's anything between the x and the sec
                                {//cout << "sec ELSE, IF" << endl;
                                    ex = 1;//defaults to 1 if nothing is there
                                }
                                else
                                {//cout << "sec ELSE ELSE" << endl;
                                    if(all[findx-1] == '-' && all[findx-4] == 'c')//we check if there's anything between the x and the sec
                                        ex = -1;//defaults to -1 if - is there
                                    else
                                        ex = atof(all.substr(f+5,findx).c_str());//we get whatever is there otherwise
                                }
                            }
                        }
                        else
                        {//cout <<"ENTERING ELSE m" << endl;
                            if(expsign != -1 &&(m == -1 || expsign < m))//means the current term has an exponent sign in it
                            {//cout <<"1m IF" << endl;
                                //atof(line.substr(0,comma).c_str())
                                co = atof(all.substr(0,all.find("x")).c_str());
                                ex = atof(all.substr(all.find("^")+1,m).c_str());//we read the things before the x and things after the exponent sign
                            }
                            else if(xindex != -1 &&(m == -1 || xindex < m))//means the term has an x in it
                            {//cout <<"1m ELSE IF" << endl;
                                co = atof(all.substr(0,all.find("x")).c_str());//we get the stuff between the start and the x
                                ex = 1; //it's 1 because the term has no ^ but has an x
                            }
                            else//it means its just a lone number
                            {//cout <<"1m ELSE" << endl;
                                co = atof(all.substr(0,m).c_str());//we get the stuff between the start and the x
                                ex = 0;//default of 1 if it's a lone number
                            }

                        }
                        all = all.substr(m+1);//we processed the current term so we will move along the iteration
                        while(all[0] == ' ')
                        {
                            all = all.substr(1);
                        }//just trimming
                        co *= old;
                        old = -1;//the next upcoming sign is a negative so we make old negative so it'll make the next term negative
                    }
                    if(!done)
                    {//cout << "spec:" << spec << "                       Co: " << co << " Ex: " << ex << endl;
                        if(spec != 1 && spec != 2 && spec != 3)//if its not one of the trig functions
                            tree.insertN(co,ex);//add it to the tree itself
                        else
                            tree.insertTrig(spec,co,ex);//otherwise add it to the vector//cout<<"Printing tree ";tree.inorder(tree.getRoot()); cout << endl;
//                        tree.trig();
                        spec = -1;
                    }//cout << "ALTERED all:" << all << endl;
                    if(p == -1 && m == -1)//means that we processed all the terms and we should be done looping
                    {//cout << "Breaking out" << endl;
                        done = true;
                    }
                }
                string answer = tree.print(tree.getRoot()) + tree.printTrig();//getting the antiderivative
                if(answer[0] == '+')//if the first term is a plus then we don't need to print that so we trim it out
                    answer = answer.substr(1);
                if(!i)//if it's not an integral and just an antiderivative
                {
                    answer += "+ C";//we just put the C and then output it to the file
                    outputfile << answer << endl;
                }
                else//this means that it's a bounded integral
                {
                    double ans = tree.evaluate(a,b,tree.getRoot()) + tree.evaluateTrig(a,b);//we evaluate the integral using the two bounds
                    answer += ", " + NumberToString(a) + "|" + NumberToString(b) + " = ";//we make it so that the answer can be put in the back of the string
                    outputfile << answer << ans << endl;//we output to the file
                }
                tree.clearTrig();
                tree.setRoot(nullptr);//we clear the tree and the vector to make sure that next line we start a new
        }
    }
    inputfile.close();
    outputfile.close();//closing all files
    return 0;
}
