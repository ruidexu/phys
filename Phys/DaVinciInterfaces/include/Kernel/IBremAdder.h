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
#ifndef KERNEL_IBREMADDER_H
#define KERNEL_IBREMADDER_H 1

// Include files
// from STL
#include <string>
// from Gaudi
#include "GaudiKernel/IAlgTool.h"
// from LHCb
#include "CaloUtils/CaloMomentum.h"
#include "Event/CaloHypo.h"
#include "Event/Particle.h"

/** @class IBremAdder IBremAdder.h Kernel/IBremAdder.h
 *
 * Interface for BremStrahlung correction to electron particle
 *
 *  @author Olivier Deschamps
 *  @date   2006-10-25
 */
struct GAUDI_API IBremAdder : extend_interfaces<IAlgTool> {

  DeclareInterfaceID( IBremAdder, 4, 0 );

  // Add Brem
  virtual bool addBrem( LHCb::Particle* particle, bool force = false ) = 0;
  // Remove Brem
  virtual bool removeBrem( LHCb::Particle* particle, bool force = false ) = 0;
  // Add Brem on particle pair (removing overlap)
  virtual bool addBrem2Pair( LHCb::Particle* p1, LHCb::Particle* p2, bool force = false ) = 0;

  // helper methods
  virtual bool                     hasBrem( const LHCb::Particle* particle )                             = 0;
  virtual const LHCb::CaloMomentum bremMomentum( const LHCb::Particle* particle, std::string flag = "" ) = 0;
  virtual const std::pair<LHCb::CaloMomentum, LHCb::CaloMomentum>
  bremMomenta( const LHCb::Particle* p1, const LHCb::Particle* p2, std::string flag = "" ) = 0;
};

#endif // KERNEL_IBREMADDER_H
