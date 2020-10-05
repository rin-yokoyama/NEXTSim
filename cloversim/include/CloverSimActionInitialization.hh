#ifndef CLOVER_SIM_ACTION_INITIALIZATION_HH
#define CLOVER_SIM_ACTION_INITIALIZATION_HH

#include "G4VUserActionInitialization.hh"

#include <iostream>
#include "CloverSimEventAction.hh"
#include "CloverSimRunAction.hh"
#include "nDetParticleSource.hh"

class CloverSimActionInitialization : public G4VUserActionInitialization {
public:
    CloverSimActionInitialization(std::string fname);
    virtual ~CloverSimActionInitialization(){};

    virtual void Build() const;
    virtual void BuildForMaster() const;
private:
    std::string output_filename_;
};

#endif /* CLOVER_SIM_ACTION_INITIALIZATION_HH */