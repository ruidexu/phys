/*****************************************************************************\
* (c) Copyright 2000-2022 CERN for the benefit of the LHCb Collaboration      *
*                                                                             *
* This software is distributed under the terms of the GNU General Public      *
* Licence version 3 (GPL Version 3), copied verbatim in the file "COPYING".   *
*                                                                             *
* In applying this licence, CERN does not waive the privileges and immunities *
* granted to it by virtue of its status as an Intergovernmental Organization  *
* or submit itself to any jurisdiction.                                       *
*                                                                             *
* Tuple tool to add jet's kinematics and jet's constituents' variables.       *
* To add constituent's variables choose withJetConstituents = True             *
* in your DaVinci script.                                                     *
\*****************************************************************************/
#ifndef TUPLETOOLJETSBASE_H
#define TUPLETOOLJETSBASE_H 1

#include "DecayTreeTupleBase/TupleToolBase.h"
#include "Event/CaloCluster.h"
#include "Event/HltObjectSummary.h"
#include "Event/Particle.h"
#include "Event/ProtoParticle.h"
#include "Event/RecVertex.h"
#include "Event/Track.h"
#include "Kernel/IDistanceCalculator.h"
#include "Kernel/IParticleTupleTool.h"
#include "Kernel/JetEnums.h"
#include "Kernel/ParticleProperty.h"
#include "LoKi/Algo.h"
#include "LoKi/LoKi.h"

#include "Kernel/ITriggerTisTos.h"

// autor: Albert Bursche
class TupleToolJetsBase : public TupleToolBase, virtual public IParticleTupleTool {
public:
  TupleToolJetsBase( const std::string& type, const std::string& name, const IInterface* parent );

  StatusCode initialize() override;

protected:
  Tuples::Tuple*             m_tuple;
  LoKi::Types::Fun           charge;
  LoKi::Types::Fun           positiveParticles;
  LoKi::Types::Fun           negativeParticles;
  LoKi::Types::Fun           neutralParticles;
  LoKi::Types::Fun           maxPT;
  LoKi::Types::Fun           m_M;
  LoKi::Types::Fun           m_MM;
  bool                       m_withJetConstituents;
  IDVAlgorithm*              m_dva;  // parent DVA Algorithm
  const IDistanceCalculator* m_dist; // for obtaining the best PV

  bool   WriteJetToTuple( const LHCb::Particle* jet, std::string prefix );
  double MaxSumNPart( const LHCb::Particle* jet, unsigned int n, const LoKi::Types::Fun& fun,
                      SmartRefVector<LHCb::Particle>* SortedDaughters );
  template <class T1, class T2>
  class Comperator {
    const LoKi::Types::Fun& m_fun;

  public:
    Comperator( const LoKi::Types::Fun& fun ) : m_fun( fun ) {}
    bool operator()( T1 t1, T2 t2 ) { return m_fun( t1 ) > m_fun( t2 ); }
  };
};

#endif // TUPLETOOLJETSBASE_H
