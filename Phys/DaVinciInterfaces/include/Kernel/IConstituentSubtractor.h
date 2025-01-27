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
// FastJet
// ============================================================================
#include "fastjet/JetDefinition.hh"
#include "fastjet/PseudoJet.hh"

// ============================================================================
/** @class IConstituentSubtractor IConstituentSubtractor.h Kernel/IConstituentSubtractor.h
 *
 *  The abstract interface to Constituent Substracotr
 *
 *  @attention It is a responsibility of users (e.g. the algorithm)
 *             to take care about the ownership of jets *AND* their
 *             vertices). The tool is not intended to do it!
 *
 *  @author Ruide Xu ruidexu@umich.edu
 * Lancast QFT textbook, learn who is teaching
 *  @date   
 */
struct GAUDI_API IConstituentSubtractor : extend_interfaces<IAlgTool> {
  // ==========================================================================
  /// interface machinery
  DeclareInterfaceID( IConstituentSubtractor, 1, 0 );
  // ==========================================================================

  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  // Only the output type and input type needs to be defined
  // The peusdojet conversion is taken care off in the LoKiFastJetMaker.cpp/.h
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  /// the actual type of input data container
  typedef std::vector<fastjet::PseudoJet>& Input;
  /// the actual type of output container of jets
  typedef std::vector<fastjet::PseudoJet>& Output;
  // ==========================================================================
  /** The main method: Constituent Subtraction
   *
   *  @code
   *
   *  @endcode
   *
   *  @attention It is a responsibility of users (e.g. the algorithm)
   *             to take care about the ownership of jets *AND* their
   *             vertices). The tool is not intended to do it!
   *
   *
   *  @param rawJets        container of raw pseudo-jets
   *  @param subtracteJets  container of processed output pseudo-jets with subtracted constituent
   *  @return status code
   */
  virtual StatusCode subJets( const Input& rawJets, Output& subtractedJets ) = 0;
};
// ============================================================================
// The END
// ============================================================================
#endif // DAVINCIKERNEL_IJETMAKER_H