/*****************************************************************************\
* (c) Copyright 2000-2022 CERN for the benefit of the LHCb Collaboration      *
*                                                                             *
* This software is distributed under the terms of the GNU General Public      *
* Licence version 3 (GPL Version 3), copied verbatim in the file "COPYING".   *
*                                                                             *
* In applying this licence, CERN does not waive the privileges and immunities *
* granted to it by virtue of its status as an Intergovernmental Organization  *
* or submit itself to any jurisdiction.                                       *
\*****************************************************************************/
#ifndef TUPLETOOLJETS_H
#define TUPLETOOLJETS_H 1

#include "Kernel/IParticleTupleTool.h"
#include "TupleToolJetsBase.h"

// autor: Albert Bursche
class TupleToolJets : public TupleToolJetsBase, virtual public IParticleTupleTool {

public:
  /// Standard constructor
  TupleToolJets( const std::string& type, const std::string& name, const IInterface* parent );

  virtual ~TupleToolJets() {} ///< Destructor

  StatusCode fill( const LHCb::Particle*, const LHCb::Particle*, const std::string&, Tuples::Tuple& ) override;

private:
  const LHCb::Particle* m_p;
  std::string           m_head;
  bool                  m_withJetConstituents;
};

#endif // TUPLETOOLJETS_H
