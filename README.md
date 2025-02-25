# Constituent Subtractor Modules for DaVinci
## Modified Routines
1. `Phys/DaVinciInterfaces/src/DaVinciInterfaces.cpp`
2. `Phys/DaVinciInterfaces/include/Kernel/IConstituentSubtractor.h`
3. `Phys/DaVinciInterfaces/dict/DaVinciInterfacesDict.h`
4. `Phys/DaVinciInterfaces/dict/DaVinciInterfacesDict.xml`
5. `Phys/DaVinciInterfaces/CMakeLists.txt`
6. `Phys/LoKiJets/CMakeLists.txt`
7. `Phys/LoKiJets/src/LoKiConstituentSub.cpp`
8. `Phys/LoKiJets/src/LoKiConstituentSub.h`
9. `Phys/LoKiJets/src/LoKiFastJetMaker.cpp`
10. `Phys/LoKiJets/src/LoKiFastJetMaker.h`
11. `Phys/JetAccessories/src/HltJetBuilder.cpp`
12. `Phys/JetAccessories/python/JetAccessories/HltJetConf.py`
## Remark
The core constituent subtractor module involves `Phys/LoKiJets/src/LoKiConstituentSub.cpp` `Phys/LoKiJets/src/LoKiConstituentSub.h` and `Phys/DaVinciInterfaces/include/Kernel/IConstituentSubtractor.h`.

The routine takes a raw pseudo jet vector with particle information and outputs a subtracted pseudo jet vector of the particle. The routine is intended to be used for event-wise background subtraction.

However, with proper modification in the src code and the implementation in the jet builder, one can also achieve jet-wise subtraction.
