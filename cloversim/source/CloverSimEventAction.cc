//@file CloverSimEventAction.cc
//@brief Geant4 Run Action for CloverSim.
//@authors R. Yokoyama
//@date 9/27/2020

#include "CloverSimEventAction.hh"
#include "CloverSingleHit.hh"

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
    
    auto hitCollections = evt->GetHCofThisEvent();
    if (hitCollections) {
        for (int i=0; i<hitCollections->GetNumberOfCollections(); ++i) {
            if (hitCollections->GetHC(i)->GetName() == "CloverSingle") {
                //auto hc = hitCollections->GetHC(i);
                //auto nhits = hc->GetSize();
                CloverSingleHitsCollection* hc = (CloverSingleHitsCollection*)hitCollections->GetHC(i);
                auto nhits = hc->entries();
                clover_hit_ = CLOVER_HIT_DEFAULT_STRUCT;
                clover_hit_.modId = i;
                G4double energy = 0;
                //std::cout << "CloverSingle n_hits: " << nhits << std::endl;
                for (int i=0; i<nhits; ++i) {
                    auto hit = (CloverSingleHit*)hc->GetHit(i);
                    energy += hit->GetEdep();
                    //std::cout << " modId: " << clover_hit_.modId << " modE: " << clover_hit_.modE;
                }
                clover_hit_.modE = energy;
                tree_data_->clover_hits_.emplace_back(clover_hit_);
            }
        }
        //std::cout << std::endl;
    }

    tree_->Fill();
}