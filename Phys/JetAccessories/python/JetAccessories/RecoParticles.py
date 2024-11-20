###############################################################################
# (c) Copyright 2000-2019 CERN for the benefit of the LHCb Collaboration      #
#                                                                             #
# This software is distributed under the terms of the GNU General Public      #
# Licence version 3 (GPL Version 3), copied verbatim in the file "COPYING".   #
#                                                                             #
# In applying this licence, CERN does not waive the privileges and immunities #
# granted to it by virtue of its status as an Intergovernmental Organization  #
# or submit itself to any jurisdiction.                                       #
###############################################################################

# =============================================================================
__author__ = "Albert Bursche"
__date__ = " 2011-07-22 "
__version__ = "0.1"
# =============================================================================

# =============================================================================
"""
Select a track sample for jet reconstruction.
"""

from Configurables import FilterDesktop
SelectedTracks = FilterDesktop("FilteredPions")  #,OutputLevel = DEBUG)
SelectedTracks.InputLocations = [
    "/Event/Phys/StdNoPIDsPions/Particles", "Phys/StdNoPIDsDownPions/Particles"
]
SelectedTracks.Code = "(PT > 200*MeV) & (PERR2/(P*P) < 0.04) "
#SelectedTracks.Preambulo = [ "from LoKiProtoParticles.decorators import *"]
