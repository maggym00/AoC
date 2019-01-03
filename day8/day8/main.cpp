//
//  main.cpp
//  day8
//
//  Created by Magnus Hall on 21/12/2018.
//  Copyright © 2018 Magnus Hall. All rights reserved.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <fstream>

using namespace std;

class tree{
protected:
    int const metaNo;
    int const childNo;
    vector<int> metaData;
    vector<tree> children;
public:
    int meta(int i){return metaData[i];}
    tree & operator [](int i){return children[i];}
    tree(int m, int c):metaNo(m),childNo(c) {}
    void addChild(tree t){children.push_back(t);}
    void addMeta(int i){metaData.push_back(i);}
    int const MetaNo() const {return metaNo;}
    int const ChildNo() const {return childNo;}
    tree & operator = (tree &t){return t;}
    bool inMeta(int i){return find(metaData.begin(),metaData.end(),i)!=metaData.end();}
};




void returnMetaDataSum(stringstream & s,  int & count);

void returnMetaDataSum(tree & t, int & count);

void returnValue(tree & t, int & count);


tree MakeTree(stringstream & s);


int main() {
    
    
    ifstream data;
    string input;
    data.open("/Users/magnushall/Desktop/coding/AoC/day8/input.txt");
    if(data.is_open()){
        getline(data,input);
    }
    data.close();
    
    // part 1
    stringstream s;
    s<<input;
    int count = 0;
    returnMetaDataSum(s, count);
    cout<<count<<endl;
    
    // part 2
    
    stringstream s2;
    s2<<input;
    count = 0;
    tree t = MakeTree(s2);
    
    // check that all data is in tree data structure - count should match result of part 1
    // returnMetaDataSum(t, count);
    
    count = 0;
    returnValue(t, count);
    
    cout<<count<<endl;
    
    
    
    return 0;
}

// recursive function to count all the metadata entries
void returnMetaDataSum(stringstream & s, int & count){
    int noChild;
    int noMeta;
    string temp;
    s>>temp;
    noChild=stoi(temp);
    s>>temp;
    noMeta=stoi(temp);
    for(int i=0;i<noChild;i++){
        returnMetaDataSum(s, count);
    }
    for(int i=0;i<noMeta;i++){
        string tempno;
        s>>tempno;
        count+=stoi(tempno);
    }
    
}

// recursive function to do same as above but using tree class that I made for part 2
void returnMetaDataSum(tree & t, int & count){
    cout<<t.ChildNo()<<endl;
    for(int i=0;i<t.ChildNo();i++){returnMetaDataSum(t[i], count);}
    for(int i=0;i<t.MetaNo();i++){count+=t.meta(i);}
}

tree MakeTree(stringstream & s){
    int noChild;
    int noMeta;
    string temp;
    
    s>>temp;
    noChild=stoi(temp);
    s>>temp;
    noMeta=stoi(temp);

    tree t(noMeta,noChild);
    for(int i=0;i<noChild;i++){
        t.addChild(MakeTree(s));
    }
    for(int i=0;i<noMeta;i++){
        string temp;
        s>>temp;
        t.addMeta(stoi(temp));
    }
    return t;
}

// function to return the node value for part 2 - took a while to read problem carefully and realise I was dealing with t.meta()-1 rather than t.meta()
void returnValue(tree & t, int & count){
    //cout<<"C:"<<t.ChildNo()<<" - ";
    //cout<<"M:"<<t.MetaNo()<<endl;
    if(t.ChildNo()==0){
        for(int i=0;i<t.MetaNo();i++){
            cout<<t.meta(i)<<endl;
            count+=t.meta(i);
        }
    }
    else{
        for(int i=0;i<t.MetaNo();i++){
            cout<<t.meta(i)<<" : "<<t.ChildNo()<<endl;
            if(t.meta(i)-1<t.ChildNo()){
                //cout<<t[t.meta(i)].ChildNo()<<endl;
                returnValue(t[t.meta(i)-1], count);
            }
        }
    }
}






