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

	addCommand(new G4UIcmdWithAString("/cloverSim/source/generator", this)); // type of generator action
	addGuidance("Set a type of generator action");
	addGuidance("point/gamma");
	
	addCommand(new G4UIcmdWithAString("/cloverSim/source/treeName", this)); // SetInputTreeName
	addGuidance("Set name of the input tree");
	addGuidance("name");
	
	addCommand(new G4UIcmdWithAString("/cloverSim/source/branchName", this)); // SetBranchName
	addGuidance("Set name of the branch that contains position data");
	addGuidance("name");
	
	addCommand(new G4UIcmdWithAString("/cloverSim/source/addFile", this)); // add a ROOT file to chain
	addGuidance("Add a ROOT file to the input chain");
	addGuidance("file name");
	
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
	else if(index == 3) {
		fAction->SetGeneratorName(newValue);
	}
	else if(index == 4) {
		fAction->SetTreeName(newValue);
	}
	else if(index == 5) {
		fAction->SetBranchName(newValue);
	}
	else if(index == 6) {
		fAction->AddFile(newValue);
	}
}
