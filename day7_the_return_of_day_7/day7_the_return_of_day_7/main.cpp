//
//  main.cpp
//  day7_the_return_of_day_7
//
//  Created by Magnus Hall on 20/12/2018.
//  Copyright © 2018 Magnus Hall. All rights reserved.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>


using namespace std;

vector<string> ReadIn(string const & address);

vector<char> Partlist(vector<string> const& input, vector<pair<char,char>> & orders);

void SortByOrders(vector<char>& list,vector<pair<char,char>> const & orders);




int main() {
    vector<string> instructions = ReadIn("/Users/magnushall/Desktop/coding/AoC/day7/input.txt");
    
    // vector of pairs of chars to represent a shortened version of the instructions
    // system is orders[i].first is before orders[i].second
    vector<pair<char,char>> orders;
    
    // Partlist finds all parts and adds exactly one copy to unordered parts in the order that it comes across them
    // it also takes in orders by reference and adds all the orders in short form to it at the same time
    vector<char> unordered_parts=Partlist(instructions, orders);
    
    orders.pop_back();
    unordered_parts.pop_back();
    for(char c:unordered_parts){
        cout<<c;
    }
    cout<<endl;
    
     
    // add in all the extra orders that also apply based on what is given
    bool ordering = true;
    while(ordering){
        ordering = false;
        for(int i=0;i<orders.size()-1;i++){
            for(int j=i+1; j<orders.size();j++){
                if(orders[i].second==orders[j].first){
                    pair<char,char> temp={orders[i].first,orders[j].second};
                    if(find(orders.begin(),orders.end(),temp)==orders.end()){
                        // cout<<temp.first<<","<<temp.second<<" 1"<<endl;
                        orders.push_back(temp);
                        ordering=true;
                    }
                }
                if(orders[j].second==orders[i].first){
                    pair<char,char> temp={orders[j].first,orders[i].second};
                    if(find(orders.begin(),orders.end(),temp)==orders.end()){
                        //cout<<temp.first<<","<<temp.second<<" 2"<<endl;
                        orders.push_back(temp);
                        ordering=true;
                    }
                }
            }
        }
    }
    
    sort(unordered_parts.begin(),unordered_parts.end(),[orders](char a,char b){
        pair<char,char> temp = {a,b};
        // if a,b in correct order
        if(find(orders.begin(),orders.end(),temp)!=orders.end()){
            return true;
        }
        temp.first = b;
        temp.second = a;
        // if a,b in opposite order
        if(find(orders.begin(),orders.end(),temp)!=orders.end()){
            return false;
        }
        // if a,b in parallel (no direct link between them) - sort alphabetically
        return a<b;
    });
    
    cout<<"---------"<<endl;
    for(char c:unordered_parts){
        cout<<c;
    }
    cout<<endl;
    
    
    
    
    
    /*
    SortByOrders(unordered_parts, orders);

    for(char c:unordered_parts){
        cout<<c;
    }
    cout<<endl;
    
    
    //at this point, the list is vaguely ordered but not fully - we only have ordering as far as block level.
    // need to order objects alphabetically too
    // to do this - expand orders to indicate all linked (forwards and backwards) parts, leaving the ones that are parallel - indication of which we are able to order
    // then implement a ladder sort on adjacent items only if the pair of items does not appear in the expanded list of orders
    

    for(char c:unordered_parts){
        cout<<c;
    }
    cout<<endl;
    bool sorting = true;
    
    while(sorting){
        sorting = false;
        for(int i=0;i<unordered_parts.size()-1;i++){
            for(int j=i+1;j<unordered_parts.size();j++){
                pair<char,char> temp = {unordered_parts[i],unordered_parts[j]};
                if(find(orders.begin(),orders.end(),temp)==orders.end()){
                    if(unordered_parts[i]>unordered_parts[j]){
                        swap(unordered_parts[i],unordered_parts[j]);
                        cout<<unordered_parts[i]<<" , "<<unordered_parts[j]<<endl;
                        sorting = true;
                    }
                }
            }
        }
    }
    for(char c:unordered_parts){
        cout<<c;
    }
    cout<<endl;
    */
    return 0;
}

/*
void SortByOrders(vector<char>& list,vector<pair<char,char>> const & orders){
    bool sorted = false;
    while(!sorted){
        //for(char c:list){
          //  cout<<c;
        //}
        //cout<<endl;
        sorted=true;
        for(int i=0;i<list.size();i++){
            for(int j=i;j<list.size();j++){
                pair<char,char> temp;
                temp.first=list[j];
                temp.second=list[i];
                bool flip = false;
                for(pair<char,char> p:orders){
                    if(temp==p){
                        flip=true;
                        break;
                    }
                }
                if(flip){
                    sorted=false;
                    //cout<<list[i]<<"  "<<list[j]<<endl;
                    // should check - if say list[i]=list[j] is this copy by value or reference?
                    swap(list[i],list[j]);
                }
            }
        }
    }
    
}
*/

vector<char> Partlist(vector<string> const& input, vector<pair<char,char>> & orders){
    
    vector<char> output;
    
    for(string i:input){
        //cout<<i<<" -- "<<endl;
        //cout<<i[5]<<" - "<<i[36]<<endl;
        pair<char,char> temp;
        temp.first = i[5];
        temp.second = i[36];
        
        orders.push_back(temp);
        // find: iterates through vector between given start and end points and points to the value given as the third arg
        // if value not in vector, point to output.end() ( = one after last value (has no value itself))
        // in this case, the two if statements check the specific chars which correspond to part numbers and find if they're in the list
        if(find(output.begin(), output.end(), i[5]) == output.end()){
            output.push_back(i[5]);
        }
        
        if(find(output.begin(), output.end(), i[36]) == output.end()){
            output.push_back(i[36]);
        }
    }
    return output;
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
    else{
        cout<<"file not found"<<endl;
    }
    data.close();
    return tempvector;
}
