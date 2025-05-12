output_dir = "/home/aburucs/G4/Geant4/ELTE_Gamma_HPGe/build/SampleHolderTeszt/"
macro_filename = "EnergySweep.mac"
events_per_energy = 1_000_000


fine_start = 0.05
fine_end = 0.2
fine_step = 0.01

coarse_start = 0.2 + 1e-6  
coarse_end = 3.0
coarse_step = 0.1

with open(macro_filename, "w") as f:
    f.write("/run/numberOfThreads 6\n\n")
    f.write("/HPGe/run/EdepHist Edep Deposited-Energy 3000 0 3.1\n")
    f.write("\n/run/initialize\n\n")
    f.write("/gps/particle gamma\n")
    f.write("/gps/pos/type Point\n")
    f.write("/gps/pos/centre 0. 0. -12. cm\n")
    f.write("/gps/ang/type iso\n\n")

    
    e = fine_start
    while e <= fine_end + 1e-6:
        name = f"{e:.3f}".rstrip("0").rstrip(".")  
        f.write(f"/HPGe/run/OutputName {output_dir} Energy_{name}\n")
        f.write(f"/gps/energy {e:.3f} MeV\n")
        f.write(f"/run/beamOn {events_per_energy}\n\n")
        e += fine_step

        e = coarse_start
    while e <= coarse_end + 1e-6:
        name = f"{e:.1f}".rstrip("0").rstrip(".")  
        f.write(f"/HPGe/run/OutputName {output_dir} Energy_{name}\n")
        f.write(f"/gps/energy {e:.1f} MeV\n")
        f.write(f"/run/beamOn {events_per_energy}\n\n")
        e += coarse_step

print(f"Macro file '{macro_filename}' generated!")
