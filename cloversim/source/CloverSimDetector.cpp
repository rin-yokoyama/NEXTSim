#include "CloverSimDetector.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4SubtractionSolid.hh"
#include "G4PVPlacement.hh"
#include "G4ThreeVector.hh"
#include "G4RotationMatrix.hh"

#include "YamlReader.hpp"
using namespace CLHEP;

CloverSimDetector::~CloverSimDetector()
{
	if (yso_vis_att_)
		delete yso_vis_att_;
	if (si_vis_att_)
		delete si_vis_att_;
	if (board_vis_att_)
		delete board_vis_att_;
}

void CloverSimDetector::ConstructDetector(LENSLongDetectorConstruction *mainDetectorConstruction)
{

	/* call LENSLongLiquidScintillator::ConstructLiquidDetector */
	LENSLongLiquidScintillator::ConstructLiquidDetector(mainDetectorConstruction);

	if (!yso_vis_att_)
	{
		yso_vis_att_ = new G4VisAttributes(G4Colour(0.7, 0.0, 0.2, 0.5));
		yso_vis_att_->SetForceSolid(true);
	}
	if (!si_vis_att_)
	{
		si_vis_att_ = new G4VisAttributes(G4Colour(0.2, 0.0, 0.8, 0.5));
		si_vis_att_->SetForceSolid(true);
	}
	if (!board_vis_att_)
	{
		board_vis_att_ = new G4VisAttributes(G4Colour(0.7, 0.7, 0.0, 0.5));
		//board_vis_att_->SetForceSolid(true);
	}

	/* placement of the other clover */
	{

		G4RotationMatrix rotation_ornl_clover = G4RotationMatrix();

		rotation_ornl_clover.rotateY(90 * deg);
		rotation_ornl_clover.rotateZ(45 * deg);
		rotation_ornl_clover.rotateX(0 * deg);

		G4ThreeVector translation_ornl_clover(0, 0., -225 * CLHEP::mm);

		translation_ornl_clover.rotateY(90 * deg);
		translation_ornl_clover.rotateZ(45 * deg);
		translation_ornl_clover.rotateX(0 * deg);

		G4RotationMatrix rotation_ornl_clover2 = G4RotationMatrix();

		rotation_ornl_clover2.rotateY(-90 * deg);
		rotation_ornl_clover2.rotateZ(315 * deg);
		rotation_ornl_clover2.rotateX(0 * deg);

		G4ThreeVector translation_ornl_clover2(0, 0., 225 * CLHEP::mm);

		translation_ornl_clover2.rotateY(-90 * deg);
		translation_ornl_clover2.rotateZ(135 * deg);
		translation_ornl_clover2.rotateX(0 * deg);

		/* defines the rotation of the clover (180 deg around the beam axis) */
		/* rotation of the first clover */
		G4Transform3D transformation_ornl_clover(rotation_ornl_clover, translation_ornl_clover);
		G4Transform3D transformation_ornl_clover2(rotation_ornl_clover2, translation_ornl_clover2);

		/* delete pre-defined clovers */
		for (int i = 0; i < m_Gas_LogicalVolumes[0]->GetNoDaughters(); ++i)
		{
			auto pvp = m_Gas_LogicalVolumes[0]->GetDaughter(i);
			if (pvp->GetName() == "SingleModule_Volume")
				delete pvp;
			else if (pvp->GetName() == "YSO_Volume")
				delete pvp;
		}
		/* find a G4LogicalVolume whose name is "SingleModule_Volume" (the first clover) */
		/* and place another one on the other side */
		auto it = std::find_if(
			m_ModuleTotal_LogicalVolumes.begin(),
			m_ModuleTotal_LogicalVolumes.end(),
			[](G4LogicalVolume *const &x) -> bool { return x->GetName() == "Al_Can_Logical"; });
		if (it != m_ModuleTotal_LogicalVolumes.end())
		{
			new G4PVPlacement(transformation_ornl_clover, m_ModuleTotal_LogicalVolumes[1], "SingleModule_Volume2", m_Gas_LogicalVolumes[0], 0, 0);
			new G4PVPlacement(transformation_ornl_clover2, m_ModuleTotal_LogicalVolumes[1], "SingleModule_Volume2", m_Gas_LogicalVolumes[0], 0, 1);
		}
		std::cout << "n_Volumes: " << m_Gas_LogicalVolumes[0]->GetNoDaughters() << std::endl;
	}
}
