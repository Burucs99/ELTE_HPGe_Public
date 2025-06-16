#include "YourDetectorMessenger.hh"
#include <CLHEP/Units/SystemOfUnits.h>
#include <G4ApplicationState.hh>
#include <G4UIcommand.hh>
#include <G4UImessenger.hh>
#include <G4UIparameter.hh>
#include <G4ios.hh>
#include "YourDetectorConstruction.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAString.hh"
#include "G4String.hh"
#include <vector>

YourDetectorMessenger::YourDetectorMessenger(YourDetectorConstruction* det)
:   G4UImessenger(),
    fYourDetector(det),
    fDirCMD(nullptr),
    fIsotopeCMD(nullptr),
    fElementCMD(nullptr),
    fMaterialCMD(nullptr),
    fBoxCmd(nullptr),
    fTubCmd(nullptr),
    fSampleHolderCmd(nullptr){

    fDirCMD = new G4UIdirectory("/HPGe/det/");
    fDirCMD->SetGuidance("UI commands specific to the detector construction of this application"); 
    
    fIsotopeCMD    = new G4UIcommand("/HPGe/det/CreateIsotope",this);
    fIsotopeCMD->SetGuidance("Sets the name of the isotope, z , a , g/mol of isotope");
    fIsotopeCMD->SetGuidance(" name of isotope G4String ");
    fIsotopeCMD->SetGuidance(" Z atomic number G4int");
    fIsotopeCMD->SetGuidance("A mass number, protons + neutrons G4int");
    fIsotopeCMD->SetGuidance("g/mol: molecular weight, no need for dimensions G4double");

    G4UIparameter* IsotopeNamePrm = new G4UIparameter("IsotName", 's', false);
    IsotopeNamePrm->SetGuidance(" name of isotope G4String ");
    fIsotopeCMD->SetParameter(IsotopeNamePrm);
    G4UIparameter* AtomicNumPrm = new G4UIparameter("AtomicNum",'i',false);
    AtomicNumPrm->SetGuidance(" Z atomic number G4int");
    fIsotopeCMD->SetParameter(AtomicNumPrm);
    G4UIparameter* MassNumPrm = new G4UIparameter("MassNum",'i',false);
    MassNumPrm->SetGuidance("A mass number, protons + neutrons G4int");
    fIsotopeCMD->SetParameter(MassNumPrm);
    G4UIparameter* MolecularWeightPrm = new G4UIparameter("MolecularWeightNum", 'd',false);
    MolecularWeightPrm->SetGuidance("g/mol: molecular weight, no need for dimensions G4double");
    fIsotopeCMD->SetParameter(MolecularWeightPrm);
    fIsotopeCMD->AvailableForStates(G4State_PreInit,G4State_Idle);
    fIsotopeCMD->SetToBeBroadcasted(false);    

    
    fElementCMD = new G4UIcommand("/HPGe/det/CreateElement",this);
    fElementCMD->SetGuidance("Creates Radioactive elements from Isotopes");
    fElementCMD->SetGuidance(" elName, symbol, isotopeFractions");
    G4UIparameter* ElementNamePrm = new G4UIparameter("ElementName",'s',false);
    fElementCMD->SetParameter(ElementNamePrm);
    G4UIparameter* ElementSymbPrm = new G4UIparameter("ElementSymbol",'s',false);
    fElementCMD->SetParameter(ElementSymbPrm);
    G4UIparameter* IsotopeFracPrm = new G4UIparameter("IsotopeFractions",'s',this);
    IsotopeFracPrm->SetGuidance("Comma separated list of isotope:percentage pairs");
    fElementCMD->SetParameter(IsotopeFracPrm);
    fElementCMD->AvailableForStates(G4State_PreInit,G4State_Idle);
    fElementCMD->SetToBeBroadcasted(false);  

    fMaterialCMD = new G4UIcommand("/HPGe/det/CreateMaterial",this);
    fMaterialCMD->SetGuidance("Creates a material from predefined elements, or from Nist database");
    fMaterialCMD->SetGuidance("matName,density in g/cm^3 ,components");
    G4UIparameter* MatNamePrm = new G4UIparameter("MatName",'s',false);
    fMaterialCMD->SetParameter(MatNamePrm);
    G4UIparameter* DensityPrm = new G4UIparameter("Density",'d',true);
    fMaterialCMD->SetParameter(DensityPrm);
    G4UIparameter* ComponentsPrm = new G4UIparameter("Components",'s',true);
    fMaterialCMD->SetParameter(ComponentsPrm);
    fMaterialCMD->AvailableForStates(G4State_PreInit,G4State_Idle);
    fMaterialCMD->SetToBeBroadcasted(false);
    fBoxCmd = new G4UIcommand("/HPGe/det/setSourceBox", this);
    fBoxCmd->SetGuidance("Define a box source geometry");
    fBoxCmd->SetGuidance("Usage: /det/setSourceBox name matName sizeX sizeY sizeZ posX posY posZ");
    
    G4UIparameter* param;
    param = new G4UIparameter("name", 's', false);
    fBoxCmd->SetParameter(param);
    
    param = new G4UIparameter("matName",'s',false);
    fBoxCmd->SetParameter(param);
    param = new G4UIparameter("sizeX", 'd', false);
    fBoxCmd->SetParameter(param);
    param = new G4UIparameter("sizeY", 'd', false);
    fBoxCmd->SetParameter(param);
    param = new G4UIparameter("sizeZ", 'd', false);
    fBoxCmd->SetParameter(param);
    
    param = new G4UIparameter("posX", 'd', false);
    fBoxCmd->SetParameter(param);
    param = new G4UIparameter("posY", 'd', false);
    fBoxCmd->SetParameter(param);
    param = new G4UIparameter("posZ", 'd', false);
    fBoxCmd->SetParameter(param);
    
    // Tube geometry command
    fTubCmd = new G4UIcommand("/HPGe/det/setSourceTube", this);
    fTubCmd->SetGuidance("Define a tube source geometry");
    fTubCmd->SetGuidance("Usage: /det/setSourceTube name matName radius height posX posY posZ");
    
    param = new G4UIparameter("name", 's', false);
    fTubCmd->SetParameter(param);
    param = new G4UIparameter("matName",'s',false);
    fTubCmd->SetParameter(param);
    param = new G4UIparameter("radius", 'd', false);
    fTubCmd->SetParameter(param);
    param = new G4UIparameter("height", 'd', false);
    fTubCmd->SetParameter(param);
    
    param = new G4UIparameter("posX", 'd', false);
    fTubCmd->SetParameter(param);
    param = new G4UIparameter("posY", 'd', false);
    fTubCmd->SetParameter(param);
    param = new G4UIparameter("posZ", 'd', false);
    fTubCmd->SetParameter(param);


    fSampleHolderCmd = new G4UIcommand("/HPGe/det/setSampleHolderPosition", this);
    param = new G4UIparameter("posX", 'd', false);
    fSampleHolderCmd->SetParameter(param);
    param = new G4UIparameter("posY", 'd', false);
    fSampleHolderCmd->SetParameter(param);
    param = new G4UIparameter("posZ", 'd', false);
    fSampleHolderCmd->SetParameter(param);
    fSampleHolderCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
    fSampleHolderCmd->SetToBeBroadcasted(false); 
}

YourDetectorMessenger::~YourDetectorMessenger() {
    delete fIsotopeCMD;
    delete fElementCMD;
    delete fMaterialCMD;
    delete fBoxCmd;
    delete fTubCmd;
    delete fDirCMD;
    delete fSampleHolderCmd;
  }

void YourDetectorMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{

     if ( command == fIsotopeCMD){
        G4String name;
        G4int z,a;
        G4double molmass;
        std::istringstream is(newValue);
        is >> name>> z >> a >> molmass;

        fYourDetector->CreateIsotope( name,  z,  a, molmass); 

        G4cout<<"Isotope has been created with "<<name<<z<<a<<molmass<<G4endl;
    } 

    if(command==fElementCMD){
        /*RIP String Manipulation*/
        G4String elementName, symbol, isotopeFractionsStr;

        std::istringstream iss(newValue);
        iss >> elementName >> symbol;
        std::getline(iss, isotopeFractionsStr); // Read the entire remaining line

        // Trim leading/trailing whitespace (optional but recommended)
        G4StrUtil::lstrip(isotopeFractionsStr);


        std::vector<std::pair<G4String, G4double>> isotopeFractions;

        G4String current;
        G4String isotope;
        bool isFractionPart = false;
        double totalFraction = 0.0;
        constexpr double EPSILON = 1e-6; 

        for (char c : isotopeFractionsStr) {
            if (c == ' ' || c == ':') {
                if (c == ':') {
                    isotope = current;
                    isFractionPart = true;
                } else if (c == ' ') {
                    double fraction = std::atof(current.c_str());
                    isotopeFractions.emplace_back(isotope, fraction);
                    totalFraction += fraction;
                    isFractionPart = false;
                }
                current.clear();
            } else {
                current += c;
            }
        }

        if (!current.empty() && isFractionPart) {
            double fraction = std::atof(current.c_str());
            isotopeFractions.emplace_back(isotope, fraction);
            totalFraction += fraction;
        }

    if (std::abs(totalFraction - 100.0) > EPSILON) { // Allow minor floating-point errors
        G4cerr << "ERROR: Total fraction is " << totalFraction 
            << "% (must be exactly 100% ± " << EPSILON << ")" << G4endl;
        
    }
    else{
        for (const auto& pair : isotopeFractions) {
            G4cout << "Isotope: " << pair.first << ", Fraction: " << pair.second << "%" << G4endl;
        }
        fYourDetector->CreateElement(elementName,symbol,isotopeFractions);
     }
    }
    if( command == fMaterialCMD){

        G4cout<<"Setting Up material"<<G4endl;
        G4String matName,components;
        G4double density;
        std::istringstream iss(newValue);
        iss >> matName>> density ;
        std::getline(iss, components); // Read the entire remaining line
        G4StrUtil::lstrip(components);

        std::vector<std::pair<G4String, G4double>> ComponentVector;
        
        G4String current;
        G4String Component;
        bool isFractionPart = false;
        double totalFraction = 0.0;
        constexpr double EPSILON = 1e-6; 

        for (char c : components) {
            if (c == ' ' || c == ':') {
                if (c == ':') {
                    Component = current;
                    isFractionPart = true;
                } else if (c == ' ') {
                    double fraction = std::atof(current.c_str());
                    ComponentVector.emplace_back(Component, fraction);
                    totalFraction += fraction;
                    isFractionPart = false;
                }
                current.clear();
            } else {
                current += c;
            }
        }
        if (!current.empty() && isFractionPart) {
            double fraction = std::atof(current.c_str());
            ComponentVector.emplace_back(Component, fraction);
            totalFraction += fraction;
        }
        if (std::abs(totalFraction - 100.0) > EPSILON) { // Allow minor floating-point errors
            G4cerr << "ERROR: Total fraction is " << totalFraction 
                << "% (must be exactly 100% ± " << EPSILON << ")" << G4endl;
            
        }
        else{
            for (const auto& pair : ComponentVector) {
                G4cout << "Component: " << pair.first << ", Fraction: " << pair.second << "%" << G4endl;
            }
            fYourDetector->CreateMaterial(matName,density,ComponentVector);
         }
        
    }
    
    if (command == fBoxCmd) {
        std::istringstream iss(newValue);
        G4String name, matName;
        G4double sizeX, sizeY, sizeZ, posX, posY, posZ;
        
        iss >> name >> matName >> sizeX >> sizeY >> sizeZ >> posX >> posY >> posZ;
        
        fYourDetector->SetSourceBox(
            name, matName,
            G4ThreeVector(sizeX, sizeY, sizeZ), 
            G4ThreeVector(posX, posY, posZ)
        );
    }
    if (command == fTubCmd) {
        std::istringstream iss(newValue);
        G4String name, matName;
        G4double radius, height, posX, posY, posZ;
        
        iss >> name >>matName >> radius >> height >> posX >> posY >> posZ;
        
        fYourDetector->SetSourceTube(
            name,  matName,
            radius, 
            height, 
            G4ThreeVector(posX, posY, posZ)
        );
    }
    if (command == fSampleHolderCmd) {
        std::istringstream iss(newValue);
        G4double  posX, posY, posZ;
        
        iss  >> posX >> posY >> posZ;
        
        fYourDetector->SetSampleHolderPosition(
            G4ThreeVector(posX*CLHEP::cm, posY*CLHEP::cm, posZ*CLHEP::cm)
        );
    }
    
}