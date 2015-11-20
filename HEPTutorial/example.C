#include "MyAnalysis.h"
#include "Plotter.h"
#include <iostream>
#include <TChain.h>
#include <TGraphAsymmErrors.h>
#include <string>
#include "Ex3.h"

#include "TGraphAsymmErrors.h"
#include "TCanvas.h"
#include "TH1F.h"

using namespace std;

int main() {

   float lumi = 50.;

   // https://root.cern.ch/root/html/TChain.html
   cout << "\n\nDATA:\n";
   MyAnalysis *A = new MyAnalysis();
   TChain* ch = new TChain("events");
   ch->Add("files/data.root");
   ch->Process(A);

   cout << "\n\nTTBar:\n";
   MyAnalysis *B = new MyAnalysis();
   TChain* ch2 = new TChain("events");
   ch2->Add("files/ttbar.root");
   ch2->Process(B);

   cout << "\n\nWjets:\n";
   MyAnalysis *C = new MyAnalysis();
   TChain* ch3 = new TChain("events");
   ch3->Add("files/wjets.root");
   ch3->Process(C);

   cout << "\n\nDY:\n";
   MyAnalysis *D = new MyAnalysis();
   TChain* ch4 = new TChain("events");
   ch4->Add("files/dy.root");
   ch4->Process(D);

   cout << "\n\nWW:\n";
   MyAnalysis *E = new MyAnalysis();
   TChain* ch5 = new TChain("events");
   ch5->Add("files/ww.root");
   ch5->Process(E);

   cout << "\n\nWZ:\n";
   MyAnalysis *F = new MyAnalysis();
   TChain* ch6 = new TChain("events");
   ch6->Add("files/wz.root");
   ch6->Process(F);

   cout << "\n\nZZ:\n";
   MyAnalysis *G = new MyAnalysis();
   TChain* ch7 = new TChain("events");
   ch7->Add("files/zz.root");
   ch7->Process(G);

   cout << "\n\nQCD:\n";
   MyAnalysis *H = new MyAnalysis();
   TChain* ch8 = new TChain("events");
   ch8->Add("files/qcd.root");
   ch8->Process(H);

   cout << "\n\nSigleTop:\n";
   MyAnalysis *I = new MyAnalysis();
   TChain* ch9 = new TChain("events");
   ch9->Add("files/single_top.root");
   ch9->Process(I);

	Plotter P;
	P.SetData(A->histograms, "Data");
	P.AddBg(B->histograms, "TTbar");
	P.AddBg(C->histograms, "Wjets");
	P.AddBg(D->histograms, "DY");
	P.AddBg(E->histograms, "WW");
	P.AddBg(F->histograms, "WZ");
	P.AddBg(G->histograms, "ZZ");
	P.AddBg(H->histograms, "QCD");
	P.AddBg(I->histograms, "single Top");

	P.Plot(string("results.pdf"));

	Plotter P_MC;
	P_MC.AddBg(B->histograms_MC, "TTbar");
	P_MC.AddBg(C->histograms_MC, "Wjets");
	P_MC.AddBg(D->histograms_MC, "DY");
	P_MC.AddBg(E->histograms_MC, "WW");
	P_MC.AddBg(F->histograms_MC, "WZ");
	P_MC.AddBg(G->histograms_MC, "ZZ");
	P_MC.AddBg(H->histograms_MC, "QCD");
	P_MC.AddBg(I->histograms_MC, "single Top");


   P_MC.Plot(string("results_MC.pdf"));


   // 3.3

   // background subtraction: we also trust the simulation to correctly predict
   // the number of back- ground events after selection.
   // Subtract the expected background from the observed (selected) data events.

   TCanvas *ex3EffiencyCanvas = new TCanvas("Canvas", "Ex3: trigger effieciency", 200, 10, 700, 500);

   ex3EffiencyCanvas->Print("ex3.pdf");





   // TGraphAsymmErrors *graphA = new TGraphAsymmErrors(A->ex3MuonsPtPassedHltHistogram, A->ex3MuonsPtHistogram);
   // TGraphAsymmErrors *graphB = new TGraphAsymmErrors(B->ex3MuonsPtPassedHltHistogram, B->ex3MuonsPtHistogram);
   // TGraphAsymmErrors *graphC = new TGraphAsymmErrors(C->ex3MuonsPtPassedHltHistogram, C->ex3MuonsPtHistogram);
   // TGraphAsymmErrors *graphD = new TGraphAsymmErrors(D->ex3MuonsPtPassedHltHistogram, D->ex3MuonsPtHistogram);
   // TGraphAsymmErrors *graphE = new TGraphAsymmErrors(E->ex3MuonsPtPassedHltHistogram, E->ex3MuonsPtHistogram);
   // TGraphAsymmErrors *graphF = new TGraphAsymmErrors(F->ex3MuonsPtPassedHltHistogram, F->ex3MuonsPtHistogram);
   // TGraphAsymmErrors *graphG = new TGraphAsymmErrors(G->ex3MuonsPtPassedHltHistogram, G->ex3MuonsPtHistogram);
   // TGraphAsymmErrors *graphH = new TGraphAsymmErrors(H->ex3MuonsPtPassedHltHistogram, H->ex3MuonsPtHistogram);
   // TGraphAsymmErrors *graphI = new TGraphAsymmErrors(I->ex3MuonsPtPassedHltHistogram, I->ex3MuonsPtHistogram);

   // graphA->SetLineColor(1);
   // graphB->SetLineColor(9);
   // graphC->SetLineColor(3);
   // graphD->SetLineColor(4);
   // graphE->SetLineColor(5);
   // graphF->SetLineColor(6);
   // graphG->SetLineColor(7);
   // graphH->SetLineColor(8);
   // graphI->SetLineColor(kRed);

   // TCanvas *ex3Try3 = new TCanvas("Canvas", "Ex3: trigger effieciency", 200, 10, 700, 500);

   // TH1F ex3MuonsPtPassedHltHistogram = *B->ex3MuonsPtPassedHltHistogram +
   //    *C->ex3MuonsPtPassedHltHistogram +
   //    *D->ex3MuonsPtPassedHltHistogram +
   //    *E->ex3MuonsPtPassedHltHistogram +
   //    *F->ex3MuonsPtPassedHltHistogram +
   //    *G->ex3MuonsPtPassedHltHistogram +
   //    *H->ex3MuonsPtPassedHltHistogram +
   //    *I->ex3MuonsPtPassedHltHistogram;

   // TH1F *ex3MuonsPtPassedHltHistogramP = &ex3MuonsPtPassedHltHistogram;

   // TH1F ex3MuonsPtHistogram = *B->ex3MuonsPtHistogram +
   //    *C->ex3MuonsPtHistogram +
   //    *D->ex3MuonsPtHistogram +
   //    *E->ex3MuonsPtHistogram +
   //    *F->ex3MuonsPtHistogram +
   //    *G->ex3MuonsPtHistogram +
   //    *H->ex3MuonsPtHistogram +
   //    *I->ex3MuonsPtHistogram;

   // TH1F *ex3MuonsPtHistogramP = &ex3MuonsPtHistogram;

   // TGraphAsymmErrors *graphData = new TGraphAsymmErrors(A->ex3MuonsPtPassedHltHistogram, A->ex3MuonsPtHistogram);
   // TGraphAsymmErrors *graphMC = new TGraphAsymmErrors(ex3MuonsPtPassedHltHistogramP, ex3MuonsPtHistogramP);

   // graphData->SetLineColor(1);
   // graphMC->SetLineColor(kRed);

   // graphData->GetXaxis()->SetTitle("pT");
   // graphMC->GetXaxis()->SetTitle("pT");

   // graphA->Draw();
   // graphMC->Draw("same");

   // ex3Try3->Print("ex3-asymmerrors-try3.pdf");

}
