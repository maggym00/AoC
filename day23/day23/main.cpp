//
//  main.cpp
//  day23
//
//  Created by Magnus Hall on 25/12/2018.
//  Copyright © 2018 Magnus Hall. All rights reserved.
//
//  Brute force solution - not recommended

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

// simple class for ease of use of coordinates (used in first part)
class coord{
private:
    int x=0;
    int y=0;
    int z=0;
public:
    coord(int X=0, int Y=0, int Z=0):x(X),y(Y),z(Z){}
    ~coord(){}
    int & operator [](int i){
        if(i==0){return x;}
        else if(i==1){return y;}
        else if(i==2){return z;}
        else{cout<<"invalid index"<<endl;
            exit(1);
        }
    }
    
    friend ostream & operator << (ostream & o, coord c){
        o<<"("<<c[0]<<","<<c[1]<<","<<c[2]<<")";
        return o;
    }
};


void Readin(string address, vector<string> & output, vector<coord> & coords);

int dist(coord a, coord b){
    return (abs(a[0]-b[0])+abs(a[1]-b[1])+abs(a[2]-b[2]));
}

class Block{
private:
    // as all blocks are aligned to the grid, only need to define bounds rather than vertices (6 DoF)
    // could actually use coord bounds[2]; - define two opposing corners
    int xbound[2];
    int ybound[2];
    int zbound[2];
    vector<Block> roots;
public:
    
    Block(){
        for(int & x: xbound){x=0;}
        for(int & y: ybound){y=0;}
        for(int & z: zbound){z=0;}
        roots.push_back(*this);
    }
    Block(int xlow=0, int xhi=0, int ylow=0, int yhi=0, int zlow=0, int zhi=0){
        xbound[0]=xlow;xbound[1]=xhi;
        ybound[0]=ylow;ybound[1]=yhi;
        zbound[0]=zlow;zbound[1]=zhi;
        roots.push_back(*this);
    }
    ~Block(){}
    
    pair<int,int> ReturnBound(int xyz);
    
    bool Intersects(Block b);
    
    Block ReturnIntersection(Block b);
    
    int mindist();
    
    bool operator == (const Block& b){return(xbound[0]==b.xbound[0]&&xbound[1]==b.xbound[1]&&ybound[0]==b.ybound[0]&&ybound[1]==b.ybound[1]&&zbound[0]==b.zbound[0]&&zbound[1]==b.zbound[1]);}
    
    // function returns true if block comparison is already a root of current block's intersection;
    bool isroot(Block const &b){
        return(find(roots.begin(),roots.end(),b)!=roots.end());
    }
    
    void addtoroots(Block const &b){
        roots.push_back(b);
    }
    
    vector<Block> giveroots(){
        return roots;
    }
    
    void copyroots(Block const &b){
        vector<Block> newroots=b.roots;
        roots=newroots;
    }
};

// recursive function to narrow down search volume to only the volumes with the most overlaps
vector<Block> FindSearchVol(vector<Block> &b, vector<Block> &c);





int main(int argc, const char * argv[]) {
    
    
    vector<string> data;
    vector<coord> coords;
    Readin("/Users/magnushall/Desktop/coding/AoC/day23/input.txt", data, coords);
    
    // Part 1
    
    int highest=0;
    coord pos;
    vector<int> numdata;
    for(string d:data){numdata.push_back(stoi(d));}
    
    for(int i=0;i<numdata.size();i++){
        if(numdata[i]>highest){
            //cout<<numdata[i]<<":";
            //cout<<coords[i]<<endl;
            highest=numdata[i];
            pos[0] = coords[i][0];
            pos[1] = coords[i][1];
            pos[2] = coords[i][2];
        }
    }
    int count =0;

    int total = 0;
    for(coord c:coords){
        total+=1;
        if(dist(c,pos)<highest){
            //cout<<highest<<" : "<<dist(c,pos)<<endl;
            count+=1;
        }
    }
   cout<<count<<endl;
    
    // part 2
    
    vector<Block> volumes;
    
    for(int i = 0; i<numdata.size(); i++){
        Block temp(coords[i][0]-numdata[i],coords[i][0]+numdata[i],coords[i][1]-numdata[i],coords[i][1]+numdata[i],coords[i][2]-numdata[i],coords[i][2]+numdata[i]);
        
        volumes.push_back(temp);
    }
    volumes = FindSearchVol(volumes, volumes);
    
    int mindistance = 100000000000;
    for(Block v: volumes){
        if(v.mindist()<mindistance){
            mindistance = v.mindist();
        }
    }
    cout<<mindistance<<endl;
    
    
    
    
    
    
    /*
    int xmin=0;
    int xmax=0;
    int ymin=0;
    int ymax=0;
    int zmin=0;
    int zmax=0;
    
    for(coord c:coords){
        if(c[0]<xmin){xmin=c[0];}
        else if(c[0]>xmax){xmax=c[0];}
        if(c[1]<ymin){ymin=c[1];}
        else if(c[1]>ymax){ymax=c[1];}
        if(c[2]<zmin){zmin=c[2];}
        else if(c[2]>zmax){zmax=c[2];}
    }
    
    int topcount=0;
    int mindist =0;
    coord toppos;
    for(int x=xmin;x<=xmax;x++){
        cout<<x<<endl;
        for(int y=ymin;y<=ymax;y++){
            for(int z=zmin;z<=zmax;z++){
                coord temp(x,y,z);
                int tempcount=0;
                for(int i=0;i<coords.size();i++){
                    if(dist(temp,coords[i])<numdata[i]){
                        tempcount+=1;
                    }
                }
                if(tempcount>topcount){
                    topcount=tempcount;
                    toppos[0]=temp[0];
                    toppos[1]=temp[1];
                    toppos[2]=temp[2];
                    coord d;
                    mindist = dist(d,temp);
                }
                else if(tempcount==topcount){
                    coord d;
                    if(dist(d,temp)<mindist){
                        toppos[0]=temp[0];
                        toppos[1]=temp[1];
                        toppos[2]=temp[2];
                        mindist = dist(d,temp);
                    }
                }
            }
        }
    }
    
    cout<<mindist<<endl;
    */
    
    return 0;
}

void Readin(string address, vector<string> & output, vector<coord> & coords){
    ifstream data;
    data.open(address);
    if(data.is_open()){
        while(!data.eof()){
            
            string temp;
            int x;
            int y;
            int z;
            getline(data,temp,'<');
            getline(data,temp,',');
            x=stoi(temp);
            getline(data,temp,',');
            y=stoi(temp);
            getline(data,temp,'>');
            z=stoi(temp);
            coord c(x,y,z);
            getline(data,temp,'=');
            getline(data,temp,'\n');
            output.push_back(temp);
            coords.push_back(c);
            
        }
    }
    data.close();
}

// Amend to take in two vectors (on first iteration = the same vector of blocks. on future iterations = vector of intersections plus vector of blocks)
// Need to make a second vector within block for past blocks? (so intersections are not repeated)
// treat first parameter as one that will change - the intersections
// second parameter as const - the roots
vector<Block> FindSearchVol(vector<Block> &b, vector<Block> &c){
    cout<<"layer"<<endl;
    vector<Block> returnBlock;
    for(int i =0;i<b.size();i++){
        cout<<returnBlock.size()<<": "<<i<<" of "<<b.size()<<endl;
        for(int j = 0; j<b.size(); j++){
            if(b[i].Intersects(c[j])&&!b[i].isroot(c[j])){
                Block temp = b[i].ReturnIntersection(c[j]);
                
                if(find(returnBlock.begin(),returnBlock.end(),temp)==returnBlock.end()){
                    temp.copyroots(b[i]);
                    temp.addtoroots(c[j]);
                    returnBlock.push_back(temp);
                    
                }
            }
        }
    }
    if(returnBlock.empty()){
        return b;
    }
    else{
        return FindSearchVol(returnBlock, c);
    }
}

///////////////////////////////////////////
// Block Functions
///////////////////////////////////////////

pair<int,int> Block::ReturnBound(int xyz){
    pair<int,int> bounds;
    if(xyz==0){
        bounds.first = xbound[0];
        bounds.second = xbound[1];
    }
    else if(xyz==1){
        bounds.first = ybound[0];
        bounds.second = ybound[1];
    }
    else if(xyz==2){
        bounds.first = zbound[0];
        bounds.second = zbound[1];
    }
    else{
        bounds.first = 0;
        bounds.second = 0;
    }
    return bounds;
}

bool Block::Intersects(Block b){
    bool intersect[3] = {false, false, false};
    for(int i =0; i<3; i++){
        // test b within a (a - b - b - a || a - b - a - b)
        if(b.ReturnBound(i).first > ReturnBound(i).first && b.ReturnBound(i).first < ReturnBound(i).second){
            intersect[i] = true;
            }
        // test a within b (b - a - a - b || b - a - b - a)
        else if (ReturnBound(i).first > b.ReturnBound(i).first && ReturnBound(i).first < b.ReturnBound(i).second){
            intersect[i] = true;
        }
    }
    if(intersect[0] && intersect[1] && intersect[2]){
        return true;
    }
    else{
        return false;
    }
}

Block Block::ReturnIntersection(Block b){
    // fail if blocks don't intersect
    if(!Intersects(b)){
        cout<< "error - blocks don't intersect"<<endl;
        exit(1);
    }
    // only intersections reach this point
    int bounds[3][2];
    
    
    for(int i = 0; i<3; i++){
        // a-b-x-x
        if(ReturnBound(i).first < b.ReturnBound(i).first){
            bounds[i][0]=b.ReturnBound(i).first;
        }
        // b-a-x-x
        else{
            bounds[i][0]=ReturnBound(i).first;
        }
        // x-x-a-b
        if(ReturnBound(i).second < b.ReturnBound(i).second){
            bounds[i][1]=ReturnBound(i).second;
        }
        // x-x-b-a
        else{
            bounds[i][1]=b.ReturnBound(i).second;
        }
    }
    
    Block intersectVol(bounds[0][0],bounds[0][1],bounds[1][0],bounds[1][1],bounds[2][0],bounds[2][1]);
    return intersectVol;
}

int Block::mindist(){
    // min x
    coord a;
    if(xbound[0]>0){
        a[0]=xbound[0];
    }
    else if(xbound[1]<0){
        a[0]=xbound[1];
    }
    else{
        a[0]=0;
    }
    //min y
    if(ybound[0]>0){
        a[0]=ybound[0];
    }
    else if(ybound[1]<0){
        a[0]=ybound[1];
    }
    else{
        a[0]=0;
    }
    if(zbound[0]>0){
        a[0]=zbound[0];
    }
    else if(zbound[1]<0){
        a[0]=zbound[1];
    }
    else{
        a[0]=0;
    }
    return a[0]+a[1]+a[2];
}




