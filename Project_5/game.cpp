#include "utilities.h"
#include <iostream>
#include <iomanip>
#include <cstring>
#include <cctype>
#include <algorithm>
using namespace std;

const char WORDFILENAME[] = "/Users/onehodge/Desktop/Project_5/Project_5/words.txt";

bool checkLower(const char theWord[])
{
    for(int i=0;i<strlen(theWord);i++)
        if(!islower(theWord[i])) return false;
    return true;
}

bool checkVocab(const char words[][7], int nWords, const char theWord[])
{
    for(int i=0;i<nWords;i++)
        if(strcmp(words[i],theWord)==0) return true;
    return false;
}

int playOneRound(const char words[][7], int nWords, int wordnum)
{
    if(nWords<=0 || wordnum<0 || wordnum>=nWords) return -1;
    char ans[7],tans[7],guess[110]; int cnt=0,numg,nums;
    strcpy(ans,words[wordnum]);
    cout<<"Probe word: ";
    while(cin>>guess)
    {
        if(strcmp(guess,"codewordhaoji")==0)
        {
            cout<<ans<<endl;continue;
        }       //my codeword to cheat
        if(strlen(guess)<4 || strlen(guess)>6)
        {
            cout<<"Your probe word must be a word of 4 to 6 lower case letters."<<endl;
            cout<<"Probe word: "; continue;
        }
        if(!checkLower(guess))
        {
            cout<<"Your probe word must be a word of 4 to 6 lower case letters."<<endl;
            cout<<"Probe word: "; continue;
        }
        if(!checkVocab(words,nWords,guess))
        {
            cout<<"I don't know that word."<<endl;
            cout<<"Probe word: "; continue;
        }
        cnt++;numg=0;nums=0;
        if(strcmp(guess,ans)==0) break;
        strcpy(tans,ans);                           //temporary ans, can be modified to mark used letters
        for(int i=0;i<strlen(guess);i++)
            if(guess[i]==tans[i])
            {
                numg++;
                tans[i]='X';guess[i]='Y';           //mark the used letters so it doesnt overcount
            }
        for(int i=0;i<strlen(guess);i++)
            for(int j=0;j<strlen(ans);j++)
                if(guess[i]==tans[j])
                {
                    nums++;
                    tans[j]='X';guess[i]='Y';
                }
        cout<<"Golds: "<<numg<<", Silvers: "<<nums<<endl;
        cout<<"Probe word: ";
    }
    return cnt;
}
int main()
{
    char w[9000][7];
    int n = getWords(w, 9000, WORDFILENAME),randi;
    if(n<1) {cout<<"No words were loaded, so I can't play the game."<<endl;return 0;}
    int rnd,score,mini,maxi;double sum=0,avg;
    cout<<"How many rounds do you want to play? "; cin>>rnd;
    if(rnd<=0) cout<<"The number of rounds must be positive."<<endl;
    for(int i=1;i<=rnd;i++)
    {
        cout<<endl<<"Round "<<i<<endl;
        randi=randInt(0,n-1);                       //print the word before going into the round
        cout<<"The hidden word is "<<strlen(w[randi])<<" letters long."<<endl;
        score=playOneRound(w,n,randi);
        if(score==1) cout<<"You got it in 1 try."<<endl;
        else cout<<"You got it in "<<score<<" tries."<<endl;
        if(i==1) {mini=score;maxi=score;}
        else {mini=min(score,mini);maxi=max(score,maxi);}
        sum+=score;avg=sum/i;
        cout<<fixed;cout<<setprecision(2);
        cout<<"Average: "<<avg<<", minimum: "<<mini<<", maximum: "<<maxi<<endl;
    }
    return 0;
}
