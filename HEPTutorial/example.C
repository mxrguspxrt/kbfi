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

	P.Plot("results.pdf");



   vector<TH1F*> dataWithoutBackgrounds;

   int histogramsSize = A->histograms.size();
   // for each data histogram
   for (int i = 0; i < histogramsSize; i++) {
      TH1F* histogram = (TH1F*) A->histograms.at(i)->Clone();

      histogram->Add(C->histograms.at(i), -1);
      histogram->Add(D->histograms.at(i), -1);
      histogram->Add(E->histograms.at(i), -1);
      histogram->Add(F->histograms.at(i), -1);
      histogram->Add(G->histograms.at(i), -1);
      histogram->Add(H->histograms.at(i), -1);
      histogram->Add(I->histograms.at(i), -1);

      dataWithoutBackgrounds.push_back(histogram);
   }

   Plotter plotterWithoutBackgrounds;
   plotterWithoutBackgrounds.SetData(dataWithoutBackgrounds, "Data");
   plotterWithoutBackgrounds.AddBg(B->histograms, "TTbar");

   plotterWithoutBackgrounds.Plot("results-without-bg.pdf");

   cout << "TTBAR events in data (having cuts and subtracted backgrounds):" << dataWithoutBackgrounds.at(histogramsSize-2)->Integral() << "\n";


	Plotter P_MC;
	P_MC.AddBg(B->histograms_MC, "TTbar");
	P_MC.AddBg(C->histograms_MC, "Wjets");
	P_MC.AddBg(D->histograms_MC, "DY");
	P_MC.AddBg(E->histograms_MC, "WW");
	P_MC.AddBg(F->histograms_MC, "WZ");
	P_MC.AddBg(G->histograms_MC, "ZZ");
	P_MC.AddBg(H->histograms_MC, "QCD");
	P_MC.AddBg(I->histograms_MC, "single Top");

   P_MC.Plot("results_MC.pdf");



}
