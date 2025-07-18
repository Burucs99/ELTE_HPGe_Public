import math
from pathlib import Path

def generate_angle_macro(
    distance_cm: float,
    output_path: str,
    num_bins: int = 200,
    beamOn_count: int = 10000,
    base_seed: int = 21340
):
    detector_front_z_cm = 0.5
    radius_mm = 24.0
    distance_mm = distance_cm * 10.0
    source_z_cm = detector_front_z_cm - distance_cm

    beta_max = math.atan(radius_mm / distance_mm)

    macro_lines = [
        "/run/numberOfThreads 6",
        "/HPGe/run/EdepHist Edep Deposited-Energy 3000 0 1.4",
        "/run/initialize",
        "",
        "/gps/particle gamma",
        "/gps/pos/type Point",
        f"/gps/pos/centre 0 0 {source_z_cm:.4f} cm",
        "",
    ]

    for i in range(num_bins):
        beta_i = beta_max * i / (num_bins - 1)
        sin_beta = math.sin(beta_i)
        cos_beta = math.cos(beta_i)

        for j, energy in enumerate([1.1732, 1.3325]):
            seed_offset = i * 2 + j
            seed1 = base_seed + seed_offset
            seed2 = base_seed + seed_offset + 1
            energy_tag = "1.17" if energy < 1.2 else "1.33"
            beta_tag = f"Beta_{i}"

            macro_lines.extend([
                f"/gps/direction {sin_beta:.12f} 0 {cos_beta:.12f}",
                f"/gps/energy {energy:.6f} MeV",
                f"/random/setSeeds {seed1} {seed2}",
                f"/HPGe/run/OutputName {output_path}/{energy_tag}/ {beta_tag}",
                f"/run/beamOn {beamOn_count}",
                ""
            ])

    return "\n".join(macro_lines)

distance_cm = 0.5
output_path = "/home/aburucs/G4/Geant4/Gamma_Beszámoló/ELTE_HPGe_Public/build/OutPutDirectory/distance_0.5"
num_bins = 200
beamOn_count = 100
base_seed = 50000

macro_text = generate_angle_macro(distance_cm, output_path, num_bins, beamOn_count, base_seed)

Path("source_distance0.5.mac").write_text(macro_text)
print("✅ Macro file 'source_distance0.5.mac' generated.")
