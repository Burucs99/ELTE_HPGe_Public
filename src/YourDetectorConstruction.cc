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
#include <G4RotationMatrix.hh>
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
//#include "/home/aburucs/CadMesh/CADMesh/CADMesh.hh"





YourDetectorConstruction::YourDetectorConstruction()
:   G4VUserDetectorConstruction()
     {
    fDetMessenger    = new YourDetectorMessenger(this);

    this->fDetector = new YourDetector();
    this->materialsTable = new Materials();
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
       
/*     auto logicalVolume = new G4LogicalVolume(solid, yourMaterial, "logicalName");
 */ 
    
    /*G4Material* NaI = nistMGR->FindOrBuildMaterial("G4_SODIUM_IODIDE");

    G4Tubs* scintiSolid = new G4Tubs(
        "Scinti",
        0.0 * mm,     // inner radius
        25.0 * mm,    // outer radius = 50/2
        25.0 * mm,    // half-length = 50/2
        0.0 * deg,
        360.0 * deg
    );

    auto activeCrystalLogical = new G4LogicalVolume(
        scintiSolid,
        NaI,
        "ActiveCrystal"
    );

    ftargetLogical=activeCrystalLogical;
    auto ScintiPlacement = new G4PVPlacement (0, G4ThreeVector(0, 0, -25.0*mm),
                                                        activeCrystalLogical,
                                                        "Calorimeter",
                                                        worldLogical,
                                                        false, 0, true);*/

    this->fDetector->Build(worldLogical, this->materialsTable->GetNatriumIodineMaterial(), G4ThreeVector(0, 0, 0), 0,
                        this->materialsTable->GetMagnesiumOxidMaterial(),
                        this->materialsTable->GetMagnesiumOxidMaterial(),
                        this->materialsTable->GetAluminiumMaterial(),
                        this->materialsTable->GetAluminiumMaterial());



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
    /*if (!(G4SDManager::GetSDMpointer()->FindSensitiveDetector("Sensitive-Detector"))){
        YourSensitiveDetector * sensDet = new YourSensitiveDetector("Sensitive-Detector");
        G4SDManager::GetSDMpointer()->AddNewDetector(sensDet);
        ftargetLogical->SetSensitiveDetector(sensDet);
    }
    else{ G4cout<<"SensDet has already been created"<<G4endl;}*/

    G4VSensitiveDetector* sd = new YourSensitiveDetector("Sensitive-Detector");
    G4SDManager::GetSDMpointer()->AddNewDetector(sd);
    this->fDetector->GetLogicalVolume()->SetSensitiveDetector(sd);
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
    /*G4bool fCheckOverlaps = true;

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

    density = 0.7145*g/cm3;
    G4Material*  PLA = new G4Material(name="Polylactic acid",density,ncomponents=3);
    PLA->AddElement(elH, natoms=4);
    PLA->AddElement(elO, natoms=2);
    PLA->AddElement(elC,natoms=3);
    auto bunny_mesh_2 = CADMesh::TessellatedMesh::FromSTL("../geom/detector_stand_ascii.stl");

    auto bunny_logical_2 = new G4LogicalVolume( bunny_mesh_2->GetSolid() 
                                                 , PLA
                                                 , "logical_2"
                                                 , 0, 0, 0
        );
 
    G4double endCapTopZ = 0.0*mm;
    G4double bunnyHalfHeight = 0*mm;
    auto bunnyRotation = new G4RotationMatrix();
    bunnyRotation->rotateX(180.0 * deg);
    new G4PVPlacement(bunnyRotation,
                  fSampleHolderPlacement,
                  bunny_logical_2,
                  "physicalBunny_2",
                  fworldLogical,
                  false, 0, fCheckOverlaps);*/
}