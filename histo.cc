#include <histo.hh>

//FastPartons::Histo::Histo() {}
//FastPartons::Histo::~Histo() {}

FastPartons::Histo::Histo(const double xmin, const double xmax, const double deltax){
  min = xmin;
  max = xmax;
  binWidth = deltax;
  binCount = (int)((max-min)/binWidth);
  counts = vector<double>(binCount,0);
  weightsOver = 0.;
  weightsUnder = 0.;
}

//@TODO: inherit from 1D histo???
FastPartons::Histo2d::Histo2d(const double xmin, const double xmax, const double deltax, const double ymin, const double ymax, const double deltay){
  minx = xmin;
  maxx = xmax;
  miny = ymin;
  maxy = ymax;
  binWidthx = deltax;
  binWidthy = deltay;
  binCountx = (int)((maxx-minx)/binWidthx);
  binCounty = (int)((maxy-miny)/binWidthy);
  counts2d = vector< vector<double>> (binCountx, vector<double>(binCounty,0));
}


//fill histo with number of events only
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

//fill histo with event weights
void FastPartons::Histo::fill(double entry, double weight) {
  if ( entry < min ) {
    weightsUnder += weight;
    return; }
  else if ( entry > max ){
    weightsOver += weight;
    return; }
  int bin = (int)((entry - min) / binWidth);
  counts[bin]+=weight;
  return;
}

//fill 2d histo
void FastPartons::Histo2d::fill(double xentry, double yentry) {
  if ( xentry < minx || xentry > maxx || yentry < miny || yentry > maxy ) return;
  int binx = (int)((xentry - minx) / binWidthx);
  int biny = (int)((yentry - miny) / binWidthy);
  counts2d[binx][biny] += 1;
  return;
}

//fill 2d histo with event weights
void FastPartons::Histo2d::fill(double xentry, double yentry, double weight) {
  if ( xentry < minx || xentry > maxx || yentry < miny || yentry > maxy ) return;
  int binx = (int)((xentry - minx) / binWidthx);
  int biny = (int)((yentry - miny) / binWidthy);
  counts2d[binx][biny] += weight;  
  return;
}

//write out raw histogram
void FastPartons::Histo::write(const char *outfile){
 std::ofstream fout;
 fout.open(outfile);
  for (int i=0; i<binCount; i++){
    fout << lowerBound(i) << "  " << upperBound(i) << "  " << counts[i] << endl;
  }
  fout.close();
  counts.clear();
}

//write out normalised histogram
void FastPartons::Histo::write(const char *outfile, double norm){
 std::ofstream fout;
 fout.open(outfile);
  for (int i=0; i<binCount; i++){
    fout << lowerBound(i) << "  " << upperBound(i) << "  " << counts[i]/norm << endl;
  }
  fout.close();
  counts.clear();
}

//write out raw 2d histogram
void FastPartons::Histo2d::write(const char *outfile){
 std::ofstream fout;
 fout.open(outfile);
  for (int i=0; i<binCountx; i++){
    for (int j=0; j<binCounty; j++){
      fout << lowerBoundx(i) << "  " << upperBoundx(i) << "  " << lowerBoundy(j) << "  " << upperBoundy(j) << "  " << counts2d[i][j]  << endl;
    }
  }
  fout.close();
  counts2d.clear();
}

//write out normalized 2d histogram
void FastPartons::Histo2d::write(const char *outfile, double norm){
 std::ofstream fout;
 fout.open(outfile);
  for (int i=0; i<binCountx; i++){
    for (int j=0; j<binCounty; j++){
      fout << lowerBoundx(i) << "  " << upperBoundx(i) << "  " << lowerBoundy(j) << "  " << upperBoundy(j) << "  " << counts2d[i][j]/norm  << endl;
    }
  }
  fout.close();
  counts2d.clear();
}

//underflow
double FastPartons::Histo::underflow(){
  return weightsUnder;
}

//overflow
double FastPartons::Histo::overflow(){
  return weightsOver;
}

//add underflow to first bin
void FastPartons::Histo::addUnderflow(){
  counts[0] += weightsUnder;
  return;
}

//add overflow to last bin
void FastPartons::Histo::addOverflow(){
  counts[binCount-1] += weightsOver;
  return;
}

//integral of a 1d histogram
double FastPartons::Histo::integral(){
  double area = 0;
  for (int i=0; i<binCount; i++){
    area += counts[i];
  }
  return area;
}

//integral of a 2d histogram
double FastPartons::Histo2d::integral(){
  double volume = 0;
  for (int i=0; i<binCountx; i++){
    for (int j=0; j<binCounty; j++){
      volume += counts2d[i][j];
    }
  }
  return volume;
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

double FastPartons::Histo2d::lowerBoundx(int bin){
  return (minx+bin*binWidthx);
}

double FastPartons::Histo2d::lowerBoundy(int bin){
  return (miny+bin*binWidthy);
}

double FastPartons::Histo2d::upperBoundx(int bin){
  return (minx+(bin+1)*binWidthx);
}

double FastPartons::Histo2d::upperBoundy(int bin){
  return (miny+(bin+1)*binWidthy);
}

int FastPartons::Histo::count(int bin){
  return (int)counts[bin];
}
