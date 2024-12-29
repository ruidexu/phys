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
#ifndef DAVINCIKERNEL_IJETMAKER_H
#define DAVINCIKERNEL_IJETMAKER_H 1
// ============================================================================
// Include files
// ============================================================================
// STD & STL
// ============================================================================
#include <string>
#include <vector>
// ============================================================================
// GaudiKernel
// ============================================================================
#include "GaudiKernel/IAlgTool.h"
// ============================================================================
// forward decalrations
// ============================================================================
#include "Event/Particle.h"
#include "Event/RecVertex.h"
// ============================================================================
/** @class IJetMaker IJetMaker.h Kernel/IJetMaker.h
 *
 *  The abstract interface to Jet Maker
 *
 *  @attention It is a responsibility of users (e.g. the algorithm)
 *             to take care about the ownership of jets *AND* their
 *             vertices). The tool is not intended to do it!
 *
 *  @author Vanya BELYAEV Ivan.Belyaev@lapp.in2p3.fr
 *  @date   2005-07-26
 */
struct GAUDI_API IJetMaker : extend_interfaces<IAlgTool> {
  // ==========================================================================
  /// interface machinery
  DeclareInterfaceID( IJetMaker, 2, 0 );
  // ==========================================================================
  /// the actual type of input data container
  typedef LHCb::Particle::ConstVector Input;
  /// the actual type of output container of jets
  typedef LHCb::Particle::Vector Jets;
  // ==========================================================================
  /** The main method: jet-finding procedure
   *
   *  @code
   *
   *  // get the tool
   *  const IJetMaker* jetMaker = tool<IJetMaker> ( .... ) ;
   *
   *  // input particles
   *  IJetMaker::Inputs input = ...
   *  // 1)
   *  // const Particles* particles = .... ;
   *  // // create the input container
   *  // IJetMaker::Inputs input( particles->begin() , particles->end() ) ;
   *  // 2)
   *  // LHCb::Particle::ConstVector particles = .... ;
   *  // // create the input container
   *  // IJetMaker::Inputs input( particles.begin() , particles.end() ) ;
   *  // 3)
   *  // LoKi::Range particles = .... ;
   *  // // create the input container
   *  // IJetMaker::Inputs input( particles.begin() , particles.end() ) ;
   *
   *  // placeholder for "output" jets
   *  IJetMaker::Jets   jets ;
   *
   *  // find the jets!
   *  StatusCode sc = jetMaker -> makeJets ( input , jets ) ;
   *
   *  // make  a loop over jets:
   *  for ( IJetMaker::Jets::const_iterator iJet = jets.begin() ;
   *        jets.end() != iJet ; ++iJet )
   *    {
   *        // get the jet
   *        LHCb::Particle* jet = *iJet ;
   *    }
   *
   *  @endcode
   *
   *  @attention It is a responsibility of users (e.g. the algorithm)
   *             to take care about the ownership of jets *AND* their
   *             vertices). The tool is not intended to do it!
   *
   *
   *  @param input contaainer of input particles
   *  @param jets  container of  output jets
   *  @return status code
   */
  virtual StatusCode makeJets( const Input& input, Jets& jets ) const = 0;
  // ==========================================================================
  /** perform jet-finding procedute getting the input data from
   *  arbitrary sequence of data, convertible to "const LHCb::Particle*",
   *  e.g. LHCb::Particle::ConstVector, Particles, LoKi::Range, etc...
   *
   *  @code
   *
   *  // get the tool
   *  const IJetMaker* jetMaker = tool<IJetMaker> ( .... ) ;
   *
   *  // get input data
   *  const Particles* ps = get<Particles> ( ... ) ;
   *
   *  // output jets
   *  IJetMaker::Jets  jets ;
   *
   *  // find the jets!
   *  StatusCode sc = jetMaker -> makeJets ( ps -> begin () ,
   *                                         ps -> end   () , jets ) ;
   *
   *
   *  // make  a loop over jets:
   *  for ( IJetMaker::Jets::const_iterator iJet = jets.begin() ;
   *        jets.end() != iJet ; ++iJet )
   *    {
   *        // get the jet
   *        LHCb::Particle* jet = *iJet ;
   *    }
   *
   *  @endcode
   *
   *  One can use e.g. LoKi::Range
   *
   *  @code
   *
   *  // get the tool
   *  const IJetMaker* jetMaker = tool<IJetMaker> ( .... ) ;
   *
   *  // get input data : get all basic particles
   *  Range basic = select( "basic" , HASORIGIN ) ;
   *`
   *  // output jets
   *  IJetMaker::Jets  jets ;
   *
   *  // find the jets!
   *  StatusCode sc = jetMaker -> makeJets ( basic.begin () ,
   *                                         basic.end   () , jets ) ;
   *
   *
   *  // make  a loop over jets:
   *  for ( IJetMaker::Jets::const_iterator iJet = jets.begin() ;
   *        jets.end() != iJet ; ++iJet )
   *    {
   *        // get the jet
   *        LHCb::Particle* jet = *iJet ;
   *    }
   *
   *  @endcode
   *
   *  @attention It is a responsibility of users (e.g. the algorithm)
   *             to take care about the ownership of jets *AND* their
   *             vertices). The tool is not intended to do it!
   *
   *
   *  @param first 'begin' iterator to the sequence of particles
   *  @param last  'end'   iterator to the sequence of particles
   *  @param jets  container of outptu jets
   *  @return status code
   */
  template <class PARTICLE>
  inline StatusCode makeJets( PARTICLE first, PARTICLE last, Jets& jets ) const {
    return makeJets( Input( first, last ), jets );
  }
  // ==========================================================================
  /** The main method: jet-finding procedure
   *
   *  @code
   *
   *  // get the tool
   *  const IJetMaker* jetMaker = tool<IJetMaker> ( .... ) ;
   *
   *  // input particles
   *  IJetMaker::Inputs input = ...
   *  // 1)
   *  // const Particles* particles = .... ;
   *  // // create the input container
   *  // IJetMaker::Inputs input( particles->begin() , particles->end() ) ;
   *  // 2)
   *  // LHCb::Particle::ConstVector particles = .... ;
   *  // // create the input container
   *  // IJetMaker::Inputs input( particles.begin() , particles.end() ) ;
   *  // 3)
   *  // LoKi::Range particles = .... ;
   *  // // create the input container
   *  // IJetMaker::Inputs input( particles.begin() , particles.end() ) ;
   *
   *  // placeholder for "output" jets
   *  IJetMaker::Jets   jets ;
   *
   *  // find the jets!
   *  StatusCode sc = jetMaker -> makeJets ( input , jets ) ;
   *
   *  // make  a loop over jets:
   *  for ( IJetMaker::Jets::const_iterator iJet = jets.begin() ;
   *        jets.end() != iJet ; ++iJet )
   *    {
   *        // get the jet
   *        LHCb::Particle* jet = *iJet ;
   *    }
   *
   *  @endcode
   *
   *  @attention It is a responsibility of users (e.g. the algorithm)
   *             to take care about the ownership of jets *AND* their
   *             vertices). The tool is not intended to do it!
   *
   *
   *  @param input contaainer of input particles
   *  @param jets  container of  output jets
   *  @return status code
   */
  virtual StatusCode makeJets( const Input& input, const LHCb::RecVertex& vtx, Jets& jets ) const = 0;
  // ==========================================================================
};
// ============================================================================
// The END
// ============================================================================
#endif // DAVINCIKERNEL_IJETMAKER_H
