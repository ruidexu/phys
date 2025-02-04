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
#ifndef TUPLETOOLWZJETS_H
#define TUPLETOOLWZJETS_H 1
#include "Kernel/FilterParticlesBase.h"
#include "Kernel/IJetMaker.h"
#include "Kernel/IParticleFilter.h"
#include "Kernel/IParticlePropertySvc.h"
#include "Kernel/IParticleTupleTool.h"
#include "Kernel/ParticleProperty.h"
#include "LoKi/PhysTypes.h"
#include "TupleToolJetsBase.h"
#include <utility>

// autor: Albert Bursche
class TupleToolWZJets : public TupleToolJetsBase, virtual public IParticleTupleTool {

public:
  /// Standard constructor
  TupleToolWZJets( const std::string& type, const std::string& name, const IInterface* parent );

  virtual ~TupleToolWZJets(){}; ///< Destructor

  StatusCode fill( const LHCb::Particle*, const LHCb::Particle*, const std::string&, Tuples::Tuple& ) override;

  StatusCode initialize() override;

private:
  std::vector<LHCb::Particle*> m_decayParticles;

  /// Check if your track belongs to your decay or not
  bool isParticleInDecay( const LHCb::Particle* part );

  /// Save all particles in your decay descriptor in a vector
  void SaveDecayChainParticles( const LHCb::Particle* top );

  std::string m_BaseName;
  // std::string m_BosonContainer;
  std::vector<std::string> m_PartContainer;
  unsigned int             m_MaxJets;
  bool                     m_IsoJetAbsID;
  //  Tuples::Tuple* m_tuple;
  std::string                       m_prefix;
  const IJetMaker*                  m_AdditionalJetMaker;
  const IJetMaker*                  m_IsoJetMaker;
  const IParticleFilter*            m_LokiAddJetFilter;
  const IParticleFilter*            m_LokiIsoJetFilter;
  const LHCb::IParticlePropertySvc* m_ppSvc;
  unsigned int                      m_magic; // magic number to identify the decay products in the jet

  LoKi::Types::Fun m_DPHI;
  LoKi::Types::Fun m_DETA;
  LoKi::Types::Fun m_DR2;

  LHCb::Particles& GetParticles();
  void             AddDecProducts( LHCb::Particles& );
  bool             StoreAdditionalJets( const IJetMaker::Jets& AddJets );
  bool             MatchAndStoreIsoJets( const IJetMaker::Jets& IsoJets );
  bool             WriteJetComparisonToTuple( const LHCb::Particle* jet, std::string prefix );
  void             addBasicParticles( std::map<int, int>& particleCharges, LHCb::Particles& myParts,
                                      LHCb::Particle::ConstVector parts );
};

#endif // TUPLETOOLWZJETS_H
