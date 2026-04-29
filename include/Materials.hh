#ifndef MATERIALTABLE_HH
#define MATERIALTABLE_HH

#include <G4Element.hh>
#include <G4Material.hh>
#include <G4MaterialPropertiesIndex.hh>
#include <G4NistManager.hh>
#include <G4Element.hh>
#include <G4SystemOfUnits.hh>


class Materials{
    public:
        Materials();
        ~Materials();

        G4Material* GetAirMaterial() { return this->airMaterial; }
        G4Material* GetLeadMaterial() { return this->leadMaterial; }
        G4Material* GetCopperMaterial() { return this->copperMaterial; }
        G4Material* GetConcreteMaterial() { return this->concreteMaterial; }
        G4Material* GetSteelMaterial() { return this->steelMaterial; }
        G4Material* GetAluminiumMaterial() { return this->aluminiumMaterial; }
        G4Material* GetMagnesiumOxidMaterial() { return this->magnesiumOxidMaterial; }
        G4Material* GetNatriumIodineMaterial() { return this->natriumIodineMaterial; }
        G4Material* GetWaterMaterial() { return this->waterMaterial; }
        G4Material* GetVacuumMaterial() { return this->vacuumMaterial; }

    private:
        
        G4NistManager* nistManager;
        G4Material *airMaterial, *leadMaterial, *copperMaterial, *concreteMaterial, 
                    *steelMaterial, *aluminiumMaterial, *magnesiumOxidMaterial, *natriumIodineMaterial, *waterMaterial, *vacuumMaterial;
        G4Element *elC, *elCr, *elNi, *elMn, *elFe, *elSi, *elMg, *elAl, *elO, *elH, *elCa, *elS, *elK, *elNa, *elI; 

        void InitialiseMaterials();
        void InitialiseElements();

        void BuildAirMaterial();
        void BuildLeadMaterial();
        void BuildCopperMaterial();
        void BuildConcreteMaterial();
        void BuildSteelMaterial();
        void BuildAluminiumMaterial();
        void BuildMagnesiumOxidMaterial();
        void BuildNatriumIodineMaterial();
        void BuildWaterMaterial();
        void BuildVacuumMaterial();

};


#endif