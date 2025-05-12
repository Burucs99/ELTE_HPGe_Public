# ELTE-HPGe
Geant4 simulation for ELTE HPGe detector, for nuclear waste studies.


# ELTE-HPGe

Geant4 szimuláció az ELTE HPGe detektorához, nukleáris hulladék vizsgálati célokra.

---

## Telepítés és bevezető – Geant4 + ROOT + CLHEP

---

### 0. Lépés – Olvasd el ezt (README a neve)
#### 0.1. Lépés – Olvasd el a hivatalos telepítő oldalakat is kérlek 

---

### 1. Lépés – Nézd meg a Linux verziódat:

```bash
cat /etc/os-release

# ROOT letöltése innen : https://root.cern/install/
# Olvasd el milyen Linux verziód van és ahoz igazítsd a telepítést
# Például Ubuntu-ra futtasd először :
```bash
sudo apt install binutils cmake dpkg-dev g++ gcc libssl-dev git libx11-dev \
libxext-dev libxft-dev libxpm-dev python3 libtbb-dev libvdt-dev libgif-dev



# Töltsük le innen a ROOT verziót a megfelelő rendszerhez https://root.cern/releases/release-63212/
# Pl : jobb klikk a linkre, copy link, és írjuk be terminálba 
wget https://root.cern/download/root_v6.32.12.Linux-ubuntu20.04-x86_64-gcc9.4.tar.gz
# Bontsuk ki
tar xzfv root_v6.32.12.Linux-ubuntu20.04-x86_64-gcc9.4.tar.gz 
## Source it
source root/bin/thisroot.sh

# Opció ezt ajánlom : Sourcoljuk ki a thisroot.sh hogy mindenhonnan elérhető legyen
# Így https://askubuntu.com/questions/17536/how-do-i-create-a-permanent-bash-alias 
# Vagyis valami ilyesmit tegyünk a .bashrc-be : alias thisroot="source /home/aburucs/ROOT/root/bin/thisroot.sh"
# Értelemszerűen ez legyen az ahol a te ROOT-od van telepítve
# Próbáljuk ki hogy működik e :
root -l
# Geant4 
A következő lépések szükségesek Linux rendszeren:

```bash
sudo apt-get update
sudo apt install cmake
sudo apt install cmake-curses-gui
sudo apt-get install libxmu-dev libxi-dev libx11-dev libxt-dev
sudo apt-get install qt3d5-dev qt3d5-dev-tools
sudo apt-get install xorg openbox
### Érdemes csinálni egy fő mappát ahova mindent telepítünk majd G4-el kapcsolatban.
### Pl 
mkdir G4
### Ekkor ez lesz ahová 3 mappa fog kerülni 1.  geant4-v11.3.2 2.  geant4-v11.3.2-build 3. geant4-v11.3.2-install
### Töltsük le innen https://geant4.web.cern.ch/download/11.3.2.html
wget https://geant4.web.cern.ch/download/11.3.2.html
tar xzfv geant4-v11.3.2.tar.gz
## build & install 
mkdir geant4-v11.3.2-build
cd geant4-v11.3.2-build
ccmake ../geant4-v11.3.2

# A ccmake konfigurációban állítsd be: 

CMAKE_INSTALL_PREFIX = /elérési/út/a/geant4-hez/geant4-v11.3.2-install
GEANT4_INSTALL_MULTITHREAD = ON
GEANT4_INSTALL_DATA = ON
GEANT4_USE_QT = ON
GEANT4_USE_RAYTRACER_X11 = ON
### Configure a c betűvel és generáld a g-vel alul írja
# Fordíts le 
make -j$(nproc)
make install
# Környezeti sourcolás itt 
cd geant4-v11.3.2-install/share/Geant4/geant4make
. geant4make.sh
### Opció : Csináld meg ezt is .bashrc-ben aliasnak 
## Próbáld ki a Geant4-et
cd geant4-v11.3.2/examples/basic/B1
mkdir build
cd build
cmake ..
make
./exampleB1
#Minden projekt elött érdemes 
. /geant4-v11.3.2-install/share/Geant4/geant4make/geant4make.sh
source root/bin/thisroot.sh

# CLHEP ez nem biztos hogy kell de kényelmesebb lehet tőle
# Innen :https://proj-clhep.web.cern.ch/proj-clhep/clhep23.html
# Lehet külön mappába, clhepnek külső build mappa kell
wget https://proj-clhep.web.cern.ch/proj-clhep/dist1/clhep-2.4.7.1.tgz
tar xzfv clhep-2.4.7.1.tgz
mkdir clhep-build
cd clhep-build
ccmake ../2.4.7.1/CLHEP
# configure és generálás
make -j$(nproc)
make install
# Ezt bele rakhatjuk a  Geant4-be belemegyünk a ccmake-be mint az előbb és
# megnyomjuk a t-betűt megkeressük ezt és beállítjuk ahol a mi CLHEP-ünk van:
CLHEP_DIR                        /usr/local/clhep/lib/CLHEP-2.4.7.1
# utána 
make -j$(nproc)
make install