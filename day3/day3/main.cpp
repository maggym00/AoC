//
//  main.cpp
//  day3
//
//  Created by Magnus Hall on 03/12/2018.
//  Copyright © 2018 Magnus Hall. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <fstream>
#include <cstring>
#include <vector>

using namespace std;
static int linecounter=0;

// read in - assume .csv format
void ReadIn(string const & address, vector<string>& output);

class material{
public:
    material(){}
    void InputRectangle(string const&,vector<int>& parameters);
    int CountOverlap() const;
    int CheckClaim(vector<vector<int>> parameter_list);
    
private:
    // [column] [row]
    int fabric [1000][1000]={};
    
};



int main(int argc, const char * argv[]) {
    vector<string> initial_input;
    ReadIn("/Users/magnushall/Desktop/coding/AoC/day3/day3/input.csv", initial_input);
    material m;
    vector<vector<int>> parameter_list;
    for(string i:initial_input){
        vector<int> parameters;
        m.InputRectangle(i,parameters);
        parameter_list.push_back(parameters);
    }
    int count = m.CountOverlap();
    cout<<count<<endl;
    m.CheckClaim(parameter_list);
    
    
    
    
    
    return 0;
}

void material::InputRectangle(string const& ID, vector<int>& parameters){
    cout<<ID<<endl;
    int xdist;
    int ydist;
    int width;
    int height;
    int IDEnd(0);
    do{
        IDEnd++;
    }while(ID[IDEnd]!='@');
    IDEnd++;
    char tempstr[ID.size()-IDEnd];
    for(int i=IDEnd;i<ID.size();i++){
        tempstr[i-IDEnd]=ID[i];
    }
    stringstream sstemp;
    sstemp<<ID;
    string temp;
    getline(sstemp,temp,'#');
    getline(sstemp,temp,'@');
    parameters.push_back(stoi(temp.c_str()));
    stringstream ss;
    ss<<tempstr;
    getline(ss,temp,',');
    xdist=stoi(temp.c_str());
    parameters.push_back(xdist);
    getline(ss,temp,':');
    ydist=stoi(temp.c_str());
    parameters.push_back(ydist);
    getline(ss,temp,'x');
    width=stoi(temp.c_str());
    parameters.push_back(width);
    getline(ss,temp,'"');
    cout<<temp<<endl;;
    height=stoi(temp.c_str());
    parameters.push_back(height);
    
    linecounter+=1;
    cout<<xdist<<" , "<<ydist<<" , "<<height<<" , "<<width<<" , "<<linecounter<<endl;
    
    for(int i = xdist ; i<xdist+width ; i++){
        for(int j = ydist ; j<ydist+height ; j++){
            fabric[i][j]+=1;
        }
    }
}


int material::CountOverlap() const{
    int count=0;
    
    for(int i=0;i<1000;i++){
        for(int j=0;j<1000;j++){
            if(fabric[i][j]>1){
                count+=1;
            }
        }
    }
    return count;
}

int material::CheckClaim(vector<vector<int>> parameter_list){
    // order = { ID , xdist , ydist , width , height }
    int ID = 0;
    for(vector<int> p : parameter_list){
        bool found = true;
        for(int i = p[1] ; i<p[1]+p[3] ; i++){
            for(int j = p[2] ; j<p[2]+p[4] ; j++){
                if(fabric[i][j]>1){
                    found = false;
                }
            }
        }
        if(found){
            cout<<p[0];
            ID=p[0];
            break;
        }
    }
    return ID;
}




void ReadIn(string const & address , vector<string>& output ){
    ifstream data;
    data.open(address);
    if(data.is_open()){
        while(!data.eof()){
            string temp;
            getline(data,temp,'"');
            getline(data,temp,'"');
            output.push_back(temp);
            
        }
    }
    output.pop_back();
    data.close();
}
