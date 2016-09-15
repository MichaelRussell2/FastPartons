#include "histo.hh"
#include <cmath>
#include <iostream>
#include <fstream>

FastPartons::Histo::Histo(double xmin, double xmax, double bw){
  min = xmin;
  max = xmax;
  binWidth = bw;
  binCount = (int)((max-min)/binWidth);
}

void FastPartons::Histo::fill(double entry) {
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

void FastPartons::Histo::write(const char *outfile){
 std::ofstream fout;
 fout.open(outfile);
  for (int i=0; i<binCount; i++){
    fout << lowerBound(i) << "  " << upperBound(i) << "  " << counts[i] << endl;
  }
  fout.close();
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
