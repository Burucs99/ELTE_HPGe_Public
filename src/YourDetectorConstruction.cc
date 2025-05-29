#include "YourDetectorConstruction.hh"
#include "G4SystemOfUnits.hh"
#include "G4RunManager.hh"
#include "G4PhysicalConstants.hh"
#include "G4NistManager.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4PVPlacement.hh"
#include <CLHEP/Units/SystemOfUnits.h>
#include <G4Element.hh>
#include <G4EventManager.hh>
#include <G4Isotope.hh>
#include <G4Material.hh>
#include <G4String.hh>
#include <G4ThreeVector.hh>
#include <G4Tubs.hh>
#include <G4Types.hh>
#include <G4VPhysicalVolume.hh>
#include <cstddef>
#include "G4VisAttributes.hh"
#include "G4Color.hh"
#include "G4SDManager.hh"
#include "YourSensitiveDetector.hh"
#include "YourDetectorMessenger.hh"
#include "G4RunManager.hh"
#include "G4SubtractionSolid.hh"
#include "G4UserLimits.hh"
#include "G4Cons.hh"
YourDetectorConstruction::YourDetectorConstruction()
:   G4VUserDetectorConstruction()
     {
    fDetMessenger    = new YourDetectorMessenger(this);
}

YourDetectorConstruction::~YourDetectorConstruction() {
    delete fDetMessenger;
    
}


G4VPhysicalVolume* YourDetectorConstruction::Construct() {
    

    G4NistManager* nistMGR =                  G4NistManager::Instance();
    
    
    // World
    G4Material* worldMat   = nistMGR->FindOrBuildMaterial("G4_AIR");
    
    G4double worldSize   = 1*m;

    G4Box* worldSolid             = new G4Box("solid-World",worldSize/2,worldSize/2,worldSize/2);
    G4LogicalVolume* worldLogical = new G4LogicalVolume(worldSolid,worldMat,"logic-World");
    G4VPhysicalVolume* worldPhysical = new G4PVPlacement(nullptr,G4ThreeVector(0,0,0),worldLogical,"World",nullptr,false,0);

    fworldLogical = worldLogical;
    // Testing 
/*     CreateKaliumContainer();
 */    
    CreateSampleHolder();
    if (fCreateBox || fCreateTub) {
        if (fCustomMats.find(fMaterialName) == fCustomMats.end()) {
            G4cerr << "ERROR: Material '" << fMaterialName 
                   << "' not found in fCustomMats!" << G4endl;
            return nullptr;  
        }


        if (fCreateBox) {
            BoxSourceGeometryCreator(
                fGeometryName, 
                fBoxSize, 
                fMaterialName,  
                fGeometryName + "_Logic",
                fPlacement,
                fGeometryName + "_Phys"
            );
        }
        else if (fCreateTub) {
            CylinderSourceGeometryCreator(
                fGeometryName,
                fTubRadius,
                fTubHeight,
                fMaterialName,
                fGeometryName + "_Logic",
                fPlacement,
                fGeometryName + "_Phys"
            );
        }
    }

    
    auto defaultMaterial  = nistMGR->FindOrBuildMaterial("G4_AIR");
    auto absorberMaterial = nistMGR->FindOrBuildMaterial("G4_Ge");
    auto vacuum           = nistMGR->FindOrBuildMaterial("G4_Galactic");
    auto aluminium        = nistMGR->FindOrBuildMaterial("G4_Al");
    auto teflon           = nistMGR->FindOrBuildMaterial("G4_TEFLON");


    constexpr G4double crystalDiameter            = 48. *mm;
    constexpr G4double crystalLength              = 54.5 *mm;
    constexpr G4double crystalHoleDiameter        = 7.5 *mm;
    constexpr G4double crystalHoleDepth           = 37.5*mm;
    
    constexpr G4double endCapThickness            = 1.5 *mm;
    constexpr G4double endCapOuterDiameter        = 7.6 *cm;
    constexpr G4double endCapInnerDiameter        = endCapOuterDiameter - endCapThickness;
    constexpr G4double endCapLength               = 7.  *cm;//TODO...

    constexpr G4double crystalHolderThickness     = 0.76 *mm;
    constexpr G4double crystalHolderInnerDiameter = crystalDiameter; //TODO actually there is a 0.5 mm boron layer on the outside of the crystal
    constexpr G4double crystalHolderOuterDiameter = crystalHolderInnerDiameter + crystalHolderThickness;
    constexpr G4double crystalHolderExtraLength   = 8. * mm;//TODO random guess
    constexpr G4double crystalHolderLength        = crystalLength + crystalHolderExtraLength;
    constexpr G4double crystalHolderEndThickness  = 3.2 *mm;

    constexpr G4double protrusionLength           = 8. * mm;//TODO random guess
    constexpr G4double protrusionThickness        = crystalHolderEndThickness;
    constexpr G4double protrusionOuterDiameter    = 30 *mm;//TODO random guess
    constexpr G4double protrusionInnerDiameter    = protrusionOuterDiameter - protrusionThickness;

    constexpr G4double teflonDiameter             = protrusionInnerDiameter;
    constexpr G4double teflonLength               = protrusionLength - protrusionThickness;//...

    constexpr G4double sampleDiameter             = 6.  *cm;
    constexpr G4double sampleHeight               = 0.5 *cm;
    constexpr G4double sampleHolderThickness      = 1.  *mm;
    constexpr G4double sampleHolderInnerDiameter  = sampleDiameter;
    constexpr G4double sampleHolderOuterDiameter  = sampleDiameter + 2 * sampleHolderThickness;

 

    constexpr G4double windowDistance          = 5. *mm;

    constexpr G4double calorimeterShift        =  endCapLength / 2;
    constexpr G4double START                   = -endCapLength / 2;

    constexpr G4double endCapShift             = START + endCapLength / 2;
    constexpr G4double endCapDisk1Shift        = START + endCapThickness / 2;
    constexpr G4double endCapDisk2Shift        = START + endCapLength - endCapThickness / 2;

    constexpr G4double crystalShift            = START + windowDistance + crystalLength / 2;
    constexpr G4double crystalHoleRelShift     = crystalLength / 2 - crystalHoleDepth / 2;

    constexpr G4double crystalHolderShift      = START + windowDistance + crystalHolderLength / 2;
    //constexpr G4double crystalHolderDisk1Shift = START + windowDistance + crystalHolderThickness / 2;//What is on the front?
    constexpr G4double crystalHolderDisk2Shift = START + windowDistance + crystalHolderLength - crystalHolderThickness / 2;

    constexpr G4double protrusionShift         = START + windowDistance + crystalHolderLength + protrusionLength / 2;
    constexpr G4double protrusionDiskShift     = START + windowDistance + crystalHolderLength + protrusionLength - protrusionThickness / 2;
    constexpr G4double teflonShift             = START + windowDistance + crystalHolderLength + teflonLength / 2;

    G4bool fCheckOverlaps = true;

    auto calorimeterSolid          = new G4Tubs ("Calorimeter", 0, endCapOuterDiameter/2, endCapLength/2, 0, 360*deg);
    auto calorimeterLogicalVolume  = new G4LogicalVolume (calorimeterSolid, vacuum, "Calorimeter");
    auto calorimeterPhysicalVolume = new G4PVPlacement (0, G4ThreeVector(0, 0, calorimeterShift),
                                                        calorimeterLogicalVolume,
                                                        "Calorimeter",
                                                        worldLogical,
                                                        false, 0, fCheckOverlaps);
 
    //------------------------
    //--------Endcap----------
    auto endCapSolid          = new G4Tubs ("EndCap", endCapInnerDiameter/2, endCapOuterDiameter/2, endCapLength/2, 0, 360*deg);
    auto endCapLogicalVolume  = new G4LogicalVolume (endCapSolid, aluminium, "EndCap");
    auto endCapPhysicalVolume = new G4PVPlacement (0, G4ThreeVector(0, 0, endCapShift),
                                                    endCapLogicalVolume,
                                                    "EndCap",
                                                    calorimeterLogicalVolume,
                                                    false, 0, fCheckOverlaps);
    
    auto endCapDisk1Solid          = new G4Tubs ("EndCapDisk1", 0, endCapOuterDiameter/2 - endCapThickness/2, endCapThickness/2, 0, 360*deg);
    auto endCapDisk1LogicalVolume  = new G4LogicalVolume (endCapDisk1Solid, aluminium, "EndCapDisk1");
    auto endCapDisk1PhysicalVolume = new G4PVPlacement (0, G4ThreeVector(0, 0, endCapDisk1Shift),
                                                        endCapDisk1LogicalVolume,
                                                        "EndCapDisk1",
                                                        calorimeterLogicalVolume,
                                                        false, 0, fCheckOverlaps);
    
    auto endCapDisk2Solid          = new G4Tubs ("EndCapDisk2", 0, endCapOuterDiameter/2 - endCapThickness/2, endCapThickness/2, 0, 360*deg);
    auto endCapDisk2LogicalVolume  = new G4LogicalVolume (endCapDisk2Solid, aluminium, "EndCapDisk2");
    auto endCapDisk2PhysicalVolume = new G4PVPlacement (0, G4ThreeVector(0, 0, endCapDisk2Shift),
                                                        endCapDisk2LogicalVolume,
                                                        "EndCapDisk2",
                                                        calorimeterLogicalVolume,
                                                        false, 0, fCheckOverlaps);
    
    //------------------------
    //--------Crystal---------

    G4cout<<absorberMaterial->GetTemperature()<<G4endl;
    constexpr G4double DeadLayerZ = 0.00001*mm;

    constexpr G4double activeCrystalLength = crystalLength - DeadLayerZ;
    constexpr G4double activeZShift = START + windowDistance + activeCrystalLength / 2;
    constexpr G4double deadZShift   = activeZShift - activeCrystalLength / 2 + DeadLayerZ / 2;

    auto crystalCylinderSolid = new G4Tubs("CrystalBase", 0, crystalDiameter/2, activeCrystalLength/2, 0, 360*deg);
    auto crystalHoleSolid     = new G4Tubs("CrystalHole", 0, crystalHoleDiameter/2, crystalHoleDepth/2, 0, 360*deg);
    auto crystalSolid         = new G4SubtractionSolid("Crystal", crystalCylinderSolid, crystalHoleSolid, 0,
                                                    G4ThreeVector(0, 0, crystalHoleRelShift + DeadLayerZ));

    auto crystalLogicalVolume  = new G4LogicalVolume(crystalSolid, absorberMaterial, "Crystal");
    auto crystalPhysicalVolume = new G4PVPlacement(0, G4ThreeVector(0, 0, activeZShift+DeadLayerZ),
                                                crystalLogicalVolume,
                                                "Crystal",
                                                calorimeterLogicalVolume,
                                                false, 0, fCheckOverlaps);

    auto DeadLayerCylinderSolid = new G4Tubs("DeadLayerZ", 0, crystalDiameter/2, DeadLayerZ/2, 0, 360*deg);
    auto DeadLayerLogicalVolume = new G4LogicalVolume(DeadLayerCylinderSolid, absorberMaterial, "DeadLayer");
    auto DeadLayerPhysicalVolume = new G4PVPlacement(0, G4ThreeVector(0, 0, deadZShift),
                                                    DeadLayerLogicalVolume,
                                                    "DeadLayer",
                                                    calorimeterLogicalVolume,
                                                    false, 0, fCheckOverlaps);

    G4double maxStep = 0.0001*mm;

    /* G4UserLimits* stepLimits = new G4UserLimits(maxStep);
    DeadLayerLogicalVolume->SetUserLimits(stepLimits);
    crystalLogicalVolume->SetUserLimits(stepLimits); */
    calorimeterLogicalVolume->SetVisAttributes(new G4VisAttributes(G4Color(1.0, 0.0, 0.0,0.1)));
    endCapDisk2LogicalVolume->SetVisAttributes(new G4VisAttributes(G4Color(1.0, 0.0, 0.0,0.1)));
    endCapDisk1LogicalVolume->SetVisAttributes(new G4VisAttributes(G4Color(0.0, 0.0, 1.0,0.6)));
    endCapLogicalVolume->SetVisAttributes(new G4VisAttributes(G4Color(0.0, 1.0, 1.0,0.2)));
    DeadLayerLogicalVolume->SetVisAttributes(new G4VisAttributes(G4Color(1.0, 1.0, 1.0,0.9)));

    G4VisAttributes* crystalVisAtt = new G4VisAttributes(G4Color(0.0, 1.0, 0.0,0.1));
    crystalVisAtt->SetForceSolid(true);
    crystalLogicalVolume->SetVisAttributes(crystalVisAtt);
    ftargetLogical=crystalLogicalVolume;

    return worldPhysical;
}

void YourDetectorConstruction::CreateIsotope(G4String name, G4int z, G4int n, G4double mol_mass){
    G4Isotope* isotope = new G4Isotope(name, z, n, mol_mass * (g/mole));
    fIsotopes[name] = isotope; // Store by name for later use
}


void YourDetectorConstruction::CreateElement(const G4String& elName,
    const G4String& symbol,
    const std::vector<std::pair<G4String, G4double>>& isotopeFractions ) {
        
        G4Element* element = new G4Element(elName, symbol, isotopeFractions.size());

        for (const auto& [isoName, frac] : isotopeFractions) {
           G4Isotope* iso = fIsotopes.at(isoName); 
           element->AddIsotope(iso, frac * CLHEP::perCent);
           
       }
       fElements[elName] = element; 
    }



void YourDetectorConstruction::CreateMaterial(
        const G4String& matName,
        G4double density,
        const std::vector<std::pair<G4String, G4double>>& components
    ) {
        G4Material* mat = new G4Material(matName, density*(g/CLHEP::cm3), components.size());
        G4NistManager* nist = G4NistManager::Instance();
    
        for (const auto& [compName, frac] : components) {
            G4Element* element = nullptr;
            G4Material* material = nullptr;
    
            if (fElements.find(compName) != fElements.end()) {
                element = fElements[compName];
                G4cout<<"Used my predefined element for "<<compName<<G4endl;
            }
            else if ((element = nist->FindOrBuildElement(compName, /*verbose=*/false))) {
                G4cout<<"Used nist->FindOrBuildElement for "<<compName<<G4endl;
            }
            else if ((material = nist->FindOrBuildMaterial(compName))) {
                G4cout<<"Used nist->FindOrBuildMaterial for "<<compName<<G4endl;

            }
            else {
                G4cerr << "Error: Component '" << compName << "' is not defined as an element, isotope, or NIST material!" << G4endl;
                continue;
            }
    
            // Add to material
            if (element) {
                mat->AddElement(element, frac * CLHEP::perCent);
            } else if (material) {
                mat->AddMaterial(material, frac * CLHEP::perCent);
            }
        }
    
        fCustomMats[matName] = mat;
    }

void YourDetectorConstruction::BoxSourceGeometryCreator(const G4String& boxName, G4ThreeVector& boxSize,
    G4String materialName,const G4String& logicName,
    G4ThreeVector& physPlacement,const G4String& physName){
    
    G4Material* material = fCustomMats[materialName];

    G4Box* solidSource = new G4Box(boxName, (boxSize.x()/ 2)*cm,  boxSize.y()*cm / 2,  boxSize.z()*cm / 2);
    G4LogicalVolume* logicSource = new G4LogicalVolume(solidSource, material, logicName);
    G4PVPlacement* physSource = new G4PVPlacement(0, physPlacement, logicSource, physName, fworldLogical, false, 0);
} 
void YourDetectorConstruction::CylinderSourceGeometryCreator(const G4String& CylinderName, 
    G4double& CylinderRadius, G4double& CylinderHeight,
    G4String materialName,const G4String& logicName,
    G4ThreeVector& physPlacement,const G4String& physName){
    G4Material* material = fCustomMats[materialName];
    G4Tubs* solidSource = new G4Tubs(CylinderName,0,(CylinderRadius*cm/2),CylinderHeight*cm/2,0,360*deg);
    G4LogicalVolume* logicSource = new G4LogicalVolume(solidSource, material, logicName);
    G4PVPlacement* physSource = new G4PVPlacement(0, physPlacement, logicSource, physName, fworldLogical, false, 0);
} 



void YourDetectorConstruction::ConstructSDandField()
{   
    if (!(G4SDManager::GetSDMpointer()->FindSensitiveDetector("Sensitive-Detector"))){
        YourSensitiveDetector * sensDet = new YourSensitiveDetector("Sensitive-Detector");
        G4SDManager::GetSDMpointer()->AddNewDetector(sensDet);
        ftargetLogical->SetSensitiveDetector(sensDet);
    }
    else{ G4cout<<"SensDet has already been created"<<G4endl;}

    YourSensitiveDetector * sensDet = new YourSensitiveDetector("Sensitive-Detector");
    G4SDManager::GetSDMpointer()->AddNewDetector(sensDet);
    ftargetLogical->SetSensitiveDetector(sensDet);
}




void YourDetectorConstruction::SetSourceBox(
    const G4String& name, const G4String& matName,
    const G4ThreeVector& size, 
    const G4ThreeVector& placement
) {
    fCreateBox = true;
    fCreateTub = false;
    fMaterialName = matName;
    

    fBoxSize = size;
    fPlacement = placement;
}

void YourDetectorConstruction::SetSourceTube(
    const G4String& name, const G4String& matName,
    G4double radius, 
    G4double height, 
    const G4ThreeVector& placement
) {
    fCreateBox = false;
    fCreateTub = true;
    fGeometryName = name;
    fMaterialName = matName;
    fTubRadius = radius;
    fTubHeight = height;
    fPlacement = placement;
}

void YourDetectorConstruction::CreateSampleHolder(){
    G4double z, a, density;
    G4String name, symbol;
    G4int ncomponents, natoms;
    //(C3H4O2)
    a = 1.01*g/mole;
    G4Element* elH  = new G4Element(name="Hydrogen",symbol="H" , z= 1., a);

    a = 16.00*g/mole;
    G4Element* elO  = new G4Element(name="Oxygen"  ,symbol="O" , z= 8., a);
    a = 12.011*g/mole;
    G4Element* elC  = new G4Element(name="Carbon",symbol="C" , z= 6., a);

    density = 1,210*g/cm3;
    G4Material*  PLA = new G4Material(name="Polylactic acid",density,ncomponents=3);
    PLA->AddElement(elH, natoms=4);
    PLA->AddElement(elO, natoms=2);
    PLA->AddElement(elC,natoms=3);
    G4double Height = 0.5*cm;
    G4double Radius = 5*cm;
    G4ThreeVector Placement(0.0,0.0,-12.0*cm);
    G4Tubs* solidSource = new G4Tubs("SampleHolder",0,Radius/2,Height/2,0,360*deg);
    G4LogicalVolume* logicSource = new G4LogicalVolume(solidSource, PLA, "SampleHolderLogic");
    G4PVPlacement* physSource = new G4PVPlacement(0, Placement, logicSource, "SampleHolderPhys", fworldLogical, false, 0);
}
void YourDetectorConstruction::CreateKaliumContainer(){
    G4double z, a, density;
    G4String name, symbol;
    G4int ncomponents, natoms;
    G4NistManager* nistMGR =                  G4NistManager::Instance();

    a = 39.0983 * g/mole;
    G4Element* elK = new G4Element(name="Kalium", symbol="K", z=19., a);

    a = 35.45 * g/mole;
    G4Element* elCl = new G4Element(name="Chlorine", symbol="Cl", z=17., a);

    G4Material* air = nistMGR->FindOrBuildMaterial("G4_AIR");

    G4Material* KCl = new G4Material("KCl", 1.984*g/cm3, 2);
    KCl->AddElement(elK, 1);
    KCl->AddElement(elCl, 1);

    G4Material* PorousKCl = new G4Material("PorousKCl", 1.38187*g/cm3, 2);
    PorousKCl->AddMaterial(KCl, 99.9735 * perCent);
    PorousKCl->AddMaterial(air, 0.0265 * perCent);
    
    G4cout<<"Here we are"<<G4endl;
    G4double R_lower = 78.0 / 2 * mm;  // kisebbik sugár az alján
    G4double R_upper = 73.0 / 2 * mm;  // nagyobbik sugár a tetején

    G4double height = 45*mm;
    G4ThreeVector Placement(0.0,0.0,-height/2-0.9*mm );
    G4Cons* solidSource = new G4Cons("TejfolosDoboz",
        0,
        R_lower/2,
        0,
        R_upper/2,
        height/2,
        0,360*deg);
    
    G4LogicalVolume* logicSource = new G4LogicalVolume(solidSource, PorousKCl, "TejfolLogic");
    G4PVPlacement* physSource = new G4PVPlacement(0, Placement, logicSource, "Tejfol", fworldLogical, false, 0);


}