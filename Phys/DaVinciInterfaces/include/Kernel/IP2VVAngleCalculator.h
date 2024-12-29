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
#ifndef IP2VVANGLETOOL_H
#define IP2VVANGLETOOL_H 1

// Include files
// from STL
#include <string>
// from Gaudi
#include "Event/Particle.h"
#include "GaudiKernel/IAlgTool.h"

/** @class IP2VVAngleCalculator IP2VVAngleCalculator.h
 *
 *  Low-level tool that calculates the three angles between the four
 *  decay products of a P->VV decay. Use IP2VVPartAngleCalculator
 *  or IP2VVMCPartAngleCalculator instead.
 *
 *  @author Thomas Blake, Greig Cowan
 *  @date   2007-08-22
 *  @modified 2008-06-02
 */
struct GAUDI_API IP2VVAngleCalculator : extend_interfaces<IAlgTool> {

  DeclareInterfaceID( IP2VVAngleCalculator, 2, 0 );

  /// calculate the angle between two planes in the rest frame of the mother particle
  virtual double calculatePlaneAngle( const Gaudi::LorentzVector&, const Gaudi::LorentzVector&,
                                      const Gaudi::LorentzVector&, const Gaudi::LorentzVector&,
                                      const Gaudi::LorentzVector& ) = 0;

  /// calculate the polar angle in the rest frame of the mother particle
  virtual double calculatePolarAngle( const Gaudi::LorentzVector&, const Gaudi::LorentzVector&,
                                      const Gaudi::LorentzVector& ) = 0;

  /// calculate the angle of the L+ wrt z-axis in dilepton frame
  virtual double calculateThetaTr( const Gaudi::LorentzVector&, const Gaudi::LorentzVector&,
                                   const Gaudi::LorentzVector&, const Gaudi::LorentzVector& ) = 0;

  /// calculate the azimuthal angle of the L+ in dilepton frame
  virtual double calculatePhiTr( const Gaudi::LorentzVector&, const Gaudi::LorentzVector&, const Gaudi::LorentzVector&,
                                 const Gaudi::LorentzVector& ) = 0;
};

#endif // IB2LLXANGLETOOL_H
