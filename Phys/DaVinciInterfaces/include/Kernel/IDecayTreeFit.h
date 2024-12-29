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
#ifndef KERNEL_IDECAYTREEFIT_H
#define KERNEL_IDECAYTREEFIT_H 1
// ============================================================================
// Include files
// ============================================================================
// GaudiKernel
// ============================================================================
#include "GaudiKernel/IAlgTool.h"
#include "GaudiKernel/IInterface.h"
// ============================================================================
// DaVinciTypes
// ============================================================================
#include "Kernel/DecayTree.h"
// ============================================================================
// forward declarations
// ============================================================================
namespace Gaudi {
  namespace Math {
    class ParticleParams;
  }
} // namespace Gaudi
namespace LHCb {
  class Particle;
} // namespace LHCb
namespace LHCb {
  class ParticleID;
} // namespace LHCb
namespace LHCb {
  class DecayTree;
} // namespace LHCb
// ============================================================================
/** @class IDecayTreeFit Kernel/IDecayTreeFit.h
 *
 *  The abstract interface for wrapping of "Decay-Tree-Fitter",
 *  the nice utility for globl fits of decay trees,
 *  coded by Wouter Hulsbergen
 *
 *  @see DecayTreeFitter::Fitter
 *  @author Vanya Belyaev
 *  @date   2010-05-24
 *
 */
struct GAUDI_API IDecayTreeFit : extend_interfaces<IAlgTool> {
  // ==========================================================================
  /// interface machinery
  DeclareInterfaceID( IDecayTreeFit, 3, 0 );
  // ==========================================================================
  /// the actual type for the fit parameters
  typedef Gaudi::Math::ParticleParams Fitted;
  // ==========================================================================
  /** fit the decay tree
   *
   *  @code
   *
   *   const IDecayTreeFitter* fitter = ...;  // get the fitter
   *
   *
   *   const LHCb::Particle*   p      = ... ; // get the particle
   *
   *   // fit it !
   *   StatusCode sc = fitter -> fit ( p ) ;  // fit it!!
   *   if ( sc.isFailure() ) { ... }
   *
   *  @endcode
   *
   *  For the fit one can also use the primary vertex constraint:
   *
   *  @code
   *
   *   const IDecayTreeFitter* fitter = ...;  // get the fitter
   *
   *
   *   const LHCb::Particle*   B      = ... ; // get the particle
   *   const LHCb::VertexBase* pv     = ... ; // get the primary vertex
   *
   *   // fit it !
   *   StatusCode sc = fitter -> fit ( B , pv ) ;  // fit it!!
   *   if ( sc.isFailure() ) { ... }
   *
   *  @endcode
   *
   *  @param decay  (INPUT) the decay tree to fit
   *  @param origin (INPUT) the origin vertex
   *  @return status code
   */
  virtual StatusCode fit( const LHCb::Particle* decay, const LHCb::VertexBase* origin = 0 ) const = 0;
  // ==========================================================================
  /** get the fitted parameters for the particle
   *
   *  @code
   *
   *   const IDecayTreeFitter* fitter = ...;  // get the fitter
   *   const LHCb::Particle*   p      = ... ; // get the particle
   *
   *   // fit it !
   *   StatusCode sc = fitter -> fit ( p ) ;  // fit it!!
   *   if ( sc.isFailure() ) { ... }
   *
   *   // get the daughter particle:
   *   const LHCb::Particle* daughter = ... ;
   *
   *   const IDecayTreeFitter::Fitted* fitted =
   *      fitter ->fitter ( daughter ) ;
   *
   *   if ( 0 == fitted ) { ... }  ;           // error here
   *   else
   *     {
   *        info () << " Fitted 4-momentum of daughter  " << fitted->momenum()
   *                << " Fitted decay-legth of daughter " << fitted->decayLength()
   *                << endmsg
   *     }
   *
   *  @endcode
   *
   *   The fitted result for mother particle ("decay head") can be extracted
   *   using the defautl argument :
   *
   *  @code
   *
   *   const IDecayTreeFitter* fitter = ...;  // get the fitter
   *   const LHCb::Particle*   B      = ... ; // get the particle
   *   const LHCb::VertexBase* pv     = ... ; // get the primary vertex
   *
   *   // fit it !
   *   StatusCode sc = fitter -> fit ( B , pv ) ;  // fit it!!
   *   if ( sc.isFailure() ) { ... }
   *
   *   // extract teh fitted results :
   *   const IDecayTreeFitter::Fitted* fitted = fitter ->fitter () ;
   *
   *   if ( 0 == fitted ) { ... }  ;           // error here
   *   else
   *     {
   *        info () << " Fitted 4-momentum   " << fitted->momenum()
   *                << " Fitted decay-length " << fitted->decayLength()
   *                << endmsg
   *     }
   *
   *  @endcode
   *
   *  @see IDecayTreeFit::Fitted
   *  @see Gaudi::Math::ParticleParams
   *  @see Gaudi::Math::ParticleParams::momentum
   *  @see Gaudi::Math::ParticleParams::decayLength
   *
   *  @param particle (INPUT) the particle, NULL corresponds to the decay head
   *  @return the fitted parameters, NULL for invalid argument/fit failure
   */
  virtual const Fitted* fitted( const LHCb::Particle* p = 0 ) const = 0;
  // ==========================================================================
  /** get the fit resuts in form of self-consistent decay tree
   *
   *  @code
   *
   *   const IDecayTreeFitter* fitter = ...;  // get the fitter
   *   const LHCb::Particle*   p      = ... ; // get the particle
   *
   *   // fit it !
   *   StatusCode sc = fitter -> fit ( p ) ;  // fit it!!
   *   if ( sc.isFailure() ) { ... }
   *
   *   // get the daughter particle:
   *   const LHCb::Particle* daughter = ... ;
   *
   *   // get the fitted tree:
   *   LHCb::DecayTree tree = fitter->fittedTree() ;
   *
   *   // get the fitted daughter form the tree
   *   const LHCb::Particle* fitted = tree.findClone ( *daughter ) ;
   *
   *  @endcode
   *
   *  @see LHCb::DecayTree
   *
   *  @return the whole fitted tree
   */
  virtual LHCb::DecayTree fittedTree() const = 0;
  // ==========================================================================
  /** the chi2 of the global fit
   *
   *  @code
   *
   *   IDecayTreeFitter*       fitter = ...;  // get the fitter
   *   const LHCb::Particle*   p      = ... ; // get the particle
   *
   *   // fit it !
   *   StatusCode sc = fitter -> fit ( p ) ;  // fit it!!
   *   if ( sc.isFailure() ) { ... }
   *
   *   // get chi2
   *   const double chi2 = fitter->chi2() ;
   *
   *  @endcode
   *
   *  @return chi2 of global fit procedure
   */
  virtual double chi2() const = 0;
  // ==========================================================================
  /** number degress of freeedom for the global fit
   *
   *  @code
   *
   *   IDecayTreeFitter*       fitter = ...;  // get the fitter
   *   const LHCb::Particle*   p      = ... ; // get the particle
   *
   *   // fit it !
   *   StatusCode sc = fitter -> fit ( p ) ;  // fit it!!
   *   if ( sc.isFailure() ) { ... }
   *
   *   // get degrees-of-freedom
   *   const unsigned int ndoF = fitter->nDoF () ;
   *
   *  @endcode
   *
   *  @return number of degrees of freedom
   */
  virtual unsigned int nDoF() const = 0;
  // ==========================================================================
  /** add the constraint
   *
   *  @code
   *
   *   IDecayTreeFitter*       fitter = ...;  // get the fitter
   *   const LHCb::Particle*   p      = ... ; // get the particle
   *
   *   // apply mass-constrainst for charm for the next fit
   *   fitter -> addConstraint ( LHCb::ParticleID( 240  )  ) ;
   *   fitter -> addConstraint ( LHCb::ParticleID( 140  )  ) ;
   *
   *   // fit it !
   *   StatusCode sc = fitter -> fit ( p ) ;  // fit it!!
   *   if ( sc.isFailure() ) { ... }
   *
   *  @endcode
   *
   * @attention Mass-constraints is active only for the next call
   *            of IDecayTreeFit::fit
   *
   *  @param pid (INPUT) particle-ID to be constrained
   */
  virtual void addConstraint( const LHCb::ParticleID& pid ) = 0;
  // ==========================================================================
  /** add the constraint
   *
   *  @code
   *
   *   IDecayTreeFitter*       fitter = ...;  // get the fitter
   *   const LHCb::Particle*   p      = ... ; // get the particle
   *
   *   const double mass1 = ... ;
   *   const double mass2 = ... ;
   *
   *   // apply mass-constrainst for charm for the next fit
   *   fitter -> addConstraint ( LHCb::ParticleID( 240  )  , mass1 ) ;
   *   fitter -> addConstraint ( LHCb::ParticleID( 140  )  , mass2 ) ;
   *
   *   // fit it !
   *   StatusCode sc = fitter -> fit ( p ) ;  // fit it!!
   *   if ( sc.isFailure() ) { ... }
   *
   *  @endcode
   *
   * @attention Mass-constraints is active only for the next call
   *            of IDecayTreeFit::fit
   *
   *  @param pid (INPUT) particle-ID to be constrained
   */
  virtual void addConstraint( const LHCb::ParticleID& pid, const double mass ) = 0;
  // ==========================================================================
};
// ============================================================================
// The END
// ============================================================================
#endif // KERNEL_IDECAYTREEFIT_H
