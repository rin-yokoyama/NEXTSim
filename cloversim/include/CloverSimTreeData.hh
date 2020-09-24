//@file CloverSimTreeData.hh
//@brief Data container for ROOT output.
//@authors R. Yokoyama
//@date 9/27/2020

#ifndef CLOVER_SIM_TREE_DATA_HH
#define CLOVER_SIM_TREE_DATA_HH

#include <iostream>
#include <vector>
#include <TObject.h>

//! Data structure for each clover hit
struct clover_hit_struct {
    /** module ID */
    int modId = -1;
    /** energy deposit in the module */
    double modE = -999;
};
static const clover_hit_struct CLOVER_HIT_DEFAULT_STRUCT;

//! Data class that stores all clover hits in an event
class CloverSimTreeData: public TObject
{
public:
    /** Default constructor */
    CloverSimTreeData(){}
    /** Default destructor */
    virtual ~CloverSimTreeData(){}
    /** Clears all data */
    void ClearData(){clover_hits_.clear();}
    /** Vector of clover hits */
    std::vector<clover_hit_struct> clover_hits_;
    ClassDef(CloverSimTreeData,1)
};

#endif