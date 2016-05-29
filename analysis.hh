#include <cmath>
#include <iostream>

using namespace std;

namespace FastPartons {

//type definitions
  typedef tuple<int,double,double,vector<tuple<int,int,double,double,double,double> > > Event;
  typedef tuple<int,int,double,double,double,double> Particle;
  typedef tuple<double,double,double,double> FourMomentum;
  
  class newEvent {

  public:
    
    int Npart;
    int Procid;
    double Weight;
    double Scale;

  };

  class newParticle {

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

    
    //overload operators for newParticle class
    newParticle operator+(const newParticle& other) const;
    newParticle operator-(const newParticle& other) const;
    
  };
  
  newParticle newParticle::operator+(const newParticle& other) const {
    newParticle tmp = *this;
    tmp.Px = this->Px + other.Px;
    tmp.Py = this->Py + other.Py;
    tmp.Pz = this->Pz + other.Pz;
    tmp.E = this->E + other.E;
    return tmp; 
    
  }

  newParticle newParticle::operator-(const newParticle& other) const {
    newParticle tmp = *this;
    tmp.Px = this->Px - other.Px;
    tmp.Py = this->Py - other.Py;
    tmp.Pz = this->Pz - other.Pz;
    tmp.E = this->E - other.E;
    return tmp; 
    
  }

}
