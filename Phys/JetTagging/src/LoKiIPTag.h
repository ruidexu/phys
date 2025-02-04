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
// bjet identification based on track impact parameters
//
//-----------------------------------------------------------------------------

#ifndef LOKIIPTAG_H
#define LOKIIPTAG_H 1

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
  class IPTag : public virtual IJetTagTool, public GaudiTool {
  public:
    StatusCode initialize() override; // standard initialise
    StatusCode finalize() override;   // standard finalise

    // Method that calculates the tag weight of a jet
    bool calculateJetProperty( const LHCb::Particle* jet, std::map<std::string, double>& jetWeight ) override;

    // Method that sets the jet vertex
    StatusCode setJetVertex();

    // standard constructor
    IPTag( const std::string& type, const std::string& name, const IInterface* parent );

  private:
    const LHCb::Particle* m_Jet;       // jet
    IJetMaker::Input      m_JetInputs; // jet inputs
    LHCb::RecVertex       m_JetVertex; // jet vertex

    LHCb::Particles*     m_CleanedDaugthers; // daughter vector
    StatusCode           removeV0();         // remove V0 daugthers from the jets daugthers
    double               m_DauTrackCutChi;   // daughter cut on track chi squared probability
    double               m_DauTrackCutGhost; // daughter cut on ghost probability
    double               m_DtrakMax;
    double               m_DMK0;
    double               m_DMLambda;
    double               m_secCut;
    double               m_sumCut;
    IDistanceCalculator* m_distCalc; // distance calculator

    std::string m_AlgMode; // algorithm mode - SumTracks, SecondTrack, ThirdTrack
  };
} // namespace LoKi

#endif
