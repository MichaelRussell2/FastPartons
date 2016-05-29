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

using namespace std;

//04.04
//It works!!!
//But! many things to improve:
//Object for histograms
//Get cross-section from sumofweights
//
//back to an old problem: how to get event info into read_lhe
//not just particles


//namespace FastPartons {
//function prototypes
vector<FastPartons::Particle> read_lhe(const char *lhefile);
bool book(int nbins, double xmin, double xmax, vector<double> Xs, const char *outfile);

const char *lhefile = "unweighted_events.lhe";  

int main(){

  double px,py,pz,E;
  int pdg, stat;
  FastPartons::newParticle Top;
  FastPartons::newParticle Antitop;
  vector<FastPartons::newParticle> Particles;
  vector<FastPartons::Particle> p;

  vector<FastPartons::newParticle > Tops;
  vector<FastPartons::newParticle > Antitops;

  p=read_lhe("unweighted_events.lhe"); 
  
  //kinematic variables to plot
  double pt, mtt, yt;

  //vectors to fill histograms
  vector<double> toppt;

  //example cut
  const double cut = 400;
  
  //this should be events.size(), then for j=0; j<Particles.size()
  for(int i=0; i<p.size(); i++){

    pdg=std::get<0>(p.at(i));
    stat=std::get<1>(p.at(i));
    px=std::get<2>(p.at(i)); 
    py=std::get<3>(p.at(i)); 
    pz=std::get<4>(p.at(i)); 
    E=std::get<5>(p.at(i)); 

    if(pdg==6){     
      Top.Px = px;
      Top.Py = py;
      Top.Pz = pz;
      Top.E = E;
      Tops.push_back(Top);   

      //
      mtt = (Top+Top).Mass(); 
      //      cout << mtt << endl;

      pt = Top.pT();  
      if(pt > cut){
	toppt.push_back(pt);
      }

    }   
    else if(pdg==-6){     
      Antitop.Px = px;
      Antitop.Py = py;
      Antitop.Pz = pz;
      Antitop.E = E;
      Antitops.push_back(Antitop);     
    }  
    
  }

  cout << toppt.size() << endl;
  book(10,0,1000,toppt,"pt_hist.dat");
  
  Tops.clear();  
  Antitops.clear();
  return 0; 
}

//book and fill the histograms
bool book(int nbins, double xmin, double xmax, vector<double> Xs, const char *outfile) {
  
  int count[nbins];
  double binedge[nbins+1];
  double bincentre[nbins];
  
  
  for (int i=0; i<=nbins; i++){
    binedge[i]=xmin+i*xmax/nbins;
    //    cout << binedge[i] << endl;
  }

  double dx = fabs(binedge[0]-binedge[1]);
  cout << dx << endl;

  for (int i=0; i<nbins; i++){
    count[i]=0;
    bincentre[i]=binedge[i]+dx/2;
  }

  for (int i=0; i<Xs.size(); i++){
    double X = Xs.at(i);
    for (int i=0; i<nbins; i++){
      if( X>binedge[i] && X<=binedge[i+1] ) {
       	count[i]++;
      }
    }
    if (X>binedge[nbins]) {
      count[nbins-1]++;
    }
  }

  int ncounts=0;
  for (int i=0; i<nbins; i++){
    cout << "bin" << i << " : " << count[i] << " entries" << endl;
    ncounts+=count[i];
  }
  cout << ncounts << endl;

  //new object for histo
  //needs nbin
  //const char *outfile = "pt_hist.dat";
  std::ofstream fout;

  fout.open(outfile);
  for (int i=0; i<nbins; i++){
    fout << bincentre[i] << "\t" << count[i] << "\t" << sqrt(count[i]) << endl;
  }
  fout.close();

  return 0;
}


//store particle momenta 
//TODO: make this store one event, not all of them
//we want read_event(i):
//split this up somehow

vector<FastPartons::Particle> read_lhe(const char *lhefile) {
  
  FastPartons::Particle Particle;
  vector<FastPartons::Particle > Particles;
  vector<vector<FastPartons::Particle > > Events; //hideously slow
 
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
          getline(fin, line);
          if (line == "<mgrwt>") break;
          istringstream iss(line);
          iss >> pdg >> stat >> moth1 >> moth2 >> col >> anticol >> px >> py >> pz >> e >> m;
	  Particle=make_tuple(pdg,stat,px,py,pz,e);
	  Particles.push_back(Particle);
	}
	//	if(i>=10) break;
	// break;
      } 
    }
    // cout << std::get<0>(Particles.at(0)) << endl;
    return Particles;
    //    return make_tuple(npart,weight,scale,Particles);
    
    Particles.clear();
    Events.clear();
  }
  else {
    cout << "Event file not found. Exiting" << endl;
    exit(1);
  }
}


