#ifndef TreeEvent_h
#define TreeEvent_h


#include "TreeClass.h"


#include "TLorentzVector.h"


class TreeEvent : public TreeClass
{
public:
  TreeEvent(TTree *tree);

  void ReadEvent();

  bool passesSelection();

protected:


};


#endif // #ifdef 
