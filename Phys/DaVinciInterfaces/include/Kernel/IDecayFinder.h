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
#ifndef TOOLS_IDECAYFINDER_H
#define TOOLS_IDECAYFINDER_H 1

// Include files
// from STL
#include <string>
#include <vector>

// from Gaudi
#include "GaudiKernel/IAlgTool.h"

#include "Event/Particle.h"

/** @class IDecayFinder IDecayFinder.h Kernel/IDecayFinder.h
 *
 *  Please see the file DecayFinder.h
 *  in the src directory of package Phys/DaVinciTools.
 *
 *  @author Olivier Dormond
 *  @date   23/04/2002
 */
struct GAUDI_API IDecayFinder : extend_interfaces<IAlgTool> {

  DeclareInterfaceID( IDecayFinder, 4, 0 );

  /// Get the decay string to find
  virtual const std::string& decay( void ) = 0;

  /// Get the decay string to find
  virtual StatusCode setDecay( const std::string& decay ) = 0;

  virtual std::string revert( void ) = 0;

  /// Does the described decay exist in the event?
  virtual bool hasDecay( const LHCb::Particle::ConstVector& event ) = 0;

  /// Does the described decay exist in the event?
  virtual bool hasDecay( const LHCb::Particle::Container& event ) = 0;

  /// Does the described decay exist in the event?
  virtual bool hasDecay( void ) = 0;

  virtual bool findDecay( const LHCb::Particle::ConstVector& event, const LHCb::Particle*& previous_result ) = 0;

  virtual bool findDecay( const LHCb::Particle::Container& event, const LHCb::Particle*& previous_result ) = 0;

  virtual bool findDecay( const LHCb::Particle*& previous_result ) = 0;

  virtual void descendants( const LHCb::Particle* head, LHCb::Particle::ConstVector& result, bool leaf = false ) = 0;

  virtual void decayMembers( const LHCb::Particle* head, LHCb::Particle::ConstVector& members ) = 0;

  virtual void
  decaySubTrees( const LHCb::Particle*                                                       head,
                 std::vector<std::pair<const LHCb::Particle*, LHCb::Particle::ConstVector>>& subtrees ) = 0;

  /// Templated hasDecay method working on particle container iterators.
  template <class PARTICLE>
  inline StatusCode hasDecay( PARTICLE begin, PARTICLE end ) {
    return StatusCode{hasDecay( LHCb::Particle::ConstVector( begin, end ) )};
  }

  /// Templated findDecay method working on particle container iterators.
  template <class PARTICLE>
  inline StatusCode findDecay( PARTICLE begin, PARTICLE end, const LHCb::Particle*& previous_result ) {
    return StatusCode{findDecay( LHCb::Particle::ConstVector( begin, end ), previous_result )};
  }
};

#endif // TOOLS_IDECAYFINDER_H
