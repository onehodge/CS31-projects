#include <iostream>
#include <string>
using namespace std;

bool checkState(string state)
{
    string code="AL AK AZ AR CA CO CT DE FL GA HI ID IL IN IA KS KY LA ME MA MD MI MN MS MO MT NE NV NH NJ NM NY NC ND OH OK OR PA RI SC SD TN TX UT VT VA WA WV WI WY";
    return (code.find(state)!=string::npos);
}

bool isValidPollString(string pd)
{
    int pos=0;
    for(int i=0;i<pd.length();i++)
    {
        if(pd[i]==' '||pd[i+1]==' ')    return false;                               //check two at a time so cases like "L " doesnt pass checkState
        if(pos==0)
        {
            string state = string()+char(toupper(pd[i]))+char(toupper(pd[i+1]));
            //cout<<state<<endl;
            if(!checkState(state))  return false;   else {pos=2; i++;}
        }
        else
        {
            if(!isalpha(pd[i]) && !isdigit(pd[i]) && pd[i]!=',')  return false;     //make sure there is no other characters like '+'
            if(isalpha(pd[i-1]) && !isdigit(pd[i]) && pd[i]!=',') return false;     //make sure no two consecutive party letter
            if(pd[i]==',')  {if(!isalpha(pd[i-1]))   return false;  pos=0;}         //make sure doesnt end with a lone number
        }
    }
    return true;
}

int countSeats(string pd, char party, int& seatCount)
{
    if(!isValidPollString(pd))    return 1;
    if(!isalpha(party)) return 2;
    seatCount=0;                                    //make sure seatcount starts with 0 instead of numbers like -888
    for(int i=2;i<pd.length();i++)
    {
        if(toupper(pd[i])==toupper(party))
        {
            int k=i-1,num=0,cnt=1;
            while(isdigit(pd[k]))
            {
                num+=(pd[k]-'0')*cnt;               //multiply each digit by their respective positions in 1,10,100
                cnt*=10;k--;
            }
            seatCount+=num;
        }
        if(pd[i]==',')  i+=2;                       //skips the state code
    }
    return 0;
}

int main()
{
    string s;int num;char p;
    getline(cin,s);
    //cout<<isValidPollString(s)<<endl;
    if(isValidPollString(s))
    {
        cin>>p;
        countSeats(s,p,num);
        cout<<num<<endl;
    }
    else    cout<<"invalid\n";
    return 0;
}

//scp Desktop/poll.cpp classump@cs31.seas.ucla.edu:
//ssh classump@cs31.seas.ucla.edu
//curl -s -L https://cs.ucla.edu/classes/fall22/cs31/Utilities/p3tester | bash

