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
#include "lhe_read.hh"

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
      t.setMomentum(Entry.Px(),Entry.Py(),Entry.Pz(),Entry.E());
    }
    
    else if(Entry.pdg==-6){     
      tbar.setMomentum(Entry.px,Entry.py,Entry.pz,Entry.e);
    }  
   
    mtt = (t+tbar).Mass();
  }
  Histo1.fill(mtt,weight);

  return; 
}
