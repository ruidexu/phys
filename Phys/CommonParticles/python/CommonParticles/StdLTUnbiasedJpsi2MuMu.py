#!/usr/bin/env python
from __future__ import print_function
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
# $Id: StdLTUnbiasedJpsi2MuMu.py,v 1.2 2009-06-28 12:02:54 gcowan Exp $
# =============================================================================
## @file  CommonParticles/StdLTUnbiasedJpsi2MuMu.py
#  configuration file for 'Standard lifetime unbiased Jpsi2MuMu'
#  @author Greig Cowan
#  @date 2009-05-21
# =============================================================================
"""
Configuration file for 'Standard lifetime unbiased Jpsi2MuMu'
"""
__author__ = "Greig Cowan"
__version__ = "CVS tag $Name: not supported by cvs2svn $, version $Revision: 1.2 $"
# =============================================================================
__all__ = ('StdLTUnbiasedJpsi2MuMu', 'locations')
# =============================================================================
from Gaudi.Configuration import *
from Configurables import FilterDesktop
from CommonParticles.Utils import *

## ============================================================================
StdLTUnbiasedJpsi2MuMu = FilterDesktop("StdLTUnbiasedJpsi2MuMu")
StdLTUnbiasedJpsi2MuMu.Inputs = ["Phys/StdLooseJpsi2MuMu/Particles"]
StdLTUnbiasedJpsi2MuMu.Code = "  (MINTREE('mu+'==ABSID, PT) > 500.*MeV)" \
                              "& (MINTREE('mu+'==ABSID, PIDmu) > -10.0)" \
                              "& (MAXTREE('mu+'==ABSID, PIDK) < 10.0)" \
                              "& (ADMASS('J/psi(1S)') < 50.*MeV)" \
                              "& (PT > 1000.*MeV)" \
                              "& (VFASPF(VCHI2) < 6.0)"

## configure Data-On-Demand service
locations = updateDoD(StdLTUnbiasedJpsi2MuMu)

## ============================================================================
if '__main__' == __name__:

    print(__doc__)
    print(__author__)
    print(__version__)
    print(locationsDoD(locations))
