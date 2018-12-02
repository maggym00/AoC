//
//  main.cpp
//  day2
//
//  Created by Magnus Hall on 02/12/2018.
//  Copyright © 2018 Magnus Hall. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <regex>

using namespace std;

char* construct_2_regexp(char a){
    char *regexp = new char[17];
    regexp[0]='[';
    regexp[1]='^';
    regexp[2]=a;
    regexp[3]=']';
    regexp[4]='*';
    regexp[5]=a;
    regexp[6]='[';
    regexp[7]='^';
    regexp[8]=a;
    regexp[9]=']';
    regexp[10]='*';
    regexp[11]=a;
    regexp[12]='[';
    regexp[13]='^';
    regexp[14]=a;
    regexp[15]=']';
    regexp[16]='*';
    return regexp;
}

char* construct_3_regexp(char a){
    char *regexp = new char[23];
    regexp[0]='[';
    regexp[1]='^';
    regexp[2]=a;
    regexp[3]=']';
    regexp[4]='*';
    regexp[5]=a;
    regexp[6]='[';
    regexp[7]='^';
    regexp[8]=a;
    regexp[9]=']';
    regexp[10]='*';
    regexp[11]=a;
    regexp[12]='[';
    regexp[13]='^';
    regexp[14]=a;
    regexp[15]=']';
    regexp[16]='*';
    regexp[17]=a;
    regexp[18]='[';
    regexp[19]='^';
    regexp[20]=a;
    regexp[21]=']';
    regexp[22]='*';
    return regexp;
}

regex regforcomp(string input,int n){
    char temp[input.size()];
    for(int i=0;i<input.size();i++){
        if(i==n){
            temp[i]='.';
        }
        else{
            temp[i]=input[i];
        }
    }
    return regex(temp);
}







int main(int argc, const char * argv[]) {
    
    ifstream data;
    
    vector<string> codes;
    data.open("/Users/magnushall/Desktop/coding/AoC/day2/input.csv");
    if(data.is_open()){
        while(!data.eof()){
            string temp;
            getline(data,temp,',');
            codes.push_back(temp);
        }
        int twoCount=0;
        int threeCount=0;
        char alphabet[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
        vector<regex> twocodes;
        vector<regex> threecodes;
        for(char a:alphabet){
            twocodes.push_back(regex(construct_2_regexp(a)));
            threecodes.push_back(regex(construct_3_regexp(a)));
        }
        
        for(string c:codes){
            //cout<<c<<endl;
            bool twomatch = false;
            bool threematch = false;
            for(int i=0;i<twocodes.size();i++){
                if(!threematch){
                    if(regex_match(c,threecodes[i])){
                        threeCount+=1;
                        threematch=true;

                    }
                }
                if(!twomatch){
                    if(regex_match(c,twocodes[i])){
                        //cout<<alphabet[i]<<" : "<<c<<endl;
                        twoCount+=1;
                        //cout<<twoCount<<endl;
                        twomatch=true;
                    }
                }
                if(twomatch&&threematch){
                    break;
                }
                
            }
        }
        cout<<twoCount<<" "<<threeCount<<endl;
    }
    
    for(int i=0;i<codes.size();i++){
        for(int l = 0; l<codes[0].size();l++){
            regex check = regforcomp(codes[i], l);
            for(int j=i+1; j<codes.size();j++){
                if(regex_match(codes[j],check)){
                    
                    cout<<j<<" : "<<codes[j]<<"\n"<<i<<" : "<<codes[i]<<" : "<<codes[i][l]<<endl;
                    
                }
            }
        }
    }
    
    
    
    
    
    
    return 0;
}
