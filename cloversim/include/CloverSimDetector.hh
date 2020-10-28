#ifndef CLOVER_SIM_DETECTOR_HH
#define CLOVER_SIM_DETECTOR_HH

#include "LENSLongLiquidScintillator.hh"
#include "LENSLongDetectorConstruction.hh"
#include "CloverSimDetectorConstruction.hh"
#include "G4VisAttributes.hh"
#include "G4SDManager.hh"

class CloverSimDetector : public LENSLongLiquidScintillator {
public:
	CloverSimDetector( G4String name ) : LENSLongLiquidScintillator( name ) {};
	virtual ~CloverSimDetector();

	void ConstructDetector(LENSLongDetectorConstruction* mainDetectorConstructor);
	//void SetSensitiveDetector();
	//void Initialize(G4HCofThisEvent* HCE);
protected:
	G4VisAttributes* yso_vis_att_ = nullptr;
	G4VisAttributes* si_vis_att_ = nullptr;
	G4VisAttributes* board_vis_att_ = nullptr;

	//std::vector<G4LogicalVolume*> m_BetaDetector_LogicalVolumes;
	//ENSLongLiquidScintillatorGammaHitsCollection* m_BetaDetectorHitsCollection = nullptr;
	//G4int m_BetaDetectorHitsCollectionID = -1;
};

#endif