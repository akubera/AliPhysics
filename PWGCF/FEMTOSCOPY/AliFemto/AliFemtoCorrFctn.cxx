///
/// \file PWGCF/FEMTOSCOPY/AliFemto/AliFemtoCorrFctn.cxx
///

#include "AliFemtoCorrFctn.h"
#include "AliLog.h"

AliFemtoCorrFctn::AliFemtoCorrFctn():
  fyAnalysis(nullptr),
  fPairCut(nullptr)
{
  /* no-op */
}

AliFemtoCorrFctn::AliFemtoCorrFctn(const AliFemtoCorrFctn& orig):
  fyAnalysis(nullptr),
  fPairCut(nullptr)
{
}

AliFemtoCorrFctn& AliFemtoCorrFctn::operator=(const AliFemtoCorrFctn& aCorrFctn)
{
  if (this != &aCorrFctn) {
    fyAnalysis = aCorrFctn.fyAnalysis;
    fPairCut = aCorrFctn.fPairCut;
  }

  return *this;
}

void AliFemtoCorrFctn::AddRealPair(AliFemtoPair*)
{
  cout << "[AliFemtoCorrFctn::AddRealPair] Not implemented" << endl;
}

void AliFemtoCorrFctn::AddMixedPair(AliFemtoPair*)
{
  cout << "[AliFemtoCorrFctn::AddMixedPair] Not implemented" << endl;
}

void AliFemtoCorrFctn::AddFirstParticle(AliFemtoParticle*, bool)
{
  cout << "[AliFemtoCorrFctn::AddFirstParticle] Not implemented" << endl;
}

void AliFemtoCorrFctn::AddSecondParticle(AliFemtoParticle*)
{
  cout << "[AliFemtoCorrFctn::AddSecondParticle] Not implemented" << endl;
}

void AliFemtoCorrFctn::CalculateAnglesForEvent()
{
  cout << "[AliFemtoCorrFctn::CalculateAnglesForEvent] Not implemented" << endl;
}


#ifdef __ROOT__
  /// \cond CLASSIMP
  ClassImp(AliFemtoCorrFctn);
  /// \endcond
#endif
