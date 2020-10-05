//@file CloverSimRunAction.hh
//@brief Geant4 Run Action for CloverSim.
//@authors R. Yokoyama
//@date 9/27/2020

#ifndef CLOVER_SIM_RUN_ACRION_HH
#define CLOVER_SIM_RUN_ACRION_HH

#include <iostream>
#include <TTree.h>
#include <TFile.h>
#include "G4UserRunAction.hh"
#include "globals.hh"
#include "CloverSimTreeData.hh"
#include "PointGammaSourceGeneratorAction.hh"

class CloverSimRunAction: public G4UserRunAction
{
public:
    CloverSimRunAction(const std::string &fname, PointGammaSourceGeneratorAction* pg_action);
    virtual ~CloverSimRunAction(){}

    virtual void BeginOfRunAction(const G4Run* run);
    virtual void EndOfRunAction(const G4Run* run);

    CloverSimTreeData* GetEventData(){return evt_data_;}
    TTree* GetTree(){return tree_;}

protected:
    std::string file_name_;
    std::string tree_name_;
    TFile* root_file_;
    TTree* tree_;
    CloverSimTreeData* evt_data_;
    PointGammaSourceGeneratorAction* pg_action_;
};

#endif /* end of CLOVER_SIM_RUN_ACTION_HH */