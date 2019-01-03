//
//  main.cpp
//  day7
//
//  Created by Magnus Hall on 11/12/2018.
//  Copyright © 2018 Magnus Hall. All rights reserved.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <algorithm>

using namespace std;

vector<string> ReadIn(string const & address);

vector<char> Partlist(vector<string> const& v,vector<pair<char,char>> & );



int main(int argc, const char * argv[]) {
    
    vector<string> input = ReadIn("/Users/magnushall/Desktop/coding/AoC/day7/input.txt");
    vector<pair<char,char>> orders;
    vector<char> cleanInput = Partlist(input,orders);
    /*for(pair<char,char> o:orders){
        cout<<o.first<<endl;
    }*/
    for(char i:cleanInput){
        cout<<i<<endl;
    }
    cout<<"  --------  "<<endl;
    
    bool sorting = true;
    while(sorting){
        sorting = false;
        for(pair<char,char> o:orders){
            int i=0;
            int j=0;
            for(int k=0;k<cleanInput.size();k++){
                if(cleanInput[k]==o.first){
                    i=k;
                }
                if(cleanInput[k]==o.second){
                    j=k;
                }
            }
            if(i>j){
                char temp1 = cleanInput[i];
                char temp2 = cleanInput[j];
                cleanInput[i]=temp2;
                cleanInput[j]=temp1;
                sorting = true;
            }
        }
    }

    for(char i:cleanInput){
        cout<<i<<endl;
    }
    vector<char> fullyOrdered;
    for(int i =0;i<cleanInput.size();i++){
        pair<char,char> temp;
        temp.first = cleanInput[i];
        temp.second = cleanInput[i+1];
        if(find(orders.begin(),orders.end(),temp)!=orders.end()){
            fullyOrdered.push_back(cleanInput[i]);
            fullyOrdered.push_back('|');
        }
        else{
            fullyOrdered.push_back(cleanInput[i]);
        }
    }
    for(char f:fullyOrdered){
        cout<<f;
    }
    
    
    
    
    return 0;
}

vector<string> ReadIn(string const & address){
    ifstream data;
    vector<string> tempvector;
    data.open(address);
    if(data.is_open()){
        //cout<<"open";
        while(!data.eof()){
            string temp;
            getline(data,temp,'\n');
            tempvector.push_back(temp);
        }
    }
    data.close();
    return tempvector;
}

vector<char> Partlist(vector<string> const& input, vector<pair<char,char>> & orders){
    
    vector<char> output;
    
    for(string i:input){
        //cout<<i<<" -- "<<endl;
        //cout<<i[5]<<" - "<<i[36]<<endl;
        pair<char,char> temp;
        temp.first = i[5];
        temp.second = i[36];
        
        orders.push_back(temp);
        if(find(output.begin(), output.end(), i[5]) == output.end()){
            output.push_back(i[5]);
        }
        if(find(output.begin(), output.end(), i[36]) == output.end()){
            output.push_back(i[36]);
        }
    }
    return output;
}
