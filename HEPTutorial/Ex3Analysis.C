// per event muon with highest pt -> to histogram
// if passed HLT -> to second histogram
// second histogram / first histogram -> third histogram

// pt - transverse momentum
// eta - angle 2.1-2.5, eta, theta

#define Ex3Analysis_cxx

#include <string>
#include <iostream>

#include "Ex3Analysis.h"
#include <TH1F.h>
#include <TH2F.h>
#include <TLatex.h>
#include <TCanvas.h>

using namespace std;

void Ex3Analysis::BuildEvent() {

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

void Ex3Analysis::Begin(TTree * /*tree*/) {
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();
   cout << "Ex3Analysis::Begin()\n";
}


// The SlaveBegin() function is called after the Begin() function.
// When running with PROOF SlaveBegin() is called on each slave server.
// The tree argument is deprecated (on PROOF 0 is passed).

void Ex3Analysis::SlaveBegin(TTree * /*tree*/) {
   TString option = GetOption();

   pt_histogram = new TH1F("Muon pt", "Muon pt", 60, 0, 200);
   pt_histogram->SetXTitle("pT");
   pt_histogram->Sumw2();

   pt_passed_hlt_histogram = new TH1F("Passed HLT", "Passed HLT", 60, 0, 200);
   pt_passed_hlt_histogram->SetXTitle("pT");
   pt_passed_hlt_histogram->Sumw2();

   efficiency_histogram = new TH1F("Efficiency", "Efficiency", 60, 0, 200);
   pt_passed_hlt_histogram->SetXTitle("pT");
   pt_passed_hlt_histogram->Sumw2();
}


// The Process() function is called for each entry in the tree (or possibly
// keyed object in the case of PROOF) to be processed. The entry argument
// specifies which entry in the currently loaded tree is to be processed.
// It can be passed to either Ex3Analysis::GetEntry() or TBranch::GetEntry()
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

Bool_t Ex3Analysis::Process(Long64_t entry) {
   ++TotalEvents;

   GetEntry(entry);

   if (TotalEvents % 10000 == 0)
      cout << "Next event -----> " << TotalEvents << endl;

   BuildEvent();

   double muon_highest_pt = get_muon_highest_pt();
   bool event_passed_hlt = triggerIsoMu24;

   if (muon_highest_pt > 0) {
      pt_histogram->Fill(muon_highest_pt, EventWeight);

      if (event_passed_hlt) {
         pt_passed_hlt_histogram->Fill(muon_highest_pt, EventWeight);
         efficiency_histogram->Fill(muon_highest_pt, EventWeight);
      }
   }

   return kTRUE;
}


double Ex3Analysis::get_muon_highest_pt() {
   double muon_highest_pt = 0;

   for (vector<MyMuon>::iterator muon = Muons.begin(); muon != Muons.end(); ++muon) {
      if (muon->IsIsolated() && muon->Pt() > muon_highest_pt) {
         muon_highest_pt = muon->Pt();
      }
   }
   return muon_highest_pt;
}


// The SlaveTerminate() function is called after all entries or objects
// have been processed. When running with PROOF SlaveTerminate() is called
// on each slave server.

void Ex3Analysis::SlaveTerminate() {
   cout << "Ex3Analysis::SlaveTerminate()\n";

   TCanvas *canvas = new TCanvas("canvas");

   pt_histogram->Draw();
   canvas->Print("ex3-pt_histogram.pdf");

   pt_passed_hlt_histogram->Draw();
   canvas->Print("ex3-pt_passed_hlt_histogram.pdf");

   efficiency_histogram->Divide(pt_histogram);
   efficiency_histogram->Draw("E1");
   canvas->Print("ex3-efficiency_histogram.pdf");

}


// The Terminate() function is the last function to be called during
// a query. It always runs on the client, it can be used to present
// the results graphically or save the results to file.

void Ex3Analysis::Terminate() {
   cout << "Ex3Analysis::Terminate()\n";
}
