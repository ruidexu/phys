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
#ifndef VBVERTEXREQUIREMENT_H
#define VBVERTEXREQUIREMENT_H 1

// Include files
// from DaVinci, this is a specialized GaudiAlgorithm
#include "Kernel/DaVinciAlgorithm.h"

/** @class VBVertexRequirement VBVertexRequirement.h
 *  Asks for same PV
 *
 *  @author Albert Bursche
 *  @date   2012-01-27
 */
class VBVertexRequirement : public DaVinciAlgorithm {

public:
  /// Standard constructor
  VBVertexRequirement( const std::string& name, ISvcLocator* pSvcLocator );

  virtual ~VBVertexRequirement(); ///< Destructor

  StatusCode execute() override; ///< Algorithm execution
};

#endif // VBVERTEXREQUIREMENT_H
