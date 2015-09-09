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
#include <TH3F.h>
#include <TLatex.h>

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
   h_Mmumu = new TH1F("Mmumu", "Invariant di-muon mass", 60, 60, 120);
   h_Mmumu->SetXTitle("m_{#mu#mu}");
   h_Mmumu->Sumw2();
   histograms.push_back(h_Mmumu);
   histograms_MC.push_back(h_Mmumu);

   h_NMuon = new TH1F("NMuon", "Number of muons", 7, 0, 7);
   h_NMuon->SetXTitle("No. Muons");
   h_NMuon->Sumw2();
   histograms.push_back(h_NMuon);
   histograms_MC.push_back(h_NMuon);

   // task 2
   h_NJets = new TH1F("NJets", "Number of jets", 12, 0, 12);
   h_NJets->SetXTitle("Number of jets");
   h_NJets->Sumw2();
   histograms.push_back(h_NJets);
   histograms_MC.push_back(h_NJets);

   h_NBtaggedJets = new TH1F("NBtaggedJets", "Number of btagged jets", 12, 0, 12);
   h_NBtaggedJets->SetXTitle("Number of btagged jets");
   h_NBtaggedJets->Sumw2();
   histograms.push_back(h_NBtaggedJets);
   histograms_MC.push_back(h_NBtaggedJets);

   h_MJets = new TH1F("NJets", "Invariant mass of jets", 50, 0, 100);
   h_MJets->SetXTitle("Invariant mass of jets");
   h_MJets->Sumw2();
   histograms.push_back(h_MJets);
   histograms_MC.push_back(h_MJets);

   h_PerpJets = new TH1F("PerpJets", "Tranverse component for jets", 50, 0, 100);
   h_PerpJets->SetXTitle("Tranverse component for jets");
   h_PerpJets->Sumw2();
   histograms.push_back(h_PerpJets);
   histograms_MC.push_back(h_PerpJets);

   h_MET = new TH1F("MET", "sqrt(MET_px*MET_px + MET_py*MET_py)", 50, 0, 100);
   h_MET->SetXTitle("sqrt(MET_px*MET_px + MET_py*MET_py)");
   h_MET->Sumw2();
   histograms.push_back(h_MET);
   histograms_MC.push_back(h_MET);

   h_IsolationElectrons = new TH1F("Electrons isolation", "Electrons isolation", 50, 0, 100);
   h_IsolationElectrons->SetXTitle("Electrons isolation");
   h_IsolationElectrons->Sumw2();
   histograms.push_back(h_IsolationElectrons);
   histograms_MC.push_back(h_IsolationElectrons);

   h_NElectrons = new TH1F("Electrons count", "Electrons count", 10, 0, 10);
   h_NElectrons->SetXTitle("Electrons count");
   h_NElectrons->Sumw2();
   histograms.push_back(h_NElectrons);
   histograms_MC.push_back(h_NElectrons);

   muonsAngularDistributionEtaGraph = new TH1F("Angular distribution of myons (eta)", "Angular distribution of myons (eta)", 100, -4, 4);
   muonsAngularDistributionEtaGraph->SetXTitle("Angular distribution of myons (eta)");
   muonsAngularDistributionEtaGraph->Sumw2();
   histograms.push_back(muonsAngularDistributionEtaGraph);
   histograms_MC.push_back(muonsAngularDistributionEtaGraph);

   muonsAngularDistributionPhiGraph = new TH1F("Angular distribution of myons (phi)", "Angular distribution of myons (phi)", 100, -4, 4);
   muonsAngularDistributionPhiGraph->SetXTitle("Angular distribution of myons (phi)");
   muonsAngularDistributionPhiGraph->Sumw2();
   histograms.push_back(muonsAngularDistributionPhiGraph);
   histograms_MC.push_back(muonsAngularDistributionPhiGraph);

   muonsAngularDistributionPtGraph = new TH1F("Angular distribution of myons (pt)", "Angular distribution of myons (pt)", 100, 0, 100);
   muonsAngularDistributionPtGraph->SetXTitle("Angular distribution of myons (pt)");
   muonsAngularDistributionPtGraph->Sumw2();
   histograms.push_back(muonsAngularDistributionPtGraph);
   histograms_MC.push_back(muonsAngularDistributionPtGraph);

   jetsAngularDistributionEtaGraph = new TH1F("Angular distribution of jets (eta)", "Angular distribution of jets (eta)", 100, -4, 4);
   jetsAngularDistributionEtaGraph->SetXTitle("Angular distribution of jets (eta)");
   jetsAngularDistributionEtaGraph->Sumw2();
   histograms.push_back(jetsAngularDistributionEtaGraph);
   histograms_MC.push_back(jetsAngularDistributionEtaGraph);

   jetsAngularDistributionPhiGraph = new TH1F("Angular distribution of jets (phi)", "Angular distribution of jets (phi)", 100, -4, 4);
   jetsAngularDistributionPhiGraph->SetXTitle("Angular distribution of jets (phi)");
   jetsAngularDistributionPhiGraph->Sumw2();
   histograms.push_back(jetsAngularDistributionPhiGraph);
   histograms_MC.push_back(jetsAngularDistributionPhiGraph);

   jetsAngularDistributionPtGraph = new TH1F("Angular distribution of jets (pt)", "Angular distribution of jets (pt)", 100, 0, 100);
   jetsAngularDistributionPtGraph->SetXTitle("Angular distribution of jets (pt)");
   jetsAngularDistributionPtGraph->Sumw2();
   histograms.push_back(jetsAngularDistributionPtGraph);
   histograms_MC.push_back(jetsAngularDistributionPtGraph);

   // MyAnalysis::DrawExercise3();

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

   //   cout << "Jets: " << endl;
   //   for (vector<MyJet>::iterator it = Jets.begin(); it != Jets.end(); ++it) {
   //      cout << "pt, eta, phi, btag, id: " << it->Pt() << ", " << it->Eta() << ", " << it->Phi() << ", " << it->IsBTagged() << ", " << it->GetJetID()
   //      << endl;
   //   }
   //   cout << "Muons: " << endl;
   //   for (vector<MyMuon>::iterator it = Muons.begin(); it != Muons.end(); ++it) {
   //      cout << "pt, eta, phi, iso, charge: " << it->Pt() << ", " << it->Eta() << ", " << it->Phi() << ", "
   //      << it->GetIsolation() << ", " << it->GetCharge() << endl;
   //   }
   //   cout << "Electrons: " << endl;
   //   for (vector<MyElectron>::iterator it = Electrons.begin(); it != Electrons.end(); ++it) {
   //      cout << "pt, eta, phi, iso, charge: " << it->Pt() << ", " << it->Eta() << ", " << it->Phi() << ", "
   //      << it->GetIsolation() << ", " << it->GetCharge() << endl;
   //   }
   //   cout << "Photons: " << endl;
   //   for (vector<MyPhoton>::iterator it = Photons.begin(); it != Photons.end(); ++it) {
   //      cout << "pt, eta, phi, iso: " << it->Pt() << ", " << it->Eta() << ", " << it->Phi() << ", " << it->GetIsolation()
   //      << endl;
   //   }


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


   if (this->analysisType == "TTbar") {
      TTBarEvents++;
   }

   if (N_IsoMuon > 0) {

      for (vector<MyMuon>::iterator it = Muons.begin(); it != Muons.end(); ++it) {
         muonsAngularDistributionEtaGraph->Fill(it->Eta(), EventWeight);
         muonsAngularDistributionPhiGraph->Fill(it->Phi(), EventWeight);
         muonsAngularDistributionPtGraph->Fill(it->Pt(), EventWeight);
      }

      int N_Jets = 0;
      // https://en.wikipedia.org/wiki/B-tagging
      int N_BtaggedJets = 0;
      for (vector<MyJet>::iterator it = Jets.begin(); it != Jets.end(); ++it) {
         ++N_Jets;
         h_MJets->Fill(it->M(), EventWeight);
         h_PerpJets->Fill(it->Perp(), EventWeight);

         if (it->IsBTagged()) {
            ++N_BtaggedJets;
         }

         jetsAngularDistributionEtaGraph->Fill(it->Eta(), EventWeight);
         jetsAngularDistributionPhiGraph->Fill(it->Phi(), EventWeight);
         jetsAngularDistributionPtGraph->Fill(it->Pt(), EventWeight);
      }
      h_NJets->Fill(N_Jets, EventWeight);
      h_MET->Fill(sqrt(MET_px*MET_px + MET_py*MET_py), EventWeight);
      h_NBtaggedJets->Fill(N_BtaggedJets);

      int N_Electrons = 0;
      float highest_pt = 0;
      for (vector<MyElectron>::iterator it = Electrons.begin(); it != Electrons.end(); ++it) {
         ++N_Electrons;
         h_IsolationElectrons->Fill(it->GetIsolation(), EventWeight);
      }
      h_NElectrons->Fill(N_Electrons, EventWeight);


      float highest_pt_for_isolated_muon = 0;

      for (vector<MyMuon>::iterator it = Muons.begin(); it != Muons.end(); ++it) {
         if (it->IsIsolated() && highest_pt_for_isolated_muon < it->Pt()) {
            highest_pt_for_isolated_muon = it->Pt();
         }
      }

      if (this->analysisType == "TTbar" && highest_pt_for_isolated_muon > 25) {
         SelectedTTBarEvents++;
      }
   }


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
   // the results graphically or save the results to file.

}
