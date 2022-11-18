#include <iostream>
#include <string>
#include <cassert>
using namespace std;

void swap(string &s1, string &s2)       //string swap function
{
    string temp=s1;
    s1=s2;s2=temp;
}

int appendToAll(string a[], int n, string value)
{
    if(n<0) return -1;
    for(int i=0;i<n;i++)
        a[i]=a[i]+value;
    return n;
}

int lookup(const string a[], int n, string target)
{
    if(n<0) return -1;
    for(int i=0;i<n;i++)
        if(a[i]==target)    return i;
    return -1;
}

int positionOfMax(const string a[], int n)
{
    if(n<=0) return -1;
    int pos=0;                          //records the array pos of current max
    for(int i=0;i<n;i++)
        if(a[i]>a[pos])  pos=i;         //compare string directly using '>'
    return pos;
}

int rotateLeft(string a[], int n, int pos)
{
    if(n<0||pos<0||pos>n-1) return -1;  //pos should be within array size
    string s=a[pos];                    //store value for swapping to end
    for(int i=pos;i<n-1;i++)
        a[pos]=a[pos+1];                //overwrite each element to the left
    a[n-1]=s;
    return pos;
}

int countRuns(const string a[], int n)
{
    if(n<0) return -1;
    if(n==0) return 0;                  //for n=0, there is no run
    int cnt=1;                          //for n>0, array has at least 1 run
    for(int i=0;i<n-1;i++)
        if(a[i]!=a[i+1]) cnt++;         //count the times element changes
    return cnt;
}

int flip(string a[], int n)
{
    if(n<0) return -1;
    for(int i=0;i<n/2;i++)      //first half of the array swapped, left out center
        swap(a[i],a[n-1-i]);
    return n;
}

int differ(const string a1[], int n1, const string a2[], int n2)
{
    if(n1<0 || n2<0) return -1;
    int n; if(n1<n2) n=n1; else n=n2;   //decide which one runs out first
    for(int i=0;i<n;i++)
        if(a1[i]!=a2[i])  return i;
    return n;                   //return n if arrays are equal to the point of n
}

int subsequence(const string a1[], int n1, const string a2[], int n2)
{
    if(n1<0 || n2<0) return -1;
    if(n2==0)   return 0;               //sequence of any sequence, hence pos=0
    for(int i=0;i<n1-n2+1;i++)
        if(a1[i]==a2[0])
        {
            int flag=1;
            for(int j=0;j<n2;j++)       //check through following strings
                if(a1[i+j]!=a2[j]) {flag=0;break;}
            if(flag)    return i;
        }
    return -1;
}

int lookupAny(const string a1[], int n1, const string a2[], int n2)
{
    for(int i=0;i<n1;i++)
        for(int j=0;j<n2;j++)
            if(a1[i]==a2[j])    return i;
    return -1;
}

int split(string a[], int n, string splitter)
{
    if(n<0) return -1;
    int i=0;                        //the idea of quick sort
    for(int j=0;j<n;j++)            //i always <=j, tracks the current lower swap position
        if(a[j]<splitter)
            swap(a[j],a[i++]);      //smaller strings all swapped to the left side
    int temp=i;
    for(int j=i;j<n;j++)            //find a[j]==splitter that are not moved yet
        if(a[j]==splitter)
            swap(a[j],a[temp++]);   //make sure all a[j]==splitter are in the middle
    return i;
}

int main()
{
    string h[7] = { "rishi", "margaret", "gordon", "tony", "", "john", "liz" };
    assert(lookup(h, 7, "john") == 5);
    assert(lookup(h, 7, "gordon") == 2);
    assert(lookup(h, 2, "gordon") == -1);
    assert(positionOfMax(h, 7) == 3);

    string g[4] = { "rishi", "margaret", "liz", "theresa" };
    assert(differ(h, 4, g, 4) == 2);
    assert(appendToAll(g, 4, "?") == 4 && g[0] == "rishi?" && g[3] == "theresa?");
    assert(rotateLeft(g, 4, 1) == 1 && g[1] == "liz?" && g[3] == "margaret?");

    string e[4] = { "gordon", "tony", "", "john" };
    assert(subsequence(h, 7, e, 4) == 2);

    string d[5] = { "margaret", "margaret", "margaret", "tony", "tony" };
    assert(countRuns(d, 5) == 2);

    string f[3] = { "liz", "gordon", "tony" };
    assert(lookupAny(h, 7, f, 3) == 2);
    assert(flip(f, 3) == 3 && f[0] == "tony" && f[2] == "liz");

    assert(split(h, 7, "liz") == 3);

    cout << "All tests succeeded" << endl;
    
    string pm[6] = { "david", "liz", "margaret", "tony", "gordon", "boris" };
    int x = split(pm, 6, "john");  cout<<x<<endl;
    for(int i=0;i<6;i++)    cout<<pm[i]<<" "; cout<<endl;
    string pm2[5] = { "margaret", "theresa", "liz", "rishi", "rishi"};
    int y = split(pm2, 5, "rishi"); cout<<y<<endl;
    for(int i=0;i<5;i++)    cout<<pm2[i]<<" "; cout<<endl;
    
    return 0;
}
