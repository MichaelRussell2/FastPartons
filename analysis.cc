#include <iostream>
#include <sstream>
#include <fstream>
#include <valarray>
#include <cmath>
#include <cassert>
#include <vector>
#include <tuple>
#include <algorithm>
#include "analysis.hh" 
#include "histo.hh"

using namespace std;
using namespace FastPartons;

//book histograms here
Histo Histo1(0.0, 1000., 20.);

//initialise weights
double sumWeights = 0.;

//simple main function
int main(int argc, char *argv[]){
  if (argc != 2) {
    cout << "Give input event file as argument" << endl;
    return 0;
  }

  const char *infile = argv[1];
  read_lhe(infile); 


  //write out histograms to file
  Histo1.write("mtt.dat");

  cout << "Total cross-sec : " << sumWeights << " pb " << endl;
  return 0;
}

void analyse_event(vector<FastPartons::LheEntry > Event, double weight) {

  sumWeights += weight;
  
  double px,py,pz,E;
  int pdg, stat;

  //kinematic variables to plot
  double pt, mtt, yt;

  //Loop over particles in event
  for(int i=0; i<Event.size(); i++){

    LheEntry Entry = Event.at(i);
    Particle t;
    Particle tbar;

    //only look at final state particles
    //if (Entry.stat != 1) continue;

    if(Entry.pdg==6){     
      t.setMomentum(Entry.px,Entry.py,Entry.pz,Entry.e);
    }
    
    else if(Entry.pdg==-6){     
      tbar.setMomentum(Entry.px,Entry.py,Entry.pz,Entry.e);
    }  
   
    mtt = (t+tbar).Mass();
  }
  Histo1.fill(mtt,weight);

  return; 
}

void read_lhe(const char *lhefile) {
  
  LheEntry Entry;
  vector<LheEntry > Event;
  ifstream fin(lhefile);
  
  //unused data
  int npart, procid, moth1, moth2;
  int col, anticol;
  
  //used data
  double weight, scale;
  double px, py, pz, e, m;
  int pdg,stat;

  if(fin){
    string line;
    int i=0;
    while(getline(fin,line)){      
      if(line == "<event>"){
	i+=1;
	//	cout << "At event " <<  i << endl;
	getline(fin, line);
        istringstream iss(line);
        iss >> npart >> procid >> weight >> scale;
	while (true) {
	  if (line == "<mgrwt>") {
	    Event.pop_back();
	    analyse_event(Event, weight);
	    break;
	  }
          getline(fin, line);
          istringstream iss(line);
	  iss >> pdg >> stat >> moth1 >> moth2 >> col >> anticol >> px >> py >> pz >> e >> m;
	  Entry.setData(pdg,stat,px,py,pz,e);
	  Event.push_back(Entry);
	}
	Event.clear();
      } 
    }
    return;
  }
  else {
    cout << "Event file not found. Exiting" << endl;
    exit(1);
  }
}

