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

}
