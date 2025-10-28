#ifndef YOUR_TRACKING_INFO_HH
#define YOUR_TRACKING_INFO_HH

#include "G4VUserTrackInformation.hh"
#include "G4Types.hh"

class YourTrackInfo : public G4VUserTrackInformation {
public:
    YourTrackInfo(): fComptonCount(0) {}
    virtual ~YourTrackInfo() {}

    void AddComptonScattering() { fComptonCount++; }
    void SetComptonCount(G4int n) { fComptonCount = n; }
    G4int GetComptonCount() const { return fComptonCount; }
    
private:
    G4int fComptonCount;
};
#endif