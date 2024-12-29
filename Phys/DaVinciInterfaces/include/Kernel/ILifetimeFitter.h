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
#ifndef DAVINCIKERNEL_ILIFETIMEFITTER_H
#define DAVINCIKERNEL_ILIFETIMEFITTER_H 1

// Include files
#include "GaudiKernel/IAlgTool.h"

#include "Event/Particle.h"
#include "Event/Vertex.h"

/** @class ILifetimeFitter
 *  Interface Class for lifetime constrained vertex fit.
 *
 *  @author G. Raven
 *  @date   05/07/2002
 */

struct GAUDI_API ILifetimeFitter : extend_interfaces<IAlgTool> {

  DeclareInterfaceID( ILifetimeFitter, 2, 0 );

  /// Get lifetime
  /// inputs: Vertex corresponding to the assumed production point
  ///         LHCb::Particle itself
  /// output: resulting lifetime and error, chisq.
  ///         The lifetime is returned in nanoseconds.
  virtual StatusCode fit( const LHCb::VertexBase&, const LHCb::Particle&, double& lifetime, double& error,
                          double& chisq ) const = 0;
};

#endif // DAVINCIKERNEL_ILIFETIMEFITTER_H
