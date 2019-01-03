//
//  main.cpp
//  day9
//
//  Created by Magnus Hall on 21/12/2018.
//  Copyright © 2018 Magnus Hall. All rights reserved.
//
//  brute force solution using normal vectors
//  should try to implement doubly connected list - much faster for inserting elements and we're only iterating through it - no need to ever single out a single element so doubly connected list is ideal.

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>


using namespace std;


// class to produce a circular, doubly linked list - doesn't really have a head or tail, just an initial starting point
class doublyLinkedNode{
private:
    doublyLinkedNode * next;
    int value;
    doublyLinkedNode * prev;
public:
    // various constructors and destructors
    // constructor w.out any other links := head constructor
    doublyLinkedNode(int i=0):value(i), next(this), prev(this){}
    doublyLinkedNode(doublyLinkedNode * p, doublyLinkedNode * n, int i=0 ):value(i),next(n), prev(p) {}
    ~doublyLinkedNode(){}
    
    // function to insert new data point after current point - reorders the linking pointers to accomodate
    void insert(int data){
        doublyLinkedNode * d =new doublyLinkedNode(this,next,data);
        next = d;
    }
    
    // function to go through list in either direction (default is +.ve but equally can be -.ve)
    doublyLinkedNode * rotate(int i=1){
        doublyLinkedNode * d = this;
        if(i>=0){
            for(int j=0;j<i;j++){
                d = d->next;
            }
        }
        else{
            for(int j =i;j<0;j++){
                d = d->prev;
            }
        }
        return d;
    }
};


int main() {

    int playerNumber = 476;
    int marbles = 7165700;
    int players[playerNumber];
    // occupy all elements with 0
    for(int &p:players){p=0;}
    
    vector<int> circle;
    //technically - current marble position (w.in vector)
    int currentMarble = 1;
    circle.push_back(0);
    circle.push_back(1);
    ofstream output;
    output.open("/Users/magnushall/Desktop/coding/AoC/day9/output.csv",ios::out);
    
    int highest =0;
    
    for(int i=2; i<=marbles; i++){
        //cout<<circle.size()<<" : "<<i<<endl;
        if(i%1000 == 0){cout<<i<<endl;
            cout<<players[0]<<endl;
        }
        if(i%23==0){
            int x=circle.size();
            players[(i-1)%playerNumber]+=i;
            players[(i-1)%playerNumber]+=circle[((currentMarble-7)%x+x)%x];
            vector<int>::iterator remove = circle.begin()+((currentMarble-7)%x+x)%x;
            if(players[(i-1)%playerNumber]>highest){
                highest=players[(i-1)%playerNumber];
                output<<players[(i-1)%playerNumber]<<",";}
     
            // theory - error appears as a result of move straddling the join in the circle (where the vector is looped back around)
            // -2%5 = -2, not 3 - hence the long winded approach
            // however screwing around with division remainder operator % does not seem to help
            // fixed - .size() output is an unsigned long - not good for using with a negative int
            circle.erase(remove,remove+1);
            currentMarble=((currentMarble-7)%x+x)%x;
            
            
        }
        else{
            currentMarble=(currentMarble+2)%circle.size();
            if(currentMarble!=0){
                circle.insert(circle.begin()+currentMarble,i);
            }
            else{
                circle.push_back(i);
                currentMarble=circle.size()-1;
            }
            
        }
        
        
    }
    //for(int i:players){cout<<i<<" ";}
    
    int highest1=0;
    for(int p : players){
        if(p>highest1){highest1=p;}
        //cout<<p<<" ";
    }
    cout<<endl<<highest1<<endl;
    
    
    
    return 0;
}





/* if - players[i%playerNumber]+=i;
 vector<int>::iterator remove = circle.begin()+((currentMarble-9)%circle.size());
 players[i%playerNumber]+=*(remove);
 circle.erase(remove,remove+1);
 currentMarble=(currentMarble-7)%circle.size();
 
 else - vector<int>::iterator start = circle.begin();
 int nextpos = (currentMarble) % circle.size();
 circle.insert(start+nextpos,i);
 currentMarble = (nextpos+2)%circle.size(); */
