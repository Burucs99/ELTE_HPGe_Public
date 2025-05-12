#include <G4MTRunManager.hh>
#include <iostream>


#include "G4RunManager.hh"
#include "G4RunManagerFactory.hh"
#include "G4PhysListFactory.hh"
#include "G4VModularPhysicsList.hh"
#include "G4UImanager.hh"
#include "G4UIExecutive.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "YourDetectorConstruction.hh"
#include "YourPhysicsList.hh"
#include "YourPrimaryGeneratorAction.hh"
#include "YourActionInitialization.hh"
#include "G4HadronicParameters.hh"

int main(int argc, char** argv){
   G4UIExecutive* ui ;

   G4HadronicParameters::Instance()->SetTimeThresholdForRadioactiveDecay(1.0e+60* CLHEP::year);

   #ifdef G4MULTITHREADED
      G4MTRunManager * runManager = new G4MTRunManager;
   #else
      G4RunManager *runManager = new G4RunManager;
   #endif
   YourDetectorConstruction* detector = new YourDetectorConstruction();

   runManager->SetUserInitialization(detector);
   runManager->SetUserInitialization(new YourPhysicsList());
   YourActionInitialization* action = new YourActionInitialization(detector);
   runManager->SetUserInitialization(action);
   if(argc == 1)
   {
      ui = new G4UIExecutive(argc,argv);
   }
   G4VisManager* visManager = new G4VisExecutive();
   visManager->SetVerboseLevel(0); 

   visManager->Initialize();

   G4UImanager* uiManager = G4UImanager::GetUIpointer();
   uiManager->SetVerboseLevel(0);
   if(ui)
   {
      //uiManager->ApplyCommand("/control/execute vis.mac");
      ui->SessionStart();
   }
   {  

      G4cout<<"Executing run mode"<<G4endl;
      G4String command = "/control/execute";
      G4String filename = argv[1];
      uiManager->ApplyCommand(command + filename);
   }


   //Kezdés...
   return 0;

}
