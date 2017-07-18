///
/// \file PWGCF/FEMTOSCOPY/AliFemto/AliFemtoCorrFctn.h
///

#pragma once

#ifndef AliFemtoCorrFctn_hh
#define AliFemtoCorrFctn_hh

#include "AliFemtoAnalysis.h"
#include "AliFemtoEvent.h"
#include "AliFemtoPair.h"
#include "AliFemtoPairCut.h"

/// \class AliFemtoCorrFctn
/// \brief The pure-virtual base class for correlation functions
///
/// All correlation function classes must inherit from this one.
///
/// This class has a optional pointers to the "parent" analysis and
/// a pair cut
///
/// Pure-abstract functions:
/// - *Report* - Create string regarding statistics of the
///    correlation function
/// - *Finish* - Any code required to run at end of analysis
///
class AliFemtoCorrFctn {

  friend class AliFemtoAnalysis;

public:
  /// Initialize with no analysis and pair cut
  AliFemtoCorrFctn();

  /// Copy constructor - DO NOT USE (does not copy data). Use `Clone` instead.
  AliFemtoCorrFctn(const AliFemtoCorrFctn& aCorrFctn);

  /// Destructor (no-op as these objects do not own analysis nor PairCut)
  virtual ~AliFemtoCorrFctn() {/* no-op */};

  /// Assignment operator copies both pointers
  AliFemtoCorrFctn& operator=(const AliFemtoCorrFctn& aCorrFctn);

  /// Return a string containing statistics about run
  virtual AliFemtoString Report() = 0;

  /// Add a "real" pair (i.e. particles from same event) to the correlation function
  virtual void AddRealPair(AliFemtoPair* aPair);
  /// Add a "mixed" pair (i.e. particles from different events) to the correlation function
  virtual void AddMixedPair(AliFemtoPair* aPir);

  /// Not Implemented - Add pair with optional
  virtual void AddFirstParticle(AliFemtoParticle *particle, bool mixing);
  virtual void AddSecondParticle(AliFemtoParticle *particle);
  virtual void CalculateAnglesForEvent();

  /// Called when switching to a new event
  virtual void EventBegin(const AliFemtoEvent* aEvent);

  /// Called when finsihed running over all data from event
  virtual void EventEnd(const AliFemtoEvent* aEvent);

  /// Called after analysis has completed - put cleanup code here
  virtual void Finish() = 0;

  /// Return a TList of analysis TObjects to return
  virtual TList* GetOutputList() = 0;

  /// Clone this object - should be overridden by subclass
  virtual AliFemtoCorrFctn* Clone() { return 0; }

  /// Return the associated FemtoAnalysis
  AliFemtoAnalysis* HbtAnalysis() { return fyAnalysis; };

  /// Set the parent FemtoAnalysis object
  void SetAnalysis(AliFemtoAnalysis* aAnalysis);

  /// Set the pair cut object
  void SetPairSelectionCut(AliFemtoPairCut* aCut);

protected:
  AliFemtoAnalysis* fyAnalysis; //!<! Link to the analysis
  AliFemtoPairCut* fPairCut;    //!<! This is a PairSelection criteria for this Correlation Function

private:

#ifdef __ROOT__
  /// \cond CLASSIMP
  ClassDef(AliFemtoCorrFctn, 1);
  /// \endcond
#endif
};

inline void AliFemtoCorrFctn::SetAnalysis(AliFemtoAnalysis* analysis)
{
  fyAnalysis = analysis;
}

inline void AliFemtoCorrFctn::SetPairSelectionCut(AliFemtoPairCut* cut)
{
  fPairCut = cut;
}

inline void AliFemtoCorrFctn::EventBegin(const AliFemtoEvent* /* event */)
{ // no-op
}

inline void AliFemtoCorrFctn::EventEnd(const AliFemtoEvent* /* event */)
{  // no-op
}




#endif
