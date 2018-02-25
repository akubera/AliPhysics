///
/// \file AliAnalysisTaskFemtoConfig.h
///

#pragma once

#ifndef ALIANALYSISTASKFEMTOCONFIG_H
#define ALIANALYSISTASKFEMTOCONFIG_H

#include "TH1.h"
#include "TString.h"

#include "AliESDInputHandler.h"
#include "AliAODHandler.h"
#include "AliAODInputHandler.h"
#include "AliMCEventHandler.h"
#include "AliESDEvent.h"
#include "AliAODEvent.h"
#include "AliMCEvent.h"

//#include "AliAnalysisTask.h"
#include "AliAnalysisTaskSE.h"
#include "AliAnalysisManager.h"
#include "AliAnalysisDataContainer.h"

#include "AliFemtoEventReaderESDChain.h"
#include "AliFemtoEventReaderESDChainKine.h"
#include "AliFemtoEventReaderAODChain.h"
#include "AliFemtoEventReaderStandard.h"
#include "AliFemtoEventReaderKinematicsChain.h"
#include "AliFemtoEventReaderKinematicsChainESD.h"
#include "AliFemtoEventReaderAODKinematicsChain.h"
#include "AliFemtoManager.h"

#include "AliESDpid.h"
#include "AliAODpidUtil.h"
#include "AliAODHeader.h"

#include "AliFemtoConfigObject.h"

/// \class AliAnalysisTaskFemtoConfig
/// \brief An AliAnalysisTaskSE class for building Femto-Analysis objects from
///       an AliFemtoConfigObject
///
/// As with all [AliAnalysisTasks](@ref AliAnalysisTask), an AliAnalysisTaskFemtoConfig
/// should be created from your macro and added to the AliAnalysisManager. The
/// proper way to construct an AliAnalysisTaskFemtoConfig is through the use of a
/// configuration macro file which defines a function with signature
///    `AliFemtoManager* ConfigFemtoAnalysis()`
/// whose name is specified to the constructor. The default name of this file
/// is 'ConfigFemtoAnalysis.C'. The macro is responsible for creating an
/// AliFemtoAnalysisManager and loading your custom AliFemtoAnalyses. Upon the
/// call to ::CreateOutputObjects, the macro will be loaded, and the analysis
/// manager created and added to the AliAnalysisTaskFemtoConfig. Parameters can be
/// specified in the constructor via the TString `aConfigParams`.
///
/// \author Andrew Kubera <Andrew.Kubera@cern.ch>, OSU
///
class AliAnalysisTaskFemtoConfig : public AliAnalysisTaskSE {
public:

protected:
  AliESDEvent          *fESD;          //!<! ESD object
  AliESDpid            *fESDpid;       //!<! ESDpid object
  AliAODEvent          *fAOD;          //!<! AOD object
  AliAODpidUtil        *fAODpidUtil;   ///<  AliAODpidUtil object
  AliAODHeader         *fAODheader;    ///<  AliAODHeader object (to get reference multiplicity in pp)

  AliStack             *fStack;        //!<! Stack from Kinematics
  TList                *fOutputList;   ///<  AliFemto results list
  AliFemtoEventReader  *fReader;       //!<! Reference to the reader
  AliFemtoManager      *fManager;      //!<! AliFemto top-level manager
  Int_t                fAnalysisType;  ///<  Mark ESD of AOD analysis
  TString              fConfigMacro;   ///<  Config macro location
  TString              fConfigParams;  ///<  Config macro parameters
  Bool_t               fVerbose;

public:

  /// Default parameters initialize all values to zero (NULL) and empty strings
  ///
  /// Do not use this constructor - objects created with it have no way to set
  /// the configuration macro or parameters. Use an alternative constructor.
  AliAnalysisTaskFemtoConfig();

  /// Full Constructor - Set the name of the task, configuration macro filename
  /// and paramters, and optional verbosity flag.
  AliAnalysisTaskFemtoConfig(TString name, TString aConfigMacro, TString aConfigParams, Bool_t aVerbose=kFALSE);

  /// Configuration-Object Constructor, all properties derrived
  AliAnalysisTaskFemtoConfig(TString name, AliFemtoConfigObject obj);

  /// Construct with task name, configuration filename, and verbosity flag.
  ///
  /// The paramters are set to the empty string.
  AliAnalysisTaskFemtoConfig(TString name, TString aConfigMacro, Bool_t aVerbose=kFALSE);

  /// Copy Constructor - should not be used
  AliAnalysisTaskFemtoConfig(const AliAnalysisTaskFemtoConfig& aFemtoTask);
  virtual ~AliAnalysisTaskFemtoConfig();

  AliAnalysisTaskFemtoConfig& operator=(const AliAnalysisTaskFemtoConfig& aFemtoTask);

  /// ConnectInputData
  virtual void ConnectInputData(Option_t *);
  virtual void CreateOutputObjects();
  virtual void Exec(Option_t *option);
  virtual void Terminate(Option_t *);
  virtual void FinishTaskOutput();

  /// Set the femtomanager containing this task's analyses.
  void SetFemtoManager(AliFemtoManager *aManager);

  void SetFemtoReaderESD(AliFemtoEventReaderESDChain *aReader);
  void SetFemtoReaderESDKine(AliFemtoEventReaderESDChainKine *aReader);
  void SetFemtoReaderAOD(AliFemtoEventReaderAODChain *aReader);
  void SetFemtoReaderStandard(AliFemtoEventReaderStandard *aReader);
  void SetFemtoReaderKinematics(AliFemtoEventReaderKinematicsChain *aReader);
  void SetFemtoReaderKinematicsESD(AliFemtoEventReaderKinematicsChainESD *aReader);
  void SetFemtoReaderAODKinematics(AliFemtoEventReaderAODKinematicsChain *aReader);

private:
  /// \cond CLASSIMP
  ClassDef(AliAnalysisTaskFemtoConfig, 1);
  /// \endcond
};

inline
AliAnalysisTaskFemtoConfig::AliAnalysisTaskFemtoConfig()
  : AliAnalysisTaskSE()
  , fESD(NULL)
  , fESDpid(NULL)
  , fAOD(NULL)
  , fAODpidUtil(NULL)
  , fAODheader(NULL)
  , fStack(NULL)
  , fOutputList(NULL)
  , fReader(NULL)
  , fManager(NULL)
  , fAnalysisType(0)
  , fConfigMacro()
  , fConfigParams()
  , fVerbose(kTRUE)
{
  /* no-op */
}

inline
void AliAnalysisTaskFemtoConfig::SetFemtoManager(AliFemtoManager *mgr)
{
  AliFemtoEventReader *event_reader = mgr->EventReader();

  if (!event_reader) {
    AliWarning("No event-reader in given AliFemtoManager! "
               "Please create and add that object to prevent future crashes.");
  }
  fManager = mgr;
  fReader = event_reader;

  if (fVerbose) {
    AliInfo(TString::Format("Set FemtoManager at %p with event-reader at %p", mgr, event_reader));
  }
}

inline
void AliAnalysisTaskFemtoConfig::Terminate(Option_t*)
{
  if (fManager) {
    fManager->Finish();
  }
}

inline
void AliAnalysisTaskFemtoConfig:: FinishTaskOutput()
{
  // Do the final processing
  if (fManager) {
    fManager->Finish();
  }
}


#endif
