/*****************************************************************************\
* (c) Copyright 2000-2018 CERN for the benefit of the LHCb Collaboration      *
*                                                                             *
* This software is distributed under the terms of the GNU General Public      *
* Licence version 3 (GPL Version 3), copied verbatim in the file "COPYING".   *
*                                                                             *
* In applying this licence, CERN does not waive the privileges and immunities *
* granted to it by virtue of its status as an Intergovernmental Organization  *
* or submit itself to any jurisdiction.                                       *
\*****************************************************************************/
#ifndef JBOREL_TUPLETOOLKINEMATIC_H
#define JBOREL_TUPLETOOLKINEMATIC_H 1

// Include files
// from Gaudi
#include "DecayTreeTupleBase/TupleToolBase.h"
#include "Kernel/IParticleTupleTool.h" // Interface

/** @class TupleToolKinematic TupleToolKinematic.h jborel/TupleToolKinematic.h
 *
 * \brief Fill kinematic information for DecayTreeTuple
 *
 * - "head_P" : "momentum's amplitude"
 * - "head_PT" : "transverse momentum"
 * - "head_P[E|X|Y|Z]" : "four vector momentum"
 * - "head_M" : "mass calculated from momentum four-vector"
 * - "!basic":
 *   - "head_MM" : "measured mass (or assigned mass in case of 'basic' particle)"
 *   - "head_MMERR" : "error on the measured mass (only for non-basic parts)"
 * - "Verbose":
 *   - "head_REFP[X|Y|Z]" : "one point the particle momentum extrapolation goes through"
 * 	 - "basic,charged":
 *     - "head_AtVtx_P" : "momentum's amplitude at origin vertex"
 * 		 - "head_AtVtx_PT" : "transverse momentum at origin vertex"
 * 		 - "head_AtVtx_P[E|X|Y|Z]" : "momentum information of basic particles at origin vertex position"
 * 		 - "head_AtSV_P" : "momentum's amplitude at secondary vertex"
 * 		 - "head_AtSV_PT" : "transverse momentum at secondary vertex"
 * 		 - "head_AtSV_P[E|X|Y|Z]" : "momentum information of basic particles at secondary vertex position"
 *
 * \sa DecayTreeTuple
 *
 *  @author Jeremie Borel
 *  @date   2007-11-07
 */
struct IParticleTransporter;
class TupleToolKinematic : public TupleToolBase, virtual public IParticleTupleTool {
public:
  /// Standard constructor
  TupleToolKinematic( const std::string& type, const std::string& name, const IInterface* parent );

  StatusCode fill( const LHCb::Particle*, const LHCb::Particle*, const std::string&, Tuples::Tuple& ) override;

  double preFitMass( const LHCb::Particle* ) const;

  const LHCb::Vertex* originVertex( const LHCb::Particle* top, const LHCb::Particle* P ) const;

  StatusCode initialize() override;

private:
  IParticleTransporter* m_transporter;
  std::string           m_transporterName;
};

#endif // JBOREL_TUPLETOOLKINEMATIC_H
