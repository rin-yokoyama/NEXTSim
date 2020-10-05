#include "CloverSimActionInitialization.hh"

CloverSimActionInitialization::CloverSimActionInitialization(std::string ofname) :
    output_filename_(ofname)
{
}

void CloverSimActionInitialization::Build() const {
    auto pg_action = new PointGammaSourceGeneratorAction();
    auto run_action = new CloverSimRunAction(output_filename_,pg_action);
    auto evt_action = new CloverSimEventAction(run_action->GetEventData(), run_action->GetTree());
    SetUserAction(run_action);
    SetUserAction(evt_action);
    SetUserAction(pg_action);
}

void CloverSimActionInitialization::BuildForMaster() const {
    SetUserAction(new CloverSimRunAction(output_filename_,nullptr));
}
