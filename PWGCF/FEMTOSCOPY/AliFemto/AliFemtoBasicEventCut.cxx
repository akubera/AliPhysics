///
/// \file AliFemtoBasicEventCut.cxx
///

#include "AliFemtoBasicEventCut.h"
#include "TObjString.h"

#ifdef __ROOT__
  /// \cond CLASSIMP
  ClassImp(AliFemtoBasicEventCut);
  /// \endcond
#endif

AliFemtoBasicEventCut::Configuration::Configuration()
  : mult_range(0, 100000)
  , vertex_z_range(-100.0f, 100.0f)
  , psi_ep_range(-1000.0f, 1000.0f)
  , select_trigger(0)
  , accept_bad_vertex(false)
  , accept_only_physics(true)
{
}

AliFemtoBasicEventCut::AliFemtoBasicEventCut():
  AliFemtoEventCut(),
  fEventMult(),
  fVertZPos(),
  fAcceptBadVertex(false),
  fNEventsPassed(0),
  fNEventsFailed(0),
  fSelectTrigger(0)
{
  /// Default constructor

  fEventMult[0] = 0;
  fEventMult[1] = 100000;
  fVertZPos[0] = -100.0;
  fVertZPos[1] = 100.0;
  fPsiEP[0] = -1000.0;
  fPsiEP[1] = 1000.0;
}

AliFemtoBasicEventCut::AliFemtoBasicEventCut(const AliFemtoBasicEventCut::Configuration& cfg):
  AliFemtoEventCut()
  // , fEventMult({cfg.mult_range.first, cfg.mult_range.second})
  // , fVertZPos({cfg.vertex_z_range.first, cfg.vertex_z_range.second})
  , fAcceptBadVertex(cfg.accept_bad_vertex)
  , fNEventsPassed(0)
  , fNEventsFailed(0)
  , fAcceptOnlyPhysics(cfg.accept_only_physics)
  , fSelectTrigger(cfg.select_trigger)
{
  fEventMult[0] = cfg.mult_range.first;
  fEventMult[1] = cfg.mult_range.second;

  fVertZPos[0] = cfg.vertex_z_range.first;
  fVertZPos[1] = cfg.vertex_z_range.second;

  fPsiEP[0] = cfg.psi_ep_range.first;
  fPsiEP[1] = cfg.psi_ep_range.second;
}


//------------------------------
AliFemtoBasicEventCut::~AliFemtoBasicEventCut()
{ // Default destructor
}

//------------------------------
bool AliFemtoBasicEventCut::Pass(const AliFemtoEvent* event)
{
  /// Pass events if they fall within the multiplicity and z-vertex
  /// position range. Fail otherwise
  ///  int mult =  event->NumberOfTracks();

  const int mult = (int) event->UncorrectedNumberOfPrimaries();
  const double vertexZPos = event->PrimVertPos().z();

  // Double_t qxEPVZERO = 0, qyEPVZERO = 0;
  // Double_t qVZERO = -999;
  const double epvzero = event->ReactionPlaneAngle();

  const bool passes_ep = (fPsiEP[0] < epvzero && epvzero < fPsiEP[1]),
           passes_mult = (fEventMult[0] <= mult && mult <= fEventMult[1]),
              passes_z = (fVertZPos[0] < vertexZPos && vertexZPos < fVertZPos[1]),
            passes_zdc = ((!fAcceptBadVertex) || (event->ZDCParticipants() > 1.0)),
        passes_trigger = ((!fSelectTrigger) || (event->TriggerCluster() == fSelectTrigger));

//   cout << "AliFemtoBasicEventCut:: epvzero:       " << fPsiEP[0] << " < " << epvzero << " < " << fPsiEP[1] << " (" << passes_ep << ")\n";
//   cout << "AliFemtoBasicEventCut:: mult:       " << fEventMult[0] << " < " << mult << " < " << fEventMult[1] << " (" << passes_mult << ")\n";
//   cout << "AliFemtoBasicEventCut:: VertexZPos: " << fVertZPos[0] << " < " << vertexZPos << " < " << fVertZPos[1] << " (" << passes_z << ")\n";
//
//   cout << "AliFemtoBasicEventCut:: VertexZErr: " << event->PrimVertCov()[4] << endl;
//
//   cout << "AliFemtoBasicEventCut:: MagneticField: " << event->MagneticField() << endl;
//   cout << "AliFemtoBasicEventCut:: IsCollisionCandidate: " << event->IsCollisionCandidate() << endl;
//   cout << "AliFemtoBasicEventCut:: TriggerCluster: " << (int)event->TriggerCluster() << " (" << passes_trigger << ")\n";
//   cout << "AliFemtoBasicEventCut:: ZDCParticipants: " << event->ZDCParticipants() << " (" << passes_zdc << ")\n";
//   cout << "AliFemtoBasicEventCut:: fSelectTrigger: " << fSelectTrigger << endl;
//   cout << "AliFemtoBasicEventCut:: fAcceptBadVertex: " << fAcceptBadVertex << endl;
//   cout << "AliFemtoBasicEventCut:: " << endl;

  const bool goodEvent = passes_ep
                      && passes_mult
                      && passes_z
                      && passes_zdc
                      && passes_trigger;

//   cout << "AliFemtoBasicEventCut:: goodEvent " << goodEvent << endl;

  goodEvent ? fNEventsPassed++ : fNEventsFailed++;

  // cout << "AliFemtoBasicEventCut:: return : " << goodEvent << endl;
//     (fAcceptBadVertex || (event->PrimVertCov()[4] > -1000.0)) &&

  return goodEvent;
}
TList* AliFemtoBasicEventCut::AppendSettings(TList *settings,
                                             const TString &prefix) const
{
  settings->AddVector(

    new TObjString(prefix + TString::Format("AliFemtoBasicEventCut.mult.min=%d", fEventMult[0])),
    new TObjString(prefix + TString::Format("AliFemtoBasicEventCut.mult.max=%d", fEventMult[1])),
    new TObjString(prefix + TString::Format("AliFemtoBasicEventCut.vertex.min=%f", fVertZPos[0])),
    new TObjString(prefix + TString::Format("AliFemtoBasicEventCut.vertex.max=%f", fVertZPos[1])),
    new TObjString(prefix + TString::Format("AliFemtoBasicEventCut.psiep.min=%f", fPsiEP[0])),
    new TObjString(prefix + TString::Format("AliFemtoBasicEventCut.psiep.max=%f", fPsiEP[1])),
    new TObjString(prefix + TString::Format("AliFemtoBasicEventCut.accept_bad_vertex=%d", fAcceptBadVertex)),
    new TObjString(prefix + TString::Format("AliFemtoBasicEventCut.accept_only_physics=%d", fAcceptOnlyPhysics)),
    new TObjString(prefix + TString::Format("AliFemtoBasicEventCut.trigger=%d", fSelectTrigger)),

  NULL);

  return settings;
}

//------------------------------
AliFemtoString AliFemtoBasicEventCut::Report()
{
  /// Prepare report
  TString report = TString::Format("Multiplicity:\t %d - %d\n", fEventMult[0], fEventMult[1]);

   report += TString::Format("Vertex Z-position:\t %E - %E\n", fVertZPos[0], fVertZPos[1])
           + TString::Format("Number of events which passed:\t%ld  Number which failed:\t%ld\n", fNEventsPassed, fNEventsFailed);

  return AliFemtoString((const char *)report);
}
void AliFemtoBasicEventCut::SetAcceptBadVertex(bool b)
{
  fAcceptBadVertex = b;
}
bool AliFemtoBasicEventCut::GetAcceptBadVertex()
{
  return fAcceptBadVertex;
}
