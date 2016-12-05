#ifndef TreeAnalysis_h
#define TreeAnalysis_h

#include "TreeEvent.h"


class TreeAnalysis {

public:

  TreeAnalysis(TreeEvent * e);

  virtual void Init();

  void CreateBaseHistos();

  virtual void EventAnalysis();

  virtual void Finish(TFile * fout =0);

protected:

  TreeEvent * evt;

};

#endif
