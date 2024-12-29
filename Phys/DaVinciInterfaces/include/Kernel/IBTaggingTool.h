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
#ifndef BTAGGINGTOOL_IBTAGGINGTOOL_H
#define BTAGGINGTOOL_IBTAGGINGTOOL_H 1

// Include files
// from STL
#include <string>

// from Gaudi
#include "Event/FlavourTag.h"
#include "Event/RecVertex.h"
#include "GaudiKernel/IAlgTool.h"

/** @class IBTaggingTool IBTaggingTool.h
 *
 *  v2.0
 *  @author Marco Musy, Julian Wishahi
 *  @date   2004-2017
 */

struct GAUDI_API IBTaggingTool : extend_interfaces<IAlgTool> {

  DeclareInterfaceID( IBTaggingTool, 3, 0 );

  /**
   * @brief      Tag a signal candidates
   *
   * @param      flavTag  The flavour tag
   * @param[in]  sigPart  The signal particle
   *
   * @return     StatusCode
   */
  virtual StatusCode tag( LHCb::FlavourTag& flavTag, const LHCb::Particle* sigPart ) = 0;

  virtual StatusCode tag( LHCb::FlavourTag& flavTag, const LHCb::Particle* sigPart,
                          const LHCb::RecVertex* assocVtx ) = 0;

  virtual StatusCode tag( LHCb::FlavourTag& flavTag, const LHCb::Particle* sigPart, const LHCb::RecVertex* assocVtx,
                          LHCb::Particle::ConstVector& tagParts ) = 0;

  /**
   * @brief      List of active Taggers
   *
   * @return     Vector of names of active taggers.
   */
  virtual std::vector<std::string> activeTaggerTypeNames() const = 0;

  /**
   * @brief      List of active Taggers
   *
   * @return     Vector of enum values of active taggers.
   */
  virtual std::vector<LHCb::Tagger::TaggerType> activeTaggerTypes() const = 0;

  /**
   * @brief      Names of the features used by the tagger for the tag decision
   *
   * @return     Vector of strings that represent the names of the features used
   *             by the tagger for the previous tag decision.
   *
   * @todo       Make fully virtual
   */
  virtual std::vector<std::string> featureNames( LHCb::Tagger::TaggerType taggerType ) const = 0;

  /**
   * @brief      Values of the features used by the tagger for the tag decision
   *
   * @return     Vector of values of all features used for the previous tagging
   *             decision. Follows the ordering as given by featureNames().
   */
  virtual std::vector<double> featureValues( LHCb::Tagger::TaggerType taggerType ) const = 0;

  /**
   * @brief      Feature names evaluated by the tagger for each tagging particle
   *
   * @return     Vector of strings that represent the names of the features used
   *             by the tagger in the process of determining the previous tag
   *             decision. In contrast to featureNames() this holds information
   *             evaluated for each tagging particle.
   */
  virtual std::vector<std::string> featureNamesTagParts( LHCb::Tagger::TaggerType taggerType ) const = 0;

  /**
   * @brief      Feature values evaluated by the tagger for each tagging particle
   *
   * @return     A vector of vector of values of all features used for the
   *             previous tagging decision. Each vector<double> represents one
   *             'column' (associated to the featureName), each 'row' represents
   *             the features of one tagging particle. The column ordering
   *             follows the ones given by featureNamesTagParts().
   */
  virtual std::vector<std::vector<double>> featureValuesTagParts( LHCb::Tagger::TaggerType taggerType ) const = 0;
};

#endif // BTAGGINGTOOL_IBTAGGINGTOOL_H
