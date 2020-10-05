
//@file CloverSimEventAction.hh
//@brief Geant4 Event Action for CloverSim.
//@authors R. Yokoyama
//@date 9/27/2020

#ifndef CLOVER_SIM_EVENT_ACTION_HH
#define CLOVER_SIM_EVENT_ACTION_HH

#include <TTree.h>
#include "G4Event.hh"
#include "G4UserEventAction.hh"
#include "CloverSimTreeData.hh"

class CloverSimEventAction: public G4UserEventAction
{
public:
    CloverSimEventAction(CloverSimTreeData* tree_data, TTree* tree);
    virtual ~CloverSimEventAction(){}

    virtual void BeginOfEventAction(const G4Event*);
    virtual void EndOfEventAction(const G4Event*);
protected:
    CloverSimTreeData* tree_data_;
    TTree* tree_;
    clover_hit_struct clover_hit_;
};

#endif /* end of CLOVER_SIM_EVENT_ACTION_HH */
