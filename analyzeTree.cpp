// #include "EventTree_V07_04_14_00.h"
#include "TreeEvent.h"

#include <string>
#include <iostream>
#include <fstream>


using namespace std;


int main(int argc, char **argv)
{
  char* outputFileName(0);
  char* inputFileName(0);
  char* fileList(0);
  bool useInputList = false;
  bool gotInput  = false;
  bool gotOutput = false;
  char c;

  while ((c = getopt (argc, argv, "i:o:l:")) != -1)
    switch (c) {
      case 'o':
        gotOutput = true;
        outputFileName = new char[strlen(optarg)+1];
        strcpy(outputFileName, optarg);
        break;
      case 'i':
        gotInput = true;
        inputFileName = new char[strlen(optarg)+1];
        strcpy(inputFileName, optarg);
        break;
      case 'l':
        useInputList = true;
        fileList = new char[strlen(optarg)+1];
        strcpy(fileList, optarg);
        break;
      default:
        cout << "usage: [-k|-g|-l] [-v] [-b <binWidth>]   -i <input> -o <output> \n";
        abort ();
    }

  // OUTPUT ROOT FILE
  TFile* fout;
  if (gotOutput)  fout = new TFile(outputFileName, "RECREATE");
  else            fout = new TFile("output.root", "RECREATE");


  // INPUT TREES
  vector<TString> inputName;
  TChain chain("TREE_IN_ROOTFILE");

  if (useInputList) {
    ifstream list(fileList);
    TString name;
    while (list>>name)  inputName.push_back(name);
  } else if (gotInput)  inputName.push_back(inputFileName);
  else {
    cout << "Got no input ROOT file: quit \n";
    return 1;
  }

  for (unsigned int input = 0; input < inputName.size(); input++) {
    cout << "Adding: " << input << endl;
    chain.Add(inputName[input]);
    cout << "Added \n";
  }

  TTree* ev_tTree = (TTree*)& chain;
  TreeEvent * the_event= new TreeEvent(ev_tTree);
  Int_t events = ev_tTree->GetEntries();
  cout << endl << "Total number of events: " << events << endl << endl;
  /////////////////////////////////////////////////////////////////////

  /// HERE IS THE PLACE WHERE YOU PUT YOUR STUFF 


// Event loop
  unsigned int nEvents = 0;

  for  (Int_t k = 0; k < events; k++) {

    if (! (k%100000) ) std::cout << "Processed " << k << " events \n";

    // Read next event before we do anything with it
    ev_tTree->GetEntry(k);
    the_event->ReadEvent();

  }

  // We need to write explicity all histograms to the output root
  fout->cd();
  fout->Close();
}

