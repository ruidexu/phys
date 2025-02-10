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
// $Id: DaVinciInterfacesDict.h,v 1.13 2010-07-21 21:19:27 tskwarni Exp $
#ifndef DICT_DAVINCIINTERFACESDICT_H
#define DICT_DAVINCIINTERFACESDICT_H 1

// Include files

/** @file DaVinciInterfacesDict.h
 *
 *
 *  @author Juan PALACIOS
 *  @date   2009-07-22
 */
// ============================================================================
// DaVinciKernel
// ============================================================================
#include "Kernel/IBTaggingTool.h"
#include "Kernel/IBremAdder.h"
#include "Kernel/ICaloParticleMaker.h"
#include "Kernel/IChangePIDTool.h"
#include "Kernel/ICheckOverlap.h"
#include "Kernel/ICheckSelResults.h"
#include "Kernel/IConstituentSubtractor.h"
#include "Kernel/IDVAlgorithm.h"
#include "Kernel/IDecayFinder.h"
#include "Kernel/IDecayTreeFit.h"
#include "Kernel/IDecodeSimpleDecayString.h"
#include "Kernel/IDirectionFit.h"
#include "Kernel/IDistanceCalculator.h"
#include "Kernel/IExtraInfoTool.h"
#include "Kernel/IFilterParticles.h"
#include "Kernel/IJetMaker.h"
#include "Kernel/IJets2Jets.h"
#include "Kernel/ILifetimeFitter.h"
#include "Kernel/IMassFit.h"
#include "Kernel/IP2VVAngleCalculator.h"
#include "Kernel/IP2VVPartAngleCalculator.h"
#include "Kernel/IPVReFitter.h"
#include "Kernel/IParticle2State.h"
#include "Kernel/IParticleArrayFilter.h"
#include "Kernel/IParticleCombiner.h"
#include "Kernel/IParticleDescendants.h"
#include "Kernel/IParticleFilter.h"
#include "Kernel/IParticleMaker.h"
#include "Kernel/IParticleReFitter.h"
#include "Kernel/IParticleStuffer.h"
#include "Kernel/IParticleTisTos.h"
#include "Kernel/IParticleTransporter.h"
#include "Kernel/IParticleTupleTool.h"
#include "Kernel/IParticleValue.h"
#include "Kernel/IParticleVeto.h"
#include "Kernel/IPlotTool.h"
#include "Kernel/IPrintDecay.h"
#include "Kernel/IProtoParticleFilter.h"
#include "Kernel/IRelatedPVFinder.h"
#include "Kernel/ISecondaryVertexTool.h"
#include "Kernel/ISetInputParticles.h"
#include "Kernel/IStandardParticleProvider.h"
#include "Kernel/ITagger.h"
#include "Kernel/ITisTos.h"
#include "Kernel/ITrackIsolation.h"
#include "Kernel/ITriggerSelectionTisTos.h"
#include "Kernel/ITriggerTisTos.h"
#include "Kernel/IVertexFit.h"

#endif // DICT_DAVINCIINTERFACESDICT_H
