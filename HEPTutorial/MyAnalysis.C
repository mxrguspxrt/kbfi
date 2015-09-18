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
#include <TLine.h>
#include <TLatex.h>
#include <TCanvas.h>
#include <stdlib.h>
#include <map>

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

   TCanvas *nJetsCanvas = new TCanvas("canvas");

   h_NJets = this->createHistogram("Number of jets before cut", 12, 0, 12);

   TLine *h_NJetsLine = new TLine(2, 3000000 , 2, 0);
   h_NJetsLine->SetLineColor(kRed);
   this->createLine(h_NJets, h_NJetsLine);

   h_NJetsAfterCut = this->createHistogram("Number of jets after cut", 12, 0, 12);
   h_NBtaggedJets = this->createHistogram("Number of btagged jets", 12, 0, 12);
   h_MJets = this->createHistogram("Invariant mass of jets", 50, 0, 100);
   h_PerpJets = this->createHistogram("Tranverse component for jets", 50, 0, 100);
   h_MET = this->createHistogram("sqrt(MET_px*MET_px + MET_py*MET_py)", 50, 0, 100);
   h_IsolationElectrons = this->createHistogram("Electrons isolation", 50, 0, 100);
   h_NElectrons = this->createHistogram("Electrons count", 10, 0, 10);
   muonsEtaHistogram = this->createHistogram("Muons (eta)", 100, -4, 4);
   muonsPhiHistogram = this->createHistogram("Muons (phi)", 100, -4, 4);
   muonsPtHistogram = this->createHistogram("Muons (pt)", 100, 0, 200);
   muonsChargeHistogram = this->createHistogram("Muons charge", 100, -2, 2);
   electronsEtaHistogram = this->createHistogram("Electrons (eta)", 100, -4, 4);
   electronsPhiHistogram = this->createHistogram("Electrons (phi)", 100, -4, 4);
   electronsPtHistogram = this->createHistogram("Electrons (pt)", 100, 0, 200);
   electronsChargeHistogram = this->createHistogram("Electrons charge", 100, -2, 2);
   jetsEtaHistogram = this->createHistogram("Jets (eta)", 100, -4, 4);
   jetsPhiHistogram = this->createHistogram("Jets (phi)", 100, -4, 4);
   jetsPtHistogram = this->createHistogram("Jets (pt)", 100, 0, 200);
   signalBackgroundHistogram = this->createHistogram("S/B", 100, 0, 100);
   signalBackgroundAfterCutsHistogram = this->createHistogram("S/B after cuts", 100, 0, 100);

   // MyAnalysis::DrawExercise3();

}

TH1F* MyAnalysis::createHistogram(const char *name, int nbinsx, double xlow, double xup) {
   TH1F *th1f = new TH1F(name, name, nbinsx, xlow, xup);
   th1f->SetXTitle(name);
   th1f->Sumw2();
   histograms.push_back(th1f);
   histograms_MC.push_back(th1f);
   return th1f;
}

bool MyAnalysis::createLine(TH1F* histogram, TLine* line) {
   lines[histogram] = line;
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

   GetEntry(entry);

   if (TotalEvents % 10000 == 0)
      cout << "Next event -----> " << TotalEvents << endl;

   BuildEvent();

   double MuonPtCut = 25.;
   double MuonRelIsoCut = 0.10;

   // cout << "Jets: " << endl;
   // for (vector<MyJet>::iterator it = Jets.begin(); it != Jets.end(); ++it) {
   //   cout << "pt, eta, phi, btag, id: " << it->Pt() << ", " << it->Eta() << ", " << it->Phi() << ", " << it->IsBTagged() << ", " << it->GetJetID()
   //   << endl;
   // }
   // cout << "Muons: " << endl;
   // for (vector<MyMuon>::iterator it = Muons.begin(); it != Muons.end(); ++it) {
   //   cout << "pt, eta, phi, iso, charge: " << it->Pt() << ", " << it->Eta() << ", " << it->Phi() << ", "
   //   << it->GetIsolation() << ", " << it->GetCharge() << endl;
   // }
   // cout << "Electrons: " << endl;
   // for (vector<MyElectron>::iterator it = Electrons.begin(); it != Electrons.end(); ++it) {
   //   cout << "pt, eta, phi, iso, charge: " << it->Pt() << ", " << it->Eta() << ", " << it->Phi() << ", "
   //   << it->GetIsolation() << ", " << it->GetCharge() << endl;
   // }
   // cout << "Photons: " << endl;
   // for (vector<MyPhoton>::iterator it = Photons.begin(); it != Photons.end(); ++it) {
   //   cout << "pt, eta, phi, iso: " << it->Pt() << ", " << it->Eta() << ", " << it->Phi() << ", " << it->GetIsolation()
   //   << endl;
   // }


   //////////////////////////////
   // Exercise 1: Invariant Di-Muon mass

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
   //////////////////////////////



   // Exercise 2

   if (!triggerIsoMu24) {
      return kTRUE;
   }

   if (this->analysisType == "TTbar") {
      TTBarEvents++;
   }

   // Generate Histograms on data without cuts

   bool hasPositiveLepton = false;
   bool hasNegativeLepton = false;

   for (vector<MyMuon>::iterator it = Muons.begin(); it != Muons.end(); ++it) {
      muonsEtaHistogram->Fill(it->Eta(), EventWeight);
      muonsPhiHistogram->Fill(it->Phi(), EventWeight);
      muonsPtHistogram->Fill(it->Pt(), EventWeight);
      muonsChargeHistogram->Fill(it->GetCharge(), EventWeight);

      if (it->GetCharge() == 1) {
         hasPositiveLepton = true;
      } else {
         hasNegativeLepton = true;
      }
   }


   int N_Jets = 0;

   for (vector<MyJet>::iterator it = Jets.begin(); it != Jets.end(); ++it) {
      ++N_Jets;
   }

   h_NJets->Fill(N_Jets, EventWeight);



   if (N_Jets < 2) {
      return true;
   }

   h_NJetsAfterCut->Fill(N_Jets, EventWeight);





   int N_BtaggedJets = 0;

   for (vector<MyJet>::iterator it = Jets.begin(); it != Jets.end(); ++it) {
      h_MJets->Fill(it->M(), EventWeight);
      h_PerpJets->Fill(it->Perp(), EventWeight);

      if (it->IsBTagged()) {
         ++N_BtaggedJets;
      }

      jetsEtaHistogram->Fill(it->Eta(), EventWeight);
      jetsPhiHistogram->Fill(it->Phi(), EventWeight);
      jetsPtHistogram->Fill(it->Pt(), EventWeight);
   }
   h_MET->Fill(sqrt(MET_px*MET_px + MET_py*MET_py), EventWeight);
   h_NBtaggedJets->Fill(N_BtaggedJets);

   int N_Electrons = 0;
   float highest_pt = 0;

   for (vector<MyElectron>::iterator it = Electrons.begin(); it != Electrons.end(); ++it) {
      ++N_Electrons;
      h_IsolationElectrons->Fill(it->GetIsolation(), EventWeight);
      electronsEtaHistogram->Fill(it->Eta(), EventWeight);
      electronsPhiHistogram->Fill(it->Phi(), EventWeight);
      electronsPtHistogram->Fill(it->Pt(), EventWeight);
      electronsChargeHistogram->Fill(it->GetCharge(), EventWeight);

      if (it->GetCharge() == 1) {
         hasPositiveLepton = true;
      } else {
         hasNegativeLepton = true;
      }
   }
   h_NElectrons->Fill(N_Electrons, EventWeight);


   float higestPtForIsolatedMuon = 0;

   for (vector<MyMuon>::iterator it = Muons.begin(); it != Muons.end(); ++it) {
      if (it->IsIsolated() && higestPtForIsolatedMuon < it->Pt()) {
         higestPtForIsolatedMuon = it->Pt();
      }
   }

   // Generate Histogram that compares signal/background without cuts
   signalBackgroundHistogram->Fill(1, EventWeight);



   // Generate Histogram that compares signal/background with cuts
   //
   // Must contain:
   //
   // * at least 2 jets and two oppositely charged leptons (currently not checking taus)

   bool hasTwoOppositelyChargedLeptons = hasPositiveLepton && hasNegativeLepton;

   if (!(N_Jets >= 2 && hasTwoOppositelyChargedLeptons)) {
      return kTRUE;
   }

   signalBackgroundAfterCutsHistogram->Fill(1, EventWeight);

   // MyAnalysis::ProcessExercise3();

   return kTRUE;
}

void MyAnalysis::SetAnalysisType(string analysisType) {
   this->analysisType = analysisType;
}

void MyAnalysis::SlaveTerminate() {
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

   if (this->analysisType=="TTbar") {
      float efficiency = (float) SelectedTTBarEvents / (float) TTBarEvents;
      cout << "3.2 Efficiency: " << SelectedTTBarEvents << " / " << TTBarEvents << " = " << efficiency << endl;
   }
}

void MyAnalysis::Terminate() {
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results Histogramically or save the results to file.

}
