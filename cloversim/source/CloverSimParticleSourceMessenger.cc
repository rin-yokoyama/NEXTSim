#include "CloverSimParticleSourceMessenger.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UIcmdWith3VectorAndUnit.hh"
#include "G4UIcmdWith3Vector.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWith3Vector.hh"
#include "G4UIcmdWithAnInteger.hh"

void CloverSimParticleSourceMessenger::addAllCommands(){
	addDirectory("/cloverSim/source/", "Particle Source Control for Clover sim");
	
	addCommand(new G4UIcmdWithAString("/cloverSim/source/type", this)); // type of source
	addGuidance("Set a pre-defined isotropic particle source");
	addGuidance("file name");
	
	addCommand(new G4UIcmdWith3Vector("/cloverSim/source/pos", this)); // source position (mm)
	addGuidance("Set the source position x, y, z (in mm)");

	addCommand(new G4UIcmdWithADouble("/cloverSim/source/energy", this));
	addGuidance("Set the current energy level to mono-energetic and set the energy (in keV)");

}

void CloverSimParticleSourceMessenger::SetNewChildValue(G4UIcommand* command, G4String newValue){ 
	size_t index;
	if(!findCommand(command, newValue, index)) return;
	if(index == 0) {
		fAction->SetSourceType(newValue);
	}
	else if(index == 1) {
		fAction->SetSourcePos(G4UIcommand::ConvertTo3Vector(newValue));
	}
	else if(index == 2) {
		fAction->SetSourceEnergy(G4UIcommand::ConvertToDouble(newValue));
	}
}
