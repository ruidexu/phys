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
#ifndef KERNEL_IPVREFITTER_H
#define KERNEL_IPVREFITTER_H 1

// Include files
#include "GaudiKernel/IAlgTool.h"

// Forward declarations
class StatusCode;

namespace LHCb {
  class Particle;
  class VertexBase;
} // namespace LHCb

/** @class IPVReFitter IPVReFitter.h Kernel/IPVReFitter.h
 *  Interface for PVReFitter
 *  @author Yuehong Xie
 *  @date   17/08/2005
 */
struct GAUDI_API IPVReFitter : extend_interfaces<IAlgTool> {

  DeclareInterfaceID( IPVReFitter, 2, 0 );

  /// refit PV
  virtual StatusCode reFit( LHCb::VertexBase* ) const = 0;

  /// remove track used for a (B) LHCb::Particle and refit PV
  virtual StatusCode remove( const LHCb::Particle*, LHCb::VertexBase* ) const = 0;
};

#endif // KERNEL_IPVREFITTER_H
