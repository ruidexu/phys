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
//-----------------------------------------------------------------------------
//
// bjet identification based on muons
//
//-----------------------------------------------------------------------------

#ifndef LOKISVTAG_H
#define LOKISVTAG_H 1

// ============================================================================
// Includes

// Kernel
#include "Kernel/IDistanceCalculator.h"
#include "Kernel/IJetMaker.h"
#include "Kernel/IJetTagTool.h"
#include "Kernel/IJets2Jets.h"
#include "Kernel/ParticleID.h"

// Gaudi
#include "GaudiAlg/GaudiTool.h"
#include "GaudiKernel/IHistogramSvc.h"

// ============================================================================
// Declaration
namespace LoKi {
  class SVTag : public virtual IJetTagTool, public GaudiTool {
  public:
    StatusCode initialize() override; // standard initialise
    StatusCode finalize() override;   // standard finalise

    // Method that calculates the tag weight of a jet
    bool calculateJetProperty( const LHCb::Particle* jet, std::map<std::string, double>& jetWeight ) override;

    // Method that sets the jet vertex
    StatusCode setJetVertex();

  public:
    // standard constructor
    SVTag( const std::string& type, const std::string& name, const IInterface* parent );

  private:
    const LHCb::Particle* m_Jet;       // jet
    IJetMaker::Input      m_JetInputs; // jet inputs
    LHCb::RecVertex       m_JetVertex; // jet vertex

    IDistanceCalculator* m_distCalc; // distance calculator

  private:
    // SeedFinder
    IJetMaker*  m_seedFinder; // combiner to be used
    std::string m_seedFinderName;

    std::string m_AlgMode; // algorithm mode - LengthAvg, LengthMax
    //                - SigAvg, SigMax (default)
    //                - Nvertices
  };
} // namespace LoKi

#endif
