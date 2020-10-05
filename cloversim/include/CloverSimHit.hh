//@file CloverSimHit.hh
//@brief G4VHit class for CloverSim.
//@authors R. Yokoyama
//@date 9/30/2020

#ifndef CLOVER_SIM_HIT_HH
#define CLOVER_SIM_HIT_HH

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "tls.hh"

///@ brief
class CloverSimHit : public G4VHit
{
  public:
    CloverSimHit();
    CloverSimHit(const CloverSimHit&);
    virtual ~CloverSimHit();

    // operators
    const CloverSimHit& operator=(const CloverSimHit&);
    G4int operator==(const CloverSimHit&) const;

    inline void* operator new(size_t);
    inline void  operator delete(void*);

    // methods from base class
    virtual void Draw();
    virtual void Print();

    // Set methods
    void SetModuleId(G4int mod_id) { fModuleId = mod_id; };
    void SetDetectorId(G4int det_id) { fDetectorId = det_id; };
    void SetEnergy(const G4double &energy) { fEnergy = energy; };

    // Get methods
    G4int GetModuleId() const     { return fModuleId; };
    G4int GetDetectorId() const   { return fDetectorId; };
    G4double GetEnergy() const     { return fEnergy; };

  private:

      G4int         fModuleId;
      G4int         fDetectorId;
      G4double      fEnergy;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

typedef G4THitsCollection<CloverSimHit> CloverSimHitsCollection;

extern G4ThreadLocal G4Allocator<CloverSimHit>* CloverSimHitAllocator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void* CloverSimHit::operator new(size_t)
{
  if(!CloverSimHitAllocator)
      CloverSimHitAllocator = new G4Allocator<CloverSimHit>;
  return (void *) CloverSimHitAllocator->MallocSingle();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void CloverSimHit::operator delete(void *hit)
{
  CloverSimHitAllocator->FreeSingle((CloverSimHit*) hit);
}

#endif /*CLOVER_SIM_HIT_HH*/