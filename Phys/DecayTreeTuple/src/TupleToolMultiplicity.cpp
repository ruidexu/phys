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
// $Id: TupleToolMultiplicity.cpp,v 1.0 $
// Include files

// local
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

//-----------------------------------------------------------------------------
// Implementation file for class : TupleToolMultiplicity
//-----------------------------------------------------------------------------

// Declaration of the Tool Factory
DECLARE_COMPONENT( TupleToolMultiplicity )

//=============================================================================
// Standard constructor, initializes variables. EventTuple
//=============================================================================
TupleToolMultiplicity::TupleToolMultiplicity( const std::string& type, const std::string& name,
                                              const IInterface* parent )
    : TupleToolBase( type, name, parent ), m_conv( nullptr ), m_dist( nullptr ) {

  declareInterface<IEventTupleTool>( this );

  declareProperty( "PVLocation", m_PVLocation = "Rec/Vertex/Primary",
                   "Set the location where to look for PVs. Only needed if RequirePV==True." );

  // Path to the correction tables in ParamFiles
  // If the user wants to upload correction tables as LocalFile, the path should be set to ""
  declareProperty( "CorrectionTablesLocation",
                   m_CorrectionTablesLocation = System::getEnv( "PARAMFILESROOT" ) + "/data/MultiplicityTupleTool/",
                   "Location of the correction files, in the ParamFiles repository" );
  // Beam
  declareProperty( "Beam", m_Beam = "pPb", "Collision type" ); // pp, pPb, Pbp

  // Year
  declareProperty( "Year", m_Year = 2012, "Data-set year." ); // So far only implemented for 2012

  // Name of the input correction table: default pPb 5TeV
  declareProperty( "Correction_Table", m_Correction_Table = "",
                   "Correction table" ); // default value is given in the initialisation

  declareProperty( "Include_NoDataCorrections", m_Include_NoData_Table = true,
                   "Write an extra column without data corrections, default true" );

  // Name of the correction table without data driven corrections : default pPb 5TeV
  declareProperty( "NoData_Corrections_Table", m_NoData_Table = "",
                   "No Data correction table" ); // default value is given in the initialisation

  // Eta cuts
  declareProperty( "Etamin", m_Etamin = -1, "Eta minimum cut" ); // default value is given in the initialisation
  declareProperty( "Etamax", m_Etamax = -1, "Eta maximum cut" ); // default value is given in the initialisation

  // pT cuts
  declareProperty( "pTmin", m_pTmin = 500, "pT minimum cut (MeV/c)" );
  declareProperty( "pTmax", m_pTmax = 8000, "pT maximum cut (MeV/c)" );
}

//=============================================================================
// Initialization
//=============================================================================

StatusCode TupleToolMultiplicity::initialize() {

  const StatusCode sc = TupleToolBase::initialize();
  if ( sc.isFailure() ) return sc;

  msg() << "----------- TupleToolMultiplicity --------------" << endmsg;

  m_y = 0;
  if ( m_Beam == "pPb" ) {
    m_y = +0.465;
  } else if ( m_Beam == "Pbp" ) {
    m_y = -0.465;
  }

  if ( m_Etamin == -1 ) { m_Etamin = 2.5 + m_y; }
  if ( m_Etamax == -1 ) { m_Etamax = 4.3 + m_y; }

  if ( m_Correction_Table == "" ) {
    if ( m_Beam == "pPb" ) {
      if ( m_Year == 2012 ) {
        m_Correction_Table = "correction_pA_Merged_MCsim09k";
      } else {
        return Error( "No correction tables for this data", StatusCode::FAILURE );
      }
    } else if ( m_Beam == "Pbp" ) {
      if ( m_Year == 2012 ) {
        m_Correction_Table = "correction_Ap_Merged_MCsim09k";
      } else {
        return Error( "No correction tables for this data", StatusCode::FAILURE );
      }
    } else if ( m_Beam == "pp" ) {
      if ( m_Year == 2012 ) {
        m_Correction_Table = "correction_pp_MD_MCsim09d";
      } else {
        return Error( "No correction tables for this data", StatusCode::FAILURE );
      }
    }
  }
  if ( m_NoData_Table == "" ) { m_NoData_Table = m_Correction_Table + "_nodata_mc_corr"; }

  msg() << " Beam: " << m_Beam << " ; Year:  " << m_Year << endmsg;
  msg() << " Etamin: " << m_Etamin << " ; Etamax:  " << m_Etamax << endmsg;
  msg() << " PTmin (MeV/c): " << m_pTmin << " ; PTmax (MeV/c):  " << m_pTmax << endmsg;
  msg() << " Corrections table: " << m_Correction_Table << endmsg;
  if ( m_Include_NoData_Table == true ) {
    msg() << " Adding no-data driven corrections: " << m_NoData_Table << endmsg;
  } else {
    msg() << " Not adding no-data-driven corrections " << endmsg;
  }

  // dictionary with cuts

  sel_cuts["pPb"][2012]["tr_GhostP"] = 0.10263;
  sel_cuts["pPb"][2012]["tr_psIP"]   = 0.348271875;
  sel_cuts["pPb"][2012]["min_p"]     = 2000;
  sel_cuts["pPb"][2012]["min_pt"]    = 500;
  sel_cuts["pPb"][2012]["max_pt"]    = 8000;
  sel_cuts["pPb"][2012]["min_eta"]   = 2;
  sel_cuts["pPb"][2012]["max_eta"]   = 4.8;

  sel_cuts["Pbp"][2012]["tr_GhostP"] = 0.10885;
  sel_cuts["Pbp"][2012]["tr_psIP"]   = 0.348271875;
  sel_cuts["Pbp"][2012]["min_p"]     = 2000;
  sel_cuts["Pbp"][2012]["min_pt"]    = 500;
  sel_cuts["Pbp"][2012]["max_pt"]    = 8000;
  sel_cuts["Pbp"][2012]["min_eta"]   = 2;
  sel_cuts["Pbp"][2012]["max_eta"]   = 4.8;

  sel_cuts["pp"][2012]["tr_GhostP"] = 0.07775;
  sel_cuts["pp"][2012]["tr_psIP"]   = 0.368173125;
  sel_cuts["pp"][2012]["min_p"]     = 2000;
  sel_cuts["pp"][2012]["min_pt"]    = 500;
  sel_cuts["pp"][2012]["max_pt"]    = 8000;
  sel_cuts["pp"][2012]["min_eta"]   = 2;
  sel_cuts["pp"][2012]["max_eta"]   = 4.8;

  m_dist = tool<IDistanceCalculator>( "LoKi::DistanceCalculator", this );
  if ( !m_dist ) return Error( "Unable to retrieve the IDistanceCalculator tool", StatusCode::FAILURE );

  TFile inFile( ( m_CorrectionTablesLocation + m_Correction_Table + ".root" ).c_str(), "READ" );
  m_hist = std::shared_ptr<TH1F>( static_cast<TH1F*>( inFile.Get( m_Correction_Table.c_str() ) ) );
  m_hist->SetDirectory( 0 );

  if ( !m_hist || m_hist->GetEntries() == 0 ) {
    return Error( "Corrections histogram is invalid or empty", StatusCode::FAILURE );
  }

  if ( m_Include_NoData_Table ) {
    try {
      m_hist_nodata = std::shared_ptr<TH1F>( static_cast<TH1F*>( inFile.Get( m_NoData_Table.c_str() ) ) );
      m_hist_nodata->SetDirectory( 0 );
      if ( !m_hist_nodata || m_hist_nodata->GetEntries() == 0 ) {
        throw std::runtime_error( " Failed to read no corrections table in" + m_CorrectionTablesLocation +
                                  m_Correction_Table + ".root" );
      }
    } catch ( const std::runtime_error& ex ) {
      // Log the error but ensure the program continues running
      warning() << "Warning: the column without data-driven corrections will not be added" << endmsg;
      m_Include_NoData_Table = false;
    }
  }
  inFile.Close();

  return sc;
}

StatusCode TupleToolMultiplicity::finalize() { return StatusCode::SUCCESS; }

StatusCode TupleToolMultiplicity::fill( Tuples::Tuple& tuple ) {

  //-------------------GETTING REC SUMMARY: TO GET VELOTRACKS------------------------------

  int nVeloTracks;
  // Load the RecSummary object from standard location
  LHCb::RecSummary* rawRecSummary = getIfExists<LHCb::RecSummary>( evtSvc(), LHCb::RecSummaryLocation::Default, false );
  if ( !rawRecSummary ) {
    // try Trubo location
    rawRecSummary = getIfExists<LHCb::RecSummary>( evtSvc(), "/Event/Turbo/Rec/Summary", false );
  }
  if ( rawRecSummary ) {
    nVeloTracks = rawRecSummary->info( LHCb::RecSummary::nVeloTracks, -1 );
  } else {
    // Use smart pointer only if we need to create a new object
    std::unique_ptr<LHCb::RecSummary> rS;
    // Initialise the converter tool
    m_conv = tool<IReportConvert>( "ReportConvertTool", this );
    if ( !m_conv ) { return Error( "Unable to retrieve the Report converter tool" ); }
    m_conv->setReportVersionLatest();
    rS                                    = std::make_unique<LHCb::RecSummary>();
    const LHCb::HltSelReports* selReports = get<LHCb::HltSelReports>( "Hlt2/SelReports" );
    if ( selReports ) {
      const LHCb::HltObjectSummary* recsummaryObj = selReports->selReport( "Hlt2RecSummary" );
      if ( recsummaryObj ) {
        const LHCb::HltObjectSummary* Rec_subobj = recsummaryObj->substructure()[0].target();
        if ( Rec_subobj ) {
          const LHCb::HltObjectSummary::Info& Rec_info = Rec_subobj->numericalInfo();
          m_conv->RecSummaryObjectFromSummary( &Rec_info, rS.get() );
        }
      }
    }
    if ( rS ) {
      nVeloTracks = rS->info( LHCb::RecSummary::nVeloTracks, -1 );
    } else {
      return Error( "No RecSummary found", StatusCode::FAILURE );
    }
  }

  // get PVs
  auto PVs  = getIfExists<LHCb::RecVertex::Range>( m_PVLocation );
  int  nPVs = PVs.size();

  //------------------- Calculate number of candidates and corrected candidates ------------------------------

  double default_value = ( nPVs == 1 ) ? 0 : -1000;

  bool test = true;

  double Ncand_LHCb     = default_value;
  double Ncorr_LHCb     = default_value;
  double Ncorr_LHCb_err = default_value;

  double Ncorr_user     = default_value;
  double Ncand_user     = default_value;
  double Ncorr_user_err = default_value;

  double N_fail = default_value;

  double Ncorr_eta1     = default_value;
  double Ncand_eta1     = default_value;
  double Ncorr_eta1_err = default_value;

  double Ncorr_eta2     = default_value;
  double Ncand_eta2     = default_value;
  double Ncorr_eta2_err = default_value;

  double N_corr_MC    = default_value;
  double Ncorr_MC_err = default_value;

  // Getting tracks from default container
  LHCb::Tracks* tracks = get<LHCb::Tracks>( LHCb::TrackLocation::Default );

  // loop over event tracks
  if ( nPVs == 1 ) {
    for ( LHCb::Tracks::const_iterator it = tracks->begin(); it != tracks->end(); ++it ) {
      LHCb::Track* track = ( *it );

      // -- Getting track information --
      double tr_type   = track->type();
      double tr_pt     = track->pt();
      double tr_p      = track->p();
      double tr_GhostP = track->ghostProbability();
      double tr_eta    = track->pseudoRapidity();
      double corr_i    = 0;
      double err_i     = 0;
      double corr_i_mc = 0;
      double err_i_mc  = 0;

      // IP-Variables: Initialization
      Double_t tr_IP = 1.e7, ipchi2 = 1.e7;

      if ( tr_type == 3 && tr_GhostP < sel_cuts[m_Beam][m_Year]["tr_GhostP"] &&
           tr_p > sel_cuts[m_Beam][m_Year]["min_p"] && tr_pt > sel_cuts[m_Beam][m_Year]["min_pt"] &&
           tr_pt < sel_cuts[m_Beam][m_Year]["max_pt"] && tr_eta > sel_cuts[m_Beam][m_Year]["min_eta"] &&
           tr_eta < sel_cuts[m_Beam][m_Year]["max_eta"] ) {

        // IP computation
        for ( auto aPV : PVs ) {
          try {
            m_dist->distance( track, aPV, tr_IP, ipchi2 ).ignore( /* AUTOMATICALLY ADDED FOR gaudi/Gaudi!763 */ );
          } catch ( std::exception const& e ) {
            N_fail += 1;
            continue;
          }
        }

        if ( tr_IP < sel_cuts[m_Beam][m_Year]["tr_psIP"] ) {

          corr_i = m_hist->GetBinContent( m_hist->FindBin( tr_pt, tr_eta, nVeloTracks ) ); // get correction from the
                                                                                           // corrections table
          err_i = m_hist->GetBinError( m_hist->FindBin( tr_pt, tr_eta, nVeloTracks ) );    // get correction from the
                                                                                           // corrections table
          Ncand_LHCb += 1;
          Ncorr_LHCb += corr_i;
          Ncorr_LHCb_err += err_i;

          if ( tr_pt > m_pTmin && tr_pt < m_pTmax && tr_eta > m_Etamin && tr_eta < m_Etamax ) {
            Ncand_user += 1;
            Ncorr_user += corr_i;
            Ncorr_user_err += err_i;
          }

          if ( isVerbose() ) {
            if ( tr_eta > 2.5 + m_y && tr_eta < 3.3 + m_y ) {
              Ncand_eta1 += 1;
              Ncorr_eta1 += corr_i;
              Ncorr_eta1_err += err_i;
            }
            if ( tr_eta > 3.3 + m_y && tr_eta < 4.3 + m_y ) {
              Ncand_eta2 += 1;
              Ncorr_eta2 += corr_i;
              Ncorr_eta2_err += err_i;
            }
          }
          if ( m_Include_NoData_Table == true && tr_pt > m_pTmin && tr_pt < m_pTmax && tr_eta > m_Etamin &&
               tr_eta < m_Etamax ) {
            corr_i_mc = m_hist_nodata->GetBinContent( m_hist_nodata->FindBin( tr_pt, tr_eta, nVeloTracks ) );
            err_i_mc  = m_hist_nodata->GetBinError( m_hist_nodata->FindBin( tr_pt, tr_eta, nVeloTracks ) );
            N_corr_MC += corr_i_mc;
            Ncorr_MC_err += err_i_mc;
          }
        }
      }
    }
  }

  // Writing
  test &= tuple->column( "Ncand_LHCb", Ncand_LHCb );
  test &= tuple->column( "Ncorr_LHCb", Ncorr_LHCb );
  test &= tuple->column( "Ncorr_LHCb_err", Ncorr_LHCb_err );

  test &= tuple->column( "Nfail", N_fail );

  test &= tuple->column( "Ncand_user", Ncand_user );
  test &= tuple->column( "Ncorr_user", Ncorr_user );
  test &= tuple->column( "Ncorr_user_err", Ncorr_user_err );

  if ( isVerbose() ) {

    test &= tuple->column( "Ncand_eta1", Ncand_eta1 );
    test &= tuple->column( "Ncorr_eta1", Ncorr_eta1 );
    test &= tuple->column( "Ncorr_eta1_err", Ncorr_eta1_err );

    test &= tuple->column( "Ncand_eta2", Ncand_eta2 );
    test &= tuple->column( "Ncorr_eta2", Ncorr_eta2 );
    test &= tuple->column( "Ncorr_eta2_err", Ncorr_eta2_err );
  }

  if ( m_Include_NoData_Table == true ) {
    test &= tuple->column( "Ncorr_MC", N_corr_MC );
    test &= tuple->column( "Ncorr_MC_err", Ncorr_MC_err );
  }

  return StatusCode( test );
}