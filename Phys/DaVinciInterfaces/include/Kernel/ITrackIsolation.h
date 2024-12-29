/*****************************************************************************\
* (c) Copyright 2000-2024 CERN for the benefit of the LHCb Collaboration      *
*                                                                             *
* This software is distributed under the terms of the GNU General Public      *
* Licence version 3 (GPL Version 3), copied verbatim in the file "COPYING".   *
*                                                                             *
* In applying this licence, CERN does not waive the privileges and immunities *
* granted to it by virtue of its status as an Intergovernmental Organization  *
* or submit itself to any jurisdiction.                                       *
\*****************************************************************************/
#ifndef KERNEL_ITRACKISOLATION_H
#define KERNEL_ITRACKISOLATION_H 1

// Include files

// from STL
#include <string>

// from Gaudi
#include "GaudiKernel/IAlgTool.h"

#include <Event/Particle.h>
#include <Event/ProtoParticle.h>
#include <Event/Track.h>

/**
 *  @class ITrackIsolation ITrackIsolation.h Kernel/ITrackIsolation.h
 *
 *  Abstract Interface of the Track Isolation tools
 *
 *  @author Simone Bifani simone.bifani@cern.ch
 *  @date   2010-03-17
 */

struct GAUDI_API ITrackIsolation : extend_interfaces<IAlgTool> {

  DeclareInterfaceID( ITrackIsolation, 1, 0 );

  /**
   *  trackConeMultiplicity method for the evaluation of
   *  the number of tracks/particles in a given range
   *  within a cone of given radius with respect to the
   *  seed track/protoparticle/particle
   *
   *  The cone radius is defined as the difference in Eta
   *  and Phi between the seed track and a track in the
   *  range (same definition as in TupleToolTrackIsolation):
   *
   *  R = sqrt (delta_Eta^2 + delta_Phi^2)
   *
   *  The method returns the track multiplicity
   */

  virtual unsigned int trackConeMultiplicity( const LHCb::Track* seedTrack, const LHCb::Track::Range& eventTracks,
                                              double coneRadius ) const = 0;

  virtual unsigned int trackConeMultiplicity( const LHCb::ProtoParticle* seedProtoParticle,
                                              const LHCb::Track::Range& eventTracks, double coneRadius ) const = 0;

  virtual unsigned int trackConeMultiplicity( const LHCb::Particle* seedParticle, const LHCb::Track::Range& eventTracks,
                                              double coneRadius ) const = 0;

  virtual unsigned int trackConeMultiplicity( const LHCb::ProtoParticle*   seedProtoParticle,
                                              const LHCb::Particle::Range& eventParticles,
                                              double                       coneRadius ) const = 0;

  virtual unsigned int trackConeMultiplicity( const LHCb::Particle*        seedParticle,
                                              const LHCb::Particle::Range& eventParticles,
                                              double                       coneRadius ) const = 0;
};

#endif // KERNEL_ITRACKISOLATION_H
