#ifndef VANDLE18_IMPLANTED_GAMMA_SOURCE_GENERATOR_ACTION_HH
#define VANDLE18_IMPLANTED_GAMMA_SOURCE_GENERATOR_ACTION_HH

#include "ImplantedGammaSourceGeneratorAction.hh"
#include "G4ThreeVector.hh"
#include "PspmtAnalyzerData.hpp"
#include "PspmtData.hpp"
#include "OutputTreeData.hpp"
#include "BigRIPSTreeData.h"
#include "CorrectedVANDLEData.h"
#include "CloverSimParticleSourceMessenger.hh"
#include <TRandom3.h>
#include <TROOT.h>

class CloverSimParticleSourceMessenger;

class VANDLE18ImplantedGammaSourceGeneratorAction : public ImplantedGammaSourceGeneratorAction<std::vector<CorrectedVANDLEData>>

{
public:
    VANDLE18ImplantedGammaSourceGeneratorAction();
    ~VANDLE18ImplantedGammaSourceGeneratorAction();

    void SetReader() override;
    const G4ThreeVector ReadPosition() override;

    static const double GetYSOPosXY(const double &x)
    {
        return 24.0 * ((x - 0.5) / 0.3) * CLHEP::mm;
    }

private:
    G4ThreeVector default_pos_;
    CloverSimParticleSourceMessenger *messenger_ = nullptr;

protected:
    TRandom3 rand3;
    static const double GetYSOThickness() { return 5.0 * CLHEP::mm; }
};

#endif /* VANDLE18_IMPLANTED_GAMMA_SOURCE_GENERATOR_ACTION_HH */