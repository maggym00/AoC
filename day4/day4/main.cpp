//
//  main.cpp
//  day4
//
//  Created by Magnus Hall on 09/12/2018.
//  Copyright © 2018 Magnus Hall. All rights reserved.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <regex>
#include <algorithm>
#include <map>

using namespace std;

class data{
public:
    data( string date, string time , string awake);
    ~data(){}
    int hour(){return Time[0];}
    int minute(){return Time[1];}
    
    int year(){return Date[0];}
    int month(){return Date[1];}
    int day(){return Date[2];}
    
    bool isAwake(){return Awake;}
    
    int id(){return ID;}
    
    void setid(int i){ID = i;/*cout<<i<<" | "<<endl;*/}
    
    friend ostream & operator <<(ostream & o, data d);
    
protected:
    int ID;
    int Time[2];
    int Date[3];
    bool Awake;
};

void ReadIn(string const & address , vector<string>& output );

void format_input(vector<vector<string>>&, vector<string> const& );

vector<data> sortByDay(vector<data>&);


int main(int argc, const char * argv[]) {
    
    vector<string> input;
    ReadIn("/Users/magnushall/Desktop/coding/AoC/day4/input.csv", input);
    vector<vector<string>> formatted_input;
    format_input(formatted_input,input);
    
    vector<data> timeline;
    
    for(vector<string> i:formatted_input){
        data d(i[0],i[1],i[2]);
        timeline.push_back(d);
    }
    
    // sort algorithm using lambda fn as sort function (kinda proud of how gross this is)
    sort(timeline.begin(),timeline.end(),[](data i, data j){if(i.day()==j.day()&&i.month()==j.month()&&i.hour()==j.hour()){return i.minute()<j.minute();} else if(i.day()==j.day()&&i.month()==j.month()){return i.hour()<j.hour();}else if(i.month()==j.month()){return i.day()<j.day();}
        else{return i.month()<j.month();}});
    
    // carry forward the guard IDs - currently only set on the instances that they turn up.
    int tempid=0;
    // note - need to pass in by reference (hence &t rather than t)
    for(data &t:timeline){
        if(t.id()!=0){
            tempid=t.id();
        }
        else{
            t.setid(tempid);
        }
    }
    
    // now time to count up minutes spent asleep by each guard
    map<int,int> guardSleeps;
    // explicitly initialise every guard id as 0 just in case
    for(data t:timeline){
        guardSleeps[t.id()]=0;
    }
    bool wasawake=true;
    int sleeping=0;
    int start=(timeline[0].hour()*60)+timeline[0].minute();
    int currentGuard=timeline[0].id();
    for(data t:timeline){
        if(t.id()==currentGuard && !t.isAwake() && wasawake){
            start=(t.hour()*60)+t.minute();
            wasawake=false;
        }
        else if(t.id()==currentGuard && t.isAwake() && !wasawake){
            wasawake=true;
            sleeping+=((t.hour()*60)+t.minute()-start);
            start=((t.hour()*60)+t.minute());
        }
        else if(t.id()!=currentGuard){
            guardSleeps[currentGuard]+=sleeping;
            start=((t.hour()*60)+t.minute());
            currentGuard=t.id();
            sleeping=0;
            wasawake=t.isAwake();
        }
        else{
            
        }
    }
    
    
    
    // find which guard sleeps for the longest and how long that is
    pair<int,int> largest = {0,0};
    for( map<int,int>::iterator it = guardSleeps.begin() ; it!=guardSleeps.end() ; it++ ){
        //cout<<it->first<<" : "<<it->second<<endl;
        if(it->second > largest.second){
            largest.second=it->second;
            largest.first=it->first;
        }
    }
    cout<<largest.first<<" : "<<largest.second<<endl;
    
    
    // isolate all data for the guard that sleeps the longest
    vector<data> sleepyGuard;
    for(data d:timeline){
        if(d.id()==largest.first){
            sleepyGuard.push_back(d);
        }
    }
    // make array for all minutes in day
    int asleep[(24*60)];
    for(int &a:asleep){a=0;}
    
    for(int i=1;i<sleepyGuard.size();i++){
        if(sleepyGuard[i].isAwake()&&!sleepyGuard[i-1].isAwake()){
            for(int j=((sleepyGuard[i-1].hour()*60)+sleepyGuard[i-1].minute());j<((sleepyGuard[i].hour()*60)+sleepyGuard[i].minute());j++){
                asleep[j]+=1;
            }
        }
    }
    int k=0;
    for(int i=0;i<(24*60);i++){
        //cout<<asleep[i]<<", ";
        if(asleep[i]>asleep[k]){
            //cout<<endl;
            //cout<<asleep[i]<<endl;
            k=i;
        }
    }
    cout<<k<<endl;
    
    cout<<k*largest.first<<endl;
    
    // do same but for all other guards
    
    // make a data structure which is the sleeping timetable for each guard
    map<int, int[24*60]> allGuards;
    
    
    
    
    bool Wasawake=true;
    int Start=(timeline[0].hour()*60)+timeline[0].minute();
    int CurrentGuard=timeline[0].id();
    for(data t:timeline){
        if(t.id()==CurrentGuard && !t.isAwake() && Wasawake){
            Start=(t.hour()*60)+t.minute();
            Wasawake=false;
        }
        else if(t.id()==CurrentGuard && t.isAwake() && !Wasawake){
            Wasawake=true;
            // add a minute asleep to each minute in range (start - current time)
            for(int i=Start;i<(t.hour()*60)+t.minute();i++ ){
                allGuards[CurrentGuard][i]+=1;
            }
            Start=((t.hour()*60)+t.minute());
        }
        else if(t.id()!=currentGuard){
            Start=((t.hour()*60)+t.minute());
            CurrentGuard=t.id();
            Wasawake=t.isAwake();
        }
        else{}
    }
    pair<int,int> topDude = {0,0};
    int currentTop = 0;
    for( map<int,int[24*60]>::iterator it = allGuards.begin() ; it!=allGuards.end() ; it++ ){
        int count = 0;
        cout<<endl;
        cout<<endl;
        for(int n:it->second){
            cout<<n<<", ";
            if(n>currentTop){
                currentTop=n;
                topDude.second=count;
                topDude.first=it->first;
            }
            count+=1;
        }
        
    }
    
    cout<<topDude.first*topDude.second<<" : "<<currentTop<<endl;
    
    
    
    
    
    
    
    
    
    
    return 0;

}

data::data(string date , string time, string awake){

    stringstream sd;
    sd<<date;
    string temp;
    getline(sd,temp,'-');
    Date[0]=stoi(temp.c_str());
    getline(sd,temp,'-');
    Date[1]=stoi(temp.c_str());
    getline(sd,temp);
    Date[2]=stoi(temp.c_str());
    
    stringstream st;
    st<<time;
    getline(st,temp,':');
    Time[0]=stoi(temp.c_str());
    getline(st,temp);
    Time[1]=stoi(temp.c_str());
    
    if(regex_match(awake,regex(".*#.*"))){
        Awake = true;
        stringstream sid;
        sid<<awake;
        string temp;
        getline(sid,temp,'#');
        sid>>ID;
    }
    else{
        Awake = (awake==" wakes up");
        ID=0;
    }
    
}

void ReadIn(string const & address , vector<string>& output ){
    ifstream data;
    data.open(address);
    if(data.is_open()){
        while(!data.eof()){
            string temp;
            getline(data,temp,',');
            output.push_back(temp);
            
        }
    }
    output.pop_back();
    data.close();
}

void format_input(vector<vector<string>>& altinput, vector<string> const& input ){
    // formatted input as
    // { date , time , string that is either whether awake or guard id }
    for(string i: input){
        vector<string> tempv;
        string temp;
        stringstream ss;
        ss<<i;
        
        getline(ss,temp,'[');
        ss>>temp;
        tempv.push_back(temp);
        getline(ss,temp,']');
        tempv.push_back(temp);
        getline(ss,temp);
        tempv.push_back(temp);
        altinput.push_back(tempv);
    }
}


vector<data> sortByDay(vector<data>& input){
    
    return input;
}


ostream & operator <<(ostream & o, data d){
    o<<d.year()<<" - "<<d.month()<<" - "<<d.day()<<" | "<<d.hour()<<" : "<<d.minute()<<" | "<<d.id()<<" | ";
    if(d.isAwake()){
        cout<<" awake ";
    }
    else{
        cout<<" asleep ";
    }
    return o;
}


