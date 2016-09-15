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

//namespace FastPartons {

//function prototypes
void analyse_event(vector<FastPartons::Particle > Event);
void read_lhe(const char *lhefile);

//book histograms here
FastPartons::Histo Histo1(0.0, 1000., 20.);


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

  return 0;
}

void analyse_event(vector<FastPartons::Entry > Event) {

  double px,py,pz,E;
  int pdg, stat;

  //kinematic variables to plot
  double pt, mtt, yt;

  //Loop over particles in event
  for(int i=0; i<Event.size(); i++){

    pdg=std::get<0>(Event.at(i));
    stat=std::get<1>(Event.at(i));
    px=std::get<2>(Event.at(i)); 
    py=std::get<3>(Event.at(i)); 
    pz=std::get<4>(Event.at(i)); 
    E=std::get<5>(Event.at(i)); 
    
    FastPartons::Particle Top;
    FastPartons::Particle Antitop;

    //only look at final state particles
    //if (stat != 1) continue;

    if(pdg==6){     
      Top.setMomentum(px,py,pz,E);
    }
    
    else if(pdg==-6){     
      Antitop.setMomentum(px,py,pz,E);
    }  
   
    mtt = (Top+Antitop).Mass();
  }
  Histo1.fill(mtt);

  return; 
}

void read_lhe(const char *lhefile) {
  
  FastPartons::Entry Particle;
  vector<FastPartons::Entry > Event;
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
	    analyse_event(Event);
	    break;
	  }
          getline(fin, line);
          istringstream iss(line);
	  iss >> pdg >> stat >> moth1 >> moth2 >> col >> anticol >> px >> py >> pz >> e >> m;
	  Particle=make_tuple(pdg,stat,px,py,pz,e);
	  Event.push_back(Particle);
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

