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
// $Id: ISecondaryVertexTool.h,v 1.4 2009-08-04 09:45:31 jpalac Exp $
#ifndef SECONDARYVERTEXTOOL_ISECONDARYVERTEXTOOL_H
#define SECONDARYVERTEXTOOL_ISECONDARYVERTEXTOOL_H 1

// Include files
// from STL
#include <vector>

// from Gaudi
#include "GaudiKernel/IAlgTool.h"

// from LHCb
#include "Event/Particle.h"
#include "Event/Vertex.h"

// forward declarations
namespace LHCb {
  class RecVertex;
}

/** @class ISecondaryVertexTool ISecondaryVertexTool.h
 *
 *  v1.2
 *  @author Marco Musy (Milano)
 *  @date   2004-12-14
 */
class GAUDI_API ISecondaryVertexTool : virtual public IAlgTool {

public:
  DeclareInterfaceID( ISecondaryVertexTool, 2, 0 );

public:
  virtual std::vector<LHCb::Vertex> buildVertex( const LHCb::RecVertex&, const LHCb::Particle::ConstVector& ) = 0;
};

#endif // SECONDARYVERTEXTOOL_ISECONDARYVERTEXTOOL_H
