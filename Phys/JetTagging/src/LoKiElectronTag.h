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

#ifndef LOKIELECTRONTAG_H
#define LOKIELECTRONTAG_H 1

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

// LoKi
#include "LoKi/ILoKiSvc.h"

// ============================================================================
// Declaration
namespace LoKi {
  class ElectronTag : public virtual IJetTagTool, public GaudiTool {
  public:
    StatusCode initialize() override; // standard initialise
    StatusCode finalize() override;   // standard finalise

    // Method that calculates the tag weight of a jet
    bool calculateJetProperty( const LHCb::Particle* jet, std::map<std::string, double>& jetWeight ) override;

    // Method that sets the jet vertex
    StatusCode setJetVertex();

    // standard constructor
    ElectronTag( const std::string& type, const std::string& name, const IInterface* parent );

  private:
    const LHCb::Particle* m_Jet;       // jet
    IJetMaker::Input      m_JetInputs; // jet inputs
    LHCb::RecVertex       m_JetVertex; // jet vertex

    LHCb::Particles* m_Electrons;             // electron vector
    StatusCode       getElectrons();          // get and select electrons
    double           m_ElectronCutPTRel;      // electron cut on ptrel
    double           m_ElectronCutDR;         // electron cut on dr
    double           m_ElectronCutPT;         // electron cut on pt
    double           m_ElectronTrackCutChi;   // electron cut on track chi squared probability
    double           m_ElectronTrackCutIP;    // electron cut on track ip significance
    double           m_ElectronTrackCutGhost; // electron cut on ghost probability

    IDistanceCalculator* m_distCalc; // distance calculator

    std::string m_AlgMode; // algorithm mode - PtRel or IPSig
  };
} // namespace LoKi

#endif
