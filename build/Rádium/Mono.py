{
 "cells": [
  {
   "cell_type": "code",
   "execution_count": null,
   "id": "ae51eb9f",
   "metadata": {
    "vscode": {
     "languageId": "plaintext"
    }
   },
   "outputs": [],
   "source": [
    "import numpy as np\n",
    "from pathlib import Path\n",
    "\n",
    "# --- Ra-226 gamma vonalak (Energy [keV], Intensity [%]) ---\n",
    "ra226_lines = np.array([\n",
    "    [186.10, 3.64],\n",
    "    [242.0, 7.12],\n",
    "    [295.22, 18.47],\n",
    "    [351.93, 35.1],\n",
    "    [609.31, 45.44],\n",
    "    [768.36, 4.889],\n",
    "    [934.06, 3.07],\n",
    "    [1120.3, 14.9],\n",
    "    [1238.1, 5.83],\n",
    "    [1377.7, 4.00],\n",
    "    [1408.0, 2.15],\n",
    "    [1509.2, 2.127],\n",
    "    [1661.274,1.046],\n",
    "    [1729.6, 2.92],\n",
    "    [1764.5, 15.29],\n",
    "    [1847.4, 2.11],\n",
    "    [2118.6, 1.17],\n",
    "    [2203.2, 4.92],\n",
    "    [2447.9, 1.545],\n",
    "])\n",
    "\n",
    "# --- Paths ---\n",
    "output_dir = Path(\"/home/aburucs/G4/Geant4/Gamma_Final/ELTE_HPGe_Public/build/Rádium/Mono\")\n",
    "output_dir.mkdir(parents=True, exist_ok=True)\n",
    "\n",
    "macro_dir = output_dir / \"macros\"\n",
    "macro_dir.mkdir(exist_ok=True)\n",
    "\n",
    "# --- Constants ---\n",
    "N_EVENTS = 1_000_000\n",
    "BASE_SEED = 25698\n",
    "base_macro_template = \"\"\"\\\n",
    "/run/numberOfThreads 8\n",
    "/HPGe/run/EdepHist Edep Deposited-Energy 3000 0 3.1\n",
    "/run/initialize\n",
    "/gps/pos/type Volume\n",
    "/gps/pos/shape Cylinder\n",
    "/gps/pos/radius 6.875 mm\n",
    "/gps/pos/halfz 3.5 mm\n",
    "/run/reinitializeGeometry\n",
    "\n",
    "/gps/particle gamma\n",
    "/gps/energy {energy:.3f} keV\n",
    "\n",
    "/gps/pos/centre 0 0 -5.350 cm\n",
    "/gps/ang/type iso\n",
    "/HPGe/det/setDeadLayer 2.5 1.5 2\n",
    "\n",
    "/HPGe/det/setCsSample 0.0 0.0 -5.350\n",
    "/HPGe/det/setSampleHolderPosition 0.0 0.0 -2.85\n",
    "/run/reinitializeGeometry\n",
    "/random/setSeeds {seed1} {seed2}\n",
    "/HPGe/run/OutputName {output_root}\n",
    "/run/beamOn {n_events}\n",
    "\"\"\"\n",
    "\n",
    "# --- Loop over all energies ---\n",
    "for i, (energy, intensity) in enumerate(ra226_lines):\n",
    "    seed1 = BASE_SEED + 2*i\n",
    "    seed2 = BASE_SEED + 2*i + 1\n",
    "    root_filename = output_dir / f\"Mono{int(energy)}.root\"\n",
    "    macro_filename = macro_dir / f\"Mono{int(energy)}.mac\"\n",
    "\n",
    "    macro_content = base_macro_template.format(\n",
    "        energy=energy,\n",
    "        seed1=seed1,\n",
    "        seed2=seed2,\n",
    "        output_root=root_filename,\n",
    "        n_events=N_EVENTS\n",
    "    )\n",
    "\n",
    "    with open(macro_filename, \"w\") as f:\n",
    "        f.write(macro_content)\n",
    "\n",
    "    print(f\"✅ Created macro for {energy:.1f} keV → {macro_filename.name}\")\n"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "id": "e8793834",
   "metadata": {
    "vscode": {
     "languageId": "plaintext"
    }
   },
   "outputs": [],
   "source": []
  }
 ],
 "metadata": {
  "language_info": {
   "name": "python"
  }
 },
 "nbformat": 4,
 "nbformat_minor": 5
}
