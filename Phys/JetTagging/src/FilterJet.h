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
#ifndef FILTERJET_H
#define FILTERJET_H 1

// ============================================================================
// Include files
// ============================================================================
// ============================================================================
// from Gaudi
// ============================================================================
#include "GaudiAlg/GaudiTool.h"
#include "GaudiKernel/IAlgTool.h"
// ============================================================================
// DaVinci Kernel
// ============================================================================
#include "Kernel/DaVinciAlgorithm.h"
// ============================================================================
// Event
// ============================================================================
#include "Event/Particle.h"
// ============================================================================
// Event
// ============================================================================
#include "Event/RecHeader.h"
#include "Kernel/IJetTagTool.h"

using namespace Gaudi::Units;
using namespace LHCb;
using namespace std;

// ============================================================================
// Main Algorithm
// ============================================================================
class FilterJet : public DaVinciAlgorithm {
public:
  /** Standard constructor
   *  @param name instance name
   *  @param pSvc pointer to Service Locator
   */
  FilterJet( const std::string& name, ISvcLocator* pSvcLocator );

  StatusCode initialize() override;

  /** standard execution of the algorithm
   *  @return status code
   */
  StatusCode execute() override;

protected:
  // ==========================================================================
  /// Write empty container if selection fails.
  void writeEmptyKeyedContainers() const;
  /// Write empty container if selection fails.
  void writeEmptySharedContainers() const;
  // ==========================================================================
private:
  // ==========================================================================
  /// save (clone if needed) selected particles in TES
  /// Success if number of saved particles == number saved
  /// to TES.
  /// Overwritten from DaVinciAlgorithm. Is called automatically.
  StatusCode _saveInTES() override;
  /// Write empty containers if selection fails.
  void writeEmptyTESContainers() override;

private:
  // ==========================================================================
  /// save (clone if needed) selected particles in TES
  template <class PARTICLES>
  StatusCode _save() const;

private:
  // name to retrieve tool
  std::string  m_tagToolName;
  IJetTagTool* m_tagTool;

  bool        m_save_all;
  bool        m_save_addinfo;
  int         m_start_addinfo;
  std::string m_SubPID;
  double      m_cut;

  std::vector<LHCb::Particle*> i_markedParticles;
};

#endif // FILTERJET_H
