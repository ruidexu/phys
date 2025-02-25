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
// ============================================================================
#ifndef DAVINCIKERNEL_ICONSTITUENTSUBTRACTOR_H
#define DAVINCIKERNEL_ICONSTITUENTSUBTRACTOR_H 1
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
 *  The abstract interface to Constituent Subtractor
 *
 *  @author Ruide Xu ruidexu@umich.edu
 *  @date   2025-02-24
 */
struct GAUDI_API IConstituentSubtractor : extend_interfaces<IAlgTool> {
  // ==========================================================================
  /// interface machinery
  public:
    DeclareInterfaceID( IConstituentSubtractor, 1, 0 );
  // ==========================================================================

  /// the actual type of input data container
  typedef std::vector<fastjet::PseudoJet>& Input;
  /// the actual type of output container of jets
  typedef std::vector<fastjet::PseudoJet>& Output;
  // ==========================================================================
  /** The main method: Constituent Subtraction
   *
   *  @param rawJets        container of raw pseudo-jets
   *  @param subtracteJets  container of processed output pseudo-jets with subtracted constituents
   *  @return status code
   */
  public:
    virtual StatusCode subJets(  Input const &rawJets, Output& subtractedJets ) const = 0;
};
// ============================================================================
// The END
// ============================================================================
#endif // DAVINCIKERNEL_ICONSTITUENTSUBTRACTOR_H