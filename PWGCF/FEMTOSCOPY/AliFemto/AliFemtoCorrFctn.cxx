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
  cout << "AliFemtoCorrFctn::AddRealPair -- Not implemented\n";
}

void AliFemtoCorrFctn::AddMixedPair(AliFemtoPair*)
{
  cout << "AliFemtoCorrFctn::AddMixedPair -- Not implemented\n";
}

void AliFemtoCorrFctn::AddFirstParticle(AliFemtoParticle*, bool)
{
  cout << "AliFemtoCorrFctn::AddFirstParticle -- Not implemented\n";
}

void AliFemtoCorrFctn::AddSecondParticle(AliFemtoParticle*)
{
  cout << "AliFemtoCorrFctn::AddSecondParticle -- Not implemented\n";
}

void AliFemtoCorrFctn::CalculateAnglesForEvent()
{
  cout << "AliFemtoCorrFctn::CalculateAnglesForEvent -- Not implemented\n";
}
