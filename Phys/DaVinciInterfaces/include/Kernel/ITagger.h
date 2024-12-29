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
// $Id: ITagger.h,v 1.4 2009-08-04 09:45:31 jpalac Exp $
#ifndef PHYS_DAVINCIINTERFACES_KERNEL_ITAGGER_H
#define PHYS_DAVINCIINTERFACES_KERNEL_ITAGGER_H 1

// Include files

// from Gaudi
#include "GaudiKernel/IAlgTool.h"

// from LHCb
#include "Event/Particle.h"
#include "Event/RecVertex.h"
#include "Event/Tagger.h"

/** @class ITagger ITagger.h
 *
 *  v2.0
 *  @author Marco Musy, Kevin Heinicke, Julian Wishahi
 *  @date   2005-06-30
 *  @date   2017-03-18
 *
 *  The ITagger class is the interface class for the various LHCb flavour
 *  tagging algorithms. Its primary method is tag, which takes a pointer to the
 *  candidate to be tagged, its associated PV, a vector of all PVs in the event,
 *  and a vector of particles to be used for tagging. The tagging algorithm then
 *  deduces the production flavour of the B candidate (encoded in the
 *  LHCb::Tagger return value) by first applying a selection to the tagging
 *  particles and then using their properties to classify the initial flavour
 *  and estimate the associated mistag probability.
 */

class GAUDI_API ITagger : virtual public IAlgTool {

public:
  DeclareInterfaceID( ITagger, 2, 0 );

  /**
   * @brief      Tags the signal candidate.
   *
   * @param[in]  sigPart   The signal candidate
   * @param[in]  assocVtx  The associated primary vertex
   * @param      nPUVtxs   Number of reconstructed primary vertices in the event
   * @param      tagParts  The tagging particles to be used
   *
   * @return     Returns a LHCb::Tagger object, as defined in the LHb project in
   *             Event/PhysEvent/xml/Tagger.xml.
   */
  virtual LHCb::Tagger tag( const LHCb::Particle* sigPart, const LHCb::RecVertex* assocVtx, const int nPUVtxs,
                            LHCb::Particle::ConstVector& tagParts ) = 0;

  /**
   * @brief      Tags the signal candidate.
   *
   * @param[in]  sigPart   The signal candidate
   * @param[in]  assocVtx  The associated primary vertex
   * @param      puVtxs    All reconstructed primary vertices in the event
   * @param      tagParts  The tagging particles to be used
   *
   * @return     Returns a LHCb::Tagger object, as defined in the LHb project in
   *             Event/PhysEvent/xml/Tagger.xml.
   */
  virtual LHCb::Tagger tag( const LHCb::Particle* sigPart, const LHCb::RecVertex* assocVtx,
                            LHCb::RecVertex::ConstVector& puVtxs, LHCb::Particle::ConstVector& tagParts ) {
    return tag( sigPart, assocVtx, puVtxs.size(), tagParts );
  };

  /**
   * @brief      Return a Tagger object that represents a "no tag"-tag
   *
   * @return     LHCb::Tagger with members representing a "no tag"-tag
   */
  virtual LHCb::Tagger emptyTag() const {
    LHCb::Tagger emptyTag;
    emptyTag.setType( taggerType() );
    emptyTag.setDecision( 0 );
    emptyTag.setOmega( 0.5 );
    emptyTag.setMvaValue( 0. );
    emptyTag.setCharge( 0. );
    return emptyTag;
  }

  /**
   * @brief      Tagger type of the tagger
   *
   * @return     Possible return values of the enum are defined in the LHCb
   *             project in Event/PhysEvent/xml/Tagger.xml.
   *
   */
  virtual LHCb::Tagger::TaggerType taggerType() const { return LHCb::Tagger::TaggerType::unknown; };

  /**
   * @brief      Names of the features used by the tagger for the tag decision
   *
   * @return     Vector of strings that represent the names of the features used
   *             by the tagger for the previous tag decision.
   *
   * @todo       Make fully virtual
   */
  virtual std::vector<std::string> featureNames() const { return {}; };

  /**
   * @brief      Values of the features used by the tagger for the tag decision
   *
   * @return     Vector of values of all features used for the previous tagging
   *             decision. Follows the ordering as given by featureNames().
   *
   * @todo       Make fully virtual
   */
  virtual std::vector<double> featureValues() const { return {}; };

  /**
   * @brief      Names of all features evaluated by the tagger
   *
   * @return     Vector of strings that represent the names of the features used
   *             by the tagger in the process of determining the previous tag
   *             decision. In contrast to featureNames() this holds
   *             information evaluated for each tagging particle.
   *
   * @todo       Make fully virtual
   */
  virtual std::vector<std::string> featureNamesTagParts() const { return {}; };

  /**
   * @brief      Names of all features evaluated for each tagging particle
   *
   * @return     A vector of vector of values of all features used for the
   *             previous tagging decision. Each 'row' represents the features
   *             of one tagging particle. Follows the ordering as given by
   *             featureNamesTagParts().
   *
   * @todo       Make fully virtual
   */
  virtual std::vector<std::vector<double>> featureValuesTagParts() const { return {{}}; };
};
#endif // PHYS_DAVINCIINTERFACES_KERNEL_ITAGGER_H
