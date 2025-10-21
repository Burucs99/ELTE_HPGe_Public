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
#include "/home/aburucs/CadMesh/CADMesh/CADMesh.hh"



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
    
    G4double worldSize   = 2*m;

    G4Box* worldSolid             = new G4Box("solid-World",worldSize/2,worldSize/2,worldSize/2);
    G4LogicalVolume* worldLogical = new G4LogicalVolume(worldSolid,worldMat,"logic-World");
    G4VPhysicalVolume* worldPhysical = new G4PVPlacement(nullptr,G4ThreeVector(0,0,0),worldLogical,"World",nullptr,false,0);

    fworldLogical = worldLogical;
    
    // Testing 
/*     CreateKaliumContainer();
 */    
       
/*     auto logicalVolume = new G4LogicalVolume(solid, yourMaterial, "logicalName");
 */ 

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

    density = 0.6579*g/cm3;
    G4Material*  PLA = new G4Material(name="Polylactic acid",density,ncomponents=3);
    PLA->AddElement(elH, natoms=4);
    PLA->AddElement(elO, natoms=2);
    PLA->AddElement(elC,natoms=3);
    auto bunny_mesh = CADMesh::TessellatedMesh::FromSTL("../geom/plate_ascii.stl");

    auto bunny_logical = new G4LogicalVolume( bunny_mesh->GetSolid() 
                                                 , PLA
                                                 , "logical"
                                                 , 0, 0, 0
        );

    //
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
    // Dead layer thicknesses
    G4double DeadLayerZ    = ftopDeadlayer;  // front face
    G4double DeadLayerRad  = fsideDeadLayer;  // around barrel
    G4double DeadLayerHole = finsideDeadLayer;  // inside hole

    // Active crystal dimensions
    G4double activeCrystalLength = crystalLength - DeadLayerZ;
    G4double activeCrystalRadius = crystalDiameter/2 - DeadLayerRad;
    G4double activeHoleRadius    = crystalHoleDiameter/2 + DeadLayerHole;

    // Placement shifts (same as your original logic)
    G4double activeZShift = START + windowDistance + activeCrystalLength / 2;
    G4double deadZShift   = activeZShift - activeCrystalLength / 2 + DeadLayerZ / 2;

    // ---------------------------------------------------------
    // Outer full crystal (including all dead layers)
    // ---------------------------------------------------------
    auto fullCrystalSolid = new G4Tubs("FullCrystal",
                                    0,
                                    crystalDiameter/2,
                                    crystalLength/2,
                                    0, 360*deg);

    // Outer hole (bore) full size (before dead layer)
    auto fullHoleSolid = new G4Tubs("FullHole",
                                    0,
                                    crystalHoleDiameter/2,
                                    crystalHoleDepth/2,
                                    0, 360*deg);

    // Full crystal with bore
    auto fullCrystalWithBore = new G4SubtractionSolid("FullCrystalWithBore",
                                                    fullCrystalSolid,
                                                    fullHoleSolid,
                                                    0,
                                                    G4ThreeVector(0, 0, crystalHoleRelShift));

    // ---------------------------------------------------------
    // Active crystal volume
    // ---------------------------------------------------------
    auto activeCrystalSolidCyl = new G4Tubs("ActiveCrystalCyl",
                                            0,
                                            activeCrystalRadius,
                                            activeCrystalLength/2,
                                            0, 360*deg);

    auto activeHoleSolid = new G4Tubs("ActiveHole",
                                    0,
                                    activeHoleRadius,
                                    crystalHoleDepth/2,
                                    0, 360*deg);

    auto activeCrystalSolid = new G4SubtractionSolid("ActiveCrystal",
                                                    activeCrystalSolidCyl,
                                                    activeHoleSolid,
                                                    0,
                                                    G4ThreeVector(0, 0, crystalHoleRelShift + DeadLayerZ));

    // ---------------------------------------------------------
    // Dead layer = Full crystal with bore - Active crystal
    // ---------------------------------------------------------
    auto deadLayerSolid = new G4SubtractionSolid("DeadLayer",
                                                fullCrystalWithBore,
                                                activeCrystalSolid);

    // ---------------------------------------------------------
    // Logical & physical volumes
    // ---------------------------------------------------------
    auto activeCrystalLogical = new G4LogicalVolume(activeCrystalSolid, absorberMaterial, "ActiveCrystal");
    auto activeCrystalPhysical = new G4PVPlacement(0,
                                                G4ThreeVector(0, 0, activeZShift + DeadLayerZ),
                                                activeCrystalLogical,
                                                "ActiveCrystal",
                                                calorimeterLogicalVolume,
                                                false, 0, fCheckOverlaps);

    auto deadLayerLogical = new G4LogicalVolume(deadLayerSolid, absorberMaterial, "DeadLayer");
    auto deadLayerPhysical = new G4PVPlacement(0,
                                            G4ThreeVector(0, 0, activeZShift + DeadLayerZ),
                                            deadLayerLogical,
                                            "DeadLayer",
                                            calorimeterLogicalVolume,
                                            false, 0, fCheckOverlaps);

    G4double endCapTopZ = calorimeterShift - endCapShift - endCapLength / 2;
     G4double bunnyHalfHeight = 0*mm; // depends on your bunny volume
    G4ThreeVector bunnyPosition(0, 0, endCapTopZ + bunnyHalfHeight);
    auto bunnyRotation = new G4RotationMatrix();
    bunnyRotation->rotateX(180.0 * deg);
    new G4PVPlacement(bunnyRotation,
                  bunnyPosition,
                  bunny_logical,
                  "physicalBunny",
                  worldLogical,
                  false, 0, fCheckOverlaps);


    G4double maxStep = 0.0001*mm;

    G4UserLimits* stepLimits = new G4UserLimits(maxStep);
    deadLayerLogical->SetUserLimits(stepLimits);
    activeCrystalLogical->SetUserLimits(stepLimits);
    calorimeterLogicalVolume->SetVisAttributes(new G4VisAttributes(G4Color(1.0, 0.0, 0.0,0.1)));
    endCapDisk2LogicalVolume->SetVisAttributes(new G4VisAttributes(G4Color(1.0, 0.0, 0.0,0.1)));
    endCapDisk1LogicalVolume->SetVisAttributes(new G4VisAttributes(G4Color(0.0, 0.0, 1.0,0.6)));
    endCapLogicalVolume->SetVisAttributes(new G4VisAttributes(G4Color(0.0, 1.0, 1.0,0.2)));
    deadLayerLogical->SetVisAttributes(new G4VisAttributes(G4Color(1.0, 0.0, 0.0,0.1)));

    G4VisAttributes* crystalVisAtt = new G4VisAttributes(G4Color(0.0, 1.0, 0.0,0.6));
    crystalVisAtt->SetForceSolid(true);
    activeCrystalLogical->SetVisAttributes(crystalVisAtt);
    ftargetLogical=activeCrystalLogical;




    


    /* constexpr G4double BoxSize                    = 60*cm; 
    constexpr G4double BoxThickness               = 10*cm;

    auto OuterBox = new G4Box ("OuterBox",BoxSize/2,BoxSize/2,BoxSize/2);
    auto InnerBox    = new G4Box ("InnerBox", BoxSize/2-BoxThickness,BoxSize/2-BoxThickness,BoxSize/2-BoxThickness);

    auto BoxSolid         = new G4SubtractionSolid ("Box", OuterBox, InnerBox, 0, G4ThreeVector(0, 0, 0));
    auto lead = nistMGR->FindOrBuildMaterial("G4_Pb");
    auto BoxLogicalVolume  = new G4LogicalVolume (BoxSolid, lead, "Box");
    auto BoxPhysicalVolume = new G4PVPlacement (0, G4ThreeVector(0, 0, 0),//
                                                    BoxLogicalVolume,
                                                    "Box",
                                                    worldLogical,
                                                    false, 0, fCheckOverlaps);
    BoxLogicalVolume->SetVisAttributes(new G4VisAttributes(G4Color(0.0, 0.0, 0.5,0.1))); */
    //PlaceCaesiumContaianer();
    G4Material* Cobalt = nistMGR->FindOrBuildMaterial("G4_Co");

    G4ThreeVector cobaltpost(0, 0, -150.0*CLHEP::mm);
    auto cobaltrot = new G4RotationMatrix();
    cobaltrot->rotateX(180.0 * deg);
    G4Tubs* Cobalt_ring=new G4Tubs("Co_ring",15.0*mm, 16.5*mm, 1*mm,0.,twopi);
    G4LogicalVolume* Cobalt_logical = new G4LogicalVolume(Cobalt_ring,Cobalt,"Co_ring");
    new G4PVPlacement(cobaltrot,cobaltpost,Cobalt_logical,"Co_ring",worldLogical,false,0,false);
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
    G4bool fCheckOverlaps = true;
    G4Material* material = fCustomMats[materialName];

    G4Box* solidSource = new G4Box(boxName, (boxSize.x()/ 2)*cm,  boxSize.y()*cm / 2,  boxSize.z()*cm / 2);
    G4LogicalVolume* logicSource = new G4LogicalVolume(solidSource, material, logicName);
    G4PVPlacement* physSource = new G4PVPlacement(0, physPlacement, logicSource, physName, fworldLogical, false, 0,fCheckOverlaps);
} 
void YourDetectorConstruction::CylinderSourceGeometryCreator(const G4String& CylinderName, 
    G4double& CylinderRadius, G4double& CylinderHeight,
    G4String materialName,const G4String& logicName,
    G4ThreeVector& physPlacement,const G4String& physName){
    G4Material* material = fCustomMats[materialName];
    
    /*  COS-16H tok  */ 


    G4NistManager* nistMGR =                  G4NistManager::Instance();

    G4Tubs* solidSource = new G4Tubs(CylinderName,0,(CylinderRadius*cm/2),CylinderHeight*cm/2,0,360*deg);
    G4cout<<"Itt akad meg"<<G4endl;
    G4LogicalVolume* logicSource = new G4LogicalVolume(solidSource, material, logicName);
    G4PVPlacement* physSource = new G4PVPlacement(0, physPlacement, logicSource, physName, fworldLogical, false, 0,true);


    G4Tubs* COS_16H = new G4Tubs("COS-16H Tub",0,8*CLHEP::mm/2,13*CLHEP::mm/2,0,360*deg);
    auto Cos_16H_tok         = new G4SubtractionSolid ("COS-16H Tok", COS_16H, solidSource, 0, G4ThreeVector(0, 0, 0));
    auto Stainless_Steel = nistMGR->FindOrBuildMaterial("G4_STAINLESS-STEEL");
    auto Cos_16H_tok_LogicalVolume  = new G4LogicalVolume (Cos_16H_tok , Stainless_Steel, "Cos16");
    auto Cos_16H_tok_Physical_Volume = new G4PVPlacement (0, physPlacement,//
                                                    Cos_16H_tok_LogicalVolume,
                                                    "Cos16",
                                                    fworldLogical,
                                                    false, 0, true);
    Cos_16H_tok_LogicalVolume->SetVisAttributes(new G4VisAttributes(G4Color(0.0, 1.0, 0.0,0.5)));
} 



void YourDetectorConstruction::ConstructSDandField()
{   
    /* if (!(G4SDManager::GetSDMpointer()->FindSensitiveDetector("Sensitive-Detector"))){
        YourSensitiveDetector * sensDet = new YourSensitiveDetector("Sensitive-Detector");
        G4SDManager::GetSDMpointer()->AddNewDetector(sensDet);
        ftargetLogical->SetSensitiveDetector(sensDet);
    }
    else{ G4cout<<"SensDet has already been created"<<G4endl;} */

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
    G4bool fCheckOverlaps = true;

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
                  false, 0, fCheckOverlaps);
    bunny_logical_2->SetVisAttributes(new G4VisAttributes(G4Color(0.0, 0.5, 0.0,1.0)));

}









void YourDetectorConstruction::PlaceCaesiumContaianer( ){
        auto placement =fCaesiumPlacement;
        G4bool fCheckOverlaps = true;
        auto logicWorld = fworldLogical;
        //  crystal
        G4double   fthick_shiel_up = 2794*um; // 380*um;//110*um ;
        G4double    fthick_shiel_down = 380*um; // 380*um;//110*um ;
    //
        G4NistManager* nist = G4NistManager::Instance();
        G4Material* default_mat = nist->FindOrBuildMaterial("G4_AIR");
        //G4Material* cryst_mat   = nist->FindOrBuildMaterial("Lu2SiO5");
        G4Material* cmos_mat   = nist->FindOrBuildMaterial("G4_Si");
        //G4Material* aluminum   = nist->FindOrBuildMaterial("G4_Al");
        G4Material* Plexiglass = nist->FindOrBuildMaterial("G4_PLEXIGLASS");

        G4Material* Polyetilen = nist->FindOrBuildMaterial("G4_POLYETHYLENE");///cover
    //  G4Material* Polycarbonat = nist->FindOrBuildMaterial("G4_POLYCARBONATE");////lentes

        // auto scintillator = G4Material::GetMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
    //"G4_POLYCARBONATE" ///lentes
    //////////////"G4_POLYACRYLONITRILE" ///telas
    //"G4_POLYETHYLENE"/////envasecover
    ///////////////"G4_POLYOXYMETHYLENE"//plastico duro
    ////////////////"G4_POLYPROPYLENE"
    ///////"G4_POLYSTYRENE" ////////envases de yougur

        // define Elements
        //
        G4Element* H  = new G4Element("Hydrogen", "H",  1,    1.01*g/mole);
        G4Element* C  = new G4Element("Carbon",   "C",  6,    12.01*g/mole);
        G4Element* N  = new G4Element("Nitrogen", "N",  7,    14.01*g/mole);
        G4Element* O  = new G4Element("Oxygen",   "O",  8,    16.00*g/mole);
        G4Element* Si = new G4Element("Silicon",  "Si", 14.,  28.09*g/mole);
        //
        // define simple materials
        //G4Element* Si  =new G4Material("Silicon"  symbol="Si", z=14, a=28.09*g/mole, density= 2.330*g/cm3)
        /*
        G4Element* H  = manager->FindOrBuildElement(1);
        G4Element* C  = manager->FindOrBuildElement(6);
        G4Element* N  = manager->FindOrBuildElement(7);
        G4Element* O  = manager->FindOrBuildElement(8);
        G4Element* Si = manager->FindOrBuildElement(14);
        */
    // PDMS SiOC2H6
    // -------------
        G4Material* PDMS = new G4Material("PDMS", 1.34*g/cm3, 4);
        PDMS->AddElement(Si, 1 );
        PDMS->AddElement(O, 1 );
        PDMS->AddElement(C, 2 );
        PDMS->AddElement(H, 6 );

        ///Photoresist (C10H6N2O)
        G4Material* PhotoR = new G4Material("PhotoR", 1.29*g/cm3, 4);
        PhotoR->AddElement(C, 10 );
        PhotoR->AddElement(H, 6 );
        PhotoR->AddElement(N, 2 );
        PhotoR->AddElement(O, 1 );

        // PMMA C5H8O2 ( Acrylic )
        // -------------
        G4Material* Acrylic = new G4Material("Acrylic", 1.19*g/cm3, 3);
        Acrylic->AddElement(C,  5);
        Acrylic->AddElement(H, 8);
        Acrylic->AddElement(O, 2);


        //Epoxy (for FR4 )
        G4Material* Epoxy = new G4Material("Epoxy" , 1.2*g/cm3, 2);
        Epoxy->AddElement(H, 2);
        Epoxy->AddElement(C, 2);


        //G4Material* Brass = nist->FindOrBuildMaterial("G4_BRASS");
        G4Material* Stainless_steel = nist->FindOrBuildMaterial("G4_STAINLESS-STEEL");
        G4Material* copper = nist->FindOrBuildMaterial("G4_Cu");
        G4Material* Beryllium = nist->FindOrBuildMaterial("G4_Be");

        G4Material* SiO2 = nist->FindOrBuildMaterial("G4_SILICON_DIOXIDE");

        G4Material* Cellophane = nist->FindOrBuildMaterial("G4_CELLULOSE_CELLOPHANE");
        // Material: Vacuum
    //  G4Material* Vacuum = G4NistManager::Instance()->FindOrBuildMaterial("G4_Galactic");
        //G4Material* default_mat = G4NistManager::Instance()->FindOrBuildMaterial("G4_Galactic");

    //  if(fSource=="e" ){ default_mat=Vacuum;}
    //  else{ default_mat=Air;}

        // Material: Vacuum
        //  G4Material* Vacuum = new G4Material("Vacuum", 1.0 , 1.01*g/mole, 1.0E-25*g/cm3, kStateGas, 2.73*kelvin, 3.0E-18*pascal );

        //Source shielding_ Sr90 Cs137
        G4double thick_z =  380*um;//110*um ;
        G4double ring_R2 = 12700 *um, ring_R1 = 3175*um;
        G4double Source_Height = 3175*um - fthick_shiel_up - fthick_shiel_down;
        
        G4double epoxy_Height = fthick_shiel_up;
        G4double thick_paper =  160*um;//110*um ;

        //Source shielding_ Fe55
        G4double monel_thick_z = 250*um, be_thick_z = 250*um;
        G4double monel_z = 2.5*mm - monel_thick_z;
    //Diámetro total: 1 pulgada (25.4 mm)
    //Diámetro activo: 0.197 pulgada (5 mm)  or 0.25in  6350*um
    //Altura: 0.125 pulgada (3.18 mm)   3175*um

        G4double place_Detec_Z;

        //
        // World
        //
        G4double world_sizeX = 5*cm;
        G4double world_sizeY = 5*cm;
        G4double world_sizeZ = 10*cm;


    // Visualization attributes

// Define new distinct colors for each component
G4VisAttributes* redOuter = new G4VisAttributes(G4Colour(1.0, 0.0, 0.0, 0.9));       // Red for outer shield
G4VisAttributes* blueEpoxy = new G4VisAttributes(G4Colour(0.0, 0.0, 1.0, 0.9));      // Bright blue for epoxy
G4VisAttributes* yellowPaper = new G4VisAttributes(G4Colour(1.0, 1.0, 0.0, 0.9));    // Yellow for paper
G4VisAttributes* greenSource = new G4VisAttributes(G4Colour(0.0, 1.0, 0.0, 0.9));    // Solid green for Cs137 source
G4VisAttributes* purpleCap = new G4VisAttributes(G4Colour(0.6, 0.0, 0.8, 0.9));      // Purple for end caps

// Set visibility
redOuter->SetVisibility(true);
blueEpoxy->SetVisibility(true);
yellowPaper->SetVisibility(true);
greenSource->SetVisibility(true);
purpleCap->SetVisibility(true);

// ======== SOURCE SHIELDING ======== //
G4RotationMatrix* Rotation = new G4RotationMatrix();
Rotation->rotateX(0*deg);
Rotation->rotateY(-180*deg);
Rotation->rotateZ(0*deg);

// Main outer shield (Plexiglass tube)
G4Tubs* solid_Sshield_out = new G4Tubs("Sshield_out", ring_R1, ring_R2, Source_Height/2, 0., twopi);
G4LogicalVolume* logic_Sshield_out = new G4LogicalVolume(solid_Sshield_out, Plexiglass, "Sshield_out");
new G4PVPlacement(Rotation, placement, logic_Sshield_out, "Sshield_out", logicWorld, false, 0, fCheckOverlaps);
logic_Sshield_out->SetVisAttributes(redOuter);  // Red




// Epoxy ring shield
G4Tubs* solid_epoxy_Sshield_down = new G4Tubs("epoxy_Sshield_down", ring_R1/2, ring_R1, Source_Height/2, 0., twopi);
G4LogicalVolume* logic_epoxy_Sshield_down = new G4LogicalVolume(solid_epoxy_Sshield_down, Epoxy, "epoxy_Sshield_down");
new G4PVPlacement(Rotation, placement, logic_epoxy_Sshield_down, "epoxy_Sshield_down", logicWorld, false, 0, fCheckOverlaps);
logic_epoxy_Sshield_down->SetVisAttributes(blueEpoxy);  // Bright blue

// Bottom epoxy cap
G4Tubs* solid_epoxy_Sshield = new G4Tubs("epoxy_Sshield", 0, ring_R1, epoxy_Height/2, 0., twopi);
G4LogicalVolume* logic_epoxy_Sshield = new G4LogicalVolume(solid_epoxy_Sshield, Epoxy, "epoxy_Sshield");
new G4PVPlacement(Rotation, G4ThreeVector(placement.x(), placement.y(), placement.z()-epoxy_Height/2-Source_Height/2),
                  logic_epoxy_Sshield, "epoxy_Sshield", logicWorld, false, 0, fCheckOverlaps);
logic_epoxy_Sshield->SetVisAttributes(yellowPaper);  // Bright blue

// Top tube shield (if present)
if(fthick_shiel_up > 0*um) {
    G4Tubs* solid_tub_Sshield_up = new G4Tubs("tub_Sshield_up", ring_R1, ring_R2, fthick_shiel_up/2, 0., twopi);
    G4LogicalVolume* logic_tub_Sshield_up = new G4LogicalVolume(solid_tub_Sshield_up, Plexiglass, "tub_Sshield_up");
    new G4PVPlacement(Rotation, G4ThreeVector(placement.x(), placement.y(), placement.z()-Source_Height/2-fthick_shiel_up/2),
                      logic_tub_Sshield_up, "tub_Sshield_up", logicWorld, false, 0, fCheckOverlaps);
    logic_tub_Sshield_up->SetVisAttributes(redOuter);  // Red
}

// Paper layer
G4Tubs* solid_paper_Sshield_up = new G4Tubs("paper_Sshield_up", 0, ring_R2, thick_paper/2, 0., twopi);
G4LogicalVolume* logic_paper_Sshield_up = new G4LogicalVolume(solid_paper_Sshield_up, Cellophane, "paper_Sshield_up");
new G4PVPlacement(Rotation, G4ThreeVector(placement.x(), placement.y(), placement.z()-fthick_shiel_up-Source_Height/2-thick_paper/2),
                  logic_paper_Sshield_up, "paper_Sshield_up", logicWorld, false, 0, fCheckOverlaps);
logic_paper_Sshield_up->SetVisAttributes(redOuter);  // Yellow

// Bottom cap (if present)
if(fthick_shiel_down > 0*um) {
    G4Tubs* solid_cap_Sshield_down = new G4Tubs("cap_Sshield_down", 0, ring_R2, fthick_shiel_down/2, 0., twopi);
    G4LogicalVolume* logic_cap_Sshield_down = new G4LogicalVolume(solid_cap_Sshield_down, Plexiglass, "cap_Sshield_down");
    new G4PVPlacement(Rotation, G4ThreeVector(placement.x(), placement.y(), placement.z()+Source_Height/2+fthick_shiel_down/2),
                      logic_cap_Sshield_down, "cap_Sshield_down", logicWorld, false, 0, fCheckOverlaps);
    logic_cap_Sshield_down->SetVisAttributes(purpleCap);  // Purple
}

// ======== CS137 SOURCE (ADD THIS) ======== //
/*
G4Tubs* solid_Cs137 = new G4Tubs("Cs137_Source", 0, source_radius, source_height/2, 0., twopi);
G4LogicalVolume* logic_Cs137 = new G4LogicalVolume(solid_Cs137, Cs137_mat, "Cs137_Source");
new G4PVPlacement(0, placement, logic_Cs137, "Cs137_Source", logicWorld, false, 0, fCheckOverlaps);
logic_Cs137->SetVisAttributes(greenSource);  // Solid green
*/

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


}
