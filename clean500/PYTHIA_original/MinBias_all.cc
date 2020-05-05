#include "Pythia8/Pythia.h"

#include "TInterpreter.h"
#include "TTree.h"
#include "TFile.h"

#include <vector>

using namespace std;
using namespace Pythia8;

int main()
{
	// create Pythia instance
	Pythia pythia;
	
	// static settings
	Settings& settings = pythia.settings;
	Info& info = pythia.info;

	// load settings
	pythia.readFile("MinBias_all.cmnd");

	// define parameters from runcard
	int maxNumberOfEvents = settings.mode("Main:numberOfEvents");
	int maxErrors = settings.mode("Main:timesAllowErrors");

	// initialize Pythia
	pythia.init();

	// define ROOT TTree
	TTree *t1 = new TTree("t1", "t1");

	// define parameters to save
	Double_t event_weight;
	Int_t nChar;

	// create TTree branches
	t1->Branch("event_weight", &event_weight, "event_weight/D");
	t1->Branch("nChar", &nChar, "nChar/I");

	// Define temporary Particle
	Particle particle;

	// loop over all events (run loop)
	for (int i = 0; i < maxNumberOfEvents; i++)
	{
		if (!pythia.next())
			continue;
		
		// init. parameters for new loop
		event_weight = info.weight();
		nChar = 0;

		// single event loop (event loop)
		for (int j = 0; j < pythia.event.size(); j++)
		{
			// Set current particle
			particle = pythia.event[j];

			// multiplicity counter
			if (particle.isFinal() && particle.isCharged())
			{
				if (particle.pT() >= .20 && abs(particle.eta()) < 1.0)
				{
					nChar++;
				}
			}
		}	// end event loop

		t1->Fill();
	}	// end run loop

	// statistics
	pythia.stat();
	
	// select output file
	TFile out("clean500_PY_original.root", "recreate");

	// write tree
	t1->Write();

	// done
	return 0;
}