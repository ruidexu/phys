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
#ifndef DAVINCIKERNEL_IPARTICLEISOLATION_H
#define DAVINCIKERNEL_IPARTICLEISOLATION_H 1

// Include files

// from Gaudi
#include "GaudiKernel/IAlgTool.h"
// ============================================================================
// forward declarations
// ============================================================================
#include "Event/Particle.h"
#include "Event/RecVertex.h"

/** @class IParticleIsolation IParticleIsolation.h
 *  The Abstract Interface for "Particle Isolation", the tools which
 *  return the degree of isolation of a set of particles (optionally
 *  from a given decay/mother), under some criteria
 *
 *  Currently it returns the numbers of non-isolating particles associated
 *  with each of the input particles.
 *
 *  @author Giampiero Mancinelli giampi@cppm.in2p3.fr
 *  @date   2010-02-12
 */
struct GAUDI_API IParticleIsolation : extend_interfaces<IAlgTool> {

  /// interface machinery
  DeclareInterfaceID( IParticleIsolation, 1, 0 );

  /** The method for the evaluation of the degree of isolation ("number
   *  of non-isolating tracks") of the input set of particles.
   *
   *  @code
   *
   *   // get the tool
   *  const IParticleIsolation* tool = ...;
   *  Particle::ConstVector vdaugh = ... ;
   *  int iso[..] = ... ;
   *  int massiso[..] = ... ;
   *  int chi2iso[..] = ... ;
   *  int isotype = ... ; //optional
   *  const RecVertex* PV = ...; // optional
   *  const RecVertex* SV = ...; // optional
   *
   *   // use the tool to evaluate the degrees of isolation
   *  StatusCode sc = tool ->getIso(vdaugh,iso,isotype,PV,SV);
   *
   *  @endcode
   *
   *  @param vdaugh   (input) pointer to the input set particles
   *  @param iso      (output) number(s) of non-isolating particles
   *  @param massiso      (output) invariant mass of non-isolating particles
   *  @param chi2iso      (output) chi2 of particle made with non-isolating particles
   *  @param PV       (input) (optional) primary vertex
   *  @param SV       (input) (optional) secondary vertex (of mother)
   *
   *  @return status code
   */
  virtual StatusCode getIso( LHCb::Particle::ConstVector& parts, int* iso, float* massiso = 0, float* chi2iso = 0,
                             const LHCb::VertexBase* PV = 0, const LHCb::VertexBase* SV = 0 ) const = 0;
};

#endif // DAVINCIKERNEL_IPARTICLEISOLATION_H
