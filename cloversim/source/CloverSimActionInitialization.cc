#include "CloverSimActionInitialization.hh"
#include "VANDLE18ImplantedGammaSourceGeneratorAction.hh"

CloverSimActionInitialization::CloverSimActionInitialization(std::string ofname) :
    output_filename_(ofname),
    generator_action_name_("point")
{
}

void CloverSimActionInitialization::Build() const {
    auto pg_action = new VANDLE18ImplantedGammaSourceGeneratorAction();
    auto run_action = new CloverSimRunAction(output_filename_,pg_action);
    auto evt_action = new CloverSimEventAction(run_action->GetEventData(), run_action->GetTree());
    SetUserAction(run_action);
    SetUserAction(evt_action);
    SetUserAction(pg_action);
}

void CloverSimActionInitialization::BuildForMaster() const {
    SetUserAction(new CloverSimRunAction(output_filename_,nullptr));
}
