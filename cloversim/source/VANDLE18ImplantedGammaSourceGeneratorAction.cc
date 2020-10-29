#include "VANDLE18ImplantedGammaSourceGeneratorAction.hh"


VANDLE18ImplantedGammaSourceGeneratorAction::VANDLE18ImplantedGammaSourceGeneratorAction() : default_pos_(0,0,0) {
    messenger_ = new CloverSimParticleSourceMessenger(this);
}

VANDLE18ImplantedGammaSourceGeneratorAction::~VANDLE18ImplantedGammaSourceGeneratorAction() {
    if (messenger_)
        delete messenger_;
}

void VANDLE18ImplantedGammaSourceGeneratorAction::SetReader(){

}

const G4ThreeVector VANDLE18ImplantedGammaSourceGeneratorAction::ReadPosition(){

    OutputTreeData<PspmtData,OutputTreeData<PspmtData,TreeData>>* data;
    do {
        /* if somehow couldn't read the next event return default position */
        if (!Next())
            return default_pos_;
        data = reader_value_->Get();
    }
    while (data->output_vec_.empty());
    
    /* Fill position of the source from root file. */
    const double x = data->high_gain_.pos_x_;
    const double y = data->high_gain_.pos_y_;
    const double z = 0;

	//std::cout << " (" <<  x << ", " << y << ", " << z << ")" << std::endl;

    return G4ThreeVector(x,y,z);
}