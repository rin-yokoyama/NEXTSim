#Enable support for GDML.
if(GEANT4_GDML)
	add_definitions(-DUSE_GDML)
endif(GEANT4_GDML)

#Enable multi-threading support..
if(GEANT4_MT)
	add_definitions(-DUSE_MULTITHREAD)
endif(GEANT4_MT)

# Generate a ROOT dictionary for ExampleDataClass and ExampleSelector.
ROOT_GENERATE_DICTIONARY(CloverSimDataDict
	../include/CloverSimTreeData.hh
	LINKDEF ../include/CloverSimLinkDef.hh
)
# Install ROOT DICTIONARY
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/CloverSimDataDict_rdict.pcm DESTINATION lib)

# Build and install shared library
add_library(CloverSimLib SHARED
#add_library(CloverSimLib STATIC
    CloverSimParticleSourceMessenger.cc
    CloverSimActionInitialization.cc
    CloverSimDataDict.cxx
    CloverSimEventAction.cc
    CloverSimRunAction.cc
    PointGammaSourceGeneratorAction.cc
    GSource4G4.cpp
    GSStateG4.cpp
)
target_link_libraries(CloverSimLib ${Geant4_LIBRARIES} ${ROOT_LIBRARIES})
install(TARGETS CloverSimLib
    LIBRARY DESTINATION lib
)

# Build cloverSim executable.
add_executable(cloverSim cloverSim.cc)
target_link_libraries(cloverSim CloverSimLib NextSimOutput NextSimDetector NextSimGenerator NextSimPeripheral NextSimCore ${Geant4_LIBRARIES} ${ROOT_LIBRARIES} ${cadmesh_LIBRARIES})
install(TARGETS cloverSim DESTINATION bin)