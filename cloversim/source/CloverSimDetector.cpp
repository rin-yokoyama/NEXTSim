#include "CloverSimDetector.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4SubtractionSolid.hh"
#include "G4PVPlacement.hh"
#include "G4ThreeVector.hh"
#include "G4RotationMatrix.hh"

#include "YamlReader.hpp"

CloverSimDetector::~CloverSimDetector() {
	if (yso_vis_att_)
		delete yso_vis_att_;
	if (si_vis_att_)
		delete si_vis_att_;
	if (board_vis_att_)
		delete board_vis_att_;
}

void CloverSimDetector::ConstructDetector(LENSLongDetectorConstruction* mainDetectorConstruction) {

	/* call LENSLongLiquidScintillator::ConstructLiquidDetector */
	LENSLongLiquidScintillator::ConstructLiquidDetector(mainDetectorConstruction);

	if (!yso_vis_att_) {
		yso_vis_att_ = new G4VisAttributes(G4Colour(0.7,0.0,0.2,0.5));
		yso_vis_att_->SetForceSolid(true);
	}
	if (!si_vis_att_) {
		si_vis_att_ = new G4VisAttributes(G4Colour(0.2,0.0,0.8,0.5));
		si_vis_att_->SetForceSolid(true);
	}
	if (!board_vis_att_) {
		board_vis_att_ = new G4VisAttributes(G4Colour(0.7,0.7,0.0,0.5));
		//board_vis_att_->SetForceSolid(true);
	}

	/* placement of the other clover */
	{
		/* defines the rotation of the clover (180 deg around the beam axis) */
		/* rotation of the first clover */
		G4RotationMatrix* rot1 = new G4RotationMatrix();
		rot2->rotateX(0. * CLHEP::deg);
		/* rotation of the second clover */
		G4RotationMatrix* rot2 = new G4RotationMatrix();
		rot2->rotateX(180. * CLHEP::deg);

		/* set placement (positive x) */
		const G4double dist = 3.5 * CLHEP::cm;
		/* placement of the first clover */
		G4ThreeVector placement1( 2.25 * CLHEP::cm, 0.0 * CLHEP::cm, -(dist + 0.5 * (297.0) * CLHEP::mm) );
		/* placement of the second clover */
		G4ThreeVector placement2( 2.25 * CLHEP::cm, 0.0 * CLHEP::cm, dist + 0.5 * (297.0) * CLHEP::mm );

		/* adjust distance between clovers */
		for (int i = 0; i < m_Gas_LogicalVolumes[0]->GetNoDaughters(); ++i) {
			auto pvp = m_Gas_LogicalVolumes[0]->GetDaughter(i);
			if(pvp->GetName() == "SingleModule_Volume")
				pvp->SetTranslation(placement1);
				pvp->SetRotation(rot1);
		}
		/* find a G4LogicalVolume whose name is "SingleModule_Volume" (the first clover) */
		/* and place another one on the other side */
		auto it = std::find_if(
			m_ModuleTotal_LogicalVolumes.begin(),
			m_ModuleTotal_LogicalVolumes.end(),
			[](G4LogicalVolume* const &x)->bool {return x->GetName()=="Al_Can_Logical"; }
		);
		if (it != m_ModuleTotal_LogicalVolumes.end()) {
			new G4PVPlacement(rot2, placement2, m_ModuleTotal_LogicalVolumes[1], "SingleModule_Volume2", m_Gas_LogicalVolumes[0], 0, 1);
		}
		std::cout << "n_Volumes: " << m_Gas_LogicalVolumes[0]->GetNoDaughters() << std::endl;
	}
