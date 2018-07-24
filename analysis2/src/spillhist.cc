#include <vector>
#include <algorithm>
#include <TApplication.h>
#include <stdio.h>
#include <string.h>
#include <exception>
#include <fstream>
#include <vector>
#include "TFile.h"
#include "TDirectory.h"
#include "TH1D.h"
#include "TSystem.h"
#include "TMacro.h"
#include <TTree.h>
#include <iostream>
#include <sstream>
#include "TH2.h"
#include "TH1.h"
#include "TH3.h"
#include <iterator>

using namespace std;

struct bsdtree
{
  vector<double> *spill;
  vector<double> *pot;
  vector<double> *unixtime;
};

struct StDate
{
  long year;
  long month;
  long day;
};


int main(int argc, char *argv[]){

  TApplication app("app", &argc, argv);
  
  int runstart = atoi(argv[1]);
  int subrunstart = atoi(argv[3]);

  int runend = atoi(argv[2]);
  int subrunend = atoi(argv[4]);

  int spillnum;
  double POT[5][9];
  int unixtime[3];

  bsdtree BsdVec;
  
  BsdVec.spill = 0;
  BsdVec.pot = 0;
  BsdVec.unixtime = 0;

  TTree* spill;
  spill = new TTree("spill", " a tree of spill history");

  spill->Branch("_spillnum", &BsdVec.spill);
  spill->Branch("_pot", &BsdVec.pot);
  spill->Branch("_unixtime", &BsdVec.unixtime);

  TString Directory_out =
    "/Users/jinaren/Documents/T2K/BabyMIND/commissioning_run/event_estimation/macro/Myanalysis/Spill/";
  
  TString Filename_txt = "Spill.txt";
  ofstream fout(Directory_out + Filename_txt);

  //**** inputfile ****//

  for(int i_run = runstart; i_run <= runend; i_run++){
    for(int i_subrun = subrunstart; i_subrun <= subrunend; i_subrun++){

      BsdVec.spill->clear();
      BsdVec.pot->clear();
      BsdVec.unixtime->clear();
  
      ostringstream sDirrun, sDirsubrun;
      string sFileName;

      sDirrun.str("");
      sDirsubrun.str("");
      sDirrun << i_run;
      sDirsubrun << i_subrun;
      sFileName =  "bsd_run0" + sDirrun.str() + "_" + sDirsubrun.str() + "p06.root";
      if(i_subrun<10){
	sFileName =  "bsd_run0" + sDirrun.str() + "_0" + sDirsubrun.str() + "p06.root";
      }
  

  TString Directory = "../bsd/";

  TString inputFile = Directory + sFileName.c_str();

  TFile *Fileinput;
  FileStat_t info;
  if (gSystem->GetPathInfo(inputFile.Data(), info)!=0) {
    printf("File '%s' does not exist.\n", inputFile.Data());
    continue;
  } else {
    Fileinput = new TFile(inputFile);
  }

  TTree *t = (TTree*)Fileinput->Get("bsd");

  //**** outputfile ****//
  
  TString Filename_out = "Spill_" + sDirrun.str() + "_" + sDirsubrun.str() + ".root";
  //TString Filename_txt = "Spill_" + sDirrun.str() + "_" + sDirsubrun.str() + ".txt";
  
  TString rootoutputFile = (Directory_out + Filename_out);  
  TFile *Fileoutput = new TFile(rootoutputFile.Data(), "recreate");


  t->SetBranchAddress("spillnum", &spillnum);
  t->SetBranchAddress("ct_np", POT);
  t->SetBranchAddress("trg_sec", unixtime);


  int N = t->GetEntries();

  cout << N << '\n';
  
  for (Int_t ientry = 0; ientry < N; ientry++) {
    t->GetEntry(ientry);

    int wagasci_spill = spillnum & 0x7FFF;

    const time_t now = unixtime[0];
    const tm* ts = localtime(&now);
    const StDate date = {ts->tm_year+1900, ts->tm_mon+1, ts->tm_mday};

    fout << wagasci_spill << " " << POT[4][0]/pow(10, 14) << " " << date.year << " " 
	 << date.month << " " << date.day <<'\n';
    BsdVec.spill->push_back(wagasci_spill);
    BsdVec.pot->push_back(POT[4][0]);
    BsdVec.unixtime->push_back(unixtime[0]);   
  }

  Fileinput->Close();
  Fileoutput->Close();
    }
  }
  
  spill->Fill();
  spill->Write();
    
  BsdVec.spill = 0;
  BsdVec.pot = 0;
  BsdVec.unixtime = 0;
  
  //app.Run();
  return 0;
}
