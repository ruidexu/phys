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
#ifndef VERTEXFITTER_IPARTICLECOMBINER_H
#define VERTEXFITTER_IPARTICLECOMBINER_H 1
// ============================================================================
// Include files
// ============================================================================
// STD & STL
// ============================================================================
#include <vector>
// ============================================================================
// GaudiKernel
// ============================================================================
#include "GaudiKernel/IAlgTool.h"
#include "GaudiKernel/IInterface.h"
// ============================================================================
// Event
// ============================================================================
#include "Event/Particle.h"
// ============================================================================
/** @class IParticleCombiner IParticleCombiner.h
 *
 *  The first "basic" abstract interface interface
 *  for fitting/combiner tools
 *
 *  @author Vanya BELYAEV belyaev@lapp.lin2p3.fr
 *  @date   2004-12-19
 */
struct GAUDI_API IParticleCombiner : extend_interfaces<IAlgTool> {
  // ==========================================================================
  /// interafce machinery
  DeclareInterfaceID( IParticleCombiner, 2, 0 );
  // ==========================================================================
  /** The major method for "combining" the daughter particles
   *  into "mother" particle.
   *
   *  The container of input particles is "combined" into
   *  "mother" particle and its decay vertex.
   *
   *  The intermediate constrains (mass, vertex, mass-vertex,
   *  etc.. could be applied in the process of "combining",
   *  dependent on the used implementation)
   *
   *  @code
   *
   *  // locate the tool
   *  const IParticleCombiner* combiner = get<IParticleCombiner>( ... )
   *
   *  // loop over the first daughter particle
   *  for( ... ipi1 = ... ; ... ; ++ipi1 )
   *  {
   *     for( ... ipi2 = ... ; ... ; ++ipi2 )
   *     {
   *        const LHCb::Particle* pi1 = *ipi1 ;
   *        const LHCb::Particle* pi2 = *ipi2 ;
   *
   *        IParticleCombiner::LHCb::Particle::ConstVector daughters ;
   *        daughters.push_back( pi1 ) ;
   *        daughters.push_back( pi2 ) ;
   *
   *        LHCb::Particle K0S  ;
   *        Vertex   Vrtx ;
   *
   *        StatusCode sc = combiner->combine( daughters , K0S , Vrtx ) ;
   *        if( sc.isFailure() )
   *        { Warning("Error in K0S fit, skip the pair", sc ); continue ; }
   *
   *        ....
   *     }
   *  }
   *
   *  @endcode
   *
   *  @param daughters the vector of daughter particles    (input)
   *  @param mother    the "mother" particle               (output)
   *  @param vertex    the decay vertex of mother particle (output)
   *  @return status code
   */
  virtual StatusCode combine( const LHCb::Particle::ConstVector& daughters, LHCb::Particle& mother,
                              LHCb::Vertex& vertex ) const = 0;
  // ==========================================================================
  /** The method which allows to use almost an arbitrary
   *  sequence of daughter particles, e.g.
   *  LHCb::Particle::ConstVector, Particles, SmartRefVector<Particle>, etc..
   *
   *  Also this signature allow to make an easy "refit"/"recombine"
   *  of the mother particle, e.g.
   *
   *  @code
   *
   *   // locate the tool
   *   const IParticleCombiner* combiner = get<IParticleCombiner>( ... )
   *
   *   LHCb::Particle*          mother = ... ;
   *
   *   StatusCode sc = combiner->combine
   *   (  mother->vertex->products().begin() ,
   *   (  mother->vertex->products().end()   ,
   *     *mother                             ,
   *     *(mother->endVertex())              ) ;
   *
   *    if( sc.isFailure() )
   *      { Warning("Error in fitter", sc ); continue ; }
   *
   *  @endcode
   *
   *  @param begin    begin-iterator for sequence of daughter parricles
   *  @param end      end-iterator for sequence of daughter parricles
   *  @param mother   the "mother" particle               (output)
   *  @param vertex   the decay vertex of mother particle (output)
   *  @return status code
   */
  template <class DAUGHTER>
  inline StatusCode combine( DAUGHTER begin, DAUGHTER end, LHCb::Particle& mother, LHCb::Vertex& vertex ) const {
    const LHCb::Particle::ConstVector children = Daughters( begin, end );
    return combine( children, mother, vertex );
  }
  // ==========================================================================
};
// ============================================================================
// The END
// ============================================================================
#endif // VERTEXFITTER_IPARTICLECOMBINER_H
