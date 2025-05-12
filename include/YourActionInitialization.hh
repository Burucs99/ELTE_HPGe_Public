#ifndef YOURACTIONINITIALIZATION_HH
#define YOURACTIONINITIALIZATION_HH

#include "G4VUserActionInitialization.hh"

class YourDetectorConstruction;

class YourActionInitialization : public G4VUserActionInitialization {
public:
    YourActionInitialization(YourDetectorConstruction* det);
    ~YourActionInitialization() override;

    void BuildForMaster() const override;
    void Build() const override;



private:
    YourDetectorConstruction* fDetector;


};

#endif
