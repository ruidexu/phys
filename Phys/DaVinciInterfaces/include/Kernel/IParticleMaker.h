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
// $Id: IParticleMaker.h,v 1.2 2009-08-04 09:45:31 jpalac Exp $
#ifndef DAVINCIKERNEL_IPARTICLEMAKER_H
#define DAVINCIKERNEL_IPARTICLEMAKER_H 1

// Include files
// from STL
#include <string>

// from Gaudi
#include "Event/Particle.h"
#include "GaudiKernel/IAlgTool.h"

/** @class IParticleMaker IParticleMaker.h Kernel/IParticleMaker.h
 *  Interface class to make Particles from other classes
 *  (e.g. ProtoParticles).
 *  This tools is internally used by the PhysDesktop.
 *
 *  @author Jose Helder Lopes
 *  @date   22/04/2002
 */

class GAUDI_API IParticleMaker : virtual public IAlgTool {

public:
  DeclareInterfaceID( IParticleMaker, 2, 0 );

public:
  /// Dispatch the making of particles
  virtual StatusCode makeParticles( LHCb::Particle::ConstVector& parts ) = 0;
};
#endif // DAVINCIKERNEL_IPARTICLEMAKER_H
