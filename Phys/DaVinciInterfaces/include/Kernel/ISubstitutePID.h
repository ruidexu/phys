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
// $Id: $
#ifndef KERNEL_ISUBSTITUTEPID_H
#define KERNEL_ISUBSTITUTEPID_H 1

// from STL
#include <string>

// from Gaudi
#include "Event/Particle.h"
#include "GaudiKernel/IAlgTool.h"
// ==========================================================================

static const InterfaceID IID_ISubstitutePID( "ISubstitutePID", 1, 0 );

/** @class ISubstitutePID ISubstitutePID.h Kernel/ISubstitutePID.h
 *
 *  Interface for SubstitutePIDTool
 *
 * @see SubstitutePIDTool
 * @see SubstitutePID
 *
 *  @author Patrick Koppenburg
 *  @date   2011-12-07
 */
class ISubstitutePID : virtual public IAlgTool {

public:
  /// Type for the subsitution map
  typedef std::map<std::string, std::string> SubstitutionMap;

  /// Return the interface ID
  static const InterfaceID& interfaceID() { return IID_ISubstitutePID; }

public:
  /// substitute PID for particles
  virtual StatusCode substitute( const LHCb::Particle::ConstVector& input, LHCb::Particle::ConstVector& output ) = 0;

  /// perform the actual substitution
  virtual unsigned int substitute( LHCb::Particle* p ) = 0;

  /// decode the substitution code
  virtual StatusCode decodeCode( const SubstitutionMap& newMap ) = 0;
};

#endif // KERNEL_ISUBSTITUTEPID_H
