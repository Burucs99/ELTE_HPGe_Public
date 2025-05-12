
#ifndef YOURDETECTORCONSTRUCTION_HH
#define YOURDETECTORCONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include <G4ThreeVector.hh>
#include <G4Types.hh>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <cstdlib>
class G4Material;
class YourDetectorMessenger;
class G4Isotope;
class G4Element;
class YourDetectorConstruction : public G4VUserDetectorConstruction {
public:
    YourDetectorConstruction();
    ~YourDetectorConstruction() override;

    G4VPhysicalVolume* Construct() override;

    
    
    
    G4VPhysicalVolume* GetTargetPhysicalVolume() const {return fTargetPhysical;};

    void CreateIsotope(G4String name, G4int z, G4int n, G4double mol_mass);
    void CreateElement(const G4String& ,const G4String& ,const std::vector<std::pair<G4String, G4double>>&); // (isotope_name, fraction)
    void CreateMaterial(const G4String&,
        G4double ,
        const std::vector<std::pair<G4String, G4double>>& );

    
    void BoxSourceGeometryCreator(const G4String& boxName, G4ThreeVector& boxSize,
        G4String materialName,const G4String& logicName,
        G4ThreeVector& physPlacement,const G4String& physName);
    void CylinderSourceGeometryCreator(const G4String& CylinderName, 
            G4double& CylinderRadius, G4double& CylinderHeight,
            G4String materialName,const G4String& logicName,
            G4ThreeVector& physPlacement,const G4String& physName);
    void SetSourceTube(const G4String& name,const G4String& matName, G4double radius, 
                G4double height, 
                const G4ThreeVector& placement);
    void SetSourceBox(const G4String& name,const G4String& matName, const G4ThreeVector& size, 
                const G4ThreeVector& placement);
    void CreateSampleHolder();
private:
    
    YourDetectorMessenger* fDetMessenger;
    G4LogicalVolume* fworldLogical;
    G4LogicalVolume* ftargetLogical;
    G4VPhysicalVolume* fTargetPhysical;
    
    

    std::map<G4String, G4Isotope*> fIsotopes;    
    std::map<G4String, G4Element*> fElements;   
    std::map<G4String, G4Material*> fCustomMats; 
        
    G4bool fCreateBox = false;
    G4bool fCreateTub = false;
    
    G4ThreeVector fBoxSize;
    G4double fTubRadius = 0.0;
    G4double fTubHeight = 0.0;
    G4ThreeVector fPlacement;
    G4String fGeometryName;
    G4String fMaterialName;
    virtual void ConstructSDandField();
};
#endif
