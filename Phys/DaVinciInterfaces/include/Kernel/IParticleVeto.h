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
#ifndef IPARTICLEVETO_H
#define IPARTICLEVETO_H 1

// Include files
// from STL
#include <string>
#include <vector>
// from Gaudi
#include "Event/Particle.h"
#include "GaudiKernel/IAlgTool.h"

static const InterfaceID IID_IParticleVeto( "IParticleVeto", 1, 0 );

/** @class IParticleVeto IParticleVeto.h
 *
 *
 *  @author Olivier Deschamps
 *  @date   2012-04-25
 */
struct IParticleVeto : extend_interfaces<IAlgTool> {
  // Return the interface ID
  static const InterfaceID& interfaceID() { return IID_IParticleVeto; }

  virtual bool foundOverlap( const LHCb::Particle* particle, std::vector<std::string> containers, int mode = 0 ) = 0;
  virtual bool foundOverlap( const LHCb::Particle* particle, std::string container, int mode = 0 )               = 0;
  virtual bool foundOverlap( const LHCb::Particle* particle, const LHCb::Particle* p2, int mode = 0 )            = 0;
};
#endif // IPARTICLEVETO_H
