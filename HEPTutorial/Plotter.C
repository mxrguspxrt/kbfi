/*
 * Plotter.C
 *
 *  Created on: 25.06.2012
 *      Author: csander
 */

#include "Plotter.h"
#include "TLine.h"

Plotter::Plotter() {
	// TODO Auto-generated constructor stub

}

Plotter::~Plotter() {
	// TODO Auto-generated destructor stub
}

void Plotter::Plot(std::string filename) {

	gROOT->Reset();
	//gROOT->SetStyle("Plain");

	TStyle *MyStyle = new TStyle("MyStyle","My Root Styles");
  MyStyle->SetPaperSize(20,24);
	MyStyle->SetStatColor(0);
	MyStyle->SetCanvasColor(0);
	MyStyle->SetPadColor(0);
	MyStyle->SetPadBorderMode(0);
	MyStyle->SetCanvasBorderMode(0);
	MyStyle->SetFrameBorderMode(0);
	MyStyle->SetOptStat(0);
	MyStyle->SetStatBorderSize(2);
	MyStyle->SetOptTitle(0);
	MyStyle->SetPadTickX(1);
	MyStyle->SetPadTickY(1);
	MyStyle->SetPadBorderSize(2);
	MyStyle->SetPalette(51, 0);
	MyStyle->SetPadBottomMargin(0.15);
	MyStyle->SetPadTopMargin(0.05);
	MyStyle->SetPadLeftMargin(0.15);
	MyStyle->SetPadRightMargin(0.25);
	MyStyle->SetTitleColor(1);
	MyStyle->SetTitleFillColor(0);
	MyStyle->SetTitleFontSize(0.05);
	MyStyle->SetTitleBorderSize(0);
	MyStyle->SetLineWidth(1);
	MyStyle->SetHistLineWidth(3);
	MyStyle->SetLegendBorderSize(0);
	MyStyle->SetNdivisions(502, "x");
	MyStyle->SetMarkerSize(0.8);
	MyStyle->SetTickLength(0.03);
	MyStyle->SetTitleOffset(1.5, "x");
	MyStyle->SetTitleOffset(1.5, "y");
	MyStyle->SetTitleOffset(1.0, "z");
	MyStyle->SetLabelSize(0.05, "x");
	MyStyle->SetLabelSize(0.05, "y");
	MyStyle->SetLabelSize(0.05, "z");
	MyStyle->SetLabelOffset(0.03, "x");
	MyStyle->SetLabelOffset(0.03, "y");
	MyStyle->SetLabelOffset(0.03, "z");
	MyStyle->SetTitleSize(0.05, "x");
	MyStyle->SetTitleSize(0.05, "y");
	MyStyle->SetTitleSize(0.05, "z");
	gROOT->SetStyle("MyStyle");

	//gROOT->ForceStyle();

	bool DrawLog = false;

	for (int i = 0; i < N_histos; ++i) {

		THStack *hs;
		TLegend *l;

    int Nset = data.size() + bg.size() + signal.size();
    if (Nset > 20)
       Nset = 20.;
    l = new TLegend(0.76, 0.95 - 0.8 * Nset / 20., 1.0, 0.95);
    l->SetFillStyle(1001);
    l->SetFillColor(kWhite);
    l->SetLineColor(kWhite);
    l->SetLineWidth(2);

		if (bg.size() > 0) {

			hs = new THStack("hs", bg.at(0).at(i)->GetName());
			int j = 0;
			for (std::vector<std::vector<TH1F*> >::const_iterator it = bg.begin(); it != bg.end(); ++it) {

        TH1F *histogram = it->at(i);

				switch (j) {
               case 0:
                  histogram->SetFillColor(kRed);
                  break;
               case 1:
                  histogram->SetFillColor(kOrange);
                  break;
               case 2:
                  histogram->SetFillColor(kYellow);
                  break;
               case 3:
                  histogram->SetFillColor(kGreen);
                  break;
               case 4:
                  histogram->SetFillColor(kCyan);
                  break;
               case 5:
                  histogram->SetFillColor(kBlue);
                  break;
               case 6:
                  histogram->SetFillColor(kMagenta);
                  break;
               case 7:
                  histogram->SetFillColor(kGray);
                  break;
               case 8:
                  histogram->SetFillColor(kGray + 2);
                  break;
               default:
                  histogram->SetFillColor(kBlack);
                  break;
				}
				hs->Add(histogram);
				l->AddEntry(histogram, bg_names.at(j).c_str(), "f");
				++j;
			}
		}
		TCanvas *c = new TCanvas("c", "c", 800, 600);
		c->SetLogy(DrawLog);
    std::string plotname;

		if (data.size() > 0) {
      plotname = std::string(data.at(0).at(i)->GetName());
			data.at(0).at(i)->SetMaximum(1.5 * data.at(0).at(i)->GetMaximum());
			data.at(0).at(i)->GetXaxis()->SetTitleOffset(1.3);
			data.at(0).at(i)->GetYaxis()->SetTitleOffset(1.3);
			data.at(0).at(i)->GetYaxis()->SetTitle("Events");
			data.at(0).at(i)->GetXaxis()->SetNdivisions(505);
			data.at(0).at(i)->Draw("");
			l->AddEntry(data.at(0).at(i), data_names.at(0).c_str(), "p");

      if (bg.size() > 0)
        hs->Draw("histsame");

      data.at(0).at(i)->SetMarkerStyle(20);
      data.at(0).at(i)->Draw("psame");
      l->Draw("same");
		}

		if (data.size() == 0 && bg.size() > 0) {
      plotname = std::string(bg.at(0).at(i)->GetName());
			hs->Draw("hist");
      hs->GetXaxis()->SetTitleOffset(1.3);
      hs->GetXaxis()->SetNdivisions(505);
      hs->GetYaxis()->SetTitleOffset(1.3);

      if (bg.size() > 0)
        hs->GetXaxis()->SetTitle(bg.at(0).at(i)->GetXaxis()->GetTitle());

      hs->GetYaxis()->SetTitle("Events");
      l->Draw("same");
		}

    if (i==2) {
      TLine *line = new TLine(2, 500*1000 , 2, 0);
      line->SetLineColor(kBlack);
      line->Draw("histsame");
    }

    if (i==4) {
      TLine *line = new TLine(1, 35000 , 1, 0);
      line->SetLineColor(kBlack);
      line->Draw("histsame");
    }

    if (i==6) {
      TLine *line = new TLine(1, 900 , 1, 0);
      line->SetLineColor(kBlack);
      line->Draw("histsame");
    }

//      c->Print((filename+std::string("_")+plotname+std::string(".pdf")).c_str());
		if (i == 0 && N_histos > 1) {
			c->Print((filename+std::string("(")).c_str());
		} else if (i > 0 && i == N_histos - 1)
			c->Print((filename+std::string(")")).c_str());
		else
			c->Print(filename.c_str());

	}

}
