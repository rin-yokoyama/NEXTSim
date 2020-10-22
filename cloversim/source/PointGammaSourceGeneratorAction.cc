//@file PointGammaSourceGeneratorAction.cc
//@brief Gamma emission from a point source.
//@authors R. Yokoyama
//@date 2/21/2020

#include "PointGammaSourceGeneratorAction.hh"
#include "CloverSimParticleSourceMessenger.hh"

using namespace CLHEP;

PointGammaSourceGeneratorAction::PointGammaSourceGeneratorAction() : file_name_("__na__"), pos_(0,0,0), energy_(1000*CLHEP::keV) {
}

void PointGammaSourceGeneratorAction::SetSourceType(const G4String &fname) {
	file_name_ = fname;
}

void PointGammaSourceGeneratorAction::SetSourcePos(const G4ThreeVector &vec) {

	pos_.setX(vec.getX()*CLHEP::mm);
	pos_.setY(vec.getY()*CLHEP::mm);
	pos_.setZ(vec.getZ()*CLHEP::mm);
	
}

void PointGammaSourceGeneratorAction::SetSourceEnergy(const double &energy) {
	energy_ = energy*CLHEP::keV;
}

int PointGammaSourceGeneratorAction::Configure() {
	/* create a particle gun for gamma */
	particle_gun_ = new G4ParticleGun(1);
	G4ParticleTable* particle_table = G4ParticleTable::GetParticleTable();
	particle_gun_->SetParticleDefinition(particle_table->FindParticle("gamma"));

	/* create a gamma source instance */
	if (file_name_ != "__na__"){
		if (gamma_source_) {
			delete gamma_source_;
			gamma_source_ = nullptr;
		}
		gamma_source_ = new GSource4G4(file_name_);
	}

	/* set particle position */
	particle_gun_->SetParticlePosition(pos_);

	completed_ = false;

	if (!gamma_source_)
		return 1;
	else
		return 0;
}

void PointGammaSourceGeneratorAction::GeneratePrimaries( G4Event* anEvent ) {

	/* isotropic direction generator */
	auto moment_dir = []() {
		/* A=-1, B=1 for 4*pi, B=0 for 2*pi emission */
		const G4double A = -1.0;
		const G4double B = 1.0;
		G4double cosTheta = G4UniformRand() * (B - A) + A;	 // A < cosTheta < B
		G4double sinTheta = sqrt(1.0 - cosTheta * cosTheta); // 0. < sinTheta < 1.
		G4double phi = G4UniformRand() * 8.0 * atan(1.0);	 // 0. <		particle_gun_->GeneratePrimaryVertex(anEvent); phi < 2*pi

		G4double randomXaim = cos(phi) * sinTheta;
		G4double randomYaim = sin(phi) * sinTheta;
		G4double randomZaim = cosTheta;
		G4ThreeVector aim(randomXaim, randomYaim, randomZaim);
		return aim;
	};

	/* No source file provided */
	if (!gamma_source_) {
		particle_gun_->SetParticleEnergy(energy_);
		particle_gun_->SetParticleMomentumDirection(moment_dir());
		particle_gun_->GeneratePrimaryVertex(anEvent);
		return;
	}

	/* set gamma-ray energy*/
	if (!gamma_source_->IfNext()) {
		particle_gun_->SetParticleEnergy(0.);
		if (!completed_) {
			std::cout << "[PointGammaSourceGeneratorAction]: gamma emission completed." << std::endl;
			completed_ = true;
		}
		return;
	}
	G4int n_gamma = gamma_source_->EmitGamma();
	for (int i = 0; i < n_gamma; ++i)
	{
		/* set gamma-ray direction */
		{
			particle_gun_->SetParticleMomentumDirection(moment_dir());
		}
		particle_gun_->SetParticleEnergy(gamma_source_->GetEGamma(i) * keV);
		particle_gun_->GeneratePrimaryVertex(anEvent);
	}
	return;
}