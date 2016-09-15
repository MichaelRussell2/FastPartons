#include <iostream>
#include <cmath>

using namespace std;

namespace FastPartons{

class Histo {
public:

  //constructor
  Histo(double xmin, double xmax, double binWidth);
  
  void fill(double entry);
  void write(const char *outfile);
  int bins();                    
  int count(int bin);         
  int getunderflowcount();// @TODO: define this     
  int getoverflowcount(); // @TODO: define this     
  double lowerBound(int bin);
  double upperBound(int bin);

  //virtual ~Histo();

  private:
  double min;
  double max;
  double binWidth;
  int binCount;
  int underflowcount, overflowcount;
  double counts[]; // @TODO: Integer counts

};

}