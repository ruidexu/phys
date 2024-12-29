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
#ifndef KERNEL_ICHECKSELRESULTS_H
#define KERNEL_ICHECKSELRESULTS_H 1
// ============================================================================
// Include files
// ============================================================================
// STD/STL
// ============================================================================
#include <string>
#include <vector>
// ============================================================================
// GaudKernel
// ============================================================================
#include "GaudiKernel/IAlgTool.h"
// ============================================================================
/** @class ICheckSelResults Kernel/ICheckSelResults.h
 *
 *  Thw abstract interface for checking of selection result
 *
 *  @author Vanya BELYAEV Ivan.Belyaev@lapp.in2p3.fr
 *  @date   2005-07-22
 */
struct GAUDI_API ICheckSelResults : extend_interfaces<IAlgTool> {
  // ==========================================================================
  /// interface machinery
  DeclareInterfaceID( ICheckSelResults, 2, 0 );
  // ==========================================================================
  /// the actual type of "Selections"
  typedef std::string Selection;
  /// the actual type of "Selections"
  typedef std::vector<Selection> Selections;
  // ==========================================================================
  /** check if the event has been (pre)selected
   *  @return true if the event has been (pre)selected
   */
  virtual bool isSelected() const = 0;
  // ==========================================================================
  /** check if the event has been (pre)selected by a certain selection
   *  @param  selection selection name
   *  @return true if the event has been (pre)selected
   */
  virtual bool isSelected( const Selection& selection ) const = 0;
  // ==========================================================================
  /** check if the event has been (pre)selected by certain selection(s)
   *  @param  selections vector of selection names
   *  @param  ANDMode    flag to distinguish AND/OR modes
   *  @return true if the event has been (pre)selected by *ALL*
   *    selections (AND-mode) or by at least one preselection (OR-mode)
   */
  virtual bool isSelected( const Selections& selections, const bool ANDMode = false ) const = 0;
  // ==========================================================================
};
// ============================================================================
// The END
// ============================================================================
#endif // KERNEL_ICHECKSELRESULTS_H
