//
//  main.cpp
//  day1
//
//  Created by Magnus Hall on 01/12/2018.
//  Copyright © 2018 Magnus Hall. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

int returnNum(string in, bool neg){
    //cout<<in<<endl;
    if(neg){
        char temp[in.size()-1];
        for(int i=1; i<in.size();i++){
            temp[i-1]=in[i];
        }
        //cout<<stoi(temp)<<endl;
        return stoi(temp);
    }
    else{
        return stoi(in);
    }
    
}

int main(int argc, const char * argv[]) {
    
    int i=0;
    int iterations = 0;
    
    ifstream data("/Users/magnushall/Desktop/coding/AoC/day1/input.csv");
    vector<int> list;
    if(data.is_open()){
        
        cout<<"open"<<endl;
        while(!data.eof()){
            string temp;
            getline(data,temp,',');
            //cout<<temp<<endl;;
            if(temp[0]=='-'){
                int n=returnNum(temp, true);
                i-=n;
                list.push_back(-1*n);
            }
            
            else{
                int n=returnNum(temp, false);
                i+=n;
                list.push_back(n);
            }
        }
        data.close();
    }
    //cout<<i<<endl;
    
    clock_t begin=clock();
    
    int cap = 10000;
    int best;
    int best_value = 200000;
    bool found = false;
    
    for(int i=0;i<list.size();i++){
        //cout<<i<<" of "<<list.size()<<endl;
        int count = 0;
        int sum = 0;
        found = false;
        for(int j=i;j<list.size();j++){
            sum+=list[j];
            count+=1;
            iterations+=1;
            if(sum==0 && i+count<best_value){
                cout<<"found";
                best= i;
                best_value=count;
                found = true;
                break;
            }
        }
        while(sum!=0 && count<cap*list.size() && i+count<best_value && !found){
            //cout<<count<<endl;
            for(int j = 0; j<list.size(); j++){
                iterations+=1;
                sum+=list[j];
                count+=1;
                if(sum==0 && i+count<best_value){
                    cout<<"found"<<endl;
                    best= i;
                    best_value=count+i;
                    cout<<best<<" - "<<count<<endl;
                    found = true;
                    break;
                }
            }
            
        }
        
    }
    int freq = 0;
    for(int i =0; i<best;i++){
        freq+=list[i];
    }
    clock_t end = clock();
    cout<<freq<<endl;
    cout<<double(end-begin)/CLOCKS_PER_SEC<<endl;
    cout<<iterations<<endl;
    
    
    
    /*
     int freq=0;
     
     for(int x=0;x<best;x++){
     freq += list[x];
     }
     for(int l:list){
     cout<<l<<" ";
     }
     cout<<endl;
     
     cout<<freq<<endl;
     */
    
    
    /*
    vector<int> freqs = {0};
    
    bool repeated=false;
    int count=0;
    
    while(!repeated){
        cout<<"running"<<endl;
        for(int l:list){
            if(repeated){
                break;
            }
            int temp = l+freqs[freqs.size()-1];
            for(int j:freqs){
                if(j==temp){
                    cout<<temp<<endl;
                    repeated=true;
                    break;
                }
            }
            freqs.push_back(temp);
        }
    }
    
    */
    
    return 0;
}
