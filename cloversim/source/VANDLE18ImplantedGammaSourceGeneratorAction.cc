#include "VANDLE18ImplantedGammaSourceGeneratorAction.hh"
#include "CorrectedVANDLEData.h"

VANDLE18ImplantedGammaSourceGeneratorAction::VANDLE18ImplantedGammaSourceGeneratorAction() : default_pos_(0, 0, 0)
{
    messenger_ = new CloverSimParticleSourceMessenger(this);
}

VANDLE18ImplantedGammaSourceGeneratorAction::~VANDLE18ImplantedGammaSourceGeneratorAction()
{
    if (messenger_)
        delete messenger_;
}

void VANDLE18ImplantedGammaSourceGeneratorAction::SetReader()

{
}

const G4ThreeVector VANDLE18ImplantedGammaSourceGeneratorAction::ReadPosition()
{

    // OutputTreeData<PspmtData, OutputTreeData<PspmtData, TreeData>> *data;

    std::vector<CorrectedVANDLEData> *data;
    do
    {
        /* if somehow couldn't read the next event return default position */
        if (!Next())
            return default_pos_;
        data = reader_value_->Get();
    } while (data->empty());

    /* Fill position of the source from root file. */
    const double x = data->at(0).GetTranformedX();
    const double y = data->at(0).GetTransformedY();
    const double z = -50 * CLHEP::mm + (rand3.Rndm() - 0.5) * GetYSOThickness() * CLHEP::mm;

    return G4ThreeVector(x, y, z);
}