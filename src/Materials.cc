#include "Materials.hh"
#include <CLHEP/Units/SystemOfUnits.h>
#include <G4Element.hh>
#include <G4Material.hh>



Materials::Materials() {
    // Initialize the NIST manager, and build the materials
    this->nistManager = G4NistManager::Instance();
    this->InitialiseElements();
    this->InitialiseMaterials();
}

void Materials::InitialiseElements() {
    this->elC = new G4Element("Carbon", "C", 6., 12.011 * g/mole);
    this->elCr = new G4Element("Chromium", "Cr", 24., 51.9961 * g/mole);
    this->elNi = new G4Element("Nickel", "Ni", 28., 58.6934 * g/mole);
    this->elMn = new G4Element("Manganese", "Mn", 25., 54.938 * g/mole);
    this->elFe = new G4Element("Iron", "Fe", 26., 55.845 * g/mole);
    this->elSi = new G4Element("Silicon", "Si", 14., 28.085 * g/mole);
    this->elMg = new G4Element("Magnesium", "Mg", 12., 24.305 * g/mole);
    this->elAl = new G4Element("Aluminium", "Al", 13., 26.9815384 * g/mole);
    this->elO = new G4Element("Oxygen", "O", 8., 15.999 * g/mole);
    this->elH = new G4Element("Hydrogen", "H", 1., 1.008 * g/mole);
    this->elCa = new G4Element("Calcium", "Ca", 20., 40.078 * g/mole);
    this->elS = new G4Element("Sulfur", "S", 16., 32.06 * g/mole);
    this->elK = new G4Element("Potassium", "K", 19., 39.098 * g/mole);
    this->elNa = new G4Element("Sodium", "Na", 11., 22.989768 * g/mole);
    this->elI = new G4Element("Iodine", "I", 53., 126.90447 * g/mole);
}

void Materials::InitialiseMaterials() {
    this->BuildAirMaterial();
    this->BuildLeadMaterial();
    this->BuildCopperMaterial();
    this->BuildConcreteMaterial();
    this->BuildSteelMaterial();
    this->BuildAluminiumMaterial();
    this->BuildMagnesiumOxidMaterial();
    this->BuildNatriumIodineMaterial();
    this->BuildWaterMaterial();
    this->BuildVacuumMaterial();
}

void Materials::BuildAirMaterial() {
    // Build the air material using NIST manager
    this->airMaterial = this->nistManager->FindOrBuildMaterial("G4_AIR");
    // Giving a warning if air material is not found
    if (!this->airMaterial) {
        G4cerr << "Error: Could not find or build G4_AIR material! Aborting now. \n";
    }
}

void Materials::BuildLeadMaterial() {
    // Build the lead material using NIST manager
    this->leadMaterial = this->nistManager->FindOrBuildMaterial("G4_Pb");
    // Giving error message if lead material is not found
    if (!this->leadMaterial) {
        G4cerr << "Error: Could not find or build G4_Pb material! Aborting now. \n";
    }
}

void Materials::BuildCopperMaterial() {
    // Build the copper material using NIST manager
    this->copperMaterial = this->nistManager->FindOrBuildMaterial("G4_Cu");
    // Giving error message if copper material is not found
    if (!this->copperMaterial) {
        G4cerr << "Error: Could not find or build G4_Cu material! Aborting now.\n";
    }
}

void Materials::BuildConcreteMaterial() {
    this->concreteMaterial = new G4Material("Concrete", 2.35 * g/cm3, 10);
    this->concreteMaterial->AddElement(this->elO, 49.9 * perCent);
    this->concreteMaterial->AddElement(this->elSi, 31.6 * perCent);
    this->concreteMaterial->AddElement(this->elCa, 8.3 * perCent);
    this->concreteMaterial->AddElement(this->elAl, 4.6 * perCent);
    this->concreteMaterial->AddElement(this->elK, 1.9 * perCent);
    this->concreteMaterial->AddElement(this->elNa, 1.7 * perCent);
    this->concreteMaterial->AddElement(this->elFe, 1.2 * perCent);
    this->concreteMaterial->AddElement(this->elH, 0.5 * perCent);
    this->concreteMaterial->AddElement(this->elMg, 0.2 * perCent);
    this->concreteMaterial->AddElement(this->elS, 0.1 * perCent);
}

void Materials::BuildSteelMaterial() {
    this->steelMaterial = new G4Material("Steel143", 8 * g/cm3, 4);
    this->steelMaterial->AddElement(this->elC, 0.05 * perCent);
    this->steelMaterial->AddElement(this->elCr, 18.0 * perCent);
    this->steelMaterial->AddElement(this->elNi, 9.0 * perCent);
    this->steelMaterial->AddElement(this->elFe, 72.95 * perCent); 
}

void Materials::BuildAluminiumMaterial() {
    this->aluminiumMaterial = new G4Material("AlMgSi", 2.7 * g/cm3, 5);
    this->aluminiumMaterial->AddElement(this->elSi, 1.0 * perCent);
    this->aluminiumMaterial->AddElement(this->elMn, 0.7 * perCent);
    this->aluminiumMaterial->AddElement(this->elMg, 0.9 * perCent);
    this->aluminiumMaterial->AddElement(this->elFe, 0.5 * perCent);
    this->aluminiumMaterial->AddElement(this->elAl, 96.9 * perCent);
}

void Materials::BuildMagnesiumOxidMaterial() {
    this->magnesiumOxidMaterial = new G4Material("MagnesiumOxide", 3.6 * g/cm3, 2);
    this->magnesiumOxidMaterial->AddElement(this->elMg, 1);
    this->magnesiumOxidMaterial->AddElement(this->elO, 1);
}

void Materials::BuildNatriumIodineMaterial() {
    this->natriumIodineMaterial = new G4Material("NatriumIodine", 3.67 * g/cm3, 2);
    this->natriumIodineMaterial->AddElement(this->elNa, 1);
    this->natriumIodineMaterial->AddElement(this->elI, 1);
}

void Materials::BuildWaterMaterial() {
    this->waterMaterial = new G4Material("Water", 1.0 * g/cm3, 2);
    this->waterMaterial->AddElement(this->elH, 2);
    this->waterMaterial->AddElement(this->elO, 1);
}

void Materials::BuildVacuumMaterial() {
    this->vacuumMaterial = this->nistManager->FindOrBuildMaterial("G4_Galactic");
    // Giving a warning if vacuum material is not found
    if (!this->vacuumMaterial) {
        G4cerr << "Error: Could not find or build G4_Galactic material! Aborting now. \n";
    }
}

Materials::~Materials() {
    // Clean up the materials
    //delete this->nistManager; maybe it isn't needed, idk yet
    //delete this->airMaterial;
    //delete this->leadMaterial;
    //delete this->copperMaterial;
    
    delete this->concreteMaterial;
    delete this->steelMaterial;
    delete this->aluminiumMaterial;
    delete this->magnesiumOxidMaterial;
    delete this->natriumIodineMaterial;
    delete this->waterMaterial;

    delete this->elC;
    delete this->elCr;
    delete this->elNi;
    delete this->elMn;
    delete this->elFe;
    delete this->elSi;
    delete this->elMg;
    delete this->elAl;
    delete this->elO;
    delete this->elH;
    delete this->elCa;
    delete this->elS;
    delete this->elK;
    delete this->elNa;
    delete this->elI;
}