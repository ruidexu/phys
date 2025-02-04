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
// $Id: IJetTagTool.h,v 1.1 2011/06/28 11:22:33 aphan Exp $

//-----------------------------------------------------------------------------
//
// Abstract interface for Jet Tag Tools
//
//-----------------------------------------------------------------------------

#ifndef IJETTAGTOOL_H
#define IJETTAGTOOL_H 1

// ============================================================================
// Includes

// from Gaudi
#include "GaudiKernel/IAlgTool.h"

// from Event
#include "Event/Particle.h"
#include "Event/RecVertex.h"

// ============================================================================
// Declaration

class GAUDI_API IJetTagTool : virtual public IAlgTool {

public:
  // Interface machinery
  DeclareInterfaceID( IJetTagTool, 2, 0 );

  // Method that calculates a jet property
  //  Takes a jet (1st parameter)
  //  Returns the jet property (2nd parameter)
  virtual bool calculateJetProperty( const LHCb::Particle* jet, std::map<std::string, double>& jetWeight

                                     ) = 0;

protected:
private:
};

#endif
