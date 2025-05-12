#ifndef YOURHITCOLLECTION_HH
#define YOURHITCOLLECTION_HH

#include "G4VHitsCollection.hh"
#include <G4String.hh>
#include "YourHit.hh"
class YourHitCollection : public G4VHitsCollection {
public:
    YourHitCollection(G4String detName,G4String collectionName)
        :G4VHitsCollection(detName,collectionName) {};
    virtual ~YourHitCollection(){} ;

    void insert(YourHit* hit){fHits.push_back(hit);};
    size_t GetSize() const {return fHits.size();};
    YourHit* GetHit(size_t i) const {return fHits[i];};


private:
    std::vector<YourHit*> fHits;
};

#endif