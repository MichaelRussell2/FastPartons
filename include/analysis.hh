#ifndef ANALYSIS_HH
#define ANALYSIS_HH

#include <cmath>
#include <iostream>

using namespace std;


namespace FastPartons {

  
//type definitions
  typedef tuple<int,int,double,double,double,double> Entry;
  
  class Particle {

  public:
    
    int Pdg;
    int Stat;
    double Px;
    double Py;
    double Pz;
    double E;
   
    double pT(){return(sqrt(Px*Px+Py*Py));}
    double Mass(){return(sqrt(E*E-Px*Px-Py*Py-Pz*Pz));}
    double y(){return(0.5*(log((E+Pz)/(E-Pz))));}

    Particle setMomentum(double& Px, double& Py, double& Pz, double& E){
      this->Px = Px;
      this->Py = Py;
      this->Pz = Pz;
      this->E = E;
      return *this;
    }

    
    //overload operators for Particle class
    Particle operator+(const Particle& other) const;
    Particle operator-(const Particle& other) const;
    
  };
  
  class LheEntry {

  public:
    
    int pdg;
    int stat;
    double px;
    double py;
    double pz;
    double e;

    int col;
    int anticol;
    int moth1;
    int moth2;

    double& Px(){return px;} 
    double& Py(){return py;} 
    double& Pz(){return pz;} 
    double& E(){return e;} 

    LheEntry setData(int& pdg, int& stat,  double& px, double& py, double& pz, double& e){
      this->pdg = pdg;
      this->stat = stat;
      this->px = px;
      this->py = py;
      this->pz = pz;
      this->e = e;
      return *this;

    }
  };

}
  
//function prototypes
extern void analyse_event(vector<FastPartons::LheEntry > Event, double weight);

#endif
