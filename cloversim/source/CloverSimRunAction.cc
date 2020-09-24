//@file CloverSimRunAction.cc
//@brief Geant4 Run Action for CloverSim.
//@authors R. Yokoyama
//@date 9/27/2020

#include "CloverSimRunAction.hh"

CloverSimRunAction::CloverSimRunAction(const std::string &fname)
{
    root_file_ = new TFile(fname.c_str(),"RECREATE");
    std::cout << "Opened a ROOT file: " << fname << std::endl;
    tree_ = new TTree("CloverSimTree","CloverSimTree");
    evt_data_ = new CloverSimTreeData();
}

void CloverSimRunAction::BeginOfRunAction(const G4Run*)
{
    evt_data_->ClearData();
    tree_->Branch("eventData","CloverSimTreeData",evt_data_);
}

void CloverSimRunAction::EndOfRunAction(const G4Run*)
{
    std::cout << "Writing data to the ROOT file." << std::endl;
    tree_->Write();
    root_file_->Close();
}