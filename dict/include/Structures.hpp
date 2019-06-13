/*! \file Structures.hpp
 *  \brief Data structures for root output
 *  \author Cory R. Thornsbery
 *  \date June 12, 2019
 *
 *  Special data types for Root output. Each individual processor which is
 *  is used in the scan code should have its own Structure class. These classes
 *  should contain simple C++ data types or vectors of simple C++ data types.
 *  Vectors should be used for processors which are likely to have multiplicities
 *  greater than one.
 *  File automatically generated by
 *   RootClassBuilder (v. 1.0.7) on June 12, 2019
 */

#ifndef ROOTDATAStructure_H
#define ROOTDATAStructure_H

#include "TObject.h"

#include <vector>

/*! \class nDetTraceStructure
 *  \brief Simple structure used to store vectors of values corresponding to digitizer traces
 *  \author Cory R. Thornsbery
 *  \date June 12, 2019
 */

class nDetTraceStructure : public TObject {
  protected:
	std::string name; ///< The name of this trace object

  public:
	std::vector<unsigned short> pulseL; ///< Vector containing trace values for left PMT
	std::vector<unsigned short> pulseR; ///< Vector containing trace values for right PMT
	unsigned int mult; ///< Multiplicity of the event

	/** Default constructor
	  * @param name_ The name of this data structure
	  */
	nDetTraceStructure(const std::string &name_="");

	/** Destructor
	  */
	~nDetTraceStructure(){}

	/** Zero all variables
	  */
	void Zero();

	/** Push back with an array of trace values
	  * @param arrL_ Array containing trace values for the left PMT
	  * @param arrR_ Array containing trace values for the right PMT
      * @param size_ The number of values to copy from the input array
	  */
	void Append(unsigned short *arrL_, unsigned short *arrR_, const size_t &size_);

	/// @cond DUMMY
	ClassDef(nDetTraceStructure, 1); // nDetTraceStructure
	/// @endcond
};

/*! \class nDetEventStructure
 *  \brief Container for NEXTSim simulation event information
 *  \author Cory R. Thornsbery
 *  \date Wed Jun 12 16:47:09 2019
 *  
 *  Structure for storing information about NEXTSim run and primary event information
 */

class nDetEventStructure : public TObject {
  public:
	int eventID; ///< Geant event ID number
	short threadID; ///< Geant thread ID number for multithreading
	short runNb; ///< Geant run number
	short nScatters; ///< Number of primary particle scatters
	double nDepEnergy; ///< Energy deposition inside of the detector (in MeV)
	double nInitEnergy; ///< Initial energy of the neutron (in MeV)
	bool nAbsorbed; ///< Flag indicating whether or not the neutron was captured inside the detector
	bool goodEvent; ///< Flag indicating a good detection event i.e. where both PMTs detect at least one scintillation photon

	/** Default constructor
	  */
	nDetEventStructure();

	/** Destructor
	  */
	~nDetEventStructure(){}

	/** Set single entry data fields
	  * @param eventID_ Geant event ID number
	  * @param threadID_ Geant thread ID number for multithreading
	  * @param runNb_ Geant run number
	  * @param nScatters_ Number of primary particle scatters
	  * @param nDepEnergy_ Energy deposition inside of the detector (in MeV)
	  * @param nInitEnergy_ Initial energy of the neutron (in MeV)
	  * @param nAbsorbed_ Flag indicating whether or not the neutron was captured inside the detector
	  * @param goodEvent_ Flag indicating a good detection event i.e. where both PMTs detect at least one scintillation photon
	  */
	void SetValues(const int &eventID_, const short &threadID_, const short &runNb_, const short &nScatters_, const double &nDepEnergy_, const double &nInitEnergy_, const bool &nAbsorbed_, const bool &goodEvent_);

	/** Push back with data
	  */
	void Append();

	/** Zero all variables
	  */
	void Zero();

	/// @cond DUMMY
	ClassDef(nDetEventStructure, 1); // nDetEvent
	/// @endcond
};

/*! \class nDetOutputStructure
 *  \brief Container for NEXTSim simulation variable output
 *  \author Cory R. Thornsbery
 *  \date Wed Jun 12 16:47:09 2019
 *  
 *  Structure for storing information about NEXTSim primary particles and optical photons produced by scattering
 */

class nDetOutputStructure : public TObject {
  public:
	unsigned int nPhotonsTot; ///< Total number of scintillation photons produced
	unsigned int nPhotonsDetTot; ///< Total number of optical photons detected by both PMTs
	double lightBalance; ///< Ratio of the difference of left and right TQDC to the sum of left and right TQDC
	double photonDetEff; ///< Ratio of optical photons detected by a PMT to the total number of photons generated
	float barTOF; ///< Average of the left and right dynode light pulse phases computed using PolyCFD (in ns)
	float barQDC; ///< Average of the left and right dynode light pulse integrals
	float barMaxADC; ///< Average of the left and right dynode light pulse maxima (in ADC channels)
	double photonComX; ///< Average of the left and right photon center-of-mass X position (in mm)
	double photonComY; ///< Average of the left and right photon center-of-mass Y position (in mm)
	double reconComX; ///< Left and right PMT photon center-of-mass along the X-axis computed using Anger Logic reconstruction
	double reconComY; ///< Left and right PMT photon center-of-mass along the Y-axis computed using Anger Logic reconstruction
	short photonComCol; ///< Segmented PMT anode column corresponding to the photon center-of-mass for the left and right PMT
	short photonComRow; ///< Segmented PMT anode row corresponding to the photon center-of-mass for the left and right PMT

	/** Default constructor
	  */
	nDetOutputStructure();

	/** Destructor
	  */
	~nDetOutputStructure(){}

	/** Set single entry data fields
	  * @param nPhotonsTot_ Total number of scintillation photons produced
	  * @param nPhotonsDetTot_ Total number of optical photons detected by both PMTs
	  * @param lightBalance_ Ratio of the difference of left and right TQDC to the sum of left and right TQDC
	  * @param photonDetEff_ Ratio of optical photons detected by a PMT to the total number of photons generated
	  * @param barTOF_ Average of the left and right dynode light pulse phases computed using PolyCFD (in ns)
	  * @param barQDC_ Average of the left and right dynode light pulse integrals
	  * @param barMaxADC_ Average of the left and right dynode light pulse maxima (in ADC channels)
	  * @param photonComX_ Average of the left and right photon center-of-mass X position (in mm)
	  * @param photonComY_ Average of the left and right photon center-of-mass Y position (in mm)
	  * @param reconComX_ Left and right PMT photon center-of-mass along the X-axis computed using Anger Logic reconstruction
	  * @param reconComY_ Left and right PMT photon center-of-mass along the Y-axis computed using Anger Logic reconstruction
	  * @param photonComCol_ Segmented PMT anode column corresponding to the photon center-of-mass for the left and right PMT
	  * @param photonComRow_ Segmented PMT anode row corresponding to the photon center-of-mass for the left and right PMT
	  */
	void SetValues(const unsigned int &nPhotonsTot_, const unsigned int &nPhotonsDetTot_, const double &lightBalance_, const double &photonDetEff_, const float &barTOF_, const float &barQDC_, const float &barMaxADC_, const double &photonComX_, const double &photonComY_, const double &reconComX_, const double &reconComY_, const short &photonComCol_, const short &photonComRow_);

	/** Push back with data
	  */
	void Append();

	/** Zero all variables
	  */
	void Zero();

	/// @cond DUMMY
	ClassDef(nDetOutputStructure, 1); // nDetOutput
	/// @endcond
};

/*! \class nDetMultiOutputStructure
 *  \brief Container for NEXTSim simulation variable output
 *  \author Cory R. Thornsbery
 *  \date Wed Jun 12 16:47:09 2019
 *  
 *  Structure for storing information about NEXTSim primary particles and optical photons produced by scattering
 */

class nDetMultiOutputStructure : public TObject {
  public:
	std::vector<unsigned int> nPhotonsTot; ///< Total number of scintillation photons produced
	std::vector<unsigned int> nPhotonsDetTot; ///< Total number of optical photons detected by both PMTs
	std::vector<double> lightBalance; ///< Ratio of the difference of left and right TQDC to the sum of left and right TQDC
	std::vector<double> photonDetEff; ///< Ratio of optical photons detected by a PMT to the total number of photons generated
	std::vector<float> barTOF; ///< Average of the left and right dynode light pulse phases computed using PolyCFD (in ns)
	std::vector<float> barQDC; ///< Average of the left and right dynode light pulse integrals
	std::vector<float> barMaxADC; ///< Average of the left and right dynode light pulse maxima (in ADC channels)
	std::vector<double> photonComX; ///< Average of the left and right photon center-of-mass X position (in mm)
	std::vector<double> photonComY; ///< Average of the left and right photon center-of-mass Y position (in mm)
	std::vector<double> reconComX; ///< Left and right PMT photon center-of-mass along the X-axis computed using Anger Logic reconstruction
	std::vector<double> reconComY; ///< Left and right PMT photon center-of-mass along the Y-axis computed using Anger Logic reconstruction
	std::vector<short> photonComCol; ///< Segmented PMT anode column corresponding to the photon center-of-mass for the left and right PMT
	std::vector<short> photonComRow; ///< Segmented PMT anode row corresponding to the photon center-of-mass for the left and right PMT
	std::vector<short> detID; ///< ID of the detector which fired
	unsigned short multiplicity; ///< Multiplicity of the event

	/** Default constructor
	  */
	nDetMultiOutputStructure();

	/** Destructor
	  */
	~nDetMultiOutputStructure(){}

	/** Set single entry data fields
	  */
	void SetValues();

	/** Push back with data
	  * @param nPhotonsTot_ Total number of scintillation photons produced
	  * @param nPhotonsDetTot_ Total number of optical photons detected by both PMTs
	  * @param lightBalance_ Ratio of the difference of left and right TQDC to the sum of left and right TQDC
	  * @param photonDetEff_ Ratio of optical photons detected by a PMT to the total number of photons generated
	  * @param barTOF_ Average of the left and right dynode light pulse phases computed using PolyCFD (in ns)
	  * @param barQDC_ Average of the left and right dynode light pulse integrals
	  * @param barMaxADC_ Average of the left and right dynode light pulse maxima (in ADC channels)
	  * @param photonComX_ Average of the left and right photon center-of-mass X position (in mm)
	  * @param photonComY_ Average of the left and right photon center-of-mass Y position (in mm)
	  * @param reconComX_ Left and right PMT photon center-of-mass along the X-axis computed using Anger Logic reconstruction
	  * @param reconComY_ Left and right PMT photon center-of-mass along the Y-axis computed using Anger Logic reconstruction
	  * @param photonComCol_ Segmented PMT anode column corresponding to the photon center-of-mass for the left and right PMT
	  * @param photonComRow_ Segmented PMT anode row corresponding to the photon center-of-mass for the left and right PMT
	  * @param detID_ ID of the detector which fired
	  */
	void Append(const unsigned int &nPhotonsTot_, const unsigned int &nPhotonsDetTot_, const double &lightBalance_, const double &photonDetEff_, const float &barTOF_, const float &barQDC_, const float &barMaxADC_, const double &photonComX_, const double &photonComY_, const double &reconComX_, const double &reconComY_, const short &photonComCol_, const short &photonComRow_, const short &detID_);

	/** Push back with data from a nDetOutputStructure object
	  * @param output nDetOutputStructure object containing simulation variables for a single detector
	  * @param detID_ ID of the detector which fired
	  */
	void Append(const nDetOutputStructure &output, const short &detID_);

	/** Zero all variables
	  */
	void Zero();

	/// @cond DUMMY
	ClassDef(nDetMultiOutputStructure, 1); // nDetMultiOutput
	/// @endcond
};

/*! \class nDetDebugStructure
 *  \brief Container for NEXTSim simulation variable output
 *  \author Cory R. Thornsbery
 *  \date Wed Jun 12 16:47:09 2019
 *  
 *  Structure for storing information about NEXTSim primary particles and optical photons produced by scattering
 */

class nDetDebugStructure : public TObject {
  public:
	double nEnterPosX; ///< X-axis position where the primary particle enters the detector
	double nEnterPosY; ///< Y-axis position where the primary particle enters the detector
	double nEnterPosZ; ///< Z-axis position where the primary particle enters the detector
	double nExitPosX; ///< X-axis position where the primary particle exits the detector
	double nExitPosY; ///< Y-axis position where the primary particle exits the detector
	double nExitPosZ; ///< Z-axis position where the primary particle exits the detector
	double nComX; ///< X-axis center-of-mass positions for all neutron scatters weighted by the energy imparted to the detector (in mm)
	double nComY; ///< Y-axis center-of-mass positions for all neutron scatters weighted by the energy imparted to the detector (in mm)
	double nComZ; ///< Z-axis center-of-mass positions for all neutron scatters weighted by the energy imparted to the detector (in mm)
	double neutronWeight; ///< Sum of all energy imparted to the detector by all neutron scatters (in MeV)
	double nFirstScatterTime; ///< Global time of the first primary particle scatter event (in ns)
	double nFirstScatterLen; ///< Flight path to the first primary particle scatter event (n mm)
	double nEnterTime; ///< Global time when the primary particle enters the detector (in ns)
	double timeInMaterial; ///< Total time the primary particle spends in the material (in ns)
	std::vector<double> nScatterX; ///< Vector of X-axis position of all primary particle scatter positions (in mm)
	std::vector<double> nScatterY; ///< Vector of Y-axis position of all primary particle scatter positions (in mm)
	std::vector<double> nScatterZ; ///< Vector of Z-axis position of all primary particle scatter positions (in mm)
	std::vector<double> nScatterAngle; ///< Angle between successive scatters of the primary particle (in degrees)
	std::vector<double> nPathLength; ///< Path length of primary particle between successive scatter events (in mm)
	std::vector<double> nScatterTime; ///< Global time of each primary particle scatter event (in ns)
	std::vector<double> impartedE; ///< Energy imparted by the primary particle for each scatter event (in MeV)
	std::vector<short> segmentCol; ///< Scintillator segment column for each primary particle scatter event (for modular detectors)
	std::vector<short> segmentRow; ///< Scintillator segment row for each primary particle scatter event (for modular detectors)
	std::vector<short> photonsProd; ///< Number of scintillation photons produced for each primary particle scatter event
	std::vector<short> recoilMass; ///< Mass of the recoil particle for each primary particle scatter event
	std::vector<bool> nScatterScint; ///< Flag indicating whether or not the scatter event occured in a scintillator material
	unsigned short mult; ///< Multiplicity of the event (for multiple scatters)
	float pulsePhase[2]; ///< Phases of the left and right dynode light pulses computed using PolyCFD (in ns)
	float anodePhase[2][4]; ///< Phases of the four anger logic anode readout pulses for the left and right PMT computed using PolyCFD (in ns)
	unsigned int nPhotons[2]; ///< Number of optical photons produced by each PMT
	double photonMinTime[2]; ///< Minimum optical photon arrival time at each PMT (in ns)
	double photonAvgTime[2]; ///< Average optical photon arrival time at each PMT (in ns)
	double pulseArrival[2]; ///< Average optical photon arrival time at each PMT weighted by the PMT anode gain and quantum efficiency (in ns)
	float pulseMaxTime[2]; ///< Time of arrival of the maximum of the left and right light pulses (in ns)
	float pulseMax[2]; ///< Maximum of the left and right light pulses (in ADC channels)
	float pulseQDC[2]; ///< Integral of the left and right light pulses
	float anodeQDC[2][4]; ///< Anger logic currents for the four readouts of the left and right PSPmts
	double photonDetCenterOfMassX[2]; ///< Left and right PMT photon center-of-mass along the X-axis weighted by the anode gain and quantum efficiency (in mm)
	double photonDetCenterOfMassY[2]; ///< Left and right PMT photon center-of-mass along the Y-axis weighted by the anode gain and quantum efficiency (in mm)
	double reconstructedCenterX[2]; ///< Left and right PMT photon center-of-mass along the X-axis computed using Anger Logic reconstruction
	double reconstructedCenterY[2]; ///< Left and right PMT photon center-of-mass along the Y-axis computed using Anger Logic reconstruction
	short centerOfMassColumn[2]; ///< Segmented PMT anode column corresponding to the photon center-of-mass for the left and right PMT
	short centerOfMassRow[2]; ///< Segmented PMT anode row corresponding to the photon center-of-mass for the left and right PMT

	/** Default constructor
	  */
	nDetDebugStructure();

	/** Destructor
	  */
	~nDetDebugStructure(){}

	/** Set single entry data fields
	  * @param nEnterPosX_ X-axis position where the primary particle enters the detector
	  * @param nEnterPosY_ Y-axis position where the primary particle enters the detector
	  * @param nEnterPosZ_ Z-axis position where the primary particle enters the detector
	  * @param nExitPosX_ X-axis position where the primary particle exits the detector
	  * @param nExitPosY_ Y-axis position where the primary particle exits the detector
	  * @param nExitPosZ_ Z-axis position where the primary particle exits the detector
	  * @param nComX_ X-axis center-of-mass positions for all neutron scatters weighted by the energy imparted to the detector (in mm)
	  * @param nComY_ Y-axis center-of-mass positions for all neutron scatters weighted by the energy imparted to the detector (in mm)
	  * @param nComZ_ Z-axis center-of-mass positions for all neutron scatters weighted by the energy imparted to the detector (in mm)
	  * @param neutronWeight_ Sum of all energy imparted to the detector by all neutron scatters (in MeV)
	  * @param nFirstScatterTime_ Global time of the first primary particle scatter event (in ns)
	  * @param nFirstScatterLen_ Flight path to the first primary particle scatter event (n mm)
	  * @param nEnterTime_ Global time when the primary particle enters the detector (in ns)
	  * @param timeInMaterial_ Total time the primary particle spends in the material (in ns)
	  */
	void SetValues(const double &nEnterPosX_, const double &nEnterPosY_, const double &nEnterPosZ_, const double &nExitPosX_, const double &nExitPosY_, const double &nExitPosZ_, const double &nComX_, const double &nComY_, const double &nComZ_, const double &neutronWeight_, const double &nFirstScatterTime_, const double &nFirstScatterLen_, const double &nEnterTime_, const double &timeInMaterial_);

	/** Push back with data
	  * @param nScatterX_ Vector of X-axis position of all primary particle scatter positions (in mm)
	  * @param nScatterY_ Vector of Y-axis position of all primary particle scatter positions (in mm)
	  * @param nScatterZ_ Vector of Z-axis position of all primary particle scatter positions (in mm)
	  * @param nScatterAngle_ Angle between successive scatters of the primary particle (in degrees)
	  * @param nPathLength_ Path length of primary particle between successive scatter events (in mm)
	  * @param nScatterTime_ Global time of each primary particle scatter event (in ns)
	  * @param impartedE_ Energy imparted by the primary particle for each scatter event (in MeV)
	  * @param segmentCol_ Scintillator segment column for each primary particle scatter event (for modular detectors)
	  * @param segmentRow_ Scintillator segment row for each primary particle scatter event (for modular detectors)
	  * @param photonsProd_ Number of scintillation photons produced for each primary particle scatter event
	  * @param recoilMass_ Mass of the recoil particle for each primary particle scatter event
	  * @param nScatterScint_ Flag indicating whether or not the scatter event occured in a scintillator material
	  */
	void Append(const double &nScatterX_, const double &nScatterY_, const double &nScatterZ_, const double &nScatterAngle_, const double &nPathLength_, const double &nScatterTime_, const double &impartedE_, const short &segmentCol_, const short &segmentRow_, const short &photonsProd_, const short &recoilMass_, const bool &nScatterScint_);

	/** Zero all variables
	  */
	void Zero();

	/// @cond DUMMY
	ClassDef(nDetDebugStructure, 1); // nDetDebug
	/// @endcond
};

#endif
