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
// Include files
// ============================================================================
// LoKiAlgo
// ============================================================================
#include "LoKi/Algo.h"
#include "LoKi/ParticleCuts.h"
// ============================================================================
// DaVinci Kernel
// ============================================================================
#include "Kernel/IJetMaker.h"
#include "Kernel/IParticleCombiner.h"
// ============================================================================
// Event
// ============================================================================
#include "Event/Particle.h"
// ============================================================================
namespace LoKi {
  // ==========================================================================
  /** @class JetMakerWR2Vtx
   *
   *  This file is a part of LoKi project -
   *    "C++ ToolKit  for Smart and Friendly Physics Analysis"
   *
   *  The package has been designed with the kind help from
   *  Galina PAKHLOVA and Sergey BARSUK.  Many bright ideas,
   *  contributions and advices from G.Raven, J.van Tilburg,
   *  A.Golutvin, P.Koppenburg have been used in the design.
   *
   *  @author Vanya BELYAEV belyaev@lapp.in2p3.fr
   *  @date   2005-03-21
   */
  class JetMakerWR2Vtx : public LoKi::Algo {
  public:
    // ========================================================================
    /** Standard constructor
     *  @param name instance name
     *  @param pSvc pointer to Service Locator
     */
    JetMakerWR2Vtx( const std::string& name, ISvcLocator* pSvc )
        : LoKi::Algo( name, pSvc )
        //
        , m_makerName( "LoKi::FastJetMaker" )
        , m_maker( 0 )
        , m_VtxLoc( "" ) {
      //
      declareProperty( "JetMaker", m_makerName, "Type type/name of jet-maker tool (IJetMaker interface)" );
      declareProperty( "InputRecVtxLoc", m_VtxLoc, "RecVtx Input location" );

      //
    }
    // ========================================================================
    /** standard execution of the algorithm
     *  @see LoKi::Algo
     *  @return status code
     */
    StatusCode analyse() override;

  private:
    // ========================================================================
    /// maker name
    std::string m_makerName; // jet maker name
    /// maker
    const IJetMaker* m_maker; // jet maker to be used
    std::string      m_VtxLoc;

    // ========================================================================
  };
  // ==========================================================================
} // end of namespace LoKi
// ============================================================================
/** @file
 *  Implementation file for class  LoKi::JetMakerWR2Vtx
 *  @date  2005-03-21
 *  @author Vanya BELYAEV  belyaev@lapp.in2p3.fr
 */

// ============================================================================
/*  standard execution of the algorithm
 *  @see LoKi::Algo
 *  @return status code
 */
// ===========================================================================
StatusCode LoKi::JetMakerWR2Vtx::analyse() {
  using namespace LoKi;
  using namespace LoKi::Types;
  // select all input particles
  Range all = select( "all", LoKi::Cuts::PALL );

  // input container of "particles"
  const std::vector<const LHCb::Particle*> input( all.begin(), all.end() );

  // const LHCb::RecVertex vtx;
  if ( 0 == m_maker ) { m_maker = tool<IJetMaker>( m_makerName, m_makerName, this ); }

  if ( m_VtxLoc == "" ) {

    IJetMaker::Jets jets;

    StatusCode sc = m_maker->makeJets( input, jets );
    if ( sc.isFailure() ) { return Error( "Error from seed maker", sc ); }

    int myj = 0;
    while ( !jets.empty() ) {

      LHCb::Particle* jet = jets.back();

      myj++;
      if ( msgLevel( MSG::DEBUG ) ) {
        debug() << "SeedsP " << myj << "| nb of combin Seeds:  " << jet->weight()
                << "  nb part in the jet:  " << jet->daughtersVector().size() << "  Pt:  " << jet->pt() << endmsg;
        debug() << "        | m  : " << jet->momentum() << endmsg;
        debug() << "        | eta: " << jet->momentum().eta() << "  / phi: " << jet->momentum().phi() << endmsg;
        debug() << "        |Chi2: " << jet->endVertex()->chi2() << endmsg;
        debug() << "        |nDoF: " << jet->endVertex()->nDoF() << endmsg;
        debug() << "        |C/N : " << jet->endVertex()->chi2PerDoF() << endmsg;
      }

      save( "jets", jet ).ignore();
      jets.pop_back();
      delete jet;
    }
  }

  if ( !exist<LHCb::RecVertex::Range>( m_VtxLoc ) ) return Error( "the VtxLoc do not exsit" );

  const LHCb::RecVertex::Range PVs = get<LHCb::RecVertex::Range>( m_VtxLoc );

  if ( msgLevel( MSG::DEBUG ) ) debug() << "Vtx size : " << PVs.size() << endmsg;

  int i = 0;
  // std::vector<int> sjets;
  for ( LHCb::RecVertex::Range::const_iterator ipv2 = PVs.begin(); ipv2 != PVs.end(); ++ipv2 ) {
    //   sjets.at(i) = 0;

    if ( msgLevel( MSG::DEBUG ) ) debug() << "Vtx: " << i << endmsg;

    IJetMaker::Jets jets;

    const LHCb::RecVertex vtx = **ipv2;

    // make the jets
    StatusCode sc = m_maker->makeJets( input, vtx, jets );

    if ( sc.isFailure() ) { return Error( "Error from seed maker", sc ); }

    // save all jets
    int myj = 0;

    while ( !jets.empty() ) {

      LHCb::Particle* jet = jets.back();
      //     sjets.at(i)++;
      myj++;
      if ( msgLevel( MSG::DEBUG ) ) {
        debug() << "SeedsP " << myj << "| nb of combin Seeds:  " << jet->weight()
                << "  nb part in the jet:  " << jet->daughtersVector().size() << "  Pt:  " << jet->pt() << endmsg;
        debug() << "        | m  : " << jet->momentum() << endmsg;
        debug() << "        | eta: " << jet->momentum().eta() << "  / phi: " << jet->momentum().phi() << endmsg;
        debug() << "        |Chi2: " << jet->endVertex()->chi2() << endmsg;
        debug() << "        |nDoF: " << jet->endVertex()->nDoF() << endmsg;
        debug() << "        |C/N : " << jet->endVertex()->chi2PerDoF() << endmsg;
      }

      save( "jets", jet ).ignore();
      jets.pop_back();
      delete jet;
    }
    //   i++;
  }

  // int kk=0;
  // for(int jj = 0; jj != (int)  sjets.size(); jj++)
  //   if( sjets.at(i) > 0)
  //     kk++;

  // if(kk > 1) std::cout<<"evt :"<<evt<<std::endl;

  if ( msgLevel( MSG::DEBUG ) ) { counter( "#jets" ) += selected( "jets" ).size(); }

  setFilterPassed( true );

  return StatusCode::SUCCESS;
}
// ===========================================================================
/// The factory
DECLARE_COMPONENT( LoKi::JetMakerWR2Vtx )
// ============================================================================
// The END
// ============================================================================
