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

#ifndef LOKITOPOTAG_H
#define LOKITOPOTAG_H 1

// ============================================================================
// Includes

// Kernel
#include "Kernel/ITriggerTisTos.h"

#include "Kernel/IJetTagTool.h"

// Gaudi
#include "GaudiAlg/GaudiTool.h"
#include "GaudiKernel/IHistogramSvc.h"

// ============================================================================
// Declaration
namespace LoKi {
  class TopoTag : public virtual IJetTagTool, public GaudiTool {
  public:
    StatusCode initialize() override; // standard initialise
    StatusCode finalize() override;   // standard finalise

    // Method that calculates the tag weight of a jet
    bool calculateJetProperty( const LHCb::Particle* jet, std::map<std::string, double>& jetWeight ) override;

    // standard constructor
    TopoTag( const std::string& type, const std::string& name, const IInterface* parent );

  private:
    ITriggerTisTos* m_TriggerTisTosTool;
    std::string     m_TLine; // algorithm mode - PtRel or IPSig
  };
} // namespace LoKi

#endif
