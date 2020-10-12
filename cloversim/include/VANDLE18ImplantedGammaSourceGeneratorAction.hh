#ifndef VANDLE18_IMPLANTED_GAMMA_SOURCE_GENERATOR_ACTION_HH
#define VANDLE18_IMPLANTED_GAMMA_SOURCE_GENERATOR_ACTION_HH

#include "ImplantedGammaSourceGeneratorAction.hh"
#include "G4ThreeVector.hh"
#include "PspmtAnalyzerData.hpp"
#include "PspmtData.hpp"
#include "OutputTreeData.hpp"
#include "BigRIPSTreeData.h"
#include "CloverSimParticleSourceMessenger.hh"

class CloverSimParticleSourceMessenger;

class VANDLE18ImplantedGammaSourceGeneratorAction :
    public ImplantedGammaSourceGeneratorAction<OutputTreeData<PspmtData, OutputTreeData<PspmtData,TreeData>>>
{
public:
    VANDLE18ImplantedGammaSourceGeneratorAction();
    ~VANDLE18ImplantedGammaSourceGeneratorAction();

	void SetReader() override;
	const G4ThreeVector ReadPosition() override;

private:
    G4ThreeVector default_pos_;
    CloverSimParticleSourceMessenger* messenger_ = nullptr;

};

#endif /* VANDLE18_IMPLANTED_GAMMA_SOURCE_GENERATOR_ACTION_HH */