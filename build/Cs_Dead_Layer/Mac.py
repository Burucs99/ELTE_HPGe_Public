import os

def generate_macro(output_file, distances_cm, dead_layers, n_events=1000000, seed_start=25698):
    seeds = seed_start
    lines = []

    # Header
    lines.append("# /control/execute OutPutDirectory/Cs_DeadLayer_Series.mac")
    lines.append("/run/numberOfThreads 8")
    lines.append("/HPGe/run/EdepHist Edep Deposited-Energy 3000 0 3.1")
    lines.append("/run/initialize")
    lines.append("/gps/pos/type Volume")
    lines.append("/gps/pos/shape Cylinder")
    lines.append("/gps/pos/radius 0.15875 cm")
    lines.append("/gps/pos/halfz 0.001 mm")
    lines.append("/run/reinitializeGeometry\n")

    # Cs-137 gamma runs
    lines.append("/gps/particle gamma")
    lines.append("/gps/energy 661.7 keV\n")

    base_dir = "/home/aburucs/G4/Geant4/Gamma_Final/ELTE_HPGe_Public/build/Cs_Dead_Layer/Data"

    for D in distances_cm:
        for offset in [0.0]:  # cm
            pos = D + offset
            sample_holder = D - 2.5  # cm

            for top, side, inside in dead_layers:
                # Mappa struktúra: D{dist}cm/T{top}_S{side}_I{inside}
                dir_name = f"D{D:.1f}cm/T{top}_S{side}_I{inside}"
                output_dir = os.path.join(base_dir, dir_name)
                os.makedirs(output_dir, exist_ok=True)

                lines.append(f"# --- Dead layer config: top={top}mm side={side}mm inside={inside}mm ---")
                lines.append(f"/HPGe/det/setDeadLayer {top} {side} {inside}")
                lines.append("/run/reinitializeGeometry")

                lines.append(f"/gps/pos/centre 0 0 -{pos:.3f} cm")
                lines.append(f"/gps/ang/type iso")
                lines.append(f"/HPGe/det/setCsSample 0.0 0.0 -{pos:.3f}")
                lines.append(f"/HPGe/det/setSampleHolderPosition 0.0 0.0 -{sample_holder:.4f}")
                lines.append("/run/reinitializeGeometry")

                # ismétlések külön seed-del
                for rep in [1]:
                    lines.append(f"/random/setSeeds {seeds} {seeds+1}")
                    output_name = os.path.join(
                        output_dir,
                        f" Cs_DL_T{top}_S{side}_I{inside}_{pos:.1f}cm_{rep}_.root"
                    )
                    lines.append(f"/HPGe/run/OutputName {output_name}")
                    A = int(n_events + (1e5 * (D - 3)))
                    lines.append(f"/run/beamOn {A}\n")
                    seeds += 2

    # Write macro file
    with open(output_file, "w") as f:
        f.write("\n".join(lines))
    print(f"✅ Macro file written to: {os.path.abspath(output_file)}")


if __name__ == "__main__":
    # Távolságok (cm)
    distances = [0.0+0.235]
   

    # Dead layer konfigurációk (top, side, inside) [mm]
    """ dead_layers = [
        (3,1,1), (3,2,1), (3,3,1),
        (4,1,1), (4,2,1), (4,3,1), (4,4,1),
        (5,2,1), (5,3,1), (5,4,1), (5,5,1)
    ] """
    """ dead_layers=[
        (4 ,1 ,2), (4,1,3),
        (3 ,2, 2), (3, 2 ,3),
        (3.5 , 1, 1), (3.5 ,1.5,1),
        (4, 1.5 , 1)
    ] """

    """ dead_layers=[
        (3.0,1,2),(2.5,1,2),
        (2,1,2),(1.5,1,2)
    ] """
    dead_layers=[]

    generate_macro("Cs_DeadLayer_Series_inner+_FINAL_0.mac", distances, dead_layers)
"""  1. T4_S1_I1        RMSE =   2.84% (átlag 4 távolságra)
 2. T3_S2_I1        RMSE =   3.93% (átlag 4 távolságra) """