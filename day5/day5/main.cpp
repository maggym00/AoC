//
//  main.cpp
//  day5
//
//  Created by Magnus Hall on 10/12/2018.
//  Copyright © 2018 Magnus Hall. All rights reserved.
//
// massive numbers of characters vanishing
// don't know why
// find out

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <cctype>

using namespace std;

string ReadIn(string const & address);

string snip2(string const& s,int i);

string snip(string const& s, int i, int j);

int main(int argc, const char * argv[]) {
    
    string input =  /*"dabAcCaCBAcCcaDA";*/ReadIn("/Users/magnushall/Desktop/coding/AoC/day5/input.txt");
    
    bool reacting=true;
    int count=0;
    while(reacting){
        //cout<<input.length()<<" -------------------------- "<<endl;
        bool stillreacting = false;
        for(int i=0;i<input.size()-1;i++){
            if(islower(input[i])){
                if(input[i]==tolower(input[i+1]) && input[i]!=input[i+1]){
                    //cout<<input<<endl;
                    cout<<" - "<<input[i+1]<<input[i]<<endl;
                    input = snip2(input,i);
                    //cout<<" = "<<input<<endl;
                    cout<<input.length()<<endl;
                    
                    stillreacting = true;
                    count+=2;
                }
            }
            else{
                if(input[i]==toupper(input[i+1])&& input[i]!=input[i+1]){
                    //cout<<input<<endl;
                    cout<<" - "<<input[i+1]<<input[i]<<endl;
                    input = snip2(input,i);
                    //cout<<" = "<<input<<endl;
                    cout<<input.length()<<endl;
                    
                    stillreacting=true;
                    count+=2;
                }
            }
            
        }
        if(!stillreacting){
            reacting = false;
        }
    }
    char l_alphabet[]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    char u_alphabet[]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    
    pair<char,int> best;
    best.first='a';
    best.second=input.size();
    for(int i=0;i<26;i++){
        string tempinput = input;
        for(int j=0; j< tempinput.size();j++){
            if(tempinput[j]==l_alphabet[i]||tempinput[j]==u_alphabet[i]){
                tempinput=snip(tempinput,j,j+1);
                j--;
            }
        }
        bool reacting=true;
        int count=0;
        while(reacting){
            //cout<<input.length()<<" -------------------------- "<<endl;
            bool stillreacting = false;
            for(int i=0;i<tempinput.size()-1;i++){
                if(islower(tempinput[i])){
                    if(tempinput[i]==tolower(tempinput[i+1]) && tempinput[i]!=tempinput[i+1]){
                        //cout<<tempinput<<endl;
                        cout<<" - "<<tempinput[i+1]<<tempinput[i]<<endl;
                        tempinput = snip2(tempinput,i);
                        //cout<<" = "<<tempinput<<endl;
                        cout<<tempinput.length()<<endl;
                        
                        stillreacting = true;
                        count+=2;
                    }
                }
                else{
                    if(tempinput[i]==toupper(tempinput[i+1])&& tempinput[i]!=tempinput[i+1]){
                        //cout<<tempinput<<endl;
                        cout<<" - "<<tempinput[i+1]<<tempinput[i]<<endl;
                        tempinput = snip2(tempinput,i);
                        //cout<<" = "<<tempinput<<endl;
                        cout<<tempinput.length()<<endl;
                        
                        stillreacting=true;
                        count+=2;
                    }
                }
                
            }
            if(!stillreacting){
                reacting = false;
            }
        }
        if(tempinput.size()<best.second){
            best.second=tempinput.size();
            best.first=l_alphabet[i];
        }
        
    }
    cout<<best.first<<" "<<best.second<<endl;
    return 0;
}


// removes portion of string - returning string up to (not inc) i, and from j onwards
// done in a general way as opposed to specific for cutting out 2 - can be reused
string snip(string const& s,int i, int j){
    //cout<<s.size()<<"  ooooooo "<<endl;
    //cout<<j-i<<endl;
    string temp1=s.substr(0,i);
    string temp2=s.substr(j,string::npos);
    string returnstring = temp1+temp2;
    return returnstring;
}

string snip2(string const& s,int i){

    string temp1=s.substr(0,i);
    string temp2=s.substr(i+2,string::npos);
    string returnstring = temp1+temp2;
    return returnstring;
}


string ReadIn(string const & address){
    ifstream data;
    string temp;
    data.open(address);
    if(data.is_open()){
        getline(data,temp,' ');
    }
    data.close();
    return temp;
}

