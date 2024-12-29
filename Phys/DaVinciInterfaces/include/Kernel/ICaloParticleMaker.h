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
#ifndef DAVINCIKERNEL_ICALOPARTICLEMAKER_H
#define DAVINCIKERNEL_ICALOPARTICLEMAKER_H 1

// Include files
// from STL
#include <string>

// from Gaudi
#include "Event/Particle.h"
#include "GaudiKernel/GenericVectorTypes.h"
#include "GaudiKernel/IAlgTool.h"
#include "GaudiKernel/SymmetricMatrixTypes.h"

// Forward declarations
namespace LHCb {
  class Vertex;
}

/** @class ICaloParticleMaker ICaloParticleMaker.h Kernel/ICaloParticleMaker.h
 *  Interface class to make Particles from other classes
 *  (e.g. ProtoParticles).
 *  This tools is internally used by the PhysDesktop.
 *
 *  @author Jose Helder Lopes
 *  @date   22/04/2002
 */

struct GAUDI_API ICaloParticleMaker : extend_interfaces<IAlgTool> {

  DeclareInterfaceID( ICaloParticleMaker, 2, 0 );

  /// Dispatch the making of particles
  virtual StatusCode makeParticles( LHCb::Particle::Vector& parts )                       = 0;
  virtual void       setPoint( const Gaudi::XYZPoint cov )                                = 0;
  virtual void       setPoint( const Gaudi::XYZPoint pos, const Gaudi::SymMatrix3x3 cov ) = 0;
  virtual void       setPoint( const LHCb::Vertex* vert )                                 = 0;
};

#endif // DAVINCIKERNEL_ICALOPARTICLEMAKER_H
