#include <vector>
#include <algorithm>
#include "TApplication.h"
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

double min(double x, double y)
  {
    if ( x < y ) {
      return x;
    } else {
      return y;
    }
  }

double max(double x, double y)
  {
    if ( x > y ) {
      return x;
    } else {
      return y;
    }
  }

struct vectorstree
{
  vector<double> *SpillTag;
  vector<double> *SpillTimeGTrig;
  vector<double> *hitTimefromSpill;
  vector<double> *SpillTrailTime;

  vector<double> *GTrigTag;
  vector<double> *SpillTime;
  vector<double> *GTrigTime;
  vector<double> *hitsChannel;
  vector<double> *hitAmpl;
  vector<double> *hitLeadTime;
  vector<double> *hitTrailTime;
  vector<double> *hitTimeDif;
  //vector<double> *TimeCoins;
};

struct eventvectorsTree
{
  vector<double> *Spill;
  vector<double> *GTrigTime;
  vector<double> *PosX;
  vector<double> *PosY;
  vector<double> *PosZ;
  //vector<double> *RSignalTime;
  //vector<double> *LSignalTime;
  //vector<double> *TSignalTime;
  vector<double> *RSignalAmpl;
  vector<double> *LSignalAmpl;
  vector<double> *TSignalAmpl;
  vector<double> *RSignalLeadTime;
  vector<double> *LSignalLeadTime;
  vector<double> *TSignalLeadTime;
  vector<double> *hitTimeDif;
  vector<double> *EventNum;
  vector<double> *LastModule;
  vector<double> *hitnum;
  vector<double> *hitmodulenum;
  vector<double> *FirstModule;
  vector<double> *ModuleNumber;
  vector<double> *ChannelNumber;

  vector<double> *SpillTag;
  vector<double> *SpillTimeGTrig;
  vector<double> *hitTimefromSpill;
  vector<double> *SpillTrailTime;

};

int main(int argc, char *argv[]){

  TApplication app("app", &argc, argv);

  int date = atoi(argv[1]);
  int run = atoi(argv[2]);
  std::string mon = string(argv[3]);
  

 //General paramter
  //const int start_spill = 65497;
  const int NumberOfFEB=65;
  const int NumberOfModule=18;
  int NumberofEventsMonitor=70000;
  const int NumberOfHorMod=96;
  const int NumberOfHorZMod=18;
  const int NumberOfVerMod=16;
  const int NumberOfTrack=250;
  int NumberOfMod=18;

  //Start of Reading Tree

  ostringstream sDirdate, sDirrun;
  string sFileName;

  sDirdate.str("");
  sDirrun.str("");
  sDirdate << date;
  sDirrun << run;
  // sFileName =  sDirdate.str() + mon + "_" + sDirrun.str() + "_MCR0"  + "_T2K_beamline_trigger_beam60us_neutrinos_ON_all.root";
  sFileName =  sDirdate.str() + mon + "_" + sDirrun.str() + "_ON_MCR0"  + "_T2K_beamline_trigger_beam60us_neutrinos_ON_all.root";

  /*
  TString Directory = 
    "/Users/jinaren/Documents/T2K/BabyMIND/J-PARC_physics_run/data/2018_Mar_May/8Apr_1/";
  TString Filename = "8Apr_1_MCR0_T2K_beamline_trigger_beam60us_neutrinos_ON_all.root";
  TString rootinputFile = (Directory + Filename);
  
  TFile *Fileinput = new TFile(rootinputFile.Data());
  */

  TString Directory = "/Users/jinaren/Documents/T2K/BabyMIND/commissioning_run/event_estimation/macro/Myanalysis/data/2018_Mar_May/" + sDirdate.str() + mon + "_" + sDirrun.str() + "/";
    
  TString Filename = sFileName.c_str();
  //TString rootinputFile = (Directory + Filename);
  TString rootinputFile = "/root/save/analysis2/inputData.root";
  TFile* Fileinput;
  FileStat_t info;
  if (gSystem->GetPathInfo(rootinputFile.Data(), info)!=0) {
    printf("File '%s' does not exist.\n", rootinputFile.Data());
    return 0;
  } else {
    Fileinput = new TFile(rootinputFile);
  }


  vectorstree FEB[NumberOfFEB];

  for(int i_FEB=0; i_FEB<NumberOfFEB; i_FEB++){

    FEB[i_FEB].SpillTag = 0;
    FEB[i_FEB].SpillTimeGTrig = 0;
    FEB[i_FEB].hitTimefromSpill = 0;
    FEB[i_FEB].SpillTrailTime = 0;

    FEB[i_FEB].SpillTime=0;
    FEB[i_FEB].GTrigTag=0;
    FEB[i_FEB].GTrigTime=0;
    FEB[i_FEB].hitsChannel=0;
    FEB[i_FEB].hitAmpl=0;
    FEB[i_FEB].hitLeadTime=0;
    FEB[i_FEB].hitTrailTime=0;
    FEB[i_FEB].hitTimeDif=0;
    //FEB[i_FEB].TimeCoins=0;
  }

  TTree* FEBtree[NumberOfFEB];

  ostringstream sFEBnum;
  string sFEB;
  for(int ih=0; ih<NumberOfFEB; ih++){
    sFEBnum.str("");
    sFEBnum << ih;
    sFEB = "FEB_" + sFEBnum.str();
    FEBtree[ih] = (TTree*)Fileinput->Get(sFEB.c_str());
    
    if((TTree*)Fileinput->Get(sFEB.c_str())){
      cout << sFEB << " ";

      FEBtree[ih]->SetBranchAddress((sFEB+ "_SpillTag").c_str(), &FEB[ih].SpillTag);
      FEBtree[ih]->SetBranchAddress((sFEB+ "_SpillTimeGTrig").c_str(), &FEB[ih].SpillTimeGTrig);
      FEBtree[ih]->SetBranchAddress((sFEB+ "_hitTimefromSpill").c_str(), &FEB[ih].hitTimefromSpill);
      FEBtree[ih]->SetBranchAddress((sFEB+ "_SpillTrailTime").c_str(), &FEB[ih].SpillTrailTime);
      
      FEBtree[ih]->SetBranchAddress((sFEB+ "_SpillTime").c_str(), &FEB[ih].SpillTime);
      FEBtree[ih]->SetBranchAddress((sFEB+ "_GTrigTag").c_str(), &FEB[ih].GTrigTag);
      FEBtree[ih]->SetBranchAddress((sFEB+ "_GTrigTime").c_str(), &FEB[ih].GTrigTime);
      FEBtree[ih]->SetBranchAddress((sFEB+ "_hitsChannel").c_str(), &FEB[ih].hitsChannel);
      FEBtree[ih]->SetBranchAddress((sFEB+ "_hitAmpl").c_str(), &FEB[ih].hitAmpl);
      FEBtree[ih]->SetBranchAddress((sFEB+ "_hitLeadTime").c_str(), &FEB[ih].hitLeadTime);
      FEBtree[ih]->SetBranchAddress((sFEB+ "_hitTrailTime").c_str(), &FEB[ih].hitTrailTime);
      FEBtree[ih]->SetBranchAddress((sFEB+ "_hitTimeDif").c_str(), &FEB[ih].hitTimeDif);

      FEBtree[ih]->GetEntry(0);
      cout << "Number of Events = " << FEB[ih].GTrigTag->size() << '\n';
    }
  }

  Fileinput->Close();

  //End of Reading Tree File

  //Start of Reading Text File

  ifstream fmap("B2-connection.map");
  int MapCon[5][19];
  int temp = 1;

  while(!fmap.eof()){
    fmap >> MapCon[0][temp] >> MapCon[1][temp] >> MapCon[2][temp] 
	 >> MapCon[3][temp] >> MapCon[4][temp];
    temp++;
  }
  fmap.close();
  cout << "read fmap" << '\n';

  ifstream horizontalgeometry("v1_horizontal_from_center.txt");
  double geomHor[5][95];
  temp=0;

  while(!horizontalgeometry.eof()){
    horizontalgeometry >> geomHor[0][temp] >> geomHor[1][temp] >> geomHor[2][temp]
		       >> geomHor[3][temp] >> geomHor[4][temp];
    temp++;
  }
  horizontalgeometry.close();
  cout << "read horizontal geometry" << '\n';

  ifstream verticalgeometry("v1_vertical_from_center.txt");
  double geomVer[5][32];
  temp=0;

  while(!verticalgeometry.eof()){
    verticalgeometry >> geomVer[0][temp] >> geomVer[1][temp] >> geomVer[2][temp]
		     >> geomVer[3][temp] >> geomVer[4][temp];
    temp++;
  }
  verticalgeometry.close();

  cout << "read vertical geometry" << '\n';
  
  ifstream ScinModPos("Scin_Mod_position.txt");
  double ModPos[4][19];
  temp=1;

  while(!ScinModPos.eof()){
    ScinModPos >> ModPos[0][temp] >> ModPos[1][temp] >> ModPos[2][temp] 
	       >> ModPos[3][temp];
    //cout << ModPos[3][temp] << '\n';
    temp++;
  }
  ScinModPos.close();
  
  cout << "read Scintillator Module Position" << '\n';

  //End Of Reading Text File

  //Making Histgram

  TH2F *EventsMap_sview = new TH2F("events_map_side_view","All_events_map_side_view",
				   118, -201, 4520, 95, -986.2, 986.2);
  TH2F *EventsMap_fview = new TH2F("events_map_front_view","All_events_map_front_view",  
				   18, -1315.2, 1315.2, 95, -986.2, 986.2);

  TH2F *reconstruction[NumberofEventsMonitor];
  ostringstream sEventnum;
  string sEvent;

  for(int i_hist=0; i_hist<NumberofEventsMonitor; i_hist++){
    sEventnum.str("");
    sEventnum << i_hist;
    sEvent = "Event(side view)_" + sEventnum.str();
    reconstruction[i_hist] = new TH2F(sEvent.c_str(), sEvent.c_str(), 
				   118, -20, 4520, 95, -986.2, 986.2); 
  }

  TH2F *reconstruction2[NumberofEventsMonitor];
  ostringstream sEventnum2;
  string sEvent2;

  for(int i_hist2=0; i_hist2<NumberofEventsMonitor; i_hist2++){
    sEventnum2.str("");
    sEventnum2 << i_hist2;
    sEvent2 = "Event(top view)_" + sEventnum2.str();
    reconstruction2[i_hist2] = new TH2F(sEvent2.c_str(), sEvent2.c_str(), 
				   118, -20, 4520, 18, -1315.2, 1315.2); 
  }

  //outputFile

  TString Directory_out = 
    "/Users/jinaren/Documents/T2K/BabyMIND/commissioning_run/event_estimation/macro/Myanalysis/Event/";
  TString Filename_out = "Event_" + sDirdate.str() + "_" + mon + "_" + sDirrun.str() + ".root";
  //TString rootoutputFile = (Directory_out + Filename_out);
  TString rootoutputFile = "/root/save/analysis2/outputData.root";

  TFile *Fileoutput = new TFile(rootoutputFile.Data(), "recreate");


  TDirectory *eventDisplay_s = Fileoutput->mkdir("eventDispSideView");
  TDirectory *eventDisplay_t = Fileoutput->mkdir("eventDispTopView");
  

  //GTrigTag

  Int_t numberevents = 0;
  vector <double> GTrigTagCoins;
  GTrigTagCoins.clear();

  Int_t verticcheck = 1;


  for (Int_t i =0; i < (FEB[MapCon[3][verticcheck]].GTrigTag->size() - 5)
	 ; i++){

    if (FEB[MapCon[3][verticcheck]].GTrigTag->at(i) == 
	FEB[MapCon[3][verticcheck]].GTrigTag->at(i+4)) {
      GTrigTagCoins.push_back(FEB[MapCon[3][verticcheck]].GTrigTag->at(i));
      numberevents++;
    }
  }

  cout << numberevents<<" "<< GTrigTagCoins.size()<<" "<<GTrigTagCoins[0]<<"\
 "<<GTrigTagCoins.back()<<endl;
  auto last = std::unique(GTrigTagCoins.begin(),GTrigTagCoins.end());
  GTrigTagCoins.erase(last, GTrigTagCoins.end());
  cout << numberevents<<" "<< GTrigTagCoins.size()<<" "<<GTrigTagCoins[0]<<"\
 "<<GTrigTagCoins.back()<<endl;

  //NumberofEventsMonitor = min (NumberofEventsMonitor,GTrigTagCoins.size());
  NumberofEventsMonitor = GTrigTagCoins.size();
  // NumberofEventsMonitor = 3000;
  //eventtree

  eventvectorsTree EventVec;

  EventVec.Spill = 0;
  EventVec.GTrigTime = 0;
  EventVec.PosX = 0;
  EventVec.PosY = 0;
  EventVec.PosZ = 0;
  //EventVec.RSignalTime = 0;
  //EventVec.LSignalTime = 0;
  //EventVec.TSignalTime = 0;
  EventVec.RSignalAmpl = 0;
  EventVec.LSignalAmpl = 0;
  EventVec.TSignalAmpl = 0;
  EventVec.RSignalLeadTime = 0;
  EventVec.LSignalLeadTime = 0;
  EventVec.TSignalLeadTime = 0;
  EventVec.EventNum = 0;
  EventVec.LastModule = 0;
  EventVec.hitnum = 0;
  EventVec.hitmodulenum = 0;
  EventVec.FirstModule = 0;
  EventVec.ModuleNumber = 0;
  EventVec.ChannelNumber = 0;
  EventVec.hitTimeDif = 0;

  EventVec.hitTimefromSpill = 0;
  EventVec.SpillTag = 0;
  EventVec.SpillTrailTime = 0;
  EventVec.SpillTimeGTrig = 0;
  
  //Fill datas

  Int_t leftindex[2]={0,0};
  Int_t rightindex[2]={0,0};
  Int_t l2_index = 0;
  Int_t r2_index = 0;
  Int_t t2_index = 0;
  Int_t topindex[2]={0,0};
  Int_t eventNumber=0;
  Int_t trackcount=0;
  Double_t MergeYPos = 0;
  Double_t MergeXPos = 0;
  Double_t MergeYAmpl = 0;
  Double_t MergeXAmpl = 0;
  

  TTree* events;
  events = new TTree("events", "a tree of hits");

  events->Branch("_Spill", &EventVec.Spill);
  events->Branch("_GTrigTime", &EventVec.GTrigTime);
  events->Branch("_PosX", &EventVec.PosX);
  events->Branch("_PosY", &EventVec.PosY);
  events->Branch("_PosZ", &EventVec.PosZ);
  //events->Branch("_RSignalTime", &EventVec.RSignalTime);
  //events->Branch("_LSignalTime", &EventVec.LSignalTime);
  //events->Branch("_TSiganlTime", &EventVec.TSignalTime);
  events->Branch("_RSignalAmpl", &EventVec.RSignalAmpl);
  events->Branch("_LSignalAmpl", &EventVec.LSignalAmpl);
  events->Branch("_TSignalAmpl", &EventVec.TSignalAmpl);
  events->Branch("_RSignalLeadTime", &EventVec.RSignalLeadTime);
  events->Branch("_LSignalLeadTime", &EventVec.LSignalLeadTime);
  events->Branch("_TSignalLeadTime", &EventVec.TSignalLeadTime);
  events->Branch("_hitTimeDif", &EventVec.hitTimeDif);
  events->Branch("_EventNum", &EventVec.EventNum);
  events->Branch("_LastModule", &EventVec.LastModule);
  events->Branch("_Hitnum", &EventVec.hitnum);
  events->Branch("_HitModulenum", &EventVec.hitmodulenum);
  events->Branch("_FirstModule", &EventVec.FirstModule);
  events->Branch("_ModuleNumber", &EventVec.ModuleNumber);
  events->Branch("_ChannelNumber", &EventVec.ChannelNumber);

  events->Branch("_hitTimefromSpill", &EventVec.hitTimefromSpill);
  events->Branch("_SpillTag", &EventVec.SpillTag);
  events->Branch("_SpillTrailTime", &EventVec.SpillTrailTime);
  events->Branch("_SpillTimeGTrig", &EventVec.SpillTimeGTrig);

  EventVec.Spill->clear();
  EventVec.GTrigTime->clear();
  EventVec.PosX->clear();
  EventVec.PosY->clear();
  EventVec.PosZ->clear();
  //EventVec.RSignalTime->clear();
  //EventVec.LSignalTime->clear();
  //EventVec.TSignalTime->clear();
  EventVec.RSignalAmpl->clear();
  EventVec.LSignalAmpl->clear();
  EventVec.TSignalAmpl->clear();
  EventVec.RSignalLeadTime->clear();
  EventVec.LSignalLeadTime->clear();
  EventVec.TSignalLeadTime->clear();
  EventVec.hitTimeDif->clear();
  EventVec.EventNum->clear();
  EventVec.LastModule->clear();
  EventVec.hitnum->clear();
  EventVec.hitmodulenum->clear();
  EventVec.FirstModule->clear();
  EventVec.ModuleNumber->clear();
  EventVec.ChannelNumber->clear();
  
  EventVec.hitTimefromSpill->clear();
  EventVec.SpillTag->clear();
  EventVec.SpillTrailTime->clear();
  EventVec.SpillTimeGTrig->clear();
  
 
  //merge parameter

  vector <int> mergeH_l;
  vector <int> mergeH_r;
  vector <int> mergeV;
  mergeH_l.clear();
  mergeH_r.clear();
  mergeV.clear();

  for (Int_t index=0; index <= NumberofEventsMonitor; index++) {

    Int_t hitnum=0;
    Int_t LastModule=1;
    bool first = true;
    vector <int> hitmodulenum;
    hitmodulenum.clear();
   
    for (Int_t mod = 1; mod<=NumberOfMod;mod++){

      auto boundsleft=std::equal_range (FEB[MapCon[1][mod]].GTrigTag->begin(), 
					FEB[MapCon[1][mod]].GTrigTag->end(), 
					GTrigTagCoins[index]);
      leftindex[0] = boundsleft.first - FEB[MapCon[1][mod]].GTrigTag->begin();
      leftindex[1] = boundsleft.second - FEB[MapCon[1][mod]].GTrigTag->begin();

      auto boundsright=std::equal_range (FEB[MapCon[2][mod]].GTrigTag->begin(), 
					 FEB[MapCon[2][mod]].GTrigTag->end(), 
					 GTrigTagCoins[index]);
      rightindex[0] = boundsright.first - FEB[MapCon[2][mod]].GTrigTag->begin();
      rightindex[1] = boundsright.second - FEB[MapCon[2][mod]].GTrigTag->begin();

      auto boundstop = std::equal_range (FEB[MapCon[3][mod]].GTrigTag->begin(), 
					 FEB[MapCon[3][mod]].GTrigTag->end(), 
					 GTrigTagCoins[index]);
      topindex[0] = boundstop.first - FEB[MapCon[3][mod]].GTrigTag->begin();
      topindex[1] = boundstop.second - FEB[MapCon[3][mod]].GTrigTag->begin();


      
      //coincidence left, right, top
      if (leftindex[0]>0 && rightindex[0]>0 && topindex[0]>0){
	for (Int_t CoinsLeft = leftindex[0]; CoinsLeft < leftindex[1]; CoinsLeft++){  
	  l2_index = 0;
	  //r2_index = 0;
	
	  for (Int_t CoinsRight = rightindex[0]; CoinsRight < rightindex[1]; CoinsRight++){
	    mergeH_r.clear();
	    mergeH_l.clear();
	
	    r2_index = 0;
	    //channel coincidence right and left 
	    if (FEB[MapCon[1][mod]].hitsChannel->at(CoinsLeft) == 
		FEB[MapCon[2][mod]].hitsChannel->at(CoinsRight)){
	      //time coincidence right and left
	      if(abs(FEB[MapCon[1][mod]].hitLeadTime->at(CoinsLeft) -
		     FEB[MapCon[2][mod]].hitLeadTime->at(CoinsRight))<3){
	       
		mergeH_l.push_back(CoinsLeft);
		mergeH_r.push_back(CoinsRight);

	  

		//search for datas for merginalization
		for(Int_t CoinsLeft2 = CoinsLeft+1; CoinsLeft2 < leftindex[1]; CoinsLeft2++){
		  for(Int_t CoinsRight2 = CoinsRight+1; CoinsRight2 < rightindex[1]; CoinsRight2++){
		  
		    if(abs(FEB[MapCon[2][mod]].hitLeadTime->at(mergeH_r.at(0)) -
			   FEB[MapCon[2][mod]].hitLeadTime->at(CoinsRight2))<3 && 
		       FEB[MapCon[1][mod]].hitsChannel->at(CoinsLeft2) == 
		       FEB[MapCon[2][mod]].hitsChannel->at(CoinsRight2) &&
		       abs(FEB[MapCon[2][mod]].hitsChannel->at(CoinsRight) - 
			   FEB[MapCon[2][mod]].hitsChannel->at(CoinsRight2)) < 1
		       ){
		      
		      l2_index = CoinsLeft2;
		      r2_index = CoinsRight2;
		      
		      mergeH_l.push_back(CoinsLeft2);
		      mergeH_r.push_back(CoinsRight2);
		      
		      
		      CoinsRight = r2_index;
		      
		    }
		  }
		}

		if(mergeH_r.size() > 1){
		  cout << mergeH_r.size() << '\n';
		  for(Int_t m = 0; m < mergeH_r.size(); m++){
		    if(m==0){
		      cout << "!!!!! Merge Horizontal Module !!!!!" << '\n';
		      cout << "event = " << index << " module = " << mod << '\n';
		      cout << "merge ch" << FEB[MapCon[2][mod]].hitsChannel->at(mergeH_r.at(m)) 
			   << '\n';
		    }
		    if(m>0){
		      cout << "and ch" << FEB[MapCon[2][mod]].hitsChannel->at(mergeH_r.at(m)) 
			   << '\n';
		    }
		    
		    //Merge Position
		    MergeYPos 
		      += geomHor[4][(int)FEB[MapCon[2][mod]].hitsChannel->at(mergeH_r.at(m))];
		    MergeYAmpl
		      += FEB[MapCon[2][mod]].hitAmpl->at(mergeH_r.at(m));
		  }
		  MergeYPos = MergeYPos/mergeH_r.size();
		  //cout << MergeYPos << '\n';
		}
		
		if(mergeH_r.size()==1){
		      MergeYPos
			= geomHor[4][(int)FEB[MapCon[2][mod]].hitsChannel->at(mergeH_r.at(0))];
		      MergeYAmpl
			= FEB[MapCon[2][mod]].hitAmpl->at(mergeH_r.at(0));
		    }
	       
	

		for(Int_t CoinsTop=topindex[0]; CoinsTop < topindex[1]; CoinsTop++){
		  mergeV.clear();
		  t2_index = 0;
		  
		  if (FEB[MapCon[3][mod]].hitsChannel->at(CoinsTop)>=32*MapCon[4][mod] && 
		      FEB[MapCon[3][mod]].hitsChannel->at(CoinsTop)<32*(1+MapCon[4][mod]) &&
		      abs(FEB[MapCon[2][mod]].hitLeadTime->at(mergeH_r.at(0)) 
			  - FEB[MapCon[3][mod]].hitLeadTime->at(CoinsTop)) < 3){
		    mergeV.push_back(CoinsTop);


		    //search for datas for merginalization
		    for(Int_t CoinsTop2=CoinsTop+1; CoinsTop2 < topindex[1]; CoinsTop2++){
		      if (FEB[MapCon[3][mod]].hitsChannel->at(CoinsTop2)>=32*MapCon[4][mod] &&  
			  FEB[MapCon[3][mod]].hitsChannel->at(CoinsTop2)<32*(1+MapCon[4][mod])){ 
			if (abs(FEB[MapCon[3][mod]].hitsChannel->at(CoinsTop)   
				- FEB[MapCon[3][mod]].hitsChannel->at(CoinsTop2))==1 && 
			    abs(FEB[MapCon[2][mod]].hitLeadTime->at(mergeH_r.at(0)) 
				- FEB[MapCon[3][mod]].hitLeadTime->at(CoinsTop2)) < 3){
			  
			  t2_index = CoinsTop2;
			  mergeV.push_back(CoinsTop2);
			
			  CoinsTop = t2_index;
			}
		      }
		    }

		    if(mergeV.size()>1){
		      cout << mergeV.size() << '\n';
		      for(Int_t m = 0; m < mergeV.size(); m++){
			if(m==0){
			  cout << "!!!!! Merge Vertical Module !!!!!" << '\n';
			  cout << "event = " << index << " module = " << mod << '\n';
			  cout << "merge ch" << FEB[MapCon[3][mod]].hitsChannel->at(mergeV.at(m)) 
			       << '\n';
			}
			if(m>0){
			  cout << "and ch" << FEB[MapCon[3][mod]].hitsChannel->at(mergeV.at(m)) 
			       << '\n';
			}
			
			//Merge Position
			MergeXPos 
			  += geomVer[4][(int)FEB[MapCon[3][mod]].hitsChannel->at(mergeV.at(m))%32];
			MergeXAmpl
		      += FEB[MapCon[3][mod]].hitAmpl->at(mergeV.at(m));
		      }
		      MergeXPos = MergeXPos/mergeV.size();
		    }

		    if(mergeV.size()==1){
		      MergeXPos
			= geomVer[4][(int)FEB[MapCon[3][mod]].hitsChannel->at(mergeV.at(0))%32];
		      MergeXAmpl
			= FEB[MapCon[3][mod]].hitAmpl->at(mergeV.at(0));
		    }
     

		    if(mergeV.size()>=1){
		   
		//eventnumber limit

		      EventsMap_sview->Fill(ModPos[3][mod],MergeYPos,1);
		      //EventsMap_sview->Fill(ModPos[3][mod],geomHor[4][(int)FEB[MapCon[2][mod]].hitsChannel
		      //->at(mergeH_r.at(0))],1);

		      
		      if(mod==2||mod==11||mod==13||mod==17||mod==18){
			EventsMap_fview->Fill(-MergeXPos,MergeYPos,1);
		      }
		      else{
			EventsMap_fview->Fill(MergeXPos,MergeYPos,1);
		      }
		      //EventsMap_tview->Fill(ModPos[3][mod],geomVer[4][(int)FEB[MapCon[2][mod]].hitsChannel
		      //->at(mergeH_r.at(0))],1);
		     


		      if (eventNumber<NumberofEventsMonitor){

			if(first){
				EventVec.FirstModule->push_back(mod);
				first = false;
			}

			EventVec.ModuleNumber->push_back(mod);

			reconstruction[eventNumber]
			  ->Fill(ModPos[3][mod], MergeYPos,1);
	
			reconstruction2[eventNumber]
			  ->Fill(ModPos[3][mod], MergeXPos,1);		   
			if(mod==2||mod==11||mod==13||mod==17||mod==18){
			  reconstruction2[eventNumber]
			    ->Fill(ModPos[3][mod], -MergeXPos,1);
		      }
		       
		    
			
		    //Filling to tree
			

			/*
			EventVec.hitTimeDif->push_back(FEB[MapCon[2][mod]].hitTimeDif->at(0));
			EventVec.Spill->push_back(FEB[MapCon[2][mod]].SpillTime->at(0));
			EventVec.SpillTag->push_back(FEB[MapCon[2][mod]].SpillTag->at(0));
			EventVec.SpillTrailTime->push_back(FEB[MapCon[2][mod]].SpillTrailTime->at(0));
			EventVec.hitTimefromSpill->push_back(FEB[MapCon[2][mod]].hitTimefromSpill
							     ->at(0));
			EventVec.SpillTimeGTrig->push_back(FEB[MapCon[2][mod]].SpillTimeGTrig
						      ->at(mergeH_r.at(0)));
			*/
		    
		    if(mod==2||mod==11||mod==13||mod==17||mod==18){
		      EventVec.PosX->push_back(-MergeXPos);
		    }
		    else{
		      EventVec.PosX->push_back(MergeXPos);
		    }

		    EventVec.PosY->push_back(MergeYPos);
		    EventVec.PosZ->push_back(ModPos[3][mod]);

		    EventVec.RSignalLeadTime->push_back(FEB[MapCon[2][mod]].hitLeadTime->at(mergeH_r.at(0)));
		    EventVec.LSignalLeadTime->push_back(FEB[MapCon[1][mod]].hitLeadTime->at(mergeH_l.at(0)));
		    EventVec.TSignalLeadTime->push_back(FEB[MapCon[3][mod]].hitLeadTime->at(mergeV.at(0)));

		    EventVec.RSignalAmpl->push_back(MergeYAmpl);
		    //EventVec.RSignalAmpl->push_back(FEB[MapCon[2][mod]].hitAmpl->at(mergeH_r.at(0)));
		    EventVec.LSignalAmpl->push_back(FEB[MapCon[1][mod]].hitAmpl->at(mergeH_l.at(0)));
		    //EventVec.TSignalAmpl->push_back(FEB[MapCon[3][mod]].hitAmpl->at(mergeV.at(0)));
		    EventVec.TSignalAmpl->push_back(MergeXAmpl);

		    //SpillTime info
		    
		    EventVec.hitTimeDif->push_back(FEB[MapCon[1][mod]].hitTimeDif->at(mergeH_l.at(0)));
		    
		    //EventVec.Spill->push_back(FEB[49].SpillTime->at(0));
		    //EventVec.SpillTag->push_back(FEB[MapCon[1][mod]].SpillTag->at(mergeH_l.at(0)));
		    int temp = int(FEB[MapCon[1][mod]].SpillTag->at(mergeH_l.at(0))) & 0x7FFF;
		    EventVec.SpillTag->push_back(temp);
		    //EventVec.SpillTrailTime->push_back(FEB[49].SpillTrailTime->at(0));
		    EventVec.hitTimefromSpill->push_back(FEB[MapCon[1][mod]].hitTimefromSpill
							 ->at(mergeH_l.at(0)));
		    EventVec.SpillTimeGTrig->push_back(FEB[MapCon[1][mod]].SpillTimeGTrig->at(mergeH_l.at(0)));
		      

		    EventVec.EventNum->push_back(index);
		 
		    hitnum++;
		    LastModule = mod;
	
		    hitmodulenum.push_back(mod);
		    
		      	  	
		      }//eventNumber<NumberofEventsMonitor
		    
		      }//if mergeV
		      
		    
		} //Top Condition
		} //Top loop
		MergeXPos=0;
		MergeYPos=0;
		MergeXAmpl=0;
		MergeYAmpl=0;

		//FEB ampl threshold

	      } //hitsChannel coincidence
	    }//hitsChannel conincidence


	    /* 
	    if(mergeH_r.size()>1 && mergeH_l.size()>1){
	    CoinsRight = r2_index;
	    CoinsLeft = l2_index;
	    }
	    */
	   
	  
	  } //CoinsRight for

	} //CoinsLeft for
      } //leftindex[0]>0 && rightindex[0]>0
      
    } //mod for
    eventNumber++;
    EventVec.hitnum->push_back(hitnum);
    EventVec.LastModule->push_back(LastModule);

    auto last = std::unique(hitmodulenum.begin(), hitmodulenum.end());
    hitmodulenum.erase(last, hitmodulenum.end());
    EventVec.hitmodulenum->push_back(hitmodulenum.size());  

    /*
    for(int i=1; i<3; i++){
      for(int j=0; j<18; j++){
	EventVec.hitTimeDif->push_back(FEB[MapCon[i][j]].hitTimeDif->at(index));
	//EventVec.Spill->push_back(FEB[49].SpillTime->at(0));
	EventVec.SpillTag->push_back(FEB[49].SpillTag->at(0));
	//EventVec.SpillTrailTime->push_back(FEB[49].SpillTrailTime->at(0));
	EventVec.hitTimefromSpill->push_back(FEB[MapCon[i][j]].hitTimefromSpill
					     ->at(index));
	EventVec.SpillTimeGTrig->push_back(FEB[49].SpillTimeGTrig->at(mergeH_r.at(0)));
      }
    }
    */
  } //index for

  events->Fill();
  events->Write();

  cout << eventNumber << '\n';

  //reconstruction[0]->Draw();

  EventsMap_sview->GetYaxis()->SetTitle("Y [mm]");
  EventsMap_sview->GetXaxis()->SetTitle("Z [mm]");
  EventsMap_sview->Write();

  EventsMap_fview->GetYaxis()->SetTitle("X [mm]");
  EventsMap_fview->GetXaxis()->SetTitle("Y [mm]");
  EventsMap_fview->Write();

  eventDisplay_s->cd();
  for (Int_t ih=0; ih < NumberofEventsMonitor;ih++){
    if (reconstruction[ih]->GetEntries()>1) {
      reconstruction[ih]->GetYaxis()->SetTitle("Y [mm]");
      reconstruction[ih]->GetXaxis()->SetTitle("Z [mm]");
      reconstruction[ih]->Write();
    }
  }

  eventDisplay_t->cd();
  for (Int_t ih=0; ih < NumberofEventsMonitor;ih++){
    if (reconstruction2[ih]->GetEntries()>1) {
      reconstruction2[ih]->GetYaxis()->SetTitle("X [mm]");
      reconstruction2[ih]->GetXaxis()->SetTitle("Z [mm]");
      reconstruction2[ih]->Write();
    }
  }

  for (Int_t i=0;i<NumberOfFEB;i++){
    //FEBtree[i]->Delete();                                                                                            
    //FEB[i].FEBSN=0;
    FEB[i].hitsChannel=0;
    FEB[i].hitAmpl=0;
    FEB[i].hitLeadTime=0;
    FEB[i].hitTrailTime=0;
    FEB[i].GTrigTag=0;
    FEB[i].GTrigTime=0;
    //FEB[i].hitLGAmpl=0;
    FEB[i].SpillTime=0;
    FEB[i].hitTimeDif=0;
    FEB[i].SpillTag=0;
    FEB[i].SpillTimeGTrig=0;
    FEB[i].hitTimefromSpill=0;
    FEB[i].SpillTrailTime=0;
    

  }

  EventVec.Spill = 0;
  EventVec.GTrigTime = 0;
  EventVec.PosX = 0;
  EventVec.PosY = 0;
  EventVec.PosZ = 0;
  //EventVec.RSignalTime = 0;
  //EventVec.LSignalTime = 0;
  //EventVec.TSignalTime = 0;
  EventVec.RSignalAmpl = 0;
  EventVec.LSignalAmpl = 0;
  EventVec.TSignalAmpl = 0;
  EventVec.RSignalLeadTime = 0;
  EventVec.LSignalLeadTime = 0;
  EventVec.TSignalLeadTime = 0;
  EventVec.EventNum = 0;
  EventVec.LastModule = 0;
  EventVec.hitmodulenum = 0;
  EventVec.FirstModule = 0;
  EventVec.ModuleNumber = 0;
  EventVec.ChannelNumber = 0;
  EventVec.hitTimeDif = 0;

  EventVec.hitTimefromSpill = 0;
  EventVec.SpillTag = 0;
  EventVec.SpillTrailTime = 0;
  EventVec.SpillTimeGTrig = 0;


  GTrigTagCoins.clear();
  Fileinput->Close();
  

    
}
