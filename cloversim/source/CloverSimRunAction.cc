//@file CloverSimRunAction.cc
//@brief Geant4 Run Action for CloverSim.
//@authors R. Yokoyama
//@date 9/27/2020

#include "CloverSimRunAction.hh"

CloverSimRunAction::CloverSimRunAction(const std::string &fname, PointGammaSourceGeneratorAction* pg_action)
{
    pg_action_ = pg_action;
    root_file_ = new TFile(fname.c_str(),"RECREATE");
    std::cout << "Opened a ROOT file: " << fname << std::endl;
    tree_ = new TTree("CloverSimTree","CloverSimTree");
    evt_data_ = new CloverSimTreeData();
}

CloverSimRunAction::~CloverSimRunAction() {
    if(root_file_){
        delete root_file_;
        root_file_ = nullptr;
    }
    if(evt_data_){
        delete evt_data_;
        evt_data_ = nullptr;
    }

}

void CloverSimRunAction::BeginOfRunAction(const G4Run*)
{
    if (pg_action_) {
        pg_action_->Configure();
    }
    else
    {
        std::cout << "[CloverSimRunAction]: Null pointer to the PrimaryGeneratorAction" << std::endl;
    }
    
    evt_data_->ClearData();
    tree_->Branch("eventData","CloverSimTreeData",evt_data_);
}

void CloverSimRunAction::EndOfRunAction(const G4Run*)
{
    std::cout << "Writing data to the ROOT file." << std::endl;
    tree_->Write();
    root_file_->Close();
}