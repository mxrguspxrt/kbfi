#define MyAnalysis_cxx
// The class definition in MyAnalysis.h has been generated automatically
// by the ROOT utility TTree::MakeSelector(). This class is derived
// from the ROOT class TSelector. For more information on the TSelector
// framework see $ROOTSYS/README/README.SELECTOR or the ROOT User Manual.

// The following methods are defined in this file:
//    Begin():        called every time a loop on the tree starts,
//                    a convenient place to create your histograms.
//    SlaveBegin():   called after Begin(), when on PROOF called only on the
//                    slave servers.
//    Process():      called for each event, in this function you decide what
//                    to read and fill your histograms.
//    SlaveTerminate: called at the end of the loop on the tree, when on PROOF
//                    called only on the slave servers.
//    Terminate():    called at the end of the loop on the tree,
//                    a convenient place to draw/fit your histograms.
//
// To use this file, try the following session on your Tree T:
//
// Root > T->Process("MyAnalysis.C")
// Root > T->Process("MyAnalysis.C","some options")
// Root > T->Process("MyAnalysis.C+")
//

#include "MyAnalysis.h"
#include <iostream>
#include <TH1F.h>
#include <TLine.h>
#include <TH3F.h>
#include <TLatex.h>
#include <TCanvas.h>
#include <stdlib.h>
#include <map>
#include "TGraphAsymmErrors.h"
#include "TCanvas.h"
#include <stdlib.h>
#include "TLorentzVector.h"
#include <math.h>

using namespace std;

void MyAnalysis::BuildEvent() {

   Muons.clear();
   for (int i = 0; i < NMuon; ++i) {
      MyMuon muon(Muon_Px[i], Muon_Py[i], Muon_Pz[i], Muon_E[i]);
      muon.SetIsolation(Muon_Iso[i]);
      muon.SetCharge(Muon_Charge[i]);
      Muons.push_back(muon);
   }

   Electrons.clear();
   for (int i = 0; i < NElectron; ++i) {
      MyElectron electron(Electron_Px[i], Electron_Py[i], Electron_Pz[i], Electron_E[i]);
      electron.SetIsolation(Electron_Iso[i]);
      electron.SetCharge(Electron_Charge[i]);
      Electrons.push_back(electron);
   }

   Photons.clear();
   for (int i = 0; i < NPhoton; ++i) {
      MyPhoton photon(Photon_Px[i], Photon_Py[i], Photon_Pz[i], Photon_E[i]);
      photon.SetIsolation(Photon_Iso[i]);
      Photons.push_back(photon);
   }

   Jets.clear();
   for (int i = 0; i < NJet; ++i) {
      MyJet jet(Jet_Px[i], Jet_Py[i], Jet_Pz[i], Jet_E[i]);
      jet.SetBTagDiscriminator(Jet_btag[i]);
      jet.SetJetID(Jet_ID[i]);
      Jets.push_back(jet);
   }

   hadB.SetXYZM(MChadronicBottom_px, MChadronicBottom_py, MChadronicBottom_pz, 4.8);
   lepB.SetXYZM(MCleptonicBottom_px, MCleptonicBottom_py, MCleptonicBottom_pz, 4.8);
   hadWq.SetXYZM(MChadronicWDecayQuark_px, MChadronicWDecayQuark_py, MChadronicWDecayQuark_pz, 0.0);
   hadWqb.SetXYZM(MChadronicWDecayQuarkBar_px, MChadronicWDecayQuarkBar_py, MChadronicWDecayQuarkBar_pz, 0.0);
   lepWl.SetXYZM(MClepton_px, MClepton_py, MClepton_pz, 0.0);
   lepWn.SetXYZM(MCneutrino_px, MCneutrino_py, MCneutrino_pz, 0.0);
   met.SetXYZM(MET_px, MET_py, 0., 0.);

   EventWeight *= weight_factor;

}

void MyAnalysis::Begin(TTree * /*tree*/) {
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

}

void MyAnalysis::SlaveBegin(TTree * /*tree*/) {
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

   // task 1
   h_Mmumu = this->createHistogram("Invariant di-muon mass", 60, 60, 120);
   h_NMuon = this->createHistogram("Number of muons", 7, 0, 7);

   // task 2
   numberOfMuonsBeforeCut = this->createHistogram("Number of muons before cut", 7, 0, 7);
   numberOfMuonsAfterCut = this->createHistogram("Number of muons after cut", 7, 0, 7);


   h_NJets = this->createHistogram("Number of jets before cut", 12, 0, 12);
   h_NJetsAfterCut = this->createHistogram("Number of jets after cut", 12, 0, 12);
   // hasTwoOppositelyChargedLeptonsHistogram = this->createHistogram("Has two opposite charged leptons", 2, 0, 2);
   // hasTwoOppositelyChargedLeptonsHistogramAfterCut = this->createHistogram("Has two opposite charged leptons after cut", 2, 0, 2);
   h_NBtaggedJets = this->createHistogram("Number of btagged jets", 12, 0, 12);
   h_NBtaggedJetsAfterCut = this->createHistogram("Number of btagged after cut", 12, 0, 12);

   h_MJets = this->createHistogram("Invariant mass of jets", 50, 0, 100);
   h_PerpJets = this->createHistogram("Tranverse component for jets", 50, 0, 100);
   h_MET = this->createHistogram("sqrt(MET_px*MET_px + MET_py*MET_py)", 50, 0, 100);
   h_IsolationElectrons = this->createHistogram("Electrons isolation", 50, 0, 100);
   h_NElectrons = this->createHistogram("Electrons count", 10, 0, 10);
   muonsEtaHistogram = this->createHistogram("Muons (eta)", 8, -4, 4);
   muonsPhiHistogram = this->createHistogram("Muons (phi)", 8, -4, 4);
   muonsPtHistogram = this->createHistogram("Muons (pt)", 20, 0, 200);
   muonsChargeHistogram = this->createHistogram("Muons charge", 50, -2, 2);
   electronsEtaHistogram = this->createHistogram("Electrons (eta)", 8, -4, 4);
   electronsPhiHistogram = this->createHistogram("Electrons (phi)", 8, -4, 4);
   electronsPtHistogram = this->createHistogram("Electrons (pt)", 50, 0, 200);
   electronsChargeHistogram = this->createHistogram("Electrons charge", 4, -2, 2);
   jetsEtaHistogram = this->createHistogram("Jets (eta)", 50, -4, 4);
   jetsPhiHistogram = this->createHistogram("Jets (phi)", 50, -4, 4);
   jetsPtHistogram = this->createHistogram("Jets (pt)", 20, 0, 200);

   signalBackgroundHistogram = this->createHistogram("S/B", 2, 1, 2);
   signalBackgroundAfterCutsHistogram = this->createHistogram("S/B after cuts", 2, 1, 2);


   // task 3
   int pins = 50;
   int xup = 0;
   int xlow = 200;

   ex3MuonsOver25Pt = this->createHistogram("ex3MuonsOver25Pt: Muon pt over 25GeV", 25, xup, 225);
   ex3MuonsOver25PtPassedHlt = this->createHistogram("ex3MuonsOver25PtPassedHlt: Muon pt over 25GeV passed HLT", 25, xup, 225);
   ex3MuonsOver25PtHltEffiency = this->createHistogram("ex3MuonsOver25PtHltEffiency: Efficiency for pt", 25, xup, 225);
   ex3TotalEvents = this->createHistogram("ex3TotalEvents", 100, 0, 2);
   ex3AFterCutsEvents = this->createHistogram("ex3AFterCutsEvents", 100, 0, 2);
   ex3AFterCutsAcceptance = this->createHistogram("ex3AFterCutsAcceptance", 100, 0, 2);
   MassOfHadronicTopGeneratorHistogram = this->createHistogram("MassOfHadronicTopGeneratorHistogram", 100, 0, 200);
   MassOfLeptonicTopGeneratorHistogram = this->createHistogram("MassOfLeptonicTopGeneratorHistogram", 100, 0, 200);
}


double MyAnalysis::getMuonHighestPt() {
   double muonHighestPt = 0;

   for (vector<MyMuon>::iterator muon = Muons.begin(); muon != Muons.end(); ++muon) {
      if (muon->IsIsolated() && muon->Pt() > muonHighestPt) {
         muonHighestPt = muon->Pt();
      }
   }
   return muonHighestPt;
}


TH1F* MyAnalysis::createHistogram(const char *name, int nbinsx, double xlow, double xup) {
   TH1F *th1f = new TH1F(name, name, nbinsx, xlow, xup);
   th1f->SetXTitle(name);
   th1f->Sumw2();
   histograms.push_back(th1f);
   histograms_MC.push_back(th1f);
   return th1f;
}

Bool_t MyAnalysis::Process(Long64_t entry) {
   // The Process() function is called for each entry in the tree (or possibly
   // keyed object in the case of PROOF) to be processed. The entry argument
   // specifies which entry in the currently loaded tree is to be processed.
   // It can be passed to either MyAnalysis::GetEntry() or TBranch::GetEntry()
   // to read either all or the required parts of the data. When processing
   // keyed objects with PROOF, the object is already loaded and is available
   // via the fObject pointer.
   //
   // This function should contain the "body" of the analysis. It can contain
   // simple or elaborate selection criteria, run algorithms on the data
   // of the event and typically fill histograms.
   //
   // The processing can be stopped by calling Abort().
   //
   // Use fStatus to set the return value of TTree::Process().
   //
   // The return value is currently not used.

   ++TotalEvents;
   TotalEventsWithEventWeight += EventWeight;

   GetEntry(entry);

   if (TotalEvents % 10000 == 0)
      cout << "Next event -----> " << TotalEvents << endl;

   BuildEvent();

   double MuonPtCut = 25.;
   double MuonRelIsoCut = 0.10;

   ProcessEx1();
   ProcessEx2();
   ProcessEx3();
   ProcessEx4();
   // Eyeball();


   return kTRUE;
}

Bool_t MyAnalysis::ProcessEx1() {
   double MuonPtCut = 25.;
   double MuonRelIsoCut = 0.10;

   int N_Muon = 0;
   int N_IsoMuon = 0;
   MyMuon *muon1, *muon2;

   for (vector<MyMuon>::iterator jt = Muons.begin(); jt != Muons.end(); ++jt) {
      ++N_Muon;
      if (jt->IsIsolated(MuonRelIsoCut)) {
         ++N_IsoMuon;
         if (N_IsoMuon == 1) muon1 = &(*jt);
         if (N_IsoMuon == 2) muon2 = &(*jt);
      }
   }

   h_NMuon->Fill(N_IsoMuon, EventWeight);

   if (N_IsoMuon > 1 && triggerIsoMu24) {
      if (muon1->Pt()>MuonPtCut) {
         h_Mmumu->Fill((*muon1 + *muon2).M(), EventWeight);
      }
   }

   return true;
}

Bool_t MyAnalysis::ProcessEx2() {

   if (!triggerIsoMu24) {
      return kTRUE;
   }


   // Generate Histogram that compares signal/background without cuts
   signalBackgroundHistogram->Fill(1, EventWeight);


   // n muon cut
   int nMuon = Muons.size();
   numberOfMuonsBeforeCut->Fill(nMuon, EventWeight);

   if (nMuon != 1) {
      // semileptonic
      return true;
   }

   numberOfMuonsAfterCut->Fill(nMuon, EventWeight);



   // n jets cut

   int nJets = Jets.size();
   h_NJets->Fill(nJets, EventWeight);

   if (nJets < 3) {
      return kTRUE;
   }

   h_NJetsAfterCut->Fill(nJets, EventWeight);


   // has positive and negative and lepton cut

   // bool hasPositiveLepton = false;
   // bool hasNegativeLepton = false;

   // for (vector<MyMuon>::iterator it = Muons.begin(); it != Muons.end(); ++it) {
   //    if (it->GetCharge() == 1) {
   //       hasPositiveLepton = true;
   //    } else {
   //       hasNegativeLepton = true;
   //    }
   // }

   // for (vector<MyElectron>::iterator it = Electrons.begin(); it != Electrons.end(); ++it) {
   //    if (it->GetCharge() == 1) {
   //       hasPositiveLepton = true;
   //    } else {
   //       hasNegativeLepton = true;
   //    }
   // }

   // bool hasTwoOppositelyChargedLeptons = hasPositiveLepton && hasNegativeLepton;

   // hasTwoOppositelyChargedLeptonsHistogram->Fill((!hasTwoOppositelyChargedLeptons ? 0 : 1), EventWeight);



   // if (!hasTwoOppositelyChargedLeptons) {
   //    return true;
   // }

   // hasTwoOppositelyChargedLeptonsHistogramAfterCut->Fill((!hasTwoOppositelyChargedLeptons ? 0 : 1), EventWeight);


   int N_BtaggedJets = 0;

   for (vector<MyJet>::iterator it = Jets.begin(); it != Jets.end(); ++it) {
      if (it->IsBTagged()) {
         ++N_BtaggedJets;
      }
   }

   h_NBtaggedJets->Fill(N_BtaggedJets, EventWeight);


   if (N_BtaggedJets < 1) {
      return true;
   }

   h_NBtaggedJetsAfterCut->Fill(N_BtaggedJets, EventWeight);

   for (vector<MyMuon>::iterator it = Muons.begin(); it != Muons.end(); ++it) {
      muonsEtaHistogram->Fill(it->Eta(), EventWeight);
      muonsPhiHistogram->Fill(it->Phi(), EventWeight);
      muonsPtHistogram->Fill(it->Pt(), EventWeight);
      muonsChargeHistogram->Fill(it->GetCharge(), EventWeight);
   }

   for (vector<MyJet>::iterator it = Jets.begin(); it != Jets.end(); ++it) {
      h_MJets->Fill(it->M(), EventWeight);
      h_PerpJets->Fill(it->Perp(), EventWeight);

      jetsEtaHistogram->Fill(it->Eta(), EventWeight);
      jetsPhiHistogram->Fill(it->Phi(), EventWeight);
      jetsPtHistogram->Fill(it->Pt(), EventWeight);
   }
   h_MET->Fill(sqrt(MET_px*MET_px + MET_py*MET_py), EventWeight);

   int N_Electrons = 0;
   float highest_pt = 0;

   for (vector<MyElectron>::iterator it = Electrons.begin(); it != Electrons.end(); ++it) {
      ++N_Electrons;
      h_IsolationElectrons->Fill(it->GetIsolation(), EventWeight);
      electronsEtaHistogram->Fill(it->Eta(), EventWeight);
      electronsPhiHistogram->Fill(it->Phi(), EventWeight);
      electronsPtHistogram->Fill(it->Pt(), EventWeight);
      electronsChargeHistogram->Fill(it->GetCharge(), EventWeight);
   }
   h_NElectrons->Fill(N_Electrons, EventWeight);


   float higestPtForIsolatedMuon = 0;

   for (vector<MyMuon>::iterator it = Muons.begin(); it != Muons.end(); ++it) {
      if (it->IsIsolated() && higestPtForIsolatedMuon < it->Pt()) {
         higestPtForIsolatedMuon = it->Pt();
      }
   }

   signalBackgroundAfterCutsHistogram->Fill(1, EventWeight);

   return kTRUE;
}

Bool_t MyAnalysis::ProcessEx3() {

   // somehow we have triggeredevents that have no muons
   //
   if (triggerIsoMu24 && (NMuon < 1)) {
      HasTriggerIsoMu24ButHasNoMuonsWithEventWeight += EventWeight;
   }


   ex3TotalEvents->Fill(1, EventWeight);

   // For our tutorial we will restrict to semi-leptonic decay cascades of pair-produced top quarks.
   // For the purpose of our tutorial, we can take these efficiencies from the simulation.
   // (Tutorial.pdf 1)

   // The first ingredient is the trigger e ciency ✏trig. We can trust the MC simulation to reproduce this e ciency correctly. Produce the trigger “turn-on” curve which shows the trigger e ciency depending on the muon transverse momentum pT. Calculate the e ciency of triggering top quark events with a reconstructed and isolated muon of pT > 25 GeV?

   // In particle physics the semileptonic decay of a hadron refers to a decay through the weak interaction
   // in which one lepton (and the corresponding neutrino) is produced in addition to one or more hadrons.
   // (https://en.wikipedia.org/wiki/Semileptonic_decay)

   // The final state consists of two quarks (jets), two b-quarks (b-jets), one charged lepton and one neutrino.


   // 3.1
   //
   // The first ingredient is the trigger e ciency ✏trig.
   // We can trust the MC simulation to reproduce this e ciency correctly.
   // Produce the trigger “turn-on” curve which shows the trigger e ciency depending
   // on the muon transverse momentum pT. Calculate the e ciency of triggering top quark events with
   // a reconstructed and isolated muon of pT > 25 GeV?

   // Additional diary material: https://docs.google.com/document/d/1E-b1kM4vT5GqBFyYiIsPiGj23XHNZ4TOnWiywftI1Jg/edit#heading=h.bzp2qiwcyr26

   // Important to rembember in the context of this task:
   //
   // 1. We have restriction "restrict to semi-leptonic decay cascades of pair-produced top quarks".
   //    Semi-leptonic = one lepton = one muon in our case.
   // 2. Lepton-plus-jets final states provides the most accurate measurements ... better signal to background ratio
   // 3. As 3.2 contains "In addition, the acceptance includes all the selection cuts that have
   //    been found in Exercise 2. ", I expect that cuts do not apply to 3.1

   BeforeTriggerIsoMu24CutWeightedCount += EventWeight;
   if (!triggerIsoMu24) {
      return false;
   }
   AfterTriggerIsoMu24CutWeightedCount += EventWeight;


   // it is semileptonic
   BeforeMuonCutWeightedCount += EventWeight;
   if (NMuon != 1) {
      return false;
   }
   AfterMuonCutWeightedCount += EventWeight;


   TriggeredEvents++;
   TriggeredEventsWithEventWeight += EventWeight;


   MyMuon muon = Muons.at(0);
   ex3MuonsOver25Pt->Fill(muon.Pt(), EventWeight);
   ex3MuonsOver25PtPassedHlt->Fill(muon.Pt(), EventWeight);


   // it is isolated and pt is creater than 25

   if (muon.IsIsolated() != true || muon.Pt() < 25) {
      return false;
   }


   // 3.2

   // The second ingredient is the acceptance ✏acc (not including the trigger).
   // This includes the fact that we only select semi-leptonic top quark decays with muons.
   // The branching fraction is well known, so we can take it from simulation.
   // In addition, the acceptance includes all the selection cuts that have been found in Exercise 2.
   // You can calculate the acceptance by comparing the number of generated top quark events with the
   // number of selected events, after all your cuts.

   // Important to rembember:
   //
   // 1. Does not include trigger (but includes the fact that N(Muons)=1 and Pt(Muon)>25)
   // 2. Branching ratio for muon + jets is 14.8%, but we should take it from simulation.
   //    HOW? Just select one muon with some b-tagged jets?
   // 3. Acceptance = Number of selected events after cuts / Number of generated top quark events
   // 4. In the name of science I am creating new cuts here


   // HOW: data.


   // cut for 1 b-tagged jets (there should be 2, but 1 is maybe not read)

   int countBTaggedJets = 0;
   for (vector<MyJet>::iterator jet = Jets.begin(); jet != Jets.end(); ++jet) {
      if (jet->IsBTagged()) {
         countBTaggedJets++;
      }
   }

   BeforeBTaggedJetsCutWeightedCount += EventWeight;
   if (countBTaggedJets < 1) {
      return false;
   }
   AfterBTaggedJetsCutWeightedCount += EventWeight;

   Before3JetsCutWeightedCount += EventWeight;
   if (NJet < 3) {
      return false;
   }
   After3JetsCutWeightedCount += EventWeight;

   if (!triggerIsoMu24) {
      return false;
   }


   ex3AFterCutsEvents->Fill(1, EventWeight);


   // this will contain Number of selected events after cuts / Number of generated top quark events

   //ex3AFterCutsAcceptance;



   // 3.3

   // background subtraction: we also trust the simulation to correctly predict
   // the number of back- ground events after selection.
   // Subtract the expected background from the observed (selected) data events.

   // see example.c



   // // We should have one muon (TTbar Feynman)
   // if (NMuon != 1) {
   //    return true;
   // }

   // // TTbar should have two b-tagged jets
   // int N_BtaggedJets = 0;

   // for (vector<MyJet>::iterator it = Jets.begin(); it != Jets.end(); ++it) {
   //    if (it->IsBTagged()) {
   //       ++N_BtaggedJets;
   //    }
   // }

   // if (N_BtaggedJets != 2) {
   //    return true;
   // }

   // // create histograms for pt and ptPassed, because effiency = pt / ptPassed
   // double muonHighestPt = this->getMuonHighestPt();
   // ex3MuonsPtHistogram->Fill(muonHighestPt);

   // if (triggerIsoMu24) {
   //    ex3MuonsPtPassedHltHistogram->Fill(muonHighestPt, EventWeight);
   // }

   // return kTRUE;
   return true;
}

Bool_t MyAnalysis::ProcessEx4() {

   if (!triggerIsoMu24) {
      return false;
   }

   if (NMuon < 1) {
      return false;
   }

   int jetsCount = Jets.size();
   if (jetsCount != 4) {
      return false;
   }

   int bJetsCount = 0;
   for(int i = 0; i < jetsCount; i++) {
      MyJet *jet = &Jets.at(i);
      if (jet->IsBTagged()) {
         bJetsCount++;
      }
   }

   if (bJetsCount != 2) {
      return false;
   }

   PassedEx4Cuts += EventWeight;

   // What is the mass of the top quark in MC simulation (in tt events)?
   // Use the generator-level truth information to calculate the top quark fourvector in the hadronic and leptonic branch.


   // cout << "MChadronicBottom_px: " << MChadronicBottom_px << "\n";
   // cout << "MChadronicBottom_py: " << MChadronicBottom_py << "\n";
   // cout << "MChadronicBottom_pz: " << MChadronicBottom_pz << "\n";
   // cout << "MChadronicWDecayQuark_px: " << MChadronicWDecayQuark_px << "\n";
   // cout << "MChadronicWDecayQuark_py: " << MChadronicWDecayQuark_py << "\n";
   // cout << "MChadronicWDecayQuark_pz: " << MChadronicWDecayQuark_pz << "\n";
   // cout << "MChadronicWDecayQuarkBar_px: " << MChadronicWDecayQuarkBar_px << "\n";
   // cout << "MChadronicWDecayQuarkBar_py: " << MChadronicWDecayQuarkBar_py << "\n";
   // cout << "MChadronicWDecayQuarkBar_pz: " << MChadronicWDecayQuarkBar_pz << "\n";
   // cout << "MCleptonicBottom_px: " << MCleptonicBottom_px << "\n";
   // cout << "MCleptonicBottom_py: " << MCleptonicBottom_py << "\n";
   // cout << "MCleptonicBottom_pz: " << MCleptonicBottom_pz << "\n";
   // cout << "MClepton_px: " << MClepton_px << "\n";
   // cout << "MClepton_py: " << MClepton_py << "\n";
   // cout << "MClepton_pz: " << MClepton_pz << "\n";
   // cout << "MCneutrino_px: " << MCneutrino_px << "\n";
   // cout << "MCneutrino_py: " << MCneutrino_py << "\n";
   // cout << "MCneutrino_pz: " << MCneutrino_pz << "\n";


   MyJet *hadronicBottom = new MyJet();
   hadronicBottom->SetXYZM(MChadronicBottom_px, MChadronicBottom_py, MChadronicBottom_pz, 0);

   MyJet *hadronicQuark = new MyJet();
   hadronicQuark->SetXYZM(MChadronicWDecayQuark_px, MChadronicWDecayQuark_py, MChadronicWDecayQuark_pz, 0);

   MyJet *hadronicAntiQuark = new MyJet();
   hadronicAntiQuark->SetXYZM(MChadronicWDecayQuarkBar_px, MChadronicWDecayQuarkBar_py, MChadronicWDecayQuarkBar_pz, 0);

   TLorentzVector hadronicTop = (*hadronicQuark + *hadronicAntiQuark + *hadronicBottom);
   MassOfHadronicTopGeneratorHistogram->Fill(hadronicTop.M(), EventWeight);


   MyJet *leptonicBottom = new MyJet();
   leptonicBottom->SetXYZM(MCleptonicBottom_px, MCleptonicBottom_py, MCleptonicBottom_pz, 0);

   TLorentzVector *leptonicLepton = new MyJet();
   leptonicBottom->SetXYZM(MClepton_px, MClepton_py, MClepton_pz, 0);

   TLorentzVector *leptonicNeutrino = new MyJet();
   leptonicNeutrino->SetXYZM(MCneutrino_px, MCneutrino_py, MCneutrino_pz, 0);

   cout << "leptonicBottom px, py, pz: " << MCleptonicBottom_px << ", " << MCleptonicBottom_py << ", " << MCleptonicBottom_pz <<  "\n";
   cout << "MClepton px, py, pz: " << MClepton_px << ", " << MClepton_py << ", " << MClepton_pz <<  "\n";
   cout << "MCneutrino px, py, pz: " << MCneutrino_px << ", " << MCneutrino_py << ", " << MCneutrino_pz <<  "\n";

   TLorentzVector leptonicTop = (*leptonicBottom + *leptonicLepton + *leptonicNeutrino);
   cout << "leptonictop M: " << leptonicTop.M() << "\n";

   MassOfLeptonicTopGeneratorHistogram->Fill(leptonicTop.M(), EventWeight);

   return true;
}

Bool_t MyAnalysis::Eyeball() {



   // we are eyeballing only first 20 events

   bool displayOutput = TotalEvents < 20;


   // get real data about MC event

   MyJet *realMcHadronicBottomJet;
   MyJet *realMcLeptonicBottomJet;
   bool hasRealMcHadronicBottomJet;
   bool hasRealMcLeptonicBottomJet;


   if (MChadronicBottom_px != 0) {
      realMcHadronicBottomJet = new MyJet();
      realMcHadronicBottomJet->SetXYZM(MChadronicBottom_px, MChadronicBottom_py, MChadronicBottom_pz, 0);
      hasRealMcHadronicBottomJet = true;

      if (displayOutput) {
         cout << "realMcHadronicBottomJet: " << realMcHadronicBottomJet->toString() << "\n";
      }

      RealMcHadronicCount++;
   }

   if (MCleptonicBottom_px != 0) {
      realMcLeptonicBottomJet = new MyJet();
      realMcLeptonicBottomJet->SetXYZM(MCleptonicBottom_px, MCleptonicBottom_py, MCleptonicBottom_pz, 0);
      hasRealMcLeptonicBottomJet = true;

      if (displayOutput) {
         cout << "realMcLeptonicBottomJet: " << realMcLeptonicBottomJet->toString() << "\n";
      }

      RealMcLeptonicCount++;
   }



   if (hasRealMcHadronicBottomJet && hasRealMcLeptonicBottomJet) {
      RealMcSemiLeptonicDecayEvents++;
   }


   // construct vectors for both. if px, py, pz can vary a bit, angles phi and eta should remain.
   // also calculate delta R.

   MyJet *constructedMcHadronicBottomJet;
   MyJet *constructedMcLeptonicBottomJet;
   bool hasConstructedMcHadronicBottomJet;
   bool hasConstructedMcLeptonicBottomJet;

   for (int i = 0; i < Jets.size(); ++i) {

      MyJet *jet = &Jets.at(i);

      double deltaRFromRealMcHadronicBottomJet;
      double deltaRFromRealMcLeptonicBottomJet;

      if (hasRealMcHadronicBottomJet) {
         deltaRFromRealMcHadronicBottomJet = realMcHadronicBottomJet->DeltaR(*jet);
      }

      if (hasRealMcLeptonicBottomJet) {
         deltaRFromRealMcLeptonicBottomJet = realMcLeptonicBottomJet->DeltaR(*jet);
      }

      bool isFromHadronicBottomDecay = hasRealMcHadronicBottomJet &&
                                   abs(jet->Px() - MChadronicBottom_px) < 20 &&
                                   abs(jet->Py() - MChadronicBottom_py) < 20 &&
                                   abs(jet->Pz() - MChadronicBottom_pz) < 20 &&
                                   abs(deltaRFromRealMcHadronicBottomJet) < 0.3;

      bool isFromLeptonicBottomDecay = hasRealMcLeptonicBottomJet &&
                                   abs(jet->Px() - MCleptonicBottom_px) < 20 &&
                                   abs(jet->Py() - MCleptonicBottom_py) < 20 &&
                                   abs(jet->Pz() - MCleptonicBottom_pz) < 20 &&
                                   abs(deltaRFromRealMcLeptonicBottomJet) < 0.3;;

      // TODO some memory error
      // if (isFromHadronicBottomDecay) {
      //    constructedMcHadronicBottomJet = (MyJet*) jet;
      //    hasConstructedMcHadronicBottomJet = true;
      //    ConstructedMcHadronicCount++;
      // }

      // if (isFromLeptonicBottomDecay) {
      //    constructedMcLeptonicBottomJet = (MyJet*) jet;
      //    hasConstructedMcLeptonicBottomJet = true;
      //    ConstructedMcLeptonicCount++;
      // }


      if (displayOutput) {
         cout << "ConstructedJet: ";
         cout << jet->toString();
         cout << ", deltaR(" << deltaRFromRealMcHadronicBottomJet << ", " << deltaRFromRealMcLeptonicBottomJet << ")";

         if (isFromHadronicBottomDecay) {
            cout << " hadronic";
         }

         if (isFromLeptonicBottomDecay) {
            cout << " leptonic";
         }

         cout << "\n";
      }

   }

   if (hasConstructedMcHadronicBottomJet && constructedMcHadronicBottomJet->GetBTagDiscriminator() > 1.74) {
      ConstructedMcHadronicWithGoodBtagCount++;
   }

   if (hasConstructedMcLeptonicBottomJet && constructedMcLeptonicBottomJet->GetBTagDiscriminator() > 1.74) {
      ConstructedMcLeptonicWithGoodBtagCount++;
   }

   if (hasConstructedMcHadronicBottomJet && hasConstructedMcLeptonicBottomJet) {
      ConstructedMcSemiLeptonicDecayEvents++;
   }

   if (hasConstructedMcHadronicBottomJet && hasConstructedMcLeptonicBottomJet && constructedMcLeptonicBottomJet->GetBTagDiscriminator() > 1.74 && constructedMcLeptonicBottomJet->GetBTagDiscriminator() > 1.74) {
      ConstructedMcHadronicAndLeptonicWithGoodBtagCount++;
   }

   if (
         (hasConstructedMcHadronicBottomJet && constructedMcLeptonicBottomJet->GetBTagDiscriminator() > 1.74) ||
         (hasConstructedMcLeptonicBottomJet && constructedMcLeptonicBottomJet->GetBTagDiscriminator() > 1.74)
      ) {
      ConstructedMcHadronicOrLeptonicWithGoodBtagCount++;
   }

   if (MCleptonPDGid==13) {
      RealMcMuonsCount++;
   }

   if (MCleptonPDGid==11) {
      RealMcElectronsCount++;
   }

   if (MCleptonPDGid==15) {
      RealMcTausCount++;
   }

   if (MCleptonPDGid==-13) {
      RealMcAntiTausCount++;
   }

   if (MCleptonPDGid==11) {
      RealMcAntiMuonsCount++;
   }

   if (MCleptonPDGid==15) {
      RealMcAntiElectronsCount++;
   }

   if (displayOutput) {
      cout << "\n";
   }

   // delta R matchimine, b taggimine

   return true;
}


void MyAnalysis::logValueAndProcent(string key, int value, int total) {
   double procent = ((double) value) / ((double) total) * 100;
   cout << key << ": " << value << " (" << procent << ")\n";
}

void MyAnalysis::SlaveTerminate() {
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

   // ex3 generate effiency

   cout << "EventWeight: " << EventWeight << "\n";
   cout << "TotalEvents: " << TotalEvents << "\n";
   cout << "TotalEventsWithEventWeight: " << TotalEventsWithEventWeight << "\n";
   cout << "TriggeredEvents: " << TriggeredEvents << "\n";
   cout << "TriggeredEventsWithEventWeight: " << TriggeredEventsWithEventWeight << "\n";
   cout << "HasTriggerIsoMu24ButHasNoMuonsWithEventWeight: " << HasTriggerIsoMu24ButHasNoMuonsWithEventWeight << "\n";


   // should understand what data MC generated, what processes are happening, what is constructed
   // should be compared to real data

   logValueAndProcent("RealMcHadronicCount", RealMcHadronicCount, TotalEvents);
   logValueAndProcent("RealMcLeptonicCount", RealMcLeptonicCount, TotalEvents);
   logValueAndProcent("RealMcSemiLeptonicDecayEvents", RealMcSemiLeptonicDecayEvents, TotalEvents);
   logValueAndProcent("RealMcMuonsCount", RealMcMuonsCount, TotalEvents);
   logValueAndProcent("RealMcElectronsCount", RealMcElectronsCount, TotalEvents);
   logValueAndProcent("RealMcTausCount", RealMcTausCount, TotalEvents);
   logValueAndProcent("RealMcAntiMuonsCount", RealMcMuonsCount, TotalEvents);
   logValueAndProcent("RealMcAntiElectronsCount", RealMcElectronsCount, TotalEvents);
   logValueAndProcent("RealMcAntiTausCount", RealMcTausCount, TotalEvents);
   logValueAndProcent("ConstructedMcHadronicCount", ConstructedMcHadronicCount, TotalEvents);
   logValueAndProcent("ConstructedMcLeptonicCount", ConstructedMcLeptonicCount, TotalEvents);
   logValueAndProcent("ConstructedMcSemiLeptonicDecayEvents", ConstructedMcSemiLeptonicDecayEvents, TotalEvents);
   logValueAndProcent("ConstructedMcHadronicWithGoodBtagCount", ConstructedMcHadronicWithGoodBtagCount, TotalEvents);
   logValueAndProcent("ConstructedMcLeptonicWithGoodBtagCount", ConstructedMcLeptonicWithGoodBtagCount, TotalEvents);
   logValueAndProcent("ConstructedMcHadronicAndLeptonicWithGoodBtagCount", ConstructedMcHadronicAndLeptonicWithGoodBtagCount, TotalEvents);
   logValueAndProcent("ConstructedMcHadronicOrLeptonicWithGoodBtagCount", ConstructedMcHadronicOrLeptonicWithGoodBtagCount, TotalEvents);

   cout << "ex3TotalEvents integral: " << ex3TotalEvents->Integral() << "\n";
   cout << "ex3MuonsOver25PtPassedHlt integral: " << ex3MuonsOver25PtPassedHlt->Integral() << "\n";
   cout << "ex3MuonsOver25Pt integral: " << ex3MuonsOver25Pt->Integral() << "\n";
   cout << "ex3AFterCutsEvents integral: " << ex3AFterCutsEvents->Integral() << "\n";
   cout << "h_NBtaggedJets: " << h_NBtaggedJets->Integral() << "\n";
   cout << "h_NBtaggedJetsAfterCut: " << h_NBtaggedJetsAfterCut->Integral() << "\n";


   cout << "BeforeTriggerIsoMu24CutWeightedCount: " << BeforeTriggerIsoMu24CutWeightedCount << "\n";
   cout << "AfterTriggerIsoMu24CutWeightedCount: " << AfterTriggerIsoMu24CutWeightedCount << "\n";
   cout << "BeforeMuonCutWeightedCount: " << BeforeMuonCutWeightedCount << "\n";
   cout << "AfterMuonCutWeightedCount: " << AfterMuonCutWeightedCount << "\n";
   cout << "BeforeBTaggedJetsCutWeightedCount: " << BeforeBTaggedJetsCutWeightedCount << "\n";
   cout << "AfterBTaggedJetsCutWeightedCount: " << AfterBTaggedJetsCutWeightedCount << "\n";
   cout << "Before3JetsCutWeightedCount: " << Before3JetsCutWeightedCount << "\n";
   cout << "After3JetsCutWeightedCount: " << After3JetsCutWeightedCount << "\n";

   cout << "PassedEx4Cuts: " << PassedEx4Cuts << "\n";


   ex3MuonsOver25PtHltEffiency->Divide(ex3MuonsOver25PtPassedHlt, ex3MuonsOver25Pt);
   ex3AFterCutsAcceptance->Divide(ex3AFterCutsEvents, ex3TotalEvents);
}

// bool MyAnalysis::ex3GenerateGraphs() {
//    TCanvas *canvas = new TCanvas("Canvas", "A Simple Graph with assymetric error bars", 200, 10, 700, 500);
//    TGraphAsymmErrors *graph = new TGraphAsymmErrors(ex3MuonsPtPassedHltHistogram, ex3MuonsPtHistogram);
//    graph->SetTitle("TGraphAsymmErrors Example");
//    graph->Draw("ALP");
//    canvas->Print("yo.pdf");
//    return true;
// }

void MyAnalysis::Terminate() {
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results Histogramically or save the results to file.

}
