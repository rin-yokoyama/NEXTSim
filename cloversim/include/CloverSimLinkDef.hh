//@file CloverSimLinkDef.hh
//@brief LinkDef for ROOT dictionary generation.
//@authors R. Yokoyama
//@date 9/27/2020

#ifndef CLOVER_SIM_LINK_DEF_HH
#define CLOVER_SIM_LINK_DEF_HH

#ifdef __CINT__

#pragma link C++ struct clover_hit_struct+;
#pragma link C++ class std::vector<clover_hit_struct>+;
#pragma link C++ class CloverSimTreeData+;

#endif /* end __CINT__ */

#endif /* end CLOVER_SIM_LINK_DEF_HH */