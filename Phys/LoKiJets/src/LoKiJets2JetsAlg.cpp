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
#include "GaudiAlg/GaudiAlgorithm.h"
// ============================================================================
// DaVinci Kernel
// ============================================================================
#include "Kernel/IJets2Jets.h"
// ===========================================================================
// Event
// ============================================================================
#include "Event/Particle.h"
// ============================================================================

// ==========================================================================
/** @class Jets2JetsAlg
 *  @date  2009-10-29
 *  @author Victor Coco  victor.coco@cern.ch
 *
 */
class Jets2JetsAlg : public GaudiAlgorithm {
  // ========================================================================
  /// the friend factory for instantiation
  // ========================================================================
public:
  // ========================================================================
  /** Standard constructor
   *  @param name instance name
   *  @param pSvc pointer to Service Locator
   */
  Jets2JetsAlg( const std::string& name, ISvcLocator* pSvc )
      : GaudiAlgorithm( name, pSvc )
      //
      , m_jetMatcherName()
      , m_jetALocation()
      , m_jetBLocation()
      , m_output()
      , m_jetMatcher( 0 ) {
    //
    declareProperty( "Jets2Jets", m_jetMatcherName, "Type type/name of jet-jetMatcher tool (IJets2Jets interface)" );
    declareProperty( "JetsALocation", m_jetALocation, "Location of the first set of jet" );
    declareProperty( "JetsBLocation", m_jetBLocation, "Location of the second set of jet" );
    declareProperty( "OutputTable", m_output, "Location of the output table" );
    //
  }
  // ========================================================================
public:
  // ========================================================================
  /** standard execution of the algorithm
   *  @see LoKi::Algo
   *  @return status code
   */
  StatusCode initialize() override;
  StatusCode execute() override;
  // ========================================================================

  // ========================================================================
private:
  // ========================================================================
  /// jetMatcher name
  std::string m_jetMatcherName; ///< jet jetMatcher name
  std::string m_jetALocation;   ///< Location of the first set of jet
  std::string m_jetBLocation;   ///< Location of the second set of jet
  std::string m_output;         ///< Location of the second set of jet
  /// jetMatcher
  const IJets2Jets* m_jetMatcher; ///< jet jetMatcher to be used
  // ========================================================================
};
// ==========================================================================
// end of namespace LoKi
// ============================================================================
/** @file
 *  Implementation file for class Jets2JetsAlg
 *  Client for implementation of IJets2Jets, furnishing the sets of jets out of
 *  transiant event store location and recording the resulting output table
 *
 *  @date  2009-10-29
 *  @author Victor COCO  victor.coco@cern.ch
 */

// Declaration of the Algorithm Factory
DECLARE_COMPONENT( Jets2JetsAlg )

StatusCode Jets2JetsAlg::initialize() {
  StatusCode sc = GaudiAlgorithm::initialize();
  if ( sc.isFailure() ) return sc;
  if ( m_jetALocation.empty() || m_jetBLocation.empty() ) return Error( "No input locations is specified" );
  if ( m_jetMatcherName.empty() || m_jetBLocation.empty() ) return Error( "No jet matching tool specified" );
  if ( m_output.empty() ) return Error( "No OutputTable is specified" );
  return sc;
}

StatusCode Jets2JetsAlg::execute() {
  // Get the jets
  const LHCb::Particles* PartsA = get<LHCb::Particles>( m_jetALocation );
  const LHCb::Particles* PartsB = get<LHCb::Particles>( m_jetBLocation );
  if ( PartsA->size() == 0 || PartsB->size() == 0 ) {
    Warning( "No jets to match in the event" ).ignore();
    setFilterPassed( false );
    return StatusCode::SUCCESS;
  }
  IJets2Jets::Jets* JetsA = new IJets2Jets::Jets();
  IJets2Jets::Jets* JetsB = new IJets2Jets::Jets();
  for ( LHCb::Particles::const_iterator ip = PartsA->begin(); PartsA->end() != ip; ip++ ) JetsA->push_back( *ip );
  for ( LHCb::Particles::const_iterator ip = PartsB->begin(); PartsB->end() != ip; ip++ ) JetsB->push_back( *ip );
  if ( 0 == m_jetMatcher ) m_jetMatcher = tool<IJets2Jets>( m_jetMatcherName, m_jetMatcherName, this );

  // create the relation table
  IJets2Jets::Table* table = new IJets2Jets::Table();
  put( table, m_output );

  // call the tool
  m_jetMatcher->makeRelation( *JetsA, *JetsB, *table );

  // total number of established links
  const size_t links = table->relations().size();

  // make a statistics
  if ( msgLevel( MSG::VERBOSE ) ) { counter( "# " + m_jetALocation + "->" + m_jetBLocation ) += links; }
  //
  if ( table->relations().empty() ) {
    Warning( "The relation table is empty!" ).ignore();
    setFilterPassed( false );
  }
  setFilterPassed( true );

  return StatusCode::SUCCESS;
}

// ===========================================================================
/// The factory
// ============================================================================
// The END
// ============================================================================
