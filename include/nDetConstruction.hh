//
// $Id: nDetConstruction.hh,v 1.0 Sept., 2015 $
//  Written by Dr. Xiaodong Zhang
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef nDetConstruction_h
#define nDetConstruction_h 1

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"

#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"

#include "nDetSD.hh"

#include "G4NistManager.hh"
#include "G4Material.hh"
#include "G4MaterialTable.hh"
#include "G4Element.hh"
#include "G4Isotope.hh"
#include "G4ElementTable.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4OpticalSurface.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Trap.hh"
#include "G4LogicalVolume.hh"
#include "G4VisAttributes.hh"
#include "G4RotationMatrix.hh"
#include "G4ThreeVector.hh"
#include "G4Transform3D.hh"
#include "G4PVPlacement.hh"
#include "G4OpBoundaryProcess.hh"
#include "G4RotationMatrix.hh"
#include "G4Transform3D.hh"
#include "G4PVParameterised.hh"
#include "G4VNestedParameterisation.hh"

// Replica 
// Assembly volumes
// no assembly is used currently
#include "G4AssemblyVolume.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class nDetConstruction : public G4VUserDetectorConstruction
{
  public:
    nDetConstruction();
   ~nDetConstruction();

  public:
    G4VPhysicalVolume* Construct();

  private:
    // data of detector structure; half of size
    G4double expHallX;		// width
    G4double expHallY;		// length
    G4double expHallZ;		// thickness

    G4double assemblyBoxX;
    G4double assemblyBoxY;
    G4double assemblyBoxZ;

    G4double assemblyPx;
    G4double assemblyPy;
    G4double assemblyPz;

    G4double ej200X;
    G4double ej200Y;
    G4double ej200Z;

    G4double greaseX;
    G4double greaseY;
    G4double greaseZ;

    G4double qwSiPMx;
    G4double qwSiPMy;
    G4double qwSiPMz;

    G4double psSiPMx;
    G4double psSiPMy;
    G4double psSiPMz;

    // logical and physical volume
    G4LogicalVolume* expHall_logV;
    G4LogicalVolume* assembly_logV;

    G4LogicalVolume* ej200_logV;    // ej200 scintillator
    G4LogicalVolume* grease_logV;
    G4LogicalVolume* qwSiPM_logV;
    G4LogicalVolume* psSiPM_logV;

    G4VPhysicalVolume* expHall_physV;
    G4VPhysicalVolume* assembly_physV;

    // member functions
    void buildExpHall();
    void buildAssembly();

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif /*nDetConstruction_h*/