#include "TreeAnalysis.h"

#include "TreeEvent.h"

#include <ios>
#include <iostream>
#include <fstream>


TreeAnalysis::TreeAnalysis(string name) {

  analysisName = name;

}


void TreeAnalysis::Add1DHistogram(char  * key, char * title, int nbins, double xmin, double xmax) {

  histos_1d[key] = new TH1D(key, title, nbins, xmin, xmax);

}


void TreeAnalysis::Init() {

  // Book your histograms here, here are examples
  //   Add1dHistogram("met","Missing ET", 100, 0., 300.);
  

}

void TreeAnalysis::EventAnalysis(TreeEvent *) {


}



void TreeAnalysis::FinishAnalysis() {

  std::cout << "Close (base class: do nothing) \n";

}


void TreeAnalysis::End(TFile * fout) {

  FinishAnalysis();

  if (fout) {
    fout->cd();

    std::map<string, TH1D* >::iterator ithist;
    for (ithist = histos_1d.begin(); ithist != histos_1d.end(); ithist++) {
      ithist->second->Write();
    }

    std::map<string, TH1D* >::iterator ithist2;
    for (ithist2 = histos_2d.begin(); ithist2 != histos_2d.end(); ithist2++) {
      ithist2->second->Write();
    }

  }

}
