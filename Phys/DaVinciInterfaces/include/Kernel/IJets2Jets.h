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
#ifndef DAVINCIKERNEL_IJETS2JETS_H
#define DAVINCIKERNEL_IJETS2JETS_H 1

// ============================================================================
// Include files
// ============================================================================
// STD & STL
// ============================================================================
#include <string>
#include <vector>
// ============================================================================
// GaudiKernel
// ============================================================================
#include "GaudiKernel/IAlgTool.h"
// ============================================================================
// forward decalrations
// ============================================================================
#include "Event/Particle.h"
#include "Relations/RelationWeighted1D.h"
// ============================================================================
/** @class IJets2Jets IJets2Jets.h Kernel/IJets2Jets.h
 *
 *  The abstract interface for tools that match a set of jets to another
 *  It returns a relation table between both sets, links being weighted
 *  by the fraction of energy of the jet1 contained in jet2 at the level
 *  of their constituents.
 *
 *  @author Victor Coco Victor.Coco@cern.ch
 *  @date   2009-10-30
 */

struct GAUDI_API IJets2Jets : extend_interfaces<IAlgTool> {
  // ==========================================================================
  /// interface machinery
  DeclareInterfaceID( IJets2Jets, 1, 0 );
  // ==========================================================================
  /// the actual type of  container of jets
  typedef LHCb::Particle::ConstVector Jets;
  // ==========================================================================
  /// the actual type of relation table between jets
  typedef LHCb::RelationWeighted1D<LHCb::Particle, LHCb::Particle, double> Table;

  /// the main method: making relation weighted between two sets of jets
  virtual void makeRelation( const Jets& jets1, const Jets& jets2, Table& table ) const = 0;
};
// ============================================================================
// The END
// ============================================================================
#endif // DAVINCIKERNEL_IJETMAKER_H
