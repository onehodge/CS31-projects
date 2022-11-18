#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main()
{
    string name="",job=""; int kid; double pay,ans=0;
    //input
    cout<<"Name: ";getline(cin,name);
    cout<<"Taxable income: ";cin>>pay;cin.ignore(256, '\n');
    cout<<"Occupation: ";getline(cin,job);
    cout<<"Number of children: ";cin>>kid;
    cout<<"---"<<endl;
    //wrong input and early exit
    if(name==""){cout<<"You must enter a name"<<endl;return 0;}
    if(pay<0){cout<<"The taxable income must not be negative"<<endl;return 0;}
    if(job==""){cout<<"You must enter an occupation"<<endl;return 0;}
    if(kid<0){cout<<"The number of children must not be negative"<<endl;return 0;}
    //tax calculation
    //i use min function to determine whichever comes first, whether to end or keep going
    ans+=0.04 * min(55000.0,pay);                       //tax plan point 1
    if(pay>55000.0)
    {
        if(job=="teacher"||job=="nurse")                //tax plan point 2: exceptions
            ans+=0.05 * min(70000.0,pay-55000.0);
        else    ans+=0.07 * min(70000.0,pay-55000.0);   //tax plan point 2
    }
    if(pay>125000.0) ans+=0.093 * (pay-125000.0);       //tax plan point 3
    if(pay<125000.0) ans-=kid*200.0; if(ans<0) ans=0;   //tax plan point 4
    //output
    cout.setf(ios::fixed);cout.precision(2);            //set to 2 decimal places
    cout<<name<<" would pay $"<<ans<<endl;
    return 0;
}
