// main91.cc is a part of the PYTHIA event generator.
// Copyright (C) 2015 Torbjorn Sjostrand.
// PYTHIA is licenced under the GNU GPL version 2, see COPYING for details.
// Please respect the MCnet Guidelines, see GUIDELINES for details.

// This is a simple test program.
// It studies the charged multiplicity distribution at the LHC.
// Modified by Rene Brun, Axel Naumann and Bernhard Meirose
// to use ROOT for histogramming.

// Stdlib header file for input and output.
#include <iostream>

// Header file to access Pythia 8 program elements.
#include "Pythia8/Pythia.h"

// ROOT, for histogramming.
#include "TH1.h"
#include "TH2.h"
#include "TTree.h"

// ROOT, for interactive graphics.
#include "TVirtualPad.h"
#include "TApplication.h"

// ROOT, for saving file.
#include "TFile.h"

using namespace Pythia8;

int nCharged, nNeutral, nTot;

int main(int argc, char* argv[]) {

  // Create the ROOT application environment.
  TApplication theApp("hist", &argc, argv);

  // Create Pythia instance and set it up to generate hard QCD processes
  // above pTHat = 20 GeV for pp collisions at 14 TeV.
  Pythia pythia;
  pythia.readFile("junk.cmnd");
  pythia.init();
  int nEvent = pythia.mode("Main:numberOfEvents");

  // Create file on which histogram(s) can be saved.
  TFile* outFile = new TFile("PythiaOutput.root", "RECREATE");

  // Book histogram.
  TH1F *hmultch = new TH1F("hmultch","charged multiplicity", 100, -0.5, 799.5);
  TH1F *hmultneu = new TH1F("hmultneu","neutral multiplicity", 100, -0.5, 799.5);
  TH1F *hppid = new TH1F("hppid","particle identification number", 1000, -500, 500);
  // dark scalar mediator 4900001
  // dark gluon 4900021
  // dark scalar quark 4900101
  // dark scalar pion 4900111
  // dark scalar rho 4900113
  TH1F *hppidHV = new TH1F("hppidHV","particle identification number-490000", 400, -200., 200.);
  TH1F *hppid2HV = new TH1F("hppid2HV","particle identification number-490000 if has stable daughter", 400, -200., 200.);
  TH1F *hppid2ddg = new TH1F("hppid2ddg","particle identification number-490000 dark gluon daughters", 400, -200., 200.);
  TH2F *hmassHV = new TH2F("hmassHV","mass versus id-4900000",300,-150.,150.,1000,-20.,1500.);
  TH2F *hqHV = new TH2F("hqHV","charge versus id-4900000",300,-150.,150.,40,-2.,2.);
  TH1F *hmHV = new TH1F("hmHV","particle mass HV", 5000, 0., 5000.);
  TH1F *hm2HV = new TH1F("hm2HV","particle mass HV", 200, 0., 50.);
  TH1F *hd0HV = new TH1F("hd0HV","impact parameter HV",200,0.,0.1);
  TH1F *hd0dHV = new TH1F("hd0dHV","impact parameter HV stable daughter",200,0.,1000.);
  TH2F *hd0d2HV = new TH2F("hd0d2HV","impact parameter HV stable daughter versus mom id",200,0.,200.,200,0.,1500.);
  TH1F *hstatus = new TH1F("hstatus","particle status HV",200,-100.,100.);
  TH1F *hstatus2 = new TH1F("hstatus2","particle status HV ndau<2",200,-100.,100.);
  TH1F *hndau = new TH1F("hndau","number daughters HV",100,0.,50.);
  TH1F *hnsdau = new TH1F("hnsdau","number stable daughters HV (at least 1 stable)",100,0.,50.);
  TH1F *hnsdauHV = new TH1F("hnsdauHV","number HV daughters HV (at least 1 stable daughter)",100,0.,50.);
  TH1F *hnsdauCH = new TH1F("hnsdauCH","number charged stable daughters HV (at least 1 stable)",100,0.,50.);
  TH2F *hnsdauvtotdau = new TH2F("hnsdauvtotdau","number stable daughters vs total daug HV (at least 1 stable)",100,0.,50.,100,0.,50.);
  TH2F *hndau2 = new TH2F("hndau2","number of daughters veruss parent ID-4900000",200,0.,200.,50,0.,50.);
  TH1F *hndpis = new TH1F("hndpis","number HV with a  stable daughter in event",100,0.,100.);
  TH1F *hnjet = new TH1F("hnjet"," number jets",50,0.,50.);
  TH1F *hjetpT = new TH1F("hjetpT","jet pT",100,0.,1000.);
  TH1F *hjet1pT = new TH1F("hjet1pT","jet pT",100,0.,1000.);
  TH1F *hjet2pT = new TH1F("hjet2pT","jet pT",100,0.,1000.);
  TH1F *hjet3pT = new TH1F("hjet3pT","jet pT",100,0.,1000.);
  TH1F *hjet4pT = new TH1F("hjet4pT","jet pT",100,0.,1000.);
  TH1F *hjety = new TH1F("hjety","jet y",50,-5.,5.);
  TH1F *hjetphi = new TH1F("hjetphi","jet phi",50,-4.,7.);
  TH1F *hndqs = new TH1F("hndqs","number dark quarks",50,0.,50.);
  TH1F *hndq71 = new TH1F("hndq71","number dark quarks code 71",50,0.,50.);
  TH1F *hndqnm = new TH1F("hndqnm","number dark quarks without dark quark mother",50,0.,50.);
  TH1F *hdRdqj = new TH1F("hdRdqj","delta R between dark quark and matching jet ",100,0.,5.);
  TH1F *hdRdj = new TH1F("hdRdj","delta R between down quark and matching jet ",100,0.,5.);
  TH1F *htright = new TH1F("htright","trigger ht",500,0.,5000.);
  TH1F *hcutflow = new TH1F("hcutflow","cut flow",20,0.,20.);
  TH1F *hdRdpisdjet = new TH1F("hdRdpisdjet","delta R between dark quark and dark pions ",100,0.,5.);
  TH1F *hnjetdpi = new TH1F("hnjetdpi","number of jets containing a dark pi",50,0.,50.);
  TH1F *hndpipj = new TH1F("hndpipj","number of dark pis per jet",50,0.,50.);
  TH1F *hptjetdp = new TH1F("hptjetdp","pt of jets with a dark pi",500,0.,1000.);
  TH1F *hndpipjndq = new TH1F("hndpipjndq","number of dark pis per jet jet not matched dq",50,0.,50.);
  TH1F *hndpipjdq = new TH1F("hndpipjdq","number of dark pis per jet jet matched dq",50,0.,50.);
  TH1F *hndpipjd = new TH1F("hndpipjd","number of dark pis per jet jet matched d",50,0.,50.);
  TH1F *hptjetdpndq = new TH1F("hptjetdpndq","pt of jets with a dark pi not matched dq",500,0.,1000.);
  TH1F *hptjetdpdq = new TH1F("hptjetdpdq","pt of jets with a dark pi matched dq",500,0.,1000.);
  TH2F *hdqvjet = new TH2F("hdqvjet"," pt of dark quark versus matched jet",500,0.,1000.,500,0.,1000.);
  TH1F *hdRdqdq71 = new TH1F("hdRdqdq71","delta R between dark quark and dark quark 71 ",100,0.,5.);
  TH2F *hpTdqdq71 = new TH2F("hpTdqdq71"," pt of dark quark versus dark quark 71",500,0.,1000.,500,0.,1000.);
  TH1F *hjetnc = new TH1F("hjetnc","number of particles in jet",150,0.,150.);
  TH1F *hjetncd = new TH1F("hjetncd","number of particles in jet that are dark pi or rho decendentss",100,0.,100.);
  TH2F *hjetncncd = new TH2F("hjetncncd","number of particles in jet versus number that are dark pi or rho descendents",100,0.,100.,100,0.,100.);
  TH1F *hjetpp = new TH1F("hjetpp"," number of particles in jet not dark pi or rho descendents",100,0.,100.);
  TH1F *hjetncdqj = new TH1F("hjetncdqj","number of particles in dark quark jet",150,0.,150.);
  TH2F *hjetncdqjvpt = new TH2F("hjetncdqjvpt","number of particles in dark quark jet",500,0.,1000.,150,0.,150.);
  TH1F *hjetncddqj = new TH1F("hjetncddqj","number of particles in jet that are dark pi or rho decendentss dark quark jet",150,0.,150.);
  TH1F *hjetppdqj = new TH1F("hjetppdqj"," number of particles in jet not dark pi or rho descendents dark quark jet",100,0.,100.);
  TH1F *hjetncdj = new TH1F("hjetncdj","number of particles in down quark jet",150,0.,150.);
  TH2F *hjetncdjvpt = new TH2F("hjetncdjvpt","number of particles in down quark jet",500,0.,100.,150,0.,150.);
  TH1F *hjetncddj = new TH1F("hjetncddj","number of particles in jet that are dark pi or rho decendentss down quark jet",150,0.,150.);
  TH1F *hjetppdj = new TH1F("hjetppdj"," number of particles in jet not dark pi or rho descendents down quark jet",100,0.,100.);


  // initialize slowjet
  SlowJet aSlowJet(-1,0.4,35.,2.5,2,1); // power, R, ptjetmin, etamax, which particle, mass
  // initialize trigger slow jet
  SlowJet trigSlowJet(-1,0.4,40.,3.0,2,1); // power, R, ptjetmin, etamax, which particle, mass

  //delete jets outside of acceptance
  


  // Begin event loop. Generate event; skip if generation aborted.


  Int_t ndqs,ndq71,ndqnm,m1,m2,ipid,dq1,dq2,d1,d2;
  Int_t dq711,dq712;
  Int_t idbg=0;
  Float_t dq1pT,dq1y,dq1phi;
  Float_t dq2pT,dq2y,dq2phi;
  Float_t d1pT,d1y,d1phi;
  Float_t d2pT,d2y,d2phi;
  Float_t dq1dR,dq2dR,d1dR,d2dR,aaatmp,aaatmp2;
  Int_t dq1sj,dq2sj,d1sj,d2sj;



  for (int iEvent = 0; iEvent < nEvent; ++iEvent) {
    if (!pythia.next()) continue;

    if(idbg>0) {
      std::cout<<endl;
      std::cout<<endl;
      std::cout<<endl;
      std::cout<<"***********************************************************"<<endl;
      std::cout<<"Will Robinson New Event "<<iEvent<<std::endl;
    }

    // do jet finding for this event
    aSlowJet.analyze(pythia.event );
    trigSlowJet.analyze(pythia.event );

    // Find number of all final charged particles.
    nCharged = 0;  // for counting the number of stable charged particles in the event
    nNeutral = 0;  // ditto neutral
    nTot=0;
    vector<int> ptdpis;
    ndqs=0;  // number of dark quarks 
    ndq71=0; // number of dark quarks with 71 code
    ndqnm=0; // number of dark quarks with no dark quark mother
    dq1=0;
    dq2=0;
    d1=0;
    d2=0;
    dq711=0;
    dq712=0;
    //pointers to stable particles from dark quarks
    vector<int> stbdq;;


    for (int i = 0; i < pythia.event.size(); ++i) {  // loop over all particles in the event
      //      std::cout<<pythia.event[i].isCharged()<<endl;

      //  look at dark quarks
      if(abs(pythia.event[i].id())==4900101) {
	ndqs++;  // count number of dark quarks in event
	// look for dark quarks that do not have a dark quark daughter
        m1=pythia.event[i].mother1();
	m2=pythia.event[i].mother2();
	if( (abs(pythia.event[m1].id())!=4900101) && (abs(pythia.event[m2].id())!=4900101) ) {
	  ndqnm++;
	  if(dq1==0) {
	    dq1=i;
	    if(abs(pythia.event[pythia.event[m1].daughter1()].id())==1) {
	      d1=pythia.event[m1].daughter1();
	    } else{
	      d1=pythia.event[m1].daughter2();
	    }
	  } else {
	    dq2=i;
	    if(abs(pythia.event[pythia.event[m1].daughter1()].id())==1) {
	      d2=pythia.event[m1].daughter1();
	    } else{
	      d2=pythia.event[m1].daughter2();
	    }
	  }
	}
	// look for dark quarks with code 71
	if(abs(pythia.event[i].status())==71) {
	  ndq71++;
	  if(idbg>0) cout<<" dark quark with code 71 is "<<i<<" "<<pythia.event[i].pT()<<" "<<pythia.event[i].y()<<" "<<pythia.event[i].phi()<<endl;
	  if(dq711==0) {
	    dq711=i;
	  } else {
	    dq712=i;
	  }
	}
      }
      // look at all HV particles
      if(abs(pythia.event[i].id())>4900000) {
	int idHV = pythia.event[i].id();
	Float_t mHV = pythia.event[i].m();
	Float_t qHV = pythia.event[i].charge();
        Float_t d0HV = sqrt(pow(pythia.event[i].xProd(),2)+pow(pythia.event[i].yProd(),2));
	Int_t ndauHV = pythia.event[i].daughter2()-pythia.event[i].daughter1()+1;
	Int_t HV = (idHV/abs(idHV))*(abs(idHV)-4900000);
	hppidHV->Fill( HV);  // get the type of the particle
        hmassHV->Fill( HV,mHV );
        hqHV->Fill( HV,qHV );
	hmHV->Fill(mHV);
	hm2HV->Fill(mHV);
	hd0HV->Fill(d0HV);
	hstatus->Fill(pythia.event[i].status());
	if(ndauHV<2) hstatus2->Fill(pythia.event[i].status());
        hndau->Fill(ndauHV);
        hndau2->Fill(abs(HV),ndauHV);
	//what are the dark gluon daughters?
	if(HV==21) {
	  if(pythia.event[i].daughter1()!=0) hppid2ddg->Fill(pythia.event[pythia.event[i].daughter1()].id()-4900000);
	  if(pythia.event[i].daughter2()!=0) hppid2ddg->Fill(pythia.event[pythia.event[i].daughter2()].id()-4900000);
	}
	if(ndauHV>0) { // if it is not a stable HV particle
	  // see if one is a hadron
	  Int_t nstable=0;
	  for(int ij=0; ij<ndauHV; ++ij) {  // loop over all the HV particle's daughters
	    Int_t iii = pythia.event[i].daughter1()+ij;
	    if(pythia.event[iii].isHadron()) {  // for stable daughters of HV particles
	      nstable++;
	    }
	  }  // end loop over HV daughters
	  if(nstable>0) {
	    ptdpis.push_back(i);
	    Float_t d0dHV = sqrt(pow(pythia.event[pythia.event[i].daughter1()].xProd(),2)+pow(pythia.event[pythia.event[i].daughter1()].yProd(),2));
 	    hppid2HV->Fill(HV);
	    hd0dHV->Fill(d0dHV);
	    hd0d2HV->Fill(abs(HV),d0dHV);
            hnsdau->Fill(nstable);
            Int_t nstableCH=0;
 	    Int_t nHVdau=0;
	    for(int ij=0; ij<ndauHV; ++ij) {  // loop over all the HV particle's daughters
 	      Int_t iii = pythia.event[i].daughter1()+ij;
	      if(abs(pythia.event[iii].id())>4900000) nHVdau++;
 	      if(pythia.event[iii].isCharged()) nstableCH++;
	    }
            hnsdauCH->Fill(nstableCH);
            hnsdauHV->Fill(nHVdau);
	    hnsdauvtotdau->Fill(ndauHV,nstable);

	  }  // end test that it has stable daughters

	}  // end test that it has daughters
      }  // end test that it is an HV particles


      if (pythia.event[i].isFinal() && pythia.event[i].isCharged()==0)  // count if stable and charged
        ++nCharged;

      if (pythia.event[i].isFinal() && pythia.event[i].isCharged()!=0) // count if stable and neutral
        ++nNeutral;

      // study stable particles
      if(pythia.event[i].isFinal()) {  // if stable
	hppid->Fill( pythia.event[i].id() );  // get the type of the particle
	nTot=nTot+1;  //count

	//trace back and see if it came from a dark quark
	if(idbg>9) cout<<"moms trace start for particle "<<i<<endl;
        Int_t ipt = i;
	vector<int> moms;
        if(pythia.event[ipt].mother1()!=0) moms.push_back(pythia.event[ipt].mother1());
	bool yuck = pythia.event[ipt].mother1()!=pythia.event[ipt].mother2();
        if( (pythia.event[ipt].mother2()!=0)&&(yuck) ) moms.push_back(pythia.event[ipt].mother2());
	bool isdqd=false;
        while( (moms.size()>0) && (isdqd==false) ) {
          ipt=moms[0];
	  if(idbg>9) cout<<"    looking at mom "<<ipt<<" size of mom array is "<<moms.size()<<endl;
	  if( (abs(pythia.event[ipt].id())==4900111)||(abs(pythia.event[ipt].id())==4900113)) { // dark pion or dark rho
	    stbdq.push_back(i);
	    isdqd=true;
	    if(idbg>9) cout<<" ending it is dark"<<endl;
	  } else {
           if(pythia.event[ipt].mother1()!=0) moms.push_back(pythia.event[ipt].mother1());
	  bool yuck = pythia.event[ipt].mother1()!=pythia.event[ipt].mother2();
           if((pythia.event[ipt].mother2()!=0)&&(yuck)) moms.push_back(pythia.event[ipt].mother2());
	   if(idbg>9) {
	     cout<<"adding mothers "<<pythia.event[ipt].mother1()<<" "<<pythia.event[ipt].mother2()<<endl;
	   }
	  }
          moms.erase(moms.begin());
	  if(idbg>9) cout<<"check size after erase "<<moms.size()<<endl;
        }



      }  // end study stable particles



    }  // end particle list loop 
    // Fill charged multiplicity in histogram. End event loop.
    hmultch->Fill( nCharged );
    hmultneu->Fill( nNeutral );
    hndpis->Fill( ptdpis.size() );
    hndqs->Fill( ndqs );
    hndq71->Fill( ndq71 );
    hndqnm->Fill( ndqnm );



    if(idbg>0) {
      cout<<"will robinson"<<endl;
      cout<<"number dark quarks without dark quark mothers is "<<ndqnm<<endl;
      cout<<" pointers to dark quarks are "<<dq1<<" "<<dq2<<endl;
      cout<<" pt y phi are "<<pythia.event[dq1].pT()<<" "<<pythia.event[dq1].y()<<" "<<pythia.event[dq1].phi()<<endl;
      cout<<" pt y phi are "<<pythia.event[dq2].pT()<<" "<<pythia.event[dq2].y()<<" "<<pythia.event[dq2].phi()<<endl;
      cout<<" pointers to d quarks are "<<d1<<" "<<d2<<endl;
      cout<<" pt y phi are "<<pythia.event[d1].pT()<<" "<<pythia.event[d1].y()<<" "<<pythia.event[d1].phi()<<endl;
      cout<<" pt y phi are "<<pythia.event[d2].pT()<<" "<<pythia.event[d2].y()<<" "<<pythia.event[d2].phi()<<endl;
      cout<<endl;
      cout<<" number dark quarks code 71 is "<<ndq71<<endl;
    }
    if(idbg>0) {
      cout<<endl;
      cout<<" information about dark pions"<<endl;
      cout<<" number of dark pions is "<<ptdpis.size()<<endl;
      cout<<" id mother1 mother2 daughter 1 daughter2 pt y phi"<<endl;
      for(int jj=0;jj<ptdpis.size();++jj) {
	Int_t kk = ptdpis[jj];
	 cout<<kk<<" "<<pythia.event[kk].id()<<" "<<pythia.event[kk].mother1()<<" "<<pythia.event[kk].mother2()<<" "<<
	  pythia.event[kk].daughter1()<<" "<<pythia.event[kk].daughter2()<<" "<<
        pythia.event[kk].pT()<<" "<<pythia.event[kk].y()<<" "<<pythia.event[kk].phi()<<" "<<endl;

      }
    }


    // compare code 71 dark quarks to initial dark quarks
    Float_t a1=abs(pythia.event[dq1].phi()-pythia.event[dq711].phi());
    if(a1>3.14159) a1=6.2832-a1;
    a1=sqrt(pow(pythia.event[dq1].y()-pythia.event[dq711].y(),2)+pow(a1,2));
    Float_t b1=abs(pythia.event[dq1].phi()-pythia.event[dq712].phi());
    if(b1>3.14159) b1=6.2832-b1;
    b1=sqrt(pow(pythia.event[dq1].y()-pythia.event[dq712].y(),2)+pow(b1,2));
    if(a1<b1) {
      hdRdqdq71->Fill(a1);
      hpTdqdq71->Fill(pythia.event[dq1].pT(),pythia.event[dq711].pT());
    } else {
      hdRdqdq71->Fill(b1);
      hpTdqdq71->Fill(pythia.event[dq1].pT(),pythia.event[dq712].pT());
    }


    a1=abs(pythia.event[dq2].phi()-pythia.event[dq711].phi());
    if(a1>3.14159) a1=6.2832-a1;
    a1=sqrt(pow(pythia.event[dq2].y()-pythia.event[dq711].y(),2)+pow(a1,2));
    b1=abs(pythia.event[dq2].phi()-pythia.event[dq712].phi());
    if(b1>3.14159) b1=6.2832-b1;
    b1=sqrt(pow(pythia.event[dq2].y()-pythia.event[dq712].y(),2)+pow(b1,2));
    if(a1<b1) {
      hdRdqdq71->Fill(a1);
      hpTdqdq71->Fill(pythia.event[dq2].pT(),pythia.event[dq711].pT());
    } else {
      hdRdqdq71->Fill(b1);
      hpTdqdq71->Fill(pythia.event[dq2].pT(),pythia.event[dq712].pT());
    }


    // change to code 71 dark quarks
    //    dq1=dq711;
    //    dq2=dq712;


    //get kinematic variables for initial dark quarks and d quarks

    dq1pT=pythia.event[dq1].pT();
    dq1y=pythia.event[dq1].y();
    dq1phi=pythia.event[dq1].phi();
    dq2pT=pythia.event[dq2].pT();
    dq2y=pythia.event[dq2].y();
    dq2phi=pythia.event[dq2].phi();
    d1pT=pythia.event[d1].pT();
    d1y=pythia.event[d1].y();
    d1phi=pythia.event[d1].phi();
    d2pT=pythia.event[d2].pT();
    d2y=pythia.event[d2].y();
    d2phi=pythia.event[d2].phi();

    // delta r between dark quark and d quark
    //    Float_t bbb=99999.;
    // aaatmp=abs(dq1phi-aSlowJet.phi(ijet));
    //  if(aaatmp>3.14159) aaatmp=6.2832-aaatmp;
    //  aaatmp=sqrt(pow(dq1y-aSlowJet.y(ijet),2)+pow(aaatmp,2));
    //  if(aaatmp<dq1dR) {
    //	dq1dR=aaatmp;
    //	dq1sj=ijet;
    // }
    
      


    // variables to do matching to slow jets
    dq1dR=99999.;
    dq2dR=99999.;
    d1dR=99999.;
    d2dR=99999.;


    // analyze jets
    hnjet->Fill( aSlowJet.sizeJet() );
    if(idbg>0) aSlowJet.list();
    if(aSlowJet.sizeJet()>0)  hjet1pT->Fill(aSlowJet.pT(0));
    if(aSlowJet.sizeJet()>1)  hjet2pT->Fill(aSlowJet.pT(1));
    if(aSlowJet.sizeJet()>2)  hjet3pT->Fill(aSlowJet.pT(2));
    if(aSlowJet.sizeJet()>3)  hjet4pT->Fill(aSlowJet.pT(3));

    // set up counters for number of dark pions in each jet and number of jets with at least one dark pion
    vector<int> ndpiinjet(aSlowJet.sizeJet());
    vector<int> ninjet(aSlowJet.sizeJet());
    vector<int> ndqdinjet(aSlowJet.sizeJet());
    for(int ii=0; ii<aSlowJet.sizeJet(); ii++) { 
      ndpiinjet[ii]=0;
      ninjet[ii]=0;
      ndqdinjet[ii]=0;
    }

    for (int ijet =0; ijet< aSlowJet.sizeJet(); ++ijet) {
      hjetpT->Fill(aSlowJet.pT(ijet));
      hjety->Fill(aSlowJet.y(ijet));
      hjetphi->Fill(aSlowJet.phi(ijet));

      //get number of constituents in jet
      vector<int> consti = aSlowJet.constituents(ijet);
      ninjet[ijet]= consti.size();
      int idd=0;  // count number that came from a dark object
      for(int ji=0;ji<consti.size(); ++ji) {
	bool innn=false;
	for(int ki=0;ki<stbdq.size(); ++ki) {
	  if(consti[ji]==stbdq[ki]) innn=true;
	}
	if(innn) {idd++;}
      }
      ndqdinjet[ijet]=idd;
      hjetnc->Fill(ninjet[ijet]);
      hjetncd->Fill(ndqdinjet[ijet]);
      hjetncncd->Fill(ninjet[ijet],ndqdinjet[ijet]);
      hjetpp->Fill(ninjet[ijet]-ndqdinjet[ijet]);

      // find number of dark quarks in jet
      for(int ll=0;ll<ptdpis.size();++ll) {
        aaatmp=abs(pythia.event[ptdpis[ll]].phi()-aSlowJet.phi(ijet));
        if(aaatmp>3.14159) aaatmp=6.2832-aaatmp;
        aaatmp=sqrt(pow(pythia.event[ptdpis[ll]].y()-aSlowJet.y(ijet),2)+pow(aaatmp,2));
	if(aaatmp<0.4) {
	  ndpiinjet[ijet]=ndpiinjet[ijet]+1;
	}
      }



      // find delta R to dq1
      aaatmp=abs(dq1phi-aSlowJet.phi(ijet));
      if(aaatmp>3.14159) aaatmp=6.2832-aaatmp;
      aaatmp=sqrt(pow(dq1y-aSlowJet.y(ijet),2)+pow(aaatmp,2));
      if(aaatmp<dq1dR) {
	dq1dR=aaatmp;
	dq1sj=ijet;
      }

      // find delta R to dq2
      aaatmp=abs(dq2phi-aSlowJet.phi(ijet));
      if(aaatmp>3.14159) aaatmp=6.2832-aaatmp;
      aaatmp=sqrt(pow(dq2y-aSlowJet.y(ijet),2)+pow(aaatmp,2));
      if(aaatmp<dq2dR) {
	dq2dR=aaatmp;
	dq2sj=ijet;
      }
      // find delta R to d1
      aaatmp=abs(d1phi-aSlowJet.phi(ijet));
      //      cout<<d1phi<<" "<<aSlowJet.phi(ijet)<<" "<<aaatmp<<endl;
      if(aaatmp>3.14159) aaatmp=6.2832-aaatmp;
      //      cout<<d1y<<" "<<aSlowJet.y(ijet)<<endl;
      aaatmp=sqrt(pow(d1y-aSlowJet.y(ijet),2)+pow(aaatmp,2));
      //      cout<<" ijet "<<ijet<<" aaatmp "<<aaatmp<<" d1dR "<<d1dR<<endl;
      if(aaatmp<d1dR) {
	d1dR=aaatmp;
	d1sj=ijet;
      }
      // find delta R to d2
      aaatmp=abs(d2phi-aSlowJet.phi(ijet));
      if(aaatmp>3.14159) aaatmp=6.2832-aaatmp;
      aaatmp=sqrt(pow(d2y-aSlowJet.y(ijet),2)+pow(aaatmp,2));
      if(aaatmp<d2dR) {
	d2dR=aaatmp;
	d2sj=ijet;
      }

    }  // end loop over slow jets


    if(idbg>0) {
      cout<<" slow jet matching to dq1 is "<<dq1sj<<endl;
      cout<<" slow jet matching to dq2 is "<<dq2sj<<endl;
      cout<<" slow jet matching to d1 is "<<d1sj<<endl;
      cout<<" slow jet matching to d2 is "<<d2sj<<endl;
    }

      hdRdqj->Fill(dq1dR);
      hdRdqj->Fill(dq2dR);

      hdRdj->Fill(d1dR);
      hdRdj->Fill(d2dR);

      hdqvjet->Fill(pythia.event[dq1].pT(),aSlowJet.pT(dq1sj));
      hdqvjet->Fill(pythia.event[dq2].pT(),aSlowJet.pT(dq2sj));
      Float_t Del1 = (pythia.event[dq1].pT()-aSlowJet.pT(dq1sj))/aSlowJet.pT(dq1sj);
      Float_t Del2 = (pythia.event[dq2].pT()-aSlowJet.pT(dq2sj))/aSlowJet.pT(dq2sj);
      if(idbg>0) {
      if( (Del1>0.5&&aSlowJet.pT(dq1sj)<60) || (Del2>0.5&&aSlowJet.pT(dq2sj)<60) ) {
	cout<<"danger danger will robinson Del1 Del2 are "<<Del1<<" "<<Del2<<endl;
      } }
    
      





    // another loop over slow jets to make plots about dark quarks matched to them
    Int_t njetdpi=0;
    if(idbg>0) cout<<" information about dark pions per jet"<<endl;
    for (int ijet =0; ijet< aSlowJet.sizeJet(); ++ijet) {

      if(ndpiinjet[ijet]>0) {  // count number of jets with at least 1 dark pions
	njetdpi=njetdpi+1;
      }

      hndpipj->Fill(ndpiinjet[ijet]);
      hptjetdp->Fill(aSlowJet.pT(ijet));
      if( (ijet!=dq1sj)&& (ijet!=dq2sj) ) {  // if doesn't match dark quart jet
        hndpipjndq->Fill(ndpiinjet[ijet]);
        hptjetdpndq->Fill(aSlowJet.pT(ijet));
      } else {  // if matches dark quark jets
        hndpipjdq->Fill(ndpiinjet[ijet]);
        hptjetdpdq->Fill(aSlowJet.pT(ijet));
        hjetncdqj->Fill(ninjet[ijet]);
        hjetncdqjvpt->Fill(aSlowJet.pT(ijet),ninjet[ijet]);
        hjetncddqj->Fill(ndqdinjet[ijet]);
        hjetppdqj->Fill(ninjet[ijet]-ndqdinjet[ijet]);

      }

      if( (ijet==d1sj) || (ijet==d2sj) ) {  // if matches down quark jets
        hndpipjd->Fill(ndpiinjet[ijet]);
        hjetncddj->Fill(ndqdinjet[ijet]);
        hjetppdj->Fill(ninjet[ijet]-ndqdinjet[ijet]);
        hjetncdj->Fill(ninjet[ijet]);
        hjetncdjvpt->Fill(aSlowJet.pT(ijet),ninjet[ijet]);
      }


      if(idbg>0) {
	cout<<ijet<<" "<<ndpiinjet[ijet]<<endl;
      }
    }
    hnjetdpi->Fill(njetdpi);


    // find delta R between dark pions and dark quarts
    for (int ii =0; ii< ptdpis.size(); ++ii) {
      Int_t ipt = ptdpis[ii];
      // find delta R to dq1
      aaatmp=abs(dq1phi-pythia.event[ipt].phi());
      if(aaatmp>3.14159) aaatmp=6.2832-aaatmp;
      aaatmp=sqrt(pow(dq1y-pythia.event[ipt].y(),2)+pow(aaatmp,2));
      // find delta R to dq2
      aaatmp2=abs(dq2phi-pythia.event[ipt].phi());
      if(aaatmp2>3.14159) aaatmp2=6.2832-aaatmp2;
      aaatmp2=sqrt(pow(dq2y-pythia.event[ipt].y(),2)+pow(aaatmp2,2));
      //take minimum
      if(aaatmp2<aaatmp) aaatmp=aaatmp2;
      if(idbg>0) {
	if(aaatmp>2) cout<<"danger danger will robinson aaatmp large"<<endl;}
      hdRdpisdjet->Fill(aaatmp);
    }


    // for each dark quark, output daughter tree until hit stable particle
    // dark quark 1
    cout<<endl;
    if(idbg>0) cout<<"beginning dark quark 1 "<<dq1<<endl;
    Int_t ipt = dq1;
    //get number of daughters
    vector<int> dpts1;
    vector<bool> indq1(pythia.event.size());
    indq1[ipt]=true;
    Int_t nd = pythia.event[ipt].daughter2()-pythia.event[ipt].daughter1()+1;
    for(int kk=0;kk<nd;++kk){
      indq1[pythia.event[ipt].daughter1()+kk]=true;
      dpts1.push_back(pythia.event[ipt].daughter1()+kk);
    }

      
    while(dpts1.size()>0) {
      ipt=dpts1[0];
      dpts1.erase(dpts1.begin());
      nd = pythia.event[ipt].daughter2()-pythia.event[ipt].daughter1()+1;
      for(int kk=0;kk<nd;++kk){
	if( (pythia.event[pythia.event[ipt].daughter1()+kk].isFinal()==false)&&
	    (abs(pythia.event[pythia.event[ipt].daughter1()+kk].id())>4900000)
	   ) {
          dpts1.push_back(pythia.event[ipt].daughter1()+kk);
	  indq1[pythia.event[ipt].daughter1()+kk]=true;
	}
      }
    }
    if(idbg>0) cout<<" id mothers daughters pt y phi deltaR"<<endl;
    for(int kk=0;kk<pythia.event.size();++kk) {
      if(indq1[kk]) {
	aaatmp=abs(dq1phi-pythia.event[kk].phi());
        if(aaatmp>3.14159) aaatmp=6.2832-aaatmp;
        aaatmp=sqrt(pow(dq1y-pythia.event[kk].y(),2)+pow(aaatmp,2));

        if(idbg>0) cout<<kk<<" "<<pythia.event[kk].id()<<" "<<pythia.event[kk].mother1()<<" "<<pythia.event[kk].mother2()<<" "<<
	  pythia.event[kk].daughter1()<<" "<<pythia.event[kk].daughter2()<<" "<<
        pythia.event[kk].pT()<<" "<<pythia.event[kk].y()<<" "<<pythia.event[kk].phi()<<" "<<aaatmp<<endl;
      }
    }
    
    // dark quark 2
    cout<<endl;
    if(idbg>0) cout<<"beginning dark quark 2 "<<dq2<<endl;
    ipt = dq2;
    //get number of daughters
    vector<int> dpts2;
    vector<bool> indq2(pythia.event.size());
    indq2[ipt]=true;
    nd = pythia.event[ipt].daughter2()-pythia.event[ipt].daughter1()+1;
    for(int kk=0;kk<nd;++kk){
      indq2[pythia.event[ipt].daughter1()+kk]=true;
      dpts2.push_back(pythia.event[ipt].daughter1()+kk);
    }

      
    while(dpts2.size()>0) {
      ipt=dpts2[0];
      dpts2.erase(dpts2.begin());
      nd = pythia.event[ipt].daughter2()-pythia.event[ipt].daughter1()+1;
      for(int kk=0;kk<nd;++kk){
	if( (pythia.event[pythia.event[ipt].daughter1()+kk].isFinal()==false)&&
	    (abs(pythia.event[pythia.event[ipt].daughter1()+kk].id())>4900000)
	   ) {
          dpts2.push_back(pythia.event[ipt].daughter1()+kk);
	  indq2[pythia.event[ipt].daughter1()+kk]=true;
	}
      }
    }
    if(idbg>0) cout<<" id mothers daughters pt y phi deltaR"<<endl;
    for(int kk=0;kk<pythia.event.size();++kk) {
      if(indq2[kk]) {
	aaatmp=abs(dq2phi-pythia.event[kk].phi());
        if(aaatmp>3.14159) aaatmp=6.2832-aaatmp;
        aaatmp=sqrt(pow(dq2y-pythia.event[kk].y(),2)+pow(aaatmp,2));

        if(idbg>0) cout<<kk<<" "<<pythia.event[kk].id()<<" "<<pythia.event[kk].mother1()<<" "<<pythia.event[kk].mother2()<<" "<<
	  pythia.event[kk].daughter1()<<" "<<pythia.event[kk].daughter2()<<" "<<
        pythia.event[kk].pT()<<" "<<pythia.event[kk].y()<<" "<<pythia.event[kk].phi()<<" "<<aaatmp<<endl;
      }
    }
    





    //calculate trigger HT
    Float_t trigHT=0.;
    for (int ijet =0; ijet< trigSlowJet.sizeJet(); ++ijet) {
      trigHT=trigHT+trigSlowJet.pT(ijet);
    }
    htright->Fill(trigHT);

    // event selection
    Int_t icut =0;
    bool pass = true;

    hcutflow->Fill(icut+0.5); icut++;// all events

    if(trigHT>800) hcutflow->Fill(icut+0.5); icut++;  //trigger

    if(aSlowJet.sizeJet()>0) {
      if(aSlowJet.pT(0)>400) {
	if(pass) hcutflow->Fill(icut+0.5); icut++;
      }  else {
	pass=false;
      }
    }
    if(aSlowJet.sizeJet()>1) {
      if(aSlowJet.pT(1)>200) {
	if(pass) hcutflow->Fill(icut+0.5); icut++;
      }  else {
	pass=false;
      }
    }
    if(aSlowJet.sizeJet()>2) {
      if(aSlowJet.pT(2)>125) {
	if(pass) hcutflow->Fill(icut+0.5); icut++;
      }  else {
	pass=false;
      }
    }
    if(aSlowJet.sizeJet()>3) {
      if(aSlowJet.pT(3)>50) {
	if(pass) hcutflow->Fill(icut+0.5);icut++;
      }  else {
	pass=false;
      }
    }




  }  // end loop over events

  // Statistics on event generation.
  pythia.stat();


  // Save histogram on file and close file.

  hcutflow->Write();


  hjetnc->Write();
  hjetncd->Write();
  hjetncncd->Write();
  hjetpp->Write();

  hjetncdqj->Write();
  hjetncdqjvpt->Write();
  hjetncddqj->Write();
  hjetppdqj->Write();

  hjetncdj->Write();
  hjetncdjvpt->Write();
  hjetncddj->Write();
  hjetppdj->Write();

  hdRdqdq71->Write();
  hpTdqdq71->Write();
  hdqvjet->Write();
  hnjetdpi->Write();
  hndpipj->Write();
  hndpipjndq->Write();
  hndpipjdq->Write();
  hndpipjd->Write();
  hptjetdp->Write();
  hptjetdpndq->Write();
  hptjetdpdq->Write();
  hdRdpisdjet->Write();
  htright->Write();
  hdRdqj->Write();
  hdRdj->Write();
  hppid2ddg->Write();
  hndpis->Write();
  hndqs->Write();
  hndq71->Write();
  hndqnm->Write();
  hmultch->Write();
  hmultneu->Write();
  hppid->Write();
  hppidHV->Write();
  hppid2HV->Write();
  hmassHV->Write();
  hqHV->Write();
  hmHV->Write();
  hm2HV->Write();
  hd0HV->Write();
  hd0dHV->Write();
  hd0d2HV->Write();
  hstatus->Write();
  hstatus2->Write();
  hndau->Write();
  hnsdau->Write();
  hnsdauHV->Write();
  hnsdauvtotdau->Write();
  hnsdauCH->Write();
  hndau2->Write();
  hnjet->Write();
  hjetpT->Write();
  hjet1pT->Write();
  hjet2pT->Write();
  hjet3pT->Write();
  hjet4pT->Write();
  hjety->Write();
  hjetphi->Write();

  // output acceptance
  cout<<"acceptance results"<<endl;
  cout<<hcutflow->GetBinContent(0)<<endl;
  cout<<hcutflow->GetBinContent(1)<<endl;
  cout<<hcutflow->GetBinContent(2)<<endl;
  cout<<hcutflow->GetBinContent(3)<<endl;
  cout<<hcutflow->GetBinContent(4)<<endl;
  cout<<hcutflow->GetBinContent(5)<<endl;
  cout<<hcutflow->GetBinContent(6)<<endl;


  delete outFile;

  // Done.
  return 0;
}
