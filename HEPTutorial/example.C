#include "MyAnalysis.h"
#include "Plotter.h"
#include <iostream>
#include <TChain.h>
#include <TGraphAsymmErrors.h>
#include <string>
#include "Ex3.h"

int main() {

   float lumi = 50.;

   // https://root.cern.ch/root/html/TChain.html
   MyAnalysis *A = new MyAnalysis();
   TChain* ch = new TChain("events");
   ch->Add("files/data.root");
   ch->Process(A);

   MyAnalysis *B = new MyAnalysis();
   B->SetAnalysisType("TTbar");
   TChain* ch2 = new TChain("events");
   ch2->Add("files/ttbar.root");
   ch2->Process(B);

   MyAnalysis *C = new MyAnalysis();
   TChain* ch3 = new TChain("events");
   ch3->Add("files/wjets.root");
   ch3->Process(C);

   MyAnalysis *D = new MyAnalysis();
   TChain* ch4 = new TChain("events");
   ch4->Add("files/dy.root");
   ch4->Process(D);

   MyAnalysis *E = new MyAnalysis();
   TChain* ch5 = new TChain("events");
   ch5->Add("files/ww.root");
   ch5->Process(E);

   MyAnalysis *F = new MyAnalysis();
   TChain* ch6 = new TChain("events");
   ch6->Add("files/wz.root");
   ch6->Process(F);

   MyAnalysis *G = new MyAnalysis();
   TChain* ch7 = new TChain("events");
   ch7->Add("files/zz.root");
   ch7->Process(G);

   MyAnalysis *H = new MyAnalysis();
   TChain* ch8 = new TChain("events");
   ch8->Add("files/qcd.root");
   ch8->Process(H);

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
   // P.AddLines(A->lines);
   // P.AddLines(B->lines);
   // P.AddLines(C->lines);
   // P.AddLines(D->lines);
   // P.AddLines(E->lines);
   // P.AddLines(F->lines);
   // P.AddLines(G->lines);
   // P.AddLines(H->lines);
   // P.AddLines(I->lines);

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
   // P.AddLines(B->lines);
   // P.AddLines(C->lines);
   // P.AddLines(D->lines);
   // P.AddLines(E->lines);
   // P.AddLines(F->lines);
   // P.AddLines(G->lines);
   // P.AddLines(H->lines);
   // P.AddLines(I->lines);


   P_MC.Plot(string("results_MC.pdf"));


   Ex3* ex3 = new Ex3();
   ex3->GenerateGraph();

}
