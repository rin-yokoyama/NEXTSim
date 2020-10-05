//@file CloverSimHit.cc
//@brief G4VHit class for CloverSim.
//@authors R. Yokoyama
//@date 9/30/202

#include "CloverSimHit.hh"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"

#include <iomanip>

G4ThreadLocal G4Allocator<CloverSimHit>* CloverSimHitAllocator=0;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

CloverSimHit::CloverSimHit()
 : G4VHit(),
   fModuleId(-1),
   fDetectorId(-1),
   fEenergy(0.),
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

CloverSimHit::~CloverSimHit() {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

CloverSimHit::CloverSimHit(const CloverSimHit& right)
  : G4VHit()
{
  fModuleId   = right.fModuleId;
  fDetectorId = right.fDetectorId;
  fEenergy      = right.fEnergy;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

const CloverSimHit& CloverSimHit::operator=(const CloverSimHit& right)
{
  fModuleId   = right.fModuleId;
  fDetectorId = right.fDetectorId;
  fEenergy      = right.fEnergy;

  return *this;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4int CloverSimHit::operator==(const CloverSimHit& right) const
{
  return ( this == &right ) ? 1 : 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void CloverSimHit::Draw()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void CloverSimHit::Print()
{
  G4cout
     << "  ModuleId: " << fModuleId << " DetectorId: " << fDetectorId
     << "Energy: "
     << std::setw(7) << G4BestUnit(fEenergy,"Energy")
     << G4endl;
}