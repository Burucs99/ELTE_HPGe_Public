macro_filename = "zscan_macro.mac"
output_dir = "/home/aburucs/G4/Geant4/ELTE_Gamma_HPGe/build/output_Cobalt_Veto/"
initial_z = -1  
final_z = -15   
z_step = -1     
initial_events = 1_000_000
event_step = 100_000

with open(macro_filename, "w") as f:
    # Static setup
    f.write("/run/numberOfThreads 6\n")
    f.write("/HPGe/run/EdepHist Edep Deposited-Energy 3000 0 3.1\n")
    f.write("/HPGe/run/EdepHist Edep_veto_3 Deposited-Energy 3000 0 3.1\n")
    f.write("/HPGe/run/EdepHist Edep_veto_6 Deposited-Energy 3000 0 3.1\n")
    f.write("/HPGe/run/EdepHist Edep_veto_9 Deposited-Energy 3000 0 3.1\n")
    f.write("/HPGe/run/EdepHist Edep_veto_12 Deposited-Energy 3000 0 3.1\n")
    f.write("/run/initialize\n\n")

    # Ion setup (same for all)
    f.write("/gps/particle ion\n")
    f.write("/gps/ion 27 60 0 0\n")
    f.write("/gps/energy 0.0 eV\n")
    f.write("/gps/pos/type Volume\n")
    f.write("/gps/pos/shape Para\n")
    f.write("/gps/pos/halfx 0.05 cm\n")
    f.write("/gps/pos/halfy 0.05 cm\n")
    f.write("/gps/pos/halfz 0.05 cm\n\n")

    # Material definition (once)
    f.write("/HPGe/det/CreateIsotope Co60 27 60 59.933816\n")
    f.write("/HPGe/det/CreateElement Cobalt Co Co60:100\n")
    f.write("/HPGe/det/CreateMaterial Cobalt 8.9 Cobalt:100\n\n")

    # Loop over z positions
    for i, z in enumerate(range(initial_z, final_z - 1, z_step), start=1):
        num_events = initial_events + (i - 1) * event_step
        output_name = f"{output_dir}Zheight_{i}"
        z_cm = z
        box_z_cm = z * 10  # Box z position in mm

        f.write(f"/gps/pos/centre 0 0 {z_cm} cm\n")
        f.write(f"/HPGe/det/setSourceBox CobaltBox Cobalt 0.1 0.1 0.1 0 0 {box_z_cm}\n")
        f.write(f"/HPGe/run/OutputName {output_name}\n")
        f.write("/run/reinitializeGeometry\n")
        f.write(f"/run/beamOn {num_events}\n\n")

print(f"Macro '{macro_filename}' created successfully.")
