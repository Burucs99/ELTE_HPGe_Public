#ifndef YOURHIT_HH
#define YOURHIT_HH

#include "G4VHit.hh"
#include <G4ThreeVector.hh>
#include <G4Types.hh>

class YourHit : public G4VHit {
public:
    YourHit():fEnergy(0.){};
    virtual ~YourHit(){};

    void SetEnergy(G4double energy) {fEnergy = energy;};
    G4double GetEnergy() const{return fEnergy;};

/*     void SetPosition(G4ThreeVector pos) {fPosition = pos;};
    G4ThreeVector GetPosition(){return fPosition;};
 */

    void SetEventID(G4int id) { fEventID = id; }
    G4int GetEventID() const { return fEventID; }

    void SetRunID(G4int id) { fRunID = id; }
    G4int GetRunID() const { return fRunID; }

    void SetComptonID(G4int id) { fCoulombIDX = id; }
    G4int GetCoulombID() const { return fCoulombIDX; }


    void SetTrackID(G4int id) { fTrackID = id; }
    G4int GetTrackID() const { return fTrackID ;}
private:
    G4double fEnergy;
   // G4ThreeVector fPosition;
    G4int fEventID;
    G4int fRunID;
    G4int fCoulombIDX;
    G4int fTrackID;
};

#endif