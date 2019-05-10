//
// ********************************************************************
// * The beutron detector program is used to simulate an				*
// * optimize the performance of the scintillation detector in the	* 
// * framework of Geant4.10.00.p01 and ROOT v5.34.14.				 *
// *	by Dr. Xiaodong Zhang on Sept., 2015.							 *
// *																	*
// ********************************************************************
//
// log: nDet.cc,v1.0	Sept., 2015
// --------------------------------------------------------------
//
																		 
// c/c++ headers

#include "G4UImanager.hh"
#include "G4ios.hh"

#ifdef USE_MULTITHREAD
#include "G4MTRunManager.hh"	
#else
#include "G4RunManager.hh"
#endif

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif

// using the modular physics list
#include "G4VModularPhysicsList.hh"
#include "QGSP_BERT_HP.hh"

#include "nDetActionInitialization.hh"
#include "nDetMasterOutputFile.hh"

#include "nDetConstruction.hh"
#include "nDetRunAction.hh"
#include "nDetEventAction.hh"
#include "nDetStackingAction.hh"
#include "nDetSteppingAction.hh"
#include "nDetTrackingAction.hh"
#include "ParticleSource.hh"
#include "optionHandler.hh"

#include "G4OpticalPhysics.hh"

#include "Randomize.hh"
#include "time.h"

int main(int argc, char** argv){
	optionHandler handler;
	handler.add(optionExt("input", required_argument, NULL, 'i', "<filename>", "Specify an input geant macro."));
	handler.add(optionExt("output", required_argument, NULL, 'o', "<filename>", "Specify the name of the output file."));
	handler.add(optionExt("gui", no_argument, NULL, 'g', "", "Run interactive GUI session."));
	handler.add(optionExt("tree", required_argument, NULL, 't', "<treename>", "Set the output TTree name (default=\"data\")."));
	handler.add(optionExt("yield", required_argument, NULL, 'Y', "<multiplier>", "Specify the light yield multiplier to use when producing photons (default=1)."));
	handler.add(optionExt("verbose", no_argument, NULL, 'V', "", "Toggle verbose mode."));
	handler.add(optionExt("delay", required_argument, NULL, 'D', "<seconds>", "Set the time delay between successive event counter updates (default=10s)."));
#ifdef USE_MULTITHREAD
	handler.add(optionExt("mt-disable", no_argument, NULL, 0x0, "", "Force single-threaded mode."));
	handler.add(optionExt("mt-thread-limit", required_argument, NULL, 0x0, "", "Set the maximum number of threads to use."));
#endif

	// Handle user input.
	if(!handler.setup(argc, argv))
		return 1;

	std::string inputFilename;
	if(handler.getOption(0)->active) // Set input filename
		inputFilename = handler.getOption(0)->argument;

	std::string outputFilename;
	if(handler.getOption(1)->active) // Set output filename
		outputFilename = handler.getOption(1)->argument;

	bool batchMode = true;
	if(handler.getOption(2)->active) // Set interactive mode
		batchMode = false;

	std::string outputTreeName;
	if(handler.getOption(3)->active) // Set output TTree name
		outputTreeName = handler.getOption(3)->argument;

	double yieldMult = -1;
	if(handler.getOption(4)->active) // Set output TTree name
		yieldMult = strtod(handler.getOption(4)->argument.c_str(), NULL);

	bool verboseMode = false;
	if(handler.getOption(5)->active) // Toggle verbose flag
		verboseMode = true;

	int userTimeDelay = -1;
	if(handler.getOption(6)->active) // Set the output time delay.
		userTimeDelay = strtol(handler.getOption(6)->argument.c_str(), NULL, 0);	

#ifdef USE_MULTITHREAD
	bool forceSingleThreaded = false;
	if(handler.getOption(7)->active) // Force single-threaded mode.
		forceSingleThreaded = true;
		
	G4int numberOfThreads = G4Threading::G4GetNumberOfCores();
	if(handler.getOption(8)->active){ // Set the maximum number of threads to use.
		G4int userInput = strtol(handler.getOption(8)->argument.c_str(), NULL, 10);
		numberOfThreads = std::min(userInput, G4Threading::G4GetNumberOfCores());
	}
#endif

	if(batchMode && inputFilename.empty()){
		std::cout << " ERROR: Input macro filename not specified!\n";
		return 1;
	}

	//make random number seeds different in different runs in Geant4 simulation
	//////////////////////////////////////
	
	//choose the Random engine
	CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine());
	
	//set random seed with system time
	G4long seed = time(NULL);
	CLHEP::HepRandom::setTheSeed(seed);
	
	//////////////////////////////////////

	// Construct the default run manager
#ifdef USE_MULTITHREAD
	G4RunManager* runManager;
	if(!forceSingleThreaded){
		runManager = new G4MTRunManager();
		((G4MTRunManager*)runManager)->SetNumberOfThreads(numberOfThreads);
		std::cout << "nextSim: Multi-threading enabled.\n";
		std::cout << "nextSim: Set number of threads to " << ((G4MTRunManager*)runManager)->GetNumberOfThreads() << std::endl;
	}
	else{
		runManager = new G4RunManager();
		std::cout << "nextSim: Multi-threading disabled by user.\n";
	}
#else
	G4RunManager* runManager = new G4RunManager();
#endif

	// Set mandatory initialization classes
	// Initialize the detector
	nDetConstruction* detector = &nDetConstruction::getInstance(); // The detector builder is a singleton class.
	if(yieldMult > 0){ // Modify the photon yield of the detector
		std::cout << "nextSim: Setting photon yield multiplier to " << yieldMult << std::endl;
		detector->SetLightYieldMultiplier(yieldMult);
	}
	runManager->SetUserInitialization(detector);

	G4VModularPhysicsList* physics = new QGSP_BERT_HP();

	G4OpticalPhysics *theOpticalPhysics=new G4OpticalPhysics();
	theOpticalPhysics->SetScintillationByParticleType(true);
	physics->ReplacePhysics(theOpticalPhysics);
	runManager->SetUserInitialization(physics);

#ifdef G4VIS_USE
	// add visulization manager
	G4VisManager *visManager = new G4VisExecutive;
	visManager->Initialize();
#endif

	// 
	nDetActionInitialization *runAction = new nDetActionInitialization(detector);
	
	// Set the action initialization.
	runManager->SetUserInitialization(runAction);

	// Initialize G4 kernel
	runManager->Initialize();
	
	// get the pointer to the UI manager and set verbosities
	G4UImanager *UImanager = G4UImanager::GetUIpointer();

	if(!batchMode){	 // Define UI session for interactive mode
#ifdef G4UI_USE
		// Set root output to a single output file.
		nDetMasterOutputFile::getInstance().setPersistentMode(true); // The master output file is a singleton class.

		G4UIExecutive *ui = new G4UIExecutive(argc, argv, "");
		UImanager->ApplyCommand("/vis/open OGL");
		UImanager->ApplyCommand("/vis/drawVolume");
		UImanager->ApplyCommand("/vis/scene/add/trajectories");
		UImanager->ApplyCommand("/vis/viewer/set/viewpointThetaPhi 90 0");
		UImanager->ApplyCommand("/vis/viewer/set/viewpointVector -1 1 1");
		UImanager->ApplyCommand("/vis/viewer/refresh");
		G4String command = "/control/execute ";
		command += inputFilename;
		UImanager->ApplyCommand(command);
		
		// start interactive session
		ui->SessionStart();		
		delete ui;
#endif
	}
	else{ // Batch mode
		G4String command = "/control/execute ";
		command += inputFilename;
		UImanager->ApplyCommand(command);
	}

	// Close the root file.
	nDetMasterOutputFile::getInstance().closeRootFile(); // The master output file is a singleton class.

	// job termination
#ifdef G4VIS_USE
	delete visManager;
#endif
	delete runManager;
	
	return 0;
}//END of main() function
