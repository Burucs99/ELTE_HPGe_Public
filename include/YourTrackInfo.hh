#ifndef YOUR_TRACKING_INFO_HH
#define YOUR_TRACKING_INFO_HH

#include "G4VUserTrackInformation.hh"
#include "G4Types.hh"

class YourTrackInfo : public G4VUserTrackInformation {
public:
    YourTrackInfo() : G4VUserTrackInformation(), Detected(false) {}  // inline definíció
    virtual ~YourTrackInfo() {}                                       // inline definíció

    void SetDetectedTrue() { Detected = true; }
    G4bool IsDetected() const { return Detected; }  // opcionális getter

private:
    G4bool Detected = false;
};

#endif