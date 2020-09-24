//@file PointGammaSourceGeneratorAction.hh
//@brief Gamma emission from a point source.
//@authors R. Yokoyama
//@date 2/21/2020

#ifndef POINT_GAMMA_SOURCE_GENERATOR_ACTION_HH
#define POINT_GAMMA_SOURCE_GENERATOR_ACTION_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4Event.hh"
#include "G4ThreeVector.hh"
#include "GSource4G4.hpp"
#include "G4RandomTools.hh"

class PointGammaSourceGeneratorAction : public G4VUserPrimaryGeneratorAction {
public:
	PointGammaSourceGeneratorAction(const std::string &fname) { Configure(fname); }
	~PointGammaSourceGeneratorAction() {}

	int Configure(const std::string &fname);
	void GeneratePrimaries(G4Event *anEvent);

protected:
	G4ParticleGun* particle_gun_;
	GSource4G4* gamma_source_ = nullptr;
	G4bool completed_ = false;
};
#endif
