//@file CloverSimEventAction.cc
//@brief Geant4 Run Action for CloverSim.
//@authors R. Yokoyama
//@date 9/27/2020

#include "CloverSimEventAction.hh"

CloverSimEventAction::CloverSimEventAction(CloverSimTreeData* tree_data, TTree* tree)
{
    tree_data_ = tree_data;
    tree_ = tree;
}

void CloverSimEventAction::BeginOfEventAction(const G4Event* evt)
{
    tree_data_->ClearData();
}

void CloverSimEventAction::EndOfEventAction(const G4Event* evt)
{
    clover_hit_ = CLOVER_HIT_DEFAULT_STRUCT;
    clover_hit_.modId = 1;
    clover_hit_.modE = 100;
    
    tree_data_->clover_hits_.push_back(clover_hit_);
    std::cout << "event action " << tree_data_->clover_hits_.size() << std::endl;

    tree_->Fill();
}