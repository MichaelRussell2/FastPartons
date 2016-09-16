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
#include "lhe_read.hh"

using namespace std;
using namespace FastPartons;

Particle Particle::operator+(const Particle& other) const {
  Particle tmp = *this;
  tmp.Px = this->Px + other.Px;
  tmp.Py = this->Py + other.Py;
  tmp.Pz = this->Pz + other.Pz;
  tmp.E = this->E + other.E;
  return tmp;   
}

Particle Particle::operator-(const Particle& other) const {
  Particle tmp = *this;
  tmp.Px = this->Px - other.Px;
  tmp.Py = this->Py - other.Py;
  tmp.Pz = this->Pz - other.Pz;
  tmp.E = this->E - other.E;
  return tmp;   
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
	  iss >> pdg >> stat >> moth1 >> moth2 >> col >> anticol >>px >> py >> pz >> e >> m;
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

