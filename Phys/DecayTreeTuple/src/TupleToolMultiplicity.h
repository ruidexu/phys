/*****************************************************************************\
* (c) Copyright 2000-2024 CERN for the benefit of the LHCb Collaboration      *
*                                                                             *
* This software is distributed under the terms of the GNU General Public      *
* Licence version 3 (GPL Version 3), copied verbatim in the file "COPYING".   *
*                                                                             *
* In applying this licence, CERN does not waive the privileges and immunities *
* granted to it by virtue of its status as an Intergovernmental Organization  *
* or submit itself to any jurisdiction.                                       *
\*****************************************************************************/
// $Id: TupleToolMultiplicity.h,v  $
#ifndef TUPLETOOLMULTIPLICITY_H
#define TUPLETOOLMULTIPLICITY_H

#include "TupleToolMultiplicity.h"

#include <map>
#include <math.h>
#include <memory>

#include "TFile.h"
#include "TH1F.h"

#include "Event/Particle.h"
#include "Event/RecSummary.h"
#include "Event/RecVertex.h"
#include "Event/Track.h"

#include "DecayTreeTupleBase/TupleToolBase.h"
#include "Kernel/IEventTupleTool.h"

#include "GaudiAlg/ITupleTool.h"
#include "GaudiAlg/Tuple.h"
#include "GaudiAlg/TupleObj.h"
#include "GaudiKernel/IRegistry.h"

#include <Kernel/IDistanceCalculator.h>

#include "GaudiKernel/PhysicalConstants.h"

#include "Kernel/IPVReFitter.h"
#include "Kernel/IParticleDescendants.h"
#include "Kernel/IVertexFit.h"

#include "HltDAQ/IReportConvert.h"
#include "HltDAQ/ReportConvertTool.h"

struct IDistanceCalculator;
struct IDVAlgorithm;

class ITupleTool;

/** @class TupleToolMultiplicity TupleToolMultiplicity.h
 *
 * \brief Add Number of Charged Particles info to DecayTreeTuple or EventTuple
 *
 * The TupleTool requires as input the tables with track-by-track corrections derived from Data and MC
 * based on charged particle measurements. These tables are .root files located in ParamFiles.
 *
 * IMPORTANT!
 * The only correction tables that have been implemented are for the 2013 pPb Data @ 5TeV:
 * - correction_pA_Merged_MCsim09k (forward)
 * - correction_Ap_Merged_MCsim09k (backward)
 * - correction_pp_MD_MCsim09d (pp reference)
 *
 * The TupleTool can be used with different correction tables if they have the same selection as the 2012 data.
 * This selection is stored in the dictionary sel_cuts.
 * In this case, the Year should be set as 2012, and the tables can be input by setting:
 * CorrectionTablesLocation, CorrectionTable and, optionally, NoData_Correction_Table.
 *
 * TO DO :
 * There are available tables for the 2016 pPb Data @ 8Tev:
 *  - merged_eff_4D_pPb_8TeV (forward)
 *  - merged_eff_4D_Pbp_8TeV (backward)
 * but the selection for this data set has not been implemented in the TupleTool.
 *
 * Tuple columns:
 * - Ncand_LHCb Candidates in pseudoraplidty range 2-4.8
 * - Ncorr_LHCb Corrected charged particles in pseudorapidity range 2-4.8
 * - Nfail Number of long tracks inside the LHCb acceptance that failed to compute the IP (should be 0)
 * - Ncand_user Candidates in user defined range of pseudorapidity and pt
 * - Ncorr_user Corrected charged particles in user defined range of pseudorapidity and pt
 * - Ncorr_user_err  Error of the corrected charged particles in user defined range of pseudorapidity and pt
 * The minimum pt is 500 MeV and the maximum pt is 8 GeV,
 * it is possible to change these values in the DecayTreeTuple options
 *
 * VERBOSE mode:
 *
 * - Ncand_eta1: Candidates in pseudoraplidty range 2.5-3.3 and user defined range of pt (applying boost to CMS in pPb
 * collisions)
 * - Ncorr_eta1: Corrected charged particles in pseudoraplidty range 2.5-3.3  and user defined range of pt (applying
 * boost to CMS in pPb collisions)
 *  - Ncorr_eta1_err: Error of the corrected charged particles in pseudoraplidty range 2.5-3.3  and user defined range
 * of pt (applying boost to CMS in pPb collisions)
 * - Ncand_eta2: Candidates in pseudoraplidty range 3.3-4.3 and user defined range of pt (applying boost to CMS in pPb
 * collisions)
 * - Ncorr_eta2: Corrected charged particles in pseudoraplidty range 3.3-4.3 and user defined range of pt (applying
 * boost to CMS in pPb collisions)
 * - Ncorr_eta2_err: Error of the corrected charged particles in pseudoraplidty range 3.3-4.3  and user defined range of
 * pt (applying boost to CMS in pPb collisions)
 * - Ncorr_MC: Same as Ncorr_user but using table with no data corrections
 *            (To check consistency, will only make sense if the right NoData_Corrections_Table is input)
 * \sa DecayTreeTuple
 *  @author Imanol Corredoira, Clara Landesa
 *  @date  29/11/2024
 */
class TupleToolMultiplicity : public TupleToolBase, virtual public IEventTupleTool {
public:
  /// Standard constructor
  TupleToolMultiplicity( const std::string& type, const std::string& name, const IInterface* parent );

  ~TupleToolMultiplicity() override = default; ///< Destructor

  StatusCode fill( Tuples::Tuple& ) override;
  StatusCode initialize() override;
  StatusCode finalize() override;

private:
  std::string           m_PVLocation;
  std::string           m_CorrectionTablesLocation;
  std::string           m_Correction_Table;
  std::string           m_NoData_Table;
  bool                  m_Include_NoData_Table;
  std::string           m_Beam;
  int                   m_Year;
  double                m_y;
  float                 m_Etamin;
  float                 m_Etamax;
  float                 m_pTmin;
  float                 m_pTmax;
  std::shared_ptr<TH1F> m_hist;
  std::shared_ptr<TH1F> m_hist_nodata;
  IReportConvert*       m_conv;
  IDistanceCalculator*  m_dist;

  // Dictionary where selection cuts are stored
  std::map<std::string, std::map<int, std::map<std::string, float>>> sel_cuts;
};
#endif //
