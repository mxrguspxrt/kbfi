#include <string>
#include <iostream>

#include "Ex3.h"
#include "Ex3Analysis.h"
#include "Plotter.h"

using namespace std;

void Ex3::GenerateGraph() {
  cout << "Ex3 start.\n";

  Ex3Analysis *a = new Ex3Analysis();

  TChain* events = new TChain("events");
  events->Add("files/ttbar.root");
  events->Process(a);

  Plotter P;
  P.AddBg(a->histograms, "TTbar");
  P.Plot("ex3.pdf");

  cout << "Ex3 end.\n";

}
