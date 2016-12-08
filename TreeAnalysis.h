#ifndef TreeAnalysis_h
#define TreeAnalysis_h

#include "TreeEvent.h"


#include "TH1D.h"

#include <string>
#include <map>


using namespace std;



class TreeAnalysis {

public:

  TreeAnalysis(string name="");

  virtual void Init();

  virtual void EventAnalysis(TreeEvent * ev);

  virtual void FinishAnalysis(); // This is for user stuff

  void End(TFile * fout =0);

  void Add1DHistogram(char  * key, char * title, int nbins, double xmin, double xmax);

protected:


  string analysisName;

  std::map<string, TH1D * > histos_1d;
  std::map<string, TH1D * > histos_2d;

};

#endif
