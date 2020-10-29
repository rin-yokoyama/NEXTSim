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
#include "G4PhysListFactory.hh"

#include "nDetActionInitialization.hh"
#include "nDetMasterOutputFile.hh"

#include "nDetConstruction.hh"
#include "nDetRunAction.hh"
#include "nDetEventAction.hh"
#include "nDetStackingAction.hh"
#include "nDetSteppingAction.hh"
#include "nDetTrackingAction.hh"
#include "optionHandler.hh"
#include "termColors.hh"
#include "version.hh"

#include "CloverSingleSD.hh"
#include "CloverSimRunAction.hh"
#include "CloverSimEventAction.hh"
//#include "PointGammaSourceGeneratorAction.hh"
#include "nDetParticleSource.hh"
#include "CloverSimActionInitialization.hh"
#include "CloverSimDetectorConstruction.hh"
#include "G4VUserDetectorConstruction.hh"

#include "G4OpticalPhysics.hh"
#include "G4EmStandardPhysics.hh"

#include "Randomize.hh"
#include "time.h"

#ifndef VERSION_STRING
#define VERSION_STRING "UNDEFINED"
#endif

#ifndef PROGRAM_NAME
#define PROGRAM_NAME "cloverSim"
#endif

int main(int argc, char** argv){
	optionHandler handler;
	handler.add(optionExt("input", required_argument, NULL, 'i', "<filename>", "Specify an input geant macro."));
	handler.add(optionExt("output", required_argument, NULL, 'o', "<filename>", "Specify the name of the output file."));
	handler.add(optionExt("gui", no_argument, NULL, 'g', "", "Run interactive GUI session."));
	handler.add(optionExt("tree", required_argument, NULL, 't', "<treename>", "Set the output TTree name (default=\"data\")."));
	handler.add(optionExt("yield", required_argument, NULL, 'Y', "<multiplier>", "Specify the light yield multiplier to use when producing photons (default=1)."));
	handler.add(optionExt("verbose", no_argument, NULL, 'v', "", "Toggle verbose mode."));
	handler.add(optionExt("delay", required_argument, NULL, 'D', "<seconds>", "Set the time delay between successive event counter updates (default=10s)."));
	handler.add(optionExt("version", no_argument, NULL, 'V', "", "Print the version number."));
	handler.add(optionExt("exp",required_argument,NULL,'e',"<setup>","Specify experimental hall setup to build (default=none)."));
	handler.add(optionExt("source", required_argument, NULL, 's', "<filename>", "Specify gamma source file."));
#ifdef USE_MULTITHREAD
	handler.add(optionExt("mt-thread-limit", required_argument, NULL, 'n', "<threads>", "Multi threading is not supported for cloverSim."));
	handler.add(optionExt("mt-max-threads", no_argument, NULL, 'T', "", "Print the maximum number of threads."));
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

	if(handler.getOption(7)->active){ // Print the version number
		std::cout << argv[0] << " version " << VERSION_STRING << std::endl;
		return 0;
	}
	std::string gamma_source_file;
	if(handler.getOption(8)->active){ // Set Gamma source file name
		gamma_source_file = handler.getOption(8)->argument;
	}

	std::string expName;
	if(handler.getOption(8)->active)
		expName = handler.getOption(8)->argument;



#ifdef USE_MULTITHREAD
	G4int numberOfThreads = 1; // Sequential mode by default.
	if(handler.getOption(10)->active){ 
		std::cout << "Multithreading is not supported for cloverSim" << std::endl;
		//G4int userInput = strtol(handler.getOption(11)->argument.c_str(), NULL, 10);
		//if(userInput > 0) // Set the number of threads to use.
		//	numberOfThreads = std::min(userInput, G4Threading::G4GetNumberOfCores());
		//else // Use all available threads.
		//	numberOfThreads = G4Threading::G4GetNumberOfCores();
	}
	
	if(handler.getOption(11)->active){ // Print maximum number of threads.
		std::cout << PROGRAM_NAME << ": Max number of threads on this machine is " << G4Threading::G4GetNumberOfCores() << ".\n";
		return 0;
	}
#endif

	if(batchMode && inputFilename.empty()){
		Display::ErrorPrint("Input macro filename not specified!", PROGRAM_NAME);
		return 1;
	}

	//make random number seeds different in different runs in Geant4 simulation
	//////////////////////////////////////
	
	//choose the Random engine
	CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine());
	
	//set random seed with system time
	G4long seed = time(NULL);
	CLHEP::HepRandom::setTheSeed(seed);
	
	std::cout << PROGRAM_NAME << ": Using random seed " << seed << std::endl;
	
	//////////////////////////////////////

	// Construct the default run manager
#ifdef USE_MULTITHREAD
	G4RunManager* runManager;
	if(batchMode && numberOfThreads > 1){
		runManager = new G4MTRunManager();
		((G4MTRunManager*)runManager)->SetNumberOfThreads(numberOfThreads);
		std::cout << PROGRAM_NAME << ": Multi-threading mode enabled.\n";
		std::cout << PROGRAM_NAME << ": Set number of threads to " << ((G4MTRunManager*)runManager)->GetNumberOfThreads() << std::endl;
	}
	else{
		runManager = new G4RunManager();
		std::cout << PROGRAM_NAME << ": Using sequential mode.\n";
	}
#else
	G4RunManager* runManager = new G4RunManager();
#endif

	// Set mandatory initialization classes
	// Initialize the detector
	nDetConstruction* detector = &nDetConstruction::getInstance(); // The detector builder is a singleton class.
	auto clover_detector_construction = new CloverSimDetectorConstruction();
	nDetWorld* exp_hall;
	if(!expName.empty()){
		exp_hall = detector->BuildExp(expName);
		//detector->Construct();
		//clover_detector_construction->ConstructInAVolume(exp_hall->getLogicalVolume(),exp_hall->getPhysicalVolume());
	}else std::cout << "<<<<<<<<<<<<<<<<<<<<   No experiment specified for \"-e\" argument. No setup will be constructed. >>>>>>>>>>>>>>>>>>>>\n";


	if(yieldMult > 0){ // Modify the photon yield of the detector
		std::cout << PROGRAM_NAME << ": Setting photon yield multiplier to " << yieldMult << std::endl;
		detector->SetLightYieldMultiplier(yieldMult);
	}

	runManager->SetUserInitialization(detector);

	//G4VModularPhysicsList* physics = new QGSP_BERT_HP();

	//G4OpticalPhysics *theOpticalPhysics=new G4OpticalPhysics();
	//theOpticalPhysics->SetScintillationByParticleType(true);
	//physics->ReplacePhysics(theOpticalPhysics);
	G4PhysListFactory *physListFactory = new G4PhysListFactory();
	auto physics = physListFactory->GetReferencePhysList("QGSP_BERT_HP");
	runManager->SetUserInitialization(physics);

#ifdef G4VIS_USE
	// add visulization manager
	G4VisManager *visManager = new G4VisExecutive;
	visManager->Initialize();
#endif

	// 
	nDetActionInitialization *nDetRunAction = new nDetActionInitialization(verboseMode);
	
	// Set the action initialization.
	//runManager->SetUserInitialization(runAction);

	//CloverSimRunAction* runAction = new CloverSimRunAction(outputFilename);
	//CloverSimEventAction* evtAction = new CloverSimEventAction(runAction->GetEventData(),runAction->GetTree());
	//PointGammaSourceGeneratorAction* genAction = new PointGammaSourceGeneratorAction(gamma_source_file);
	//auto genAction = new nDetPrimaryGeneratorAction();
	//runManager->SetUserAction(runAction);
	//runManager->SetUserAction(evtAction);
	//runManager->SetUserAction(genAction);
	CloverSimActionInitialization* action = new CloverSimActionInitialization(outputFilename);
	runManager->SetUserInitialization(action);

	// Ensure that the output file is initialized.
	nDetMasterOutputFile *output = &nDetMasterOutputFile::getInstance();

	// Initialize G4 kernel
	runManager->Initialize();
	
	// get the pointer to the UI manager and set verbosities
	G4UImanager *UImanager = G4UImanager::GetUIpointer();

	if(userTimeDelay > 0)
		output->setDisplayTimeInterval(userTimeDelay);

	if(!batchMode){	 // Define UI session for interactive mode
#ifdef G4UI_USE
		// Set root output to a single output file.
		output->setPersistentMode(true); // The master output file is a singleton class.

		G4UIExecutive *ui = new G4UIExecutive(argc, argv, "");
		
		G4String command = "/control/execute ";
		command += inputFilename;
		UImanager->ApplyCommand(command);
		UImanager->ApplyCommand("/vis/open OGL");
		UImanager->ApplyCommand("/vis/drawVolume");
		UImanager->ApplyCommand("/vis/scene/add/trajectories");
		UImanager->ApplyCommand("/vis/viewer/set/viewpointThetaPhi 90 0");
		UImanager->ApplyCommand("/vis/viewer/set/viewpointVector -1 1 1");
		UImanager->ApplyCommand("/vis/viewer/refresh");
		
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

	// Write the random seed to the file.
	std::stringstream stream;
	stream << seed;
	output->writeInfoToFile("seed", stream.str());

	// Write the program version number to the file.
	output->writeInfoToFile("version", VERSION_STRING);

	// Close the root file.
	output->closeRootFile();

	// Job termination
#ifdef G4VIS_USE
	delete visManager;
#endif
	// We MUST set detector initialization to NULL because the run manager does not
	// own the detector and will cause a seg-fault when its destructor is called.
	runManager->SetUserInitialization((G4VUserDetectorConstruction*)nullptr);
	delete runManager;
	
	return 0;
}
