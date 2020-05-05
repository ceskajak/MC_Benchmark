#include "Pythia8/Pythia.h"

#include "TTree.h"
#include "TFile.h"

#include <vector>

using namespace std;
using namespace Pythia8;

int main()
{
	// create PYTHIA instance
	Pythia pythia;

	// load settings
	int nEvents = 1000000;

	pythia.readString("Beams:idA = 2212");
	pythia.readString("Beams:idB = 2212");
	pythia.readString("Beams:ecM = 500.");

	pythia.readString("SoftQCD:all = on");

	pythia.readString("PhaseSpace:pTHatMin = 0");
	pythia.readString("PhaseSpace:pTHatMax= 500");
	pythia.readString("PhaseSpace:mHatMin = 0");
	pythia.readString("PhaseSpace:mHatMax= 500");

	pythia.readString("ParticleDecays:limitTau0 = On");
	pythia.readString("ParticleDecays:tau0Max = 8.");

	pythia.readString("Random:setSeed = on");
	pythia.readString("Random:seed = 125442");

	// initialize PYTHIA
	pythia.init();

	// create TTree
	auto *t1 = new TTree("t1", "t1");

	// define parameters to save
	Double_t event_weight;
	Int_t nChar;

	// create TTree branches
	t1->Branch("event_weight", &event_weight, "event_weight/D");
	t1->Branch("nChar", &nChar, "nChar/I");

	// define tempoparty PYTHIA Particle
	Particle particle;

	// run loop
	for (int i = 0; i < nEvents; i++)
	{
		if (!pythia.next())
			continue;

		// init parameters for event loop
		event_weight = pythia.info.weight();
		nChar = 0;

		// event loop
		for (int j = 0; j < pythia.event.size(); j++)
		{
			// set current particle
			particle = pythia.event[j];

			// multiplicity counter
			if (particle.isFinal() && particle.isCharged())
				if (particle.pT() >= .20 && abs(particle.eta()) < 1.)
					nChar++;
		}	// end event loop
	t1->Fill();
	}	// end run loop

	// staticstics
	pythia.stat();

	// select output file
	TFile out("clean500_PY_Miro_tau8.root", "recreate");

	// write TTree
	t1->Write();

	return 0;
}
