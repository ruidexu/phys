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
#ifndef KERNEL_IDECODESIMPLEDECAYSTRING_H
#define KERNEL_IDECODESIMPLEDECAYSTRING_H 1
// ============================================================================
// Include files
// ============================================================================
// STS&STL
// ============================================================================
#include <string>
#include <vector>
// ============================================================================
// GaudiKernel
// ============================================================================
#include "GaudiKernel/IAlgTool.h"
// ============================================================================
// forward declarations
// ============================================================================
namespace Decays {
  class Decay;
}
// ============================================================================
/** @class IDecodeSimpleDecayString
 *  IDecodeSimpleDecayString.h Kernel/IDecodeSimpleDecayString.h
 *
 *
 *  @author Patrick KOPPENBURG
 *  @date   2004-06-30
 */
struct GAUDI_API IDecodeSimpleDecayString : extend_interfaces<IAlgTool> {
  // ==========================================================================
  /// interface machinery
  DeclareInterfaceID( IDecodeSimpleDecayString, 4, 0 );
  // ==========================================================================
  virtual StatusCode  setDescriptor( const std::string& )                            = 0;
  virtual std::string getDescriptor() const                                          = 0;
  virtual StatusCode  getStrings( std::string&, std::vector<std::string>& ) const    = 0;
  virtual StatusCode  getPIDs( int&, std::vector<int>& ) const                       = 0;
  virtual StatusCode  getStrings_cc( std::string&, std::vector<std::string>& ) const = 0;
  virtual StatusCode  getPIDs_cc( int&, std::vector<int>& ) const                    = 0;
  virtual bool        is_cc() const                                                  = 0;
  // ==========================================================================
  /** get the decay form the descriptor
   *  @param decay (output) the decay
   *  @return status code
   */
  virtual StatusCode getDecay( Decays::Decay& decay ) const = 0;
  // ==========================================================================
  /** get the charge conjugated decay form the descriptor
   *  @param decay (output) the decay
   *  @return status code
   */
  virtual StatusCode getDecay_cc( Decays::Decay& decay ) const = 0;
  // ==========================================================================
  /** get all decays form the descriptor
   *  @param decays (output) the vector of decays
   *  @return status code
   */
  virtual StatusCode getDecays( std::vector<Decays::Decay>& decays ) const = 0;
  // ==========================================================================
};
// ============================================================================
// The END
// ============================================================================
#endif // KERNEL_IDECODESIMPLEDECAYSTRING_H
