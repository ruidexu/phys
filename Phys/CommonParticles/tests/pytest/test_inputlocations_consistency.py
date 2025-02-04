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
Test loading various CommonParticles in the Stripping environment. Needs to be extended.
'''
__author__ = 'Juan Palacios juan.palacios@nikhef.nl'


def test():
    from CommonParticles import StandardBasic, StandardIntermediate

    outputLocations = list(StandardBasic.locations) + list(
        StandardIntermediate.locations)

    algs = list(StandardBasic.locations.values()) + list(
        StandardIntermediate.locations.values())

    for alg in algs:
        if not hasattr(alg, 'Inputs'): continue
        for inputLocation in alg.Inputs:
            assert inputLocation in outputLocations, \
                      'Algorithm {}.Input {} not in output locations'.format(alg, inputLocation)
