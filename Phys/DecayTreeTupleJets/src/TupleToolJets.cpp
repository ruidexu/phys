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
#include "TupleToolJets.h"
#include "boost/lexical_cast.hpp"
#include <boost/bind.hpp>
#include <math.h>

//-----------------------------------------------------------------------------
// Implementation file for class : TupleToolJets
// Autor: Albert Bursche
//-----------------------------------------------------------------------------

// Declaration of the Tool Factory
DECLARE_COMPONENT( TupleToolJets )

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
TupleToolJets::TupleToolJets( const std::string& type, const std::string& name, const IInterface* parent )
    : TupleToolJetsBase( type, name, parent )

{
  declareInterface<IParticleTupleTool>( this );
  declareProperty( "withJetConstituents", m_withJetConstituents = false, "Save jets constituents?" );
}

//=============================================================================

StatusCode TupleToolJets::fill( const LHCb::Particle* /* top */, const LHCb::Particle* p, const std::string& head,
                                Tuples::Tuple& tuple ) {
  m_tuple   = &tuple;
  bool test = true;
  m_p       = p;
  m_head    = m_extraName + head;
  test &= WriteJetToTuple( p, m_head );
  return StatusCode( test );
}
