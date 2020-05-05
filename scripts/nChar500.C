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

void nChar500()
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
	TFile *fileHE = TFile::Open("../clean500/clean500_HE.root");
	TFile *filePY_Miro = TFile::Open("../clean500/clean500_PY_Miro_tau10.root");
	TFile *filePY_original = TFile::Open("../clean500/clean500_PY_original.root");

	// Read TTree from files
	TTreeReader readHE("tree", fileHE);
	TTreeReader readPY_Miro("t1", filePY_Miro);
	TTreeReader readPY_original("t1", filePY_original);

	// Read nChar values from TTree
	TTreeReaderValue<Int_t> HE_nChar(readHE, "nChar");
	TTreeReaderValue<Int_t> PY_Miro_nChar(readPY_Miro, "nChar");
	TTreeReaderValue<Int_t> PY_original_nChar(readPY_original, "nChar");

	// nChar hitogram for Herwig
	TH1D *HE = new TH1D("HE", "", 70, 0, 70);
	while(readHE.Next())
	{
		if (*HE_nChar == 0)
			continue;
		else
		{
			HE->Fill(*HE_nChar);
		}
	}

	// Normalise Herwig histogram
	HE->Sumw2(kTRUE);
	HE->Scale(1/(HE->GetEntries()));

	// nChar histogram for PYTHIA Miro
	TH1D *PY_Miro = new TH1D("PY_Miro", "", 70, 0, 70);
	while(readPY_Miro.Next())
	{
		if (*PY_Miro_nChar == 0)
			continue;
		else
		{
			PY_Miro->Fill(*PY_Miro_nChar);
		}
	}

	// Normalise PYTHIA Miro histogram
	PY_Miro->Sumw2(kTRUE);
	PY_Miro->Scale(1/(PY_Miro->GetEntries()));

	// nChar histogram for PYTHIA original
	TH1D *PY_original = new TH1D("PY_original", "", 70, 0, 70);
	while(readPY_original.Next())
	{
		if (*PY_original_nChar == 0)
			continue;
		else
		{
			PY_original->Fill(*PY_original_nChar);
		}
	}

	// Normalise PYTHIA original histogram
	PY_original->Sumw2(kTRUE);
	PY_original->Scale(1/(PY_original->GetEntries()));

	// Define canvas
	TCanvas* c1 = new TCanvas("MB nChar spectrum", "MB nChar spectrum", 800, 600);
	c1->SetLogy();


	// Format Herwig hist.
	HE->SetMarkerStyle(20);
	HE->SetMarkerSize(.75);
	HE->SetMarkerColor(kBlue);
	HE->SetLineColor(kBlue);

	HE->GetYaxis()->SetTitle("Normalised Count");
	HE->GetYaxis()->LabelsOption("v");
	HE->GetYaxis()->SetTitleOffset(1);

	HE->GetXaxis()->SetTitle("N_{Ch}");
	HE->GetXaxis()->SetTitleOffset(1.25);
	HE->GetYaxis()->SetRangeUser(0.0001,0.5);

	HE->SetStats(kFALSE);

	// Format PYTHIA Miro hist.
	PY_Miro->SetMarkerStyle(20);
	PY_Miro->SetMarkerSize(.75);
	PY_Miro->SetMarkerColor(kRed);
	PY_Miro->SetLineColor(kRed);

	PY_Miro->GetYaxis()->SetRangeUser(0.0001,0.5);

	PY_Miro->SetStats(kFALSE);

	// Format PYTHIA original hist.
	PY_original->SetMarkerStyle(20);
	PY_original->SetMarkerSize(.75);
	PY_original->SetMarkerColor(kGreen);
	PY_original->SetLineColor(kGreen);

	PY_original->GetYaxis()->SetRangeUser(0.0001,0.5);

	PY_original->SetStats(kFALSE);

	// Add hists to canvas
	c1->cd();
	HE->Draw("P");
	PY_Miro->Draw("P same");
	PY_original->Draw("P same");
	
	// Define legend
	TLegend *leg = new TLegend(.35,.6,.9,.9);
	leg->SetTextSize(0.035);
	leg->SetHeader("p+p@500 GeV, |#eta| < 1, p_{T} > 500 MeV");
	leg->AddEntry(HE, "Herwig 7", "p");
	leg->AddEntry(PY_Miro, "PYTHIA 8, Miro", "p");
	leg->AddEntry(PY_original, "PYTHIA 8, original", "p");

	leg->Draw("same");

	c1->Print("../output/nChar500.png", "png");
}
