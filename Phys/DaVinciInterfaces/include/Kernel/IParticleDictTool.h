/*****************************************************************************\
* (c) Copyright 2000-2021 CERN for the benefit of the LHCb Collaboration      *
*                                                                             *
* This software is distributed under the terms of the GNU General Public      *
* Licence version 3 (GPL Version 3), copied verbatim in the file "COPYING".   *
*                                                                             *
* In applying this licence, CERN does not waive the privileges and immunities *
* granted to it by virtue of its status as an Intergovernmental Organization  *
* or submit itself to any jurisdiction.                                       *
\*****************************************************************************/
#ifndef IPARTICLEDICTTOOL_H
#define IPARTICLEDICTTOOL_H 1

// Include files
// from STL
#include <string>

// from Gaudi
#include "GaudiKernel/IAlgTool.h"
#include "GaudiKernel/VectorMap.h"

static const InterfaceID IID_IParticleDictTool( "IParticleDictTool", 1, 0 );

namespace LHCb {
  class Particle;
}

/** @class IParticleDictTool IParticleDictTool.h
 *  returns a dictionary of variable-names and their values
 *
 *  @author Sebastian Neubert
 *  @date   2013-07-08
 *
 */

class IParticleDictTool : virtual public IAlgTool {

public:
  // Return the interface ID
  static const InterfaceID& interfaceID() { return IID_IParticleDictTool; }

public:
  /// Dict definition
  typedef GaudiUtils::VectorMap<std::string, double> DICT;

  /** fill the dictionary:
   *  @param p (INPUT) the particle
   *  @param dict (UPDATE) the dictionary to be filled
   */
  virtual StatusCode fill( const LHCb::Particle* p, DICT& dict ) const = 0;
};

#endif // IPARTICLEDICTTOOL_H
