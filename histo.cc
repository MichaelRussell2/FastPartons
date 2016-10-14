#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include "histo.hh"

//FastPartons::Histo::Histo() {}
//FastPartons::Histo::~Histo() {}

FastPartons::Histo::Histo(const double xmin, const double xmax, const double deltax){

  // cout << "xmin   "  << xmin << endl;
  // cout << "xmax   "  << xmax << endl;
  // cout << "deltax "  << deltax << endl;
  min = xmin;
  max = xmax;
  // cout << "min    "  << min << endl;
  // cout << "max    "  << max << endl;
  binWidth = deltax;
  binCount = (int)((max-min)/binWidth);
 
  counts = vector<double>(binCount,0);
  cout << counts.size() << endl;
  cout << "END HCTOR" << endl;
}

//fill histo with number of events only
void FastPartons::Histo::fill(double entry) {
  cout << "min    "  << min << endl;
  cout << "max    "  << max << endl;
  int bin = (int)((entry - min) / binWidth);
  if (bin < 0) {
    underflowcount++;
  } 
  else if (bin >= binCount) {
    overflowcount++;
  } 
  else {
    counts[bin]+=1.;
  }
}

//fill histo with event weights
void FastPartons::Histo::fill(double entry, double weight) {
  //  cout << "binwid "  << binWidth << endl;
  //  cout << "min    "  << min << endl;
  //  cout << "max    "  << max << endl;
  int bin = (int)((entry - min) / binWidth);
  //  cout << bin << endl;
  counts[bin]+=weight;  
}

void FastPartons::Histo::write(const char *outfile){
 std::ofstream fout;
 fout.open(outfile);
  for (int i=0; i<binCount; i++){
    //    cout << "counts[" << i << "] " << counts[i] << endl;
    fout << lowerBound(i) << "  " << upperBound(i) << "  " << counts[i] << endl;
  }
  fout.close();
  counts.clear();
}

int FastPartons::Histo::bins(){
  return (int)((max-min)/binWidth);
}

double FastPartons::Histo::lowerBound(int bin){
  return (min+bin*binWidth);
}

double FastPartons::Histo::upperBound(int bin){
  return (min+(bin+1)*binWidth);
}

int FastPartons::Histo::count(int bin){
  return (int)counts[bin];
}
