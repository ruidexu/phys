/***************************************************************************** \
* (c) Copyright 2019-2021 CERN for the benefit of the LHCb Collaboration      *
*                                                                             *
* This software is distributed under the terms of the GNU General Public      *
* Licence version 3 (GPL Version 3), copied verbatim in the file "COPYING".   *
*                                                                             *
* In applying this licence, CERN does not waive the privileges and immunities *
* granted to it by virtue of its status as an Intergovernmental Organization  *
* or submit itself to any jurisdiction.                                       *
\*****************************************************************************/
// Include files
#include <boost/foreach.hpp>

// from Gaudi
#include "Event/ProtoParticle.h"
#include "GaudiAlg/GaudiAlgorithm.h"
#include "TrackInterfaces/ITrackSelector.h"

// from LHCb
#include "Event/ProcStatus.h"
#include "Event/RecVertex.h"

#include "KalmanFilter/FastVertex.h"
#include "LoKi/Constants.h"
#include "LoKi/TrackCuts.h"

// boost
#include "boost/limits.hpp"
#include "boost/numeric/conversion/bounds.hpp"

// TrackKernel
#include "TrackKernel/TrackCloneData.h"

using namespace LoKi::Cuts;

//-----------------------------------------------------------------------------
// Implementation file for class: PFlowProtoFilter
//
// @author S. Farry
// 2019-03-27
// Based heavily on code by Wouter et. al.. (TrackUniqueSegmentSelectorS20p3)
// Designed for jet particle flow selection, to select only tracks with unique
// velo segments. Also includes a track selector for filtering
//-----------------------------------------------------------------------------

class PFlowProtoFilter : public GaudiAlgorithm {

public:
  /// Standard constructor
  PFlowProtoFilter( const std::string& name, ISvcLocator* pSvcLocator );

  virtual ~PFlowProtoFilter(); ///< Destructor

  StatusCode initialize() override; ///< Algorithm initialization

  StatusCode execute() override; ///< Algorithm execution

  /// flag clones by modifying track Clone flag. note this function /changes/ the tracks!
  // StatusCode flag( std::vector<const LHCb::ProtoParticle*>& protos ) const;

  /// select a subset of tracks with unique velo/T segments
  // StatusCode select( const LHCb::ProtoParticles* protosin, LHCb::ProtoParticles* protosout ) const;

private:
  bool m_debug;

  bool m_verbose;
  /// this is the routine that does the actual work.
  void flagClones( std::vector<LHCb::ProtoParticle*> protos, std::vector<bool>& isclone ) const;

  // track selector
  ITrackSelector* m_trSel;
  // ToolHandle<ITrackSelector> m_trSel ;
  // track selector type
  std::string m_trSelType;

  bool m_debugLevel;

  LHCb::ProtoParticles* m_inputProtos;
  // LHCb::Track::ConstVector m_outputTracks;

  // std::vector<std::string> m_protosLocations; ///< where the input tracks are located
  std::string m_protosLocation;
  std::string m_outputLocation;
};

// Declaration of the Algorithm Factory
DECLARE_COMPONENT( PFlowProtoFilter )

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
PFlowProtoFilter::PFlowProtoFilter( const std::string& name, ISvcLocator* pSvcLocator )
    : GaudiAlgorithm( name, pSvcLocator ), m_trSel( NULL ) {
  declareProperty( "Input", m_protosLocation, "Input ProtoParticle location" );

  declareProperty( "Output", m_outputLocation = "Rec/ProtoP/Unique", "Output ProtoParticle location" );

  declareProperty( "TrackSelectorType", m_trSelType = "" );
}
//=============================================================================
// Destructor
//=============================================================================
PFlowProtoFilter::~PFlowProtoFilter() {}

//=============================================================================
// Initialization
//=============================================================================
StatusCode PFlowProtoFilter::initialize() {
  const StatusCode sc = GaudiAlgorithm::initialize();
  if ( sc.isFailure() ) { return sc; }

  m_debug   = msgLevel( MSG::DEBUG );
  m_verbose = msgLevel( MSG::VERBOSE );

  if ( m_trSelType != "" ) m_trSel = tool<ITrackSelector>( m_trSelType, "TrackSelector", this );

  return sc;
}

namespace {

  /// Helper class to cache information about tracks needed to check
  /// that they are clones. This is now derived from TrackCloneData,
  /// but since we only use velo hits, it may be better to just copy
  /// what we need.

  class TrackData : public LHCb::TrackCloneData<false, false> {
  public:
    TrackData( const LHCb::ProtoParticle* proto, size_t index )
        : LHCb::TrackCloneData<false, false>( TrackPtr( proto->track() ) ), m_index( index ) {
      m_weightFromHits        = proto->track() ? ( proto->track()->nDoF() - proto->track()->chi2() ) : 0;
      m_flaggedByCloneCleaner = proto->track() ? ( proto->track()->info( LHCb::Track::CloneDist, -1 ) > 0 ) : false;
      m_ghostprob             = proto->track() ? ( proto->track()->ghostProbability() ) : 0;
      // the sorting criteria is based on track type, number of hits
      // and chi2/dof, just like in trackclonecleaner. I am not sure
      // if number of hits is so great criterion: can we somehow give
      // the chi2 a bit more weight?
      static const int weightFromType[10] = {0, 11, 10, 20, 15, 16, 12, 2, 3};
      m_weightFromType                    = weightFromType[proto->track()->type()];
    }
    double weightFromHits() const { return m_weightFromHits; }

    size_t index() const { return m_index; }

    // this routine should actually be in base class
    size_t nHits( HitType type ) const { return lhcbIDs( type ).size(); }

    // This routine determines the order of tracks. Of two tracks that
    // are clones, only the first one is selected. We give a
    // preference to longer tracks. Furthermore, in order to ease
    // comparison with the standard clone cleaner, we rank tracks with
    // clone dist flag lower.
    bool operator<( const TrackData& rhs ) const {
      // added in ghost probability as condition
      return m_weightFromType > rhs.m_weightFromType ||
             ( m_weightFromType == rhs.m_weightFromType &&
               ( m_flaggedByCloneCleaner < rhs.m_flaggedByCloneCleaner ||
                 ( m_flaggedByCloneCleaner == rhs.m_flaggedByCloneCleaner &&
                   ( m_ghostprob < rhs.m_ghostprob ||
                     ( m_ghostprob == rhs.m_ghostprob && m_weightFromHits > rhs.m_weightFromHits ) ) ) ) );
    }

  private:
    double m_weightFromHits;
    size_t m_index;
    int    m_weightFromType;
    bool   m_flaggedByCloneCleaner;
    double m_ghostprob;
  };
} // namespace

//=============================================================================
// Main execution
//=============================================================================
void PFlowProtoFilter::flagClones( std::vector<LHCb::ProtoParticle*> protos, std::vector<bool>& isclone ) const {
  // initialize all values to false
  size_t N = protos.size();
  isclone.resize( 0 );
  isclone.resize( N, false );

  if ( m_debugLevel ) debug() << "==> Execute" << endmsg;

  // we don't want dynamic memory allocation as it is expensive.
  std::vector<TrackData> alltracksstore;
  alltracksstore.reserve( N );
  size_t i( 0 );
  for ( auto ip : protos ) alltracksstore.push_back( TrackData( ( ip ), i++ ) );

  // create vector of pointers and sort it
  std::vector<std::reference_wrapper<TrackData>> alltracks( std::begin( alltracksstore ), std::end( alltracksstore ) );
  std::stable_sort( alltracks.begin(), alltracks.end(),
                    []( const TrackData& lhs, const TrackData& rhs ) { return lhs < rhs; } );

  // loop over all tracks and add them to output container if they
  // pass selector and are not yet there.
  std::vector<std::reference_wrapper<TrackData>> selectedtracks;
  selectedtracks.reserve( alltracks.size() );
  for ( auto it = alltracks.begin(); it != alltracks.end(); ++it ) {
    TrackData& itd( *it );

    bool found( false );
    bool iHasVelo = itd.nHits( TrackData::VeloR ) > 0;
    for ( auto jt( selectedtracks.begin() ), jend( selectedtracks.end() ); jt != jend && !found; ++jt ) {
      TrackData& jtd( *jt );
      bool       jHasVelo = jtd.nHits( TrackData::VeloR ) > 0;

      // our main goal is two remove velo segments that have been used
      // more than once to create different long tracks.  however, we
      // also see track finding errors in the velo tracking: often
      // there are tracks that share most phi hits and a few R
      // hits. the minimal criteria to catch these all is two require
      // two R and two phi hits overlap since that essentially defines
      // a straight line. however, this looks a bit too inclusive. so
      // in the end we require 2 hits for tracks with 3 or 4 hits, and
      // 3 or more for tracks with more hits.

      // computing how many hits are in common, is expensive. that's why this looks a bit cumbersome.
      size_t nCommonR, nCommonPhi;
      found =
          iHasVelo && jHasVelo &&
          ( ( nCommonR = itd.nCommon( jtd, TrackData::VeloR ) ) >= 2 &&
            ( nCommonR >= 3 || std::min( itd.nHits( TrackData::VeloR ), jtd.nHits( TrackData::VeloR ) ) < 5 ) ) &&
          ( ( nCommonPhi = itd.nCommon( jtd, TrackData::VeloPhi ) ) >= 2 &&
            ( nCommonPhi >= 3 || std::min( itd.nHits( TrackData::VeloPhi ), jtd.nHits( TrackData::VeloPhi ) ) < 5 ) );

      if ( !found && ( itd.overlapFraction( jtd, TrackData::VeloR ) >= 0.5 &&
                       itd.overlapFraction( jtd, TrackData::VeloPhi ) >= 0.5 ) ) {
        info() << "Huh? " << itd.nCommon( jtd, TrackData::VeloR ) << " " << itd.nHits( TrackData::VeloR ) << " "
               << jtd.nHits( TrackData::VeloR ) << " | " << itd.nCommon( jtd, TrackData::VeloPhi ) << " "
               << itd.nHits( TrackData::VeloPhi ) << " " << jtd.nHits( TrackData::VeloPhi ) << endmsg;
      }

      // For T tracks we just use '>50%' overlap.  After some
      // deliberation, decided that we don't check for T if tracks are
      // really different in the Velo. Otherwise we just loose too
      // many good velo segments.
      if ( !found && !iHasVelo ) found = itd.overlapFraction( jtd, TrackData::T ) > 0.5;

      if ( found && m_debugLevel ) {
        verbose() << "Found clone: " << itd.nCommon( jtd, TrackData::VeloPhi ) << " "
                  << itd.nCommon( jtd, TrackData::VeloR ) << " j: " << jtd.track().type() << " "
                  << jtd.lhcbIDs( TrackData::VeloPhi ).size() << " " << jtd.lhcbIDs( TrackData::VeloR ).size() << " "
                  << jtd.track().info( LHCb::Track::CloneDist, -1 ) << " i: " << itd.track().type() << " "
                  << itd.lhcbIDs( TrackData::VeloPhi ).size() << " " << itd.lhcbIDs( TrackData::VeloR ).size() << " "
                  << itd.track().info( LHCb::Track::CloneDist, -1 ) << endmsg;
      }
    }
    if ( !found )
      selectedtracks.push_back( itd );
    else {
      isclone[itd.index()] = true;
    }
  }

  if ( m_debugLevel ) debug() << "Selected " << selectedtracks.size() << " out of " << alltracks.size() << endmsg;
}

//=============================================================================
// Main execution
//=============================================================================
StatusCode PFlowProtoFilter::execute() {
  if ( m_debug ) { debug() << "==> Execute" << endmsg; }

  setFilterPassed( false );

  LHCb::ProtoParticles* outputProtos = new LHCb::ProtoParticles();
  put( outputProtos, m_outputLocation );

  m_inputProtos = get<LHCb::ProtoParticles>( m_protosLocation );

  std::vector<LHCb::ProtoParticle*> toFlag;

  int ntrackprotos = 0;

  // we first accept any protos without a track, and put the others in a container to be
  // checked for shared velo segments, and that they pass the track selection
  for ( LHCb::ProtoParticles::iterator itr = m_inputProtos->begin(); itr != m_inputProtos->end(); ++itr ) {
    if ( ( *itr )->track() ) {
      ntrackprotos++;
      if ( m_trSel && m_trSel->accept( *( *itr )->track() ) ) {
        toFlag.push_back( const_cast<LHCb::ProtoParticle*>( *itr ) );
      }
    } else {
      outputProtos->insert( const_cast<LHCb::ProtoParticle*>( *itr ) );
    }
  }
  counter( "# input protos" ) += ( outputProtos->size() + ntrackprotos );
  counter( "# input protos with track" ) += toFlag.size();

  std::vector<bool> isclone( m_inputProtos->size(), false );
  flagClones( toFlag, isclone );

  for ( unsigned int i = 0; i < toFlag.size(); ++i )
    if ( !isclone[i] ) outputProtos->insert( toFlag[i] );

  counter( "# accepted protos" ) += outputProtos->size();

  setFilterPassed( true );
  return StatusCode::SUCCESS;
}
