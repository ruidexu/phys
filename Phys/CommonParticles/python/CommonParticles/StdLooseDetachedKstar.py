###############################################################################
from __future__ import print_function
# (c) Copyright 2000-2019 CERN for the benefit of the LHCb Collaboration      #
#                                                                             #
# This software is distributed under the terms of the GNU General Public      #
# Licence version 3 (GPL Version 3), copied verbatim in the file "COPYING".   #
#                                                                             #
# In applying this licence, CERN does not waive the privileges and immunities #
# granted to it by virtue of its status as an Intergovernmental Organization  #
# or submit itself to any jurisdiction.                                       #
###############################################################################
"""
Configuration file for Standard Loose Kstar2Kpi
"""

__author__ = 'Diego Martinez Santos, P. Koppenburg'
__date__ = '29/06/2009'

from Gaudi.Configuration import *
from Configurables import FilterDesktop
from CommonParticles.Utils import *
import GaudiKernel.SystemOfUnits as Units

###########################
# StdLooseDetachetKst2Kpi #
###########################

StdLooseDetachedKst2Kpi = FilterDesktop("StdLooseDetachedKst2Kpi")
StdLooseDetachedKst2Kpi.Inputs = ["Phys/StdVeryLooseDetachedKst2Kpi/Particles"]
StdLooseDetachedKst2Kpi.Code = "(MIPCHI2DV(PRIMARY)> 2.25)"
locations = updateDoD(StdLooseDetachedKst2Kpi)
