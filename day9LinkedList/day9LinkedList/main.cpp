//
//  main.cpp
//  day9LinkedList
//
//  Created by Magnus Hall on 27/12/2018.
//  Copyright © 2018 Magnus Hall. All rights reserved.
//
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
    
    doublyLinkedNode & operator = (doublyLinkedNode &d);
    
    // function to insert new data point after current point - reorders the linking pointers to accomodate
    void insert(int data);
    
    int Next(){return next->value;}
    int Prev(){return prev->value;}
    
    doublyLinkedNode * NextAddress(){return next;}
    doublyLinkedNode * PrevAddress(){return prev;}
    
    
    // physically can't delete the object you're on
    // the fix is to copy the next node's value + next pointer to this one and then delete the next node
    void remove();
    
    // function to go through list in either direction
    doublyLinkedNode * rotate(int);
    
    int Value(){return value;}
    
    friend ostream & operator <<(ostream & o, doublyLinkedNode &d);
    
    // thoughts on a changed structure - make insert, remove and rotate functions external from class - make so not overwriting memory for current data - keep seperate - pointer to a specific point in list - and the list itself -
    
};







int main(int argc, const char * argv[]) {
    
    // fixing the class
    
    
    doublyLinkedNode head(0);
    head.insert(1);
    cout<<head.Next()<<" "<<head.Prev()<<" "<<&head<<endl;
    doublyLinkedNode circle = *head.rotate(1);
    
    cout<<circle.Next()<<" "<<circle.Prev()<<" "<<&circle<<endl;
    
    circle.insert(2);
    
    cout<<circle.Next()<<" "<<circle.Prev()<<" "<<&circle<<endl;
    
    

    return 0;
}

// deep copy assignment
doublyLinkedNode & doublyLinkedNode::operator = (doublyLinkedNode &d){
    if(&d==this){
        return *this;
    }
    this -> next = d.next;
    this -> prev = d.prev;
    this -> value = d.value;
    return *this;
}

// insert new element (currently not properly working properly)
void doublyLinkedNode::insert(int data){
    doublyLinkedNode * d = new doublyLinkedNode(this,next,data);
    next->prev=d;
    next = d;
    
    //cout<<d->prev<<" "<<d->next<<" "<<&d<<endl;
}

// remove element
void doublyLinkedNode::remove(){
    value = next -> value;
    doublyLinkedNode * temp = next;
    next = next -> next;
    delete temp;
}

// iterate through by i elements
doublyLinkedNode * doublyLinkedNode::rotate(int i){
    doublyLinkedNode * d = this;
    //cout<<d->Value();
    if(i>=0){
        for(int j=0;j<i;j++){
            d = d->next;
            //cout<<d->Value()<<endl;
        }
    }
    else{
        for(int j = i;j<0;j++){
            d = d->prev;
        }
    }
    //cout<<"rotated to:"<<d->Value()<<endl;
    return d;
}

// cout
ostream & operator <<(ostream & o, doublyLinkedNode &d){
    doublyLinkedNode * end = &d;
    doublyLinkedNode * temp = &d;
    o<<"( "<<d.value<<", ";
    temp = d.next;
    //int count(0);
    cout<<d.next<<" "<<&d<<endl;
    while(temp!=end){
        o<<temp->value<<", ";
        temp = temp->rotate(1);
        //cout<<count;
        //count+=1;
    }
    o<<")";
    return o;
}







//////////////

// DUMP FOR CODE FOR MAIN //

/*
 
 int playerNumber = 476;
 int marbles = 25;//7165700;
 int players[playerNumber];
 // occupy all elements with 0
 for(int &p:players){p=0;}
 
 for(int i = 2; i<=marbles; i++){
 cout<<circle<<endl;
 if(i%23==0){
 players[(i-1)%playerNumber]+=i;
 circle = *circle.rotate(-7);
 players[(i-1)%playerNumber]+=circle.Value();
 circle.remove();
 }
 else{
 circle = *circle.rotate(1);
 circle.insert(i);
 circle = *circle.rotate(1);
 }
 }
 
 int highest=0;
 for(int p:players){
 if(p>highest){
 highest=p;
 }
 }
 cout<<highest<<endl;
 */






