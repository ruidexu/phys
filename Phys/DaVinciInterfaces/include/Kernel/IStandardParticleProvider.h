/*****************************************************************************\
* (c) Copyright 2000-2019 CERN for the benefit of the LHCb Collaboration      *
*                                                                             *
* This software is distributed under the terms of the GNU General Public      *
* Licence version 3 (GPL Version 3), copied verbatim in the file "COPYING".   *
*                                                                             *
* In applying this licence, CERN does not waive the privileges and immunities *
* granted to it by virtue of its status as an Intergovernmental Organization  *
* or submit itself to any jurisdiction.                                       *
\*****************************************************************************/

#ifndef DAVINCIKERNEL_IStandardParticleProvider_H
#define DAVINCIKERNEL_IStandardParticleProvider_H 1

// from STL
#include <string>

// from Gaudi
#include "GaudiKernel/IAlgTool.h"

// Event Model
namespace LHCb {
  class Particle;
  class ParticleID;
  class ProtoParticle;
} // namespace LHCb

/** @class IStandardParticleProvider Kernel/IStandardParticleProvider.h
 *
 *  Interface to tool that provides pointer to 'standard' Particles
 *  for a given ProtoParticle and PID hypothesis
 *
 *  @author Chris Jones
 *  @date   26/02/2012
 */

class GAUDI_API IStandardParticleProvider : virtual public IAlgTool {

public:
  /// Declare the interface
  DeclareInterfaceID( IStandardParticleProvider, 1, 0 );

public:
  /** Get a Particle for a given ProtoParticle and PID
   *  @param proto Pointer to the ProtoParticle
   *  @param pid   The PID hypothesis
   *  @return Pointer to the associated standard Particle
   */
  virtual const LHCb::Particle* particle( const LHCb::ProtoParticle* proto, const LHCb::ParticleID& pid ) const = 0;
};

#endif // DAVINCIKERNEL_IStandardParticleProvider_H
