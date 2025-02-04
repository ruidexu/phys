#!/usr/bin/env python
###############################################################################
# (c) Copyright 2000-2020 CERN for the benefit of the LHCb Collaboration      #
#                                                                             #
# This software is distributed under the terms of the GNU General Public      #
# Licence version 3 (GPL Version 3), copied verbatim in the file "COPYING".   #
#                                                                             #
# In applying this licence, CERN does not waive the privileges and immunities #
# granted to it by virtue of its status as an Intergovernmental Organization  #
# or submit itself to any jurisdiction.                                       #
###############################################################################
'''
Test loading various CommonParticles in the Analysis environment. Needs to be extended.
'''
__author__ = 'Juan Palacios juan.palacios@nikhef.nl'


def test_load_utils():
    from CommonParticles import Utils


def test_load_standard_basic_neutral():
    from CommonParticles import StandardBasicNeutral


def test_load_standard_basic_charged():
    from CommonParticles import StandardBasicCharged


def test_load_standard_basic():
    from CommonParticles import StandardBasic


def test_load_standard_intermediate():
    from CommonParticles import StandardIntermediate


def test_load_all():
    import CommonParticles
