#ifndef CLOVER_SIM_PARTICLE_SOURCE_MESSENGER_HH
#define CLOVER_SIM_PARTICLE_SOURCE_MESSENGER_HH

#include "PointGammaSourceGeneratorAction.hh"
#include "messengerHandler.hh"

/*! \class CloverSimParticleSourceMessenger
 *  \brief Class used to handle user commands for ParticleSource class
 *  \author Cory R. Thornsberry (cthornsb@vols.utk.edu)
 *  \date May 31, 2019
*/
class PointGammaSourceGeneratorAction;

class CloverSimParticleSourceMessenger: public messengerHandler {
  public:
	/** Default constructor
	  */
	CloverSimParticleSourceMessenger() : messengerHandler("particleSourceMessenger"), fAction(NULL) { addAllCommands(); }

	/** Constructor taking a pointer to a ParticleSource object
	  * @param detector Pointer to the ParticleSource object for which this messenger is defined
	  */
	CloverSimParticleSourceMessenger(PointGammaSourceGeneratorAction* Gun) : messengerHandler("particleSourceMessenger"), fAction(Gun) { addAllCommands(); }

	/** Handle commands called by the user. Called from messengerHandler::SetNewValue()
	  * @param command Pointer to the G4UIcommand called by the user
	  * @param newValue String containing the argument passed by the user
	  */
	virtual void SetNewChildValue(G4UIcommand* command, G4String newValue);

  private:
	PointGammaSourceGeneratorAction* fAction; ///< Pointer to the particle source object for which this messenger is defined

	/** Add all commands to the messenger
	  */
	void addAllCommands();
};

#endif /* CLOVER_SIM_PARTICLE_SOURCE_MESSENGER_HH */
