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
#ifndef DECAYTUPLE_IPARTICLETUPLETOOL_H
#define DECAYTUPLE_IPARTICLETUPLETOOL_H 1

// Include files
// from STL
#include <string>

// from Gaudi
#include "GaudiKernel/IAlgTool.h"

namespace Tuples {
  class Tuple;
}
namespace LHCb {
  class Particle;
}

/** @class IParticleTupleTool
 *
 * Fill some particle related variables into a tuple.
 *
 * \sa IEventTupleTool
 *
 * @author Jeremie Borel
 * @date November 2007
 */
struct GAUDI_API IParticleTupleTool : extend_interfaces<IAlgTool> {

  DeclareInterfaceID( IParticleTupleTool, 2, 0 );

  //! Fill the tuple.
  //! - \b top  : may be used to provide additional information about \b part, like the top particle of the decay.
  //! - \b part : the particle about which some info are filled.
  //! - \b head : prefix for the tuple column name.
  //! - \b tuple: the tuple to fill
  virtual StatusCode fill( const LHCb::Particle* top, const LHCb::Particle* part, const std::string& head,
                           Tuples::Tuple& tuple ) = 0;
};

#endif // DECAYTUPLE_IPARTICLETUPLETOOL_H
