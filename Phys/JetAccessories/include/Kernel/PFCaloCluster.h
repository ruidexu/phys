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
#ifndef KERNEL_PFCALOCLUSTER_H
#define KERNEL_PFCALOCLUSTER_H 1

// Include files
#include "CaloDet/DeCalorimeter.h"
#include "Event/CaloCluster.h"
#include "Kernel/PFParticle.h"

/** @class PFCaloCluster PFCaloCluster.h
 *  PFCaloCluster inherit from LHCb::CaloCluster
 *  and contains few usefull extra information
 *
 *  @author Victor Coco
 *  @date   2012-07-23
 */
namespace LHCb {

  class PFCaloCluster : public CaloCluster {
  public:
    enum BanStatusType { Available = 0, AvailableForNeutralRecovery, ContainsInfMomentum, Used };

    /// Copy constructor from CaloCluster
    PFCaloCluster( const CaloCluster& c )
        : CaloCluster( c )
        , m_nSat( 0 )
        , m_status( Available )
        , m_trackKeyBestPointing( -1 )
        , m_trackWeightBestPointing( -1. ){};
    /// Copy constructor from PFCaloCluster
    PFCaloCluster( const PFCaloCluster& pfc )
        : CaloCluster( pfc )
        , m_nSat( pfc.m_nSat )
        , m_status( pfc.m_status )
        , m_trackKeyBestPointing( pfc.m_trackKeyBestPointing )
        , m_trackWeightBestPointing( pfc.m_trackWeightBestPointing )
        , m_particleList( pfc.m_particleList ){};

    /// Destructor
    ~PFCaloCluster(){};

    int nSat() const { return m_nSat; };

    int status() const { return m_status; };

    void setStatus( int status ) {
      // If anything else than ContainsInfMomentum and Used alredy, then fill
      if ( this->m_status < ContainsInfMomentum ) this->m_status = status;
      // Otherwise only fill if it is not already used
      else if ( this->m_status != Used )
        this->m_status = status;
    };
    // TODO: ther accessors
    void updateParticleList( const LHCb::PFParticle* part ) {
      // if (part->info(LHCb::PFParticle::Type,LHCb::PFParticle::Unknown)>LHCb::PFParticle::Unknown){
      this->m_particleList.push_back( part );
      //}
      /* else{
      int pftype(LHCb::PFParticle::Unknown);
      if ( part->particleID().isHadron() && part->particleID().threeCharge ()!=0 ) pftype =
      LHCb::PFParticle::ChargedHadron ; else if (part->particleID().abspid()==11) pftype = LHCb::PFParticle::Electron;
      else if (part->particleID().abspid()==13) pftype = LHCb::PFParticle::Muon;
      this->m_particleList.push_back(std::make_pair(part,pftype));
      }*/
    };

    std::vector<const LHCb::PFParticle*> particleList() const { return m_particleList; };

  protected:
  private:
    int    m_nSat;                    ///< Number of saturated cells
    int    m_status;                  ///< Cluster status
    int    m_trackKeyBestPointing;    ///< Key of the track with best pointing to the cluster
    double m_trackWeightBestPointing; ///< Weight of the best pointing track to the cluster
    std::vector<const LHCb::PFParticle*> m_particleList;
  };
} // namespace LHCb

#endif // KERNEL_PFCALOCLUSTER_H
