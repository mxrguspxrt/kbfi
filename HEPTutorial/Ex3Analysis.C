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

   pt_histogram = new TH1F("Myon tranverse momentum", "Myon tranverse momentum", 60, 0, 200);
   pt_histogram->SetXTitle("pT");

   histograms.push_back(pt_histogram);
   histograms_MC.push_back(pt_histogram);

   // in C++ they are not 0 by default
   for(int i = 0; i < 250; i++) {
      counts_for_events[i] = 0;
   }

   efficiency_histogram = new TH2F("Efficiency histogram", "Efficiency histogram", 250, 0.0, 1.0, 250, 0.0, 200.0);
   efficiency_histogram->SetXTitle("Efficiency");
   efficiency_histogram->SetYTitle("GeV limit");
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


   // just put muon pt into histogram
   for (vector<MyMuon>::iterator muon = Muons.begin(); muon != Muons.end(); ++muon) {
      if (muon->IsIsolated()) {
         pt_histogram->Fill(muon->Perp(), EventWeight);
      }
   }

   // calc effiencies
   for (int gev = 0; gev < 100; gev++) {
      if (has_muon_with_pt_creater_than(gev)) {
         count_event_for(gev);
      }
   }

   return kTRUE;
}

bool Ex3Analysis::has_muon_with_pt_creater_than(double gev) {
   for (vector<MyMuon>::iterator muon = Muons.begin(); muon != Muons.end(); ++muon) {
      if (muon->IsIsolated() && muon->Perp() > gev) {
         return true;
      }
   }
   return false;
}

void Ex3Analysis::count_event_for(int gev) {
   counts_for_events[gev] = counts_for_events[gev] ? counts_for_events[gev] + 1 : 1;
}


// The SlaveTerminate() function is called after all entries or objects
// have been processed. When running with PROOF SlaveTerminate() is called
// on each slave server.

void Ex3Analysis::SlaveTerminate() {
   cout << "Ex3Analysis::SlaveTerminate()\n";

   TCanvas* canvas = new TCanvas("canvas");

   for(int i = 0; i < 250; i++) {
      double efficiency = 1 - (double)counts_for_events[i] / (double)TotalEvents;
      cout
         << "TotalEvents: " << TotalEvents
         << " and events over " << i << " GeV: " << counts_for_events[i]
         << " that means that efficiency is: " << efficiency
         << "\n";

      efficiency_histogram->Fill(efficiency, i);
   }
   efficiency_histogram->Draw();

   canvas->Print("ex3-efficiency.pdf");

}


// The Terminate() function is the last function to be called during
// a query. It always runs on the client, it can be used to present
// the results graphically or save the results to file.

void Ex3Analysis::Terminate() {
   cout << "Ex3Analysis::Terminate()\n";
}
