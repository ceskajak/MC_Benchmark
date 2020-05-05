#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TSystem.h>

#include <TTreeReader.h>
#include <TTreeReaderValue.h>

#include "TMathBase.h"

#include "vector"

void nChar500_tau()
{
	// Setup canvas
	gStyle->SetCanvasColor(0);
   	gStyle->SetFrameBorderMode(0);
   	gStyle->SetStatBorderSize(1);
   	gStyle->SetFrameFillColor(0);
   	gStyle->SetTitleFillColor(0);
   	gStyle->SetPalette(1);
	gROOT->ForceStyle();

	// Open files
	TFile *filePY_5 = TFile::Open("../clean500/clean500_PY_Miro_tau5.root");
	TFile *filePY_tau10 = TFile::Open("../clean500/clean500_PY_Miro_tau10.root");
	TFile *filePY_15 = TFile::Open("../clean500/clean500_PY_Miro_tau15.root");

	// Read TTree from files
	TTreeReader readPY_5("t1", filePY_5);
	TTreeReader readPY_tau10("t1", filePY_tau10);
	TTreeReader readPY_15("t1", filePY_15);

	// Read nChar values from TTree
	TTreeReaderValue<Int_t> PY_5_nChar(readPY_5, "nChar");
	TTreeReaderValue<Int_t> PY_tau10_nChar(readPY_tau10, "nChar");
	TTreeReaderValue<Int_t> PY_15_nChar(readPY_15, "nChar");

	// nChar hitogram for PYTHIA tau 5
	TH1D *PY_5 = new TH1D("PY_5", "", 70, 0, 70);
	while(readPY_5.Next())
	{
		if (*PY_5_nChar == 0)
			continue;
		else
		{
			PY_5->Fill(*PY_5_nChar);
		}
	}

	// Normalise PYTHIA tau 5 histogram
	PY_5->Sumw2(kTRUE);
	PY_5->Scale(1/(PY_5->GetEntries()));

	// nChar histogram for PYTHIA tau 10
	TH1D *PY_tau10 = new TH1D("PY_tau10", "", 70, 0, 70);
	while(readPY_tau10.Next())
	{
		if (*PY_tau10_nChar == 0)
			continue;
		else
		{
			PY_tau10->Fill(*PY_tau10_nChar);
		}
	}

	// Normalise PYTHIA tau 10 histogram
	PY_tau10->Sumw2(kTRUE);
	PY_tau10->Scale(1/(PY_tau10->GetEntries()));

	// nChar histogram for PYTHIA tau 15
	TH1D *PY_15 = new TH1D("PY_15", "", 70, 0, 70);
	while(readPY_15.Next())
	{
		if (*PY_15_nChar == 0)
			continue;
		else
		{
			PY_15->Fill(*PY_15_nChar);
		}
	}

	// Normalise PYTHIA tau 15 histogram
	PY_15->Sumw2(kTRUE);
	PY_15->Scale(1/(PY_15->GetEntries()));

	// Define canvas
	TCanvas* c1 = new TCanvas("MB nChar spectrum", "MB nChar spectrum", 800, 600);
	c1->SetLogy();


	// Format PYTHIA tau 5 hist.
	PY_5->SetMarkerStyle(20);
	PY_5->SetMarkerSize(.75);
	PY_5->SetMarkerColor(kBlue);
	PY_5->SetLineColor(kBlue);

	PY_5->GetYaxis()->SetTitle("Normalised Count");
	PY_5->GetYaxis()->LabelsOption("v");
	PY_5->GetYaxis()->SetTitleOffset(1);

	PY_5->GetXaxis()->SetTitle("N_{Ch}");
	PY_5->GetXaxis()->SetTitleOffset(1.25);
	PY_5->GetYaxis()->SetRangeUser(0.0001,0.5);

	PY_5->SetStats(kFALSE);

	// Format PYTHIA tau 10 hist.
	PY_tau10->SetMarkerStyle(20);
	PY_tau10->SetMarkerSize(.75);
	PY_tau10->SetMarkerColor(kRed);
	PY_tau10->SetLineColor(kRed);

	PY_tau10->GetYaxis()->SetRangeUser(0.0001,0.5);

	PY_tau10->SetStats(kFALSE);

	// Format PYTHIA tau 15 hist.
	PY_15->SetMarkerStyle(20);
	PY_15->SetMarkerSize(.75);
	PY_15->SetMarkerColor(kGreen);
	PY_15->SetLineColor(kGreen);

	PY_15->GetYaxis()->SetRangeUser(0.0001,0.5);

	PY_15->SetStats(kFALSE);

	// Add hists to canvas
	c1->cd();
	PY_5->Draw("P");
	PY_tau10->Draw("P same");
	PY_15->Draw("P same");
	
	// Define legend
	TLegend *leg = new TLegend(.35,.6,.9,.9);
	leg->SetTextSize(0.035);
	leg->SetHeader("p+p@500 GeV, |#eta| < 1, p_{T} > 500 MeV");
	leg->AddEntry(PY_5, "PYTHIA 8, tau 5", "p");
	leg->AddEntry(PY_tau10, "PYTHIA 8, tau 10", "p");
	leg->AddEntry(PY_15, "PYTHIA 8, tau 15", "p");

	leg->Draw("same");

	c1->Print("../output/nChar500_tau.png", "png");
}
