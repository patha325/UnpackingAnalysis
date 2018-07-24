#include <unistd.h>
#include <vector>

#include "BMdisp.h"
#include "Fit.h"
#include "recon.h"
#include "function.h"

#include <TLatex.h>
#include <TGraphErrors.h>
#include <TImage.h>
#include <TStyle.h>
#include <TSystem.h>
#include <TCanvas.h>
#include <algorithm>
#include <TApplication.h>
#include <stdio.h>
#include <string.h>
#include <exception>
#include <fstream>
#include <vector>
#include "TFile.h"
#include "TDirectory.h"
#include "TMacro.h"
#include <TTree.h>
#include <iostream>
#include <sstream>
#include "TH2.h"
#include "TH1.h"
#include "TH3.h"
#include "TF1.h"
#include <iterator>
#include <TCut.h>
#include <TText.h>

using namespace std;
void eventchecker(double NumMod, double positionY,int *checkpoint){

  int cut =8;

  if(NumMod<cut){
    *checkpoint = 0;
  }
  if(NumMod>=cut){
    if(positionY>500){
     *checkpoint = 1;
    }
    if(positionY<500 && positionY>-500){
      *checkpoint = 2;
    }
    if(positionY<-500){
      *checkpoint = 3;
    }

  }
}
    

struct reconvectorstree
{
  vector<double> *Numofgoodevent;
  vector<double> *goodeventnumber;
  vector<double> *degree;
  vector<double> *momentum;
  vector<double> *P_O_T;
  vector<double> *muplus;
  vector<double> *muminus;
  vector<double> *ratio;
  vector<double> *babymind_spill;
};

int main(int argc, char *argv[]){

  TApplication app("app", &argc, argv);

  bool display = false;
  bool analysis = false;
  bool fitting = false;
  bool recon = false;


  if(string(argv[4]) == "d" ){
    display = true;
  }
  if(string(argv[4]) == "a"){
    analysis = true;
  }
  if(string(argv[4]) == "f"){
    fitting = true;
  }
  if(string(argv[4]) == "r"){
    recon = true;
  }

  //  else{
  //exit(0);
  //}

 
  const int NumberOfHor = 95;
  const int NumberOfVer = 16;
  const int NumberOfModule = 18;
  const int entry_limit = 1;
  int numberOfhistgram = 0;

  int track_flag;

  int date = atoi(argv[1]);
  int run = atoi(argv[2]);
  std::string mon = string(argv[3]);

  vector <int> uprange;
  vector <int> middlerange;
  vector <int> downrange;
  vector <double> module;
  vector <double> number;
  vector <double> rmnumber;
  vector <double> goodevent;
  vector <double> P_O_T;
  vector <double> babymind_spill;

  ostringstream sDirdate, sDirrun;
  string sFileName;

    //Branch
  vector <double> *PosX;
  vector <double> *PosY;
  vector <double> *PosZ;
  vector <double> *RSignalAmpl;
  vector <double> *TSignalAmpl;
  vector <double> *RSignalLeadTime;
  vector <double> *TSignalLeadTime;
  vector <double> *EventNum;
  vector <double> *HitModuleNum;
  vector <double> *GTrigTime;
  vector <double> *SpillNumber;
  vector <double> *FirstModule;
  vector <double> *ModuleNumber;
  vector <double> *hitTimefromSpill;
  vector <double> *hitTimeDif;
  vector <double> *SpillTag;

  //TBranch
  TBranch *bPosX;
  TBranch *bPosY;
  TBranch *bPosZ;
  TBranch *bRSignalAmpl;
  TBranch *bTSignalAmpl;
  TBranch *bRSignalLeadTime;
  TBranch *bTSignalLeadTime;  
  TBranch *bEventNum;
  TBranch *bHitModuleNum;
  TBranch *bGTrigTime;
  TBranch *bSpillNumber;
  TBranch *bFirstModule;
  TBranch *bModuleNumber;
  TBranch *bhitTimefromSpill;
  TBranch *bhitTimeDif;
  TBranch *bSpillTag;


  vector <double> Eventnumber;
  

  vector <double> tracktime;
  
  reconvectorstree ReconVec;

  int month;
  if(mon=="mar"){
    month = 3;
  }
  if(mon=="Apr"){
    month = 4;
  }
  if(mon=="May"){
    month = 5;
  }


  ReconVec.Numofgoodevent = 0;
  ReconVec.goodeventnumber = 0;
  ReconVec.degree = 0;
  ReconVec.momentum = 0;
  ReconVec.P_O_T = 0;
  ReconVec.muplus = 0;
  ReconVec.muminus = 0;
  ReconVec.ratio = 0;
  ReconVec.babymind_spill = 0;
  
  TTree* Recontree;
  Recontree = new TTree("recon", " a tree of reconstruction");
    
  Recontree->Branch("_Numofgoodevent", &ReconVec.Numofgoodevent);
  Recontree->Branch("_goodeventnumber", &ReconVec.goodeventnumber);
  Recontree->Branch("_degree", &ReconVec.degree);
  Recontree->Branch("_momentum", &ReconVec.momentum);
  Recontree->Branch("_muplus", &ReconVec.muplus);
  Recontree->Branch("_muminus", &ReconVec.muminus);
  Recontree->Branch("_ratio", &ReconVec.ratio);
  Recontree->Branch("_babymind_spill", &ReconVec.babymind_spill);
  Recontree->Branch("_POT", &ReconVec.P_O_T);

  ReconVec.Numofgoodevent->clear();
  ReconVec.goodeventnumber->clear();
  ReconVec.degree->clear();
  ReconVec.momentum->clear();
  ReconVec.muplus->clear();    
  ReconVec.muminus->clear();    
  ReconVec.ratio->clear();
  ReconVec.P_O_T->clear();    
  ReconVec.babymind_spill->clear();    

  double EVENTRATE[100];
  double erry[100];
  double errx[100];
  double x[100];
  int i_count = 0;

  for(int i=0; i<100; i++){
    x[i] = i;
    errx[i] = 0;
  }

  TH2D *Recon_Track;
  TH1D *bunch_hist = new TH1D("bunch_hist", "bunch_hist",
			      250, 30000, 40000);
  bunch_hist->SetFillColor(2);

  TH1D *coffa = new TH1D("coffa", "coffa",
			      200, -1, 1);
  bunch_hist->SetFillColor(3);

  TString Directory ="/Users/jinaren/Documents/T2K/BabyMIND/commissioning_run/event_estimation/macro/Myanalysis/Spill/";
  TString Filename = "Spill.txt";
  ifstream fin(Directory + Filename);
 
    
  vector <int> spillnumber;
  vector <double> Pot;
  vector <int> Year;
  vector <int> Month;
  vector <int> Date;
  vector <int> Badtimingevent;
  vector <int> Badtiming;
  vector <string> DateLabel;
  
  spillnumber.clear();
  Pot.clear();
  Year.clear();
  Month.clear();
  Date.clear();
  Badtiming.clear();
  Badtimingevent.clear();
  DateLabel.clear();

  while(!fin.eof()){
    double temp1;
    int temp0, temp2, temp3, temp4;
    fin >> temp0 >> temp1 >> temp2 >> temp3 >> temp4;
    spillnumber.push_back(temp0);
    Pot.push_back(temp1);
    Year.push_back(temp2);
    Month.push_back(temp3);
    Date.push_back(temp4);
  }
  
  Int_t index[2] ={0, 0};
  int count = 0;
  int firstcount = 0;
  int Bunch = 0;
  int count_plus = 0;
  int count_minus = 0;
  double ratio;

  // **** Merge Datas **** //

  for(int i_date = 1; i_date <= date; i_date++){
    for(int i_run = 1; i_run <= run; i_run++){
    
        double totalpot = 0;
	double deliveredpot = 0;
	double goodeventpot = 0;
	double eventrate = 0;
	

        //Initialization
      PosX=0;
      PosY=0;
      PosZ=0;
      RSignalAmpl=0;
      TSignalAmpl=0;
      RSignalLeadTime=0;
      TSignalLeadTime=0;
      EventNum=0;
      HitModuleNum=0;
      GTrigTime=0;
      SpillNumber=0;
      FirstModule=0;
      ModuleNumber=0;
      hitTimefromSpill=0;
      hitTimeDif=0;
      SpillTag=0;

      Eventnumber.clear();
      tracktime.clear();

      uprange.clear();
      middlerange.clear();
      downrange.clear();
      module.clear();
      number.clear();
      rmnumber.clear();
      goodevent.clear();
      P_O_T.clear();
      babymind_spill.clear();
      
      index[0] = 0;
      index[1] = 0;
      
      sDirdate.str("");
      sDirrun.str("");
      sDirdate << i_date;
      sDirrun << i_run;
      sFileName =  "Event_" + sDirdate.str() + "_" + mon + "_" + sDirrun.str() + ".root";
      
      TString Directory = "../Event/";
      
      TString inputFile = Directory + sFileName.c_str();
      
      TFile *Fileinput;
      FileStat_t info;
      if (gSystem->GetPathInfo(inputFile.Data(), info)!=0) {
	printf("File '%s' does not exist.\n", inputFile.Data());
	continue;
      } else {
	Fileinput = new TFile(inputFile);
      }

      cout << "File:" << sFileName.c_str() << " Analyzed ..." << '\n';

      /*
      ostringstream sDirdate, sDirrun;
      string sFileName;
      
      sDirdate.str("");
      sDirrun.str("");
      sDirdate << date;
      sDirrun << run;
      */

      TString Filename_out = "Recon_" + sDirdate.str() + "_" + mon + "_" + sDirrun.str() + ".root";

      TTree *t = (TTree*)Fileinput->Get("events");

          t->SetBranchAddress("_PosX", &PosX, &bPosX);
	  t->SetBranchAddress("_PosY", &PosY, &bPosY);
	  t->SetBranchAddress("_PosZ", &PosZ, &bPosZ);
	  t->SetBranchAddress("_RSignalAmpl", &RSignalAmpl,&bRSignalAmpl);
	  t->SetBranchAddress("_TSignalAmpl", &TSignalAmpl,&bTSignalAmpl);
	  t->SetBranchAddress("_RSignalLeadTime", &RSignalLeadTime,&bRSignalLeadTime);
	  t->SetBranchAddress("_TSignalLeadTime", &TSignalLeadTime,&bTSignalLeadTime);
	  t->SetBranchAddress("_EventNum", &EventNum, &bEventNum);  
	  t->SetBranchAddress("_HitModulenum", &HitModuleNum, &bHitModuleNum);  
	  t->SetBranchAddress("_GTrigTime", &GTrigTime, &bGTrigTime);  
	  t->SetBranchAddress("_Spill", &SpillNumber, &bSpillNumber);  
	  t->SetBranchAddress("_FirstModule", &FirstModule, &bFirstModule);  
	  t->SetBranchAddress("_ModuleNumber", &ModuleNumber, &bModuleNumber);  
	  t->SetBranchAddress("_SpillTag", &SpillTag, &bSpillTag);  
	  t->SetBranchAddress("_hitTimefromSpill", &hitTimefromSpill, &bhitTimefromSpill);  
	  t->SetBranchAddress("_hitTimeDif", &hitTimeDif, &bhitTimeDif);  
  
  const int NumberOfEvent = t->GetEntries();

  for(int i_entry=0; i_entry<NumberOfEvent; i_entry++){

    t->GetEntry(i_entry);
    Long64_t tentry = t->LoadTree(i_entry);

    //Filling vector
    bPosX->GetEntry(tentry);
    bPosY->GetEntry(tentry);
    bPosZ->GetEntry(tentry);
    bRSignalAmpl->GetEntry(tentry);
    bTSignalAmpl->GetEntry(tentry);
    bRSignalLeadTime->GetEntry(tentry);
    bTSignalLeadTime->GetEntry(tentry);
    bEventNum->GetEntry(tentry);
    bHitModuleNum->GetEntry(tentry);
    bGTrigTime->GetEntry(tentry);
    bSpillNumber->GetEntry(tentry);
    bFirstModule->GetEntry(tentry);
    bModuleNumber->GetEntry(tentry);
    bSpillTag->GetEntry(tentry);
    bhitTimefromSpill->GetEntry(tentry);
    bhitTimeDif->GetEntry(tentry);
    
  } //i_entry

  
  const int numberOfeventdata = PosX->size(); 

  for(Int_t i=0; i<numberOfeventdata; i++){
    Eventnumber.push_back(EventNum->at(i));
  }


  auto last = std::unique(Eventnumber.begin(), Eventnumber.end());
  Eventnumber.erase(last, Eventnumber.end());

  
  int checkpoint;
  double basetime = 0;

  numberOfhistgram = Eventnumber.size();
  //numberOfhistgram = 400;    

   //Coincidence check

  for(int i=2; i<=4; i++){
    number.push_back(i);
    }

  
    for(int i_rm=1; i_rm<=1; i_rm++){
    rmnumber.push_back(i_rm);
    }
  
    /*
    for(int i_rm=8; i_rm<=18; i_rm++){
    rmnumber.push_back(i_rm);
    }
    */


    
  for(int i_event=0; i_event<numberOfhistgram; i_event++){
    checkpoint = 0;
    tracktime.clear();
    module.clear();
    //for(int i_event=0; i_event<3; i_event++){
    //cout << i_event << '\n';

    const int numberOftrack = 10;
    ostringstream shistnum;
    string shist;  
      shistnum.str("");
      shistnum << Eventnumber.at(i_event);     
      shist = "All tracks Event_" + shistnum.str();
       

      Recon_Track = new TH2D(shist.c_str(), shist.c_str(),
			     50, -60, 4540, 95, -986.2, 986.2);

      Recon_Track->SetStats(0);
      Recon_Track->SetTitle(shist.c_str());
      Recon_Track->SetTitleSize(0.07);
      Recon_Track->SetMarkerStyle(1);
      Recon_Track->SetMarkerSize(2);
      Recon_Track->SetXTitle("Z [mm]");
      Recon_Track->SetYTitle("Y [mm]");
      Recon_Track->GetXaxis()->SetTitleSize(0.05);
      Recon_Track->GetXaxis()->SetLabelSize(0.05);
      Recon_Track->GetYaxis()->SetTitleSize(0.05);
      Recon_Track->GetYaxis()->SetLabelSize(0.05);
      Recon_Track->GetZaxis()->SetLabelSize(0.03);

    //histgram

    /*
    TH2D *Recon_Track[100000][10];
    const int numberOftrack = 10;
    ostringstream shistnum;
    string shist;  
    for(int i_track=0; i_track<numberOftrack; i_track++){
      shistnum.str("");
      shistnum << Eventnumber.at(i_event);
      if(i_track==0){
	  shist = "All tracks Event_" + shistnum.str();
	}
      if(i_track==1){
	  shist = "1st Track Event_" + shistnum.str();
	}
      if(i_track==2){
	shist = "2nd Track Event_" + shistnum.str();
      }
      if(i_track==3){
	shist = "3rd Track Event_" + shistnum.str();
      }
      if(i_track==4){
	shist = "4th Track Event_" + shistnum.str();
      }
      if(i_track==5){
	shist = "5th Track Event_" + shistnum.str();
      }
      if(i_track==6){
	shist = "6th Track Event_" + shistnum.str();
      }
      if(i_track==7){
	shist = "7th Track Event_" + shistnum.str();
      }
      if(i_track==8){
	shist = "8th Track Event_" + shistnum.str();
      }
      if(i_track==9){
	shist = "9th Track Event_" + shistnum.str();
      }
      if(i_track==10){
	shist = "10th Track Event_" + shistnum.str();
      }

      Recon_Track[i_event][i_track] = new TH2D(shist.c_str(), shist.c_str(),
				      50, -60, 4540, 95, -986.2, 986.2);

      Recon_Track[i_event][i_track]->SetStats(0);
      Recon_Track[i_event][i_track]->SetTitle(shist.c_str());
      Recon_Track[i_event][i_track]->SetTitleSize(0.07);
      Recon_Track[i_event][i_track]->SetMarkerStyle(1);
      Recon_Track[i_event][i_track]->SetMarkerSize(2);
      Recon_Track[i_event][i_track]->SetXTitle("Z [mm]");
      Recon_Track[i_event][i_track]->SetYTitle("Y [mm]");
      Recon_Track[i_event][i_track]->GetXaxis()->SetTitleSize(0.05);
      Recon_Track[i_event][i_track]->GetXaxis()->SetLabelSize(0.05);
      Recon_Track[i_event][i_track]->GetYaxis()->SetTitleSize(0.05);
      Recon_Track[i_event][i_track]->GetYaxis()->SetLabelSize(0.05);
      Recon_Track[i_event][i_track]->GetZaxis()->SetLabelSize(0.03);

    }//i_track loop
    */


    
    auto bounds = std::equal_range(EventNum->begin(), EventNum->end(), Eventnumber.at(i_event));
    index[0] = bounds.first - EventNum->begin();
    index[1] = bounds.second - EventNum->begin();
    
    //checked missed spills
    if(i_date == 5 && SpillTag->at(index[0])==22575)
      {
	continue;
      }
      

    //add pot infomation

    //numberOfhistgram = 1;
    
    //for(int i=0; i<numberOfhistgram; i++){
    
    if(i_event==0){
     
    while(!(SpillTag->at(index[0])==spillnumber.at(count) && Year.at(count)==2018 
            && i_date == Date.at(count) && month==Month.at(count))){
      //cout << count << '\n';
      firstcount = count;
      count++;
    }
    }
    
    else{ 
      while(!(SpillTag->at(index[0])==spillnumber.at(count) && Year.at(count)==2018 
            && month==Month.at(count))){
	/*
	if(i_run==2){
	  cout << Date.size() << " " << SpillTag->size() << " " <<  count  
	  << " " << index[0] << " " <<  i_event << " " << SpillTag->at(index[0])  << '\n';
	}
	*/
	count++;
	
      }
    }


      //cout << Date.size() << " " << Month.size() << " " << SpillTag->size() << " " << Year.size() << " " <<  count  << " " << index[0] << " " <<  i_event << " " << SpillTag->at(index[0])  << '\n';
      
      ReconVec.babymind_spill->push_back(spillnumber.at(count));
      ReconVec.P_O_T->push_back(Pot.at(count));
      totalpot += Pot.at(count) * pow(10, 14);
    
      //cout << Pot.at(count) << '\n';
      //ReconVec.babymind_spill->push_back(1);
      //ReconVec.pot->push_back(1);
      //}
    
  
    for(Int_t i_data=index[0]; i_data<index[1]; i_data++){

      module.push_back(ModuleNumber->at(i_data));
      track_flag=0;
          
      //  cout << "Eventnumber= "  <<Eventnumber.at(i_event) << " " << PosZ->at(i_data) << " " << PosY->at(i_data) << " " << RSignalLeadTime->at(i_data) << '\n';

      if(i_data==index[0]){
	tracktime.push_back(RSignalLeadTime->at(i_data));
	//Recon_Track[i_event][1]->Fill(PosZ->at(i_data), PosY->at(i_data), RSignalLeadTime->at(i_data));
	/*
	Recon_Track[i_event][1]->Fill(PosZ->at(i_data), PosY->at(i_data), 1);
	Recon_Track[i_event][0]->Fill(PosZ->at(i_data), PosY->at(i_data), RSignalLeadTime->at(i_data));
	track_flag=1;
	*/
	
	Recon_Track->Fill(PosZ->at(i_data), PosY->at(i_data), 1);
	Recon_Track->Fill(PosZ->at(i_data), PosY->at(i_data), RSignalLeadTime->at(i_data));
	track_flag=1;
	

      }
            

      if(i_data>index[0]){
	for(int i_size=1; i_size<=tracktime.size(); i_size++){
	  if(RSignalLeadTime->at(i_data)<tracktime.at(i_size-1)+10 
	     && RSignalLeadTime->at(i_data)>tracktime.at(i_size-1)-10){
	    track_flag = i_size;
	    
	    //cout << "former " << Eventnumber.at(i_event)  << " error "  << track_flag << "\n";
	    continue;
	  }

	}//i_size loop
	if(track_flag==0){
	  tracktime.push_back(RSignalLeadTime->at(i_data));
	  track_flag = tracktime.size();

	  //  cout << "former " << i_event  << " error "  << track_flag << "\n";
       
	} //track_flag condition
      
      } //i_data condition

      //   cout << "latter " << i_event  << " error "  << track_flag << "\n";

      //Recon_Track[i_event][track_flag]->Fill(PosZ->at(i_data), PosY->at(i_data), RSignalLeadTime->at(i_data));
      /*
      Recon_Track[i_event][track_flag]->Fill(PosZ->at(i_data), PosY->at(i_data), 1);
      Recon_Track[i_event][0]->Fill(PosZ->at(i_data), PosY->at(i_data), RSignalLeadTime->at(i_data));
      */
      
     
      if(track_flag==1){
      Recon_Track->Fill(PosZ->at(i_data), PosY->at(i_data), 1);
      Recon_Track->Fill(PosZ->at(i_data), PosY->at(i_data), RSignalLeadTime->at(i_data));
      }

    } //i_data loop

    //Event check
    
    eventchecker(HitModuleNum->at(Eventnumber.at(i_event)), PosY->at(index[0]), &checkpoint);
    auto last = std::unique(module.begin(), module.end());
    module.erase(last, module.end());
    
    /*
    if(i_event==1||i_event==2||i_event==3||i_event==4||i_event==5||i_event==6||i_event==7
       ||i_event==8||i_event==51||i_event==52||i_event==53){
      cout << coincidence_check(&module, &number) << '\n';
    }
    */
    
    bool eventselection = coincidence_check(&module, &number)&&!first_check(&module, &number)&&coincidence_check_remove(&module, &rmnumber)&&Centralregion(PosY, PosX, index[0]);
    
    
    //bool eventselection = coincidence_check(&module, &number)&&Centralregion(PosY, PosX, index[0]);

    if(eventselection){
      goodevent.push_back(i_event);
      goodeventpot += Pot.at(count) * pow(10, 14);
      bunch_hist->Fill((hitTimefromSpill->at(index[0]))*2.5);
      if(!TimingCheck(hitTimefromSpill->at(index[0])*2.5, &Bunch)){
	Badtimingevent.push_back(i_event);
	Badtiming.push_back(hitTimefromSpill->at(index[0])*2.5);
      }
      
    }
      
    // bunch_hist->Fill(hitTimefromSpill->at(index[0]));
    
    //  cout << Eventnumber.at(i_event)  <<   " " << HitModuleNum->at(Eventnumber.at(i_event)) << " " << PosY->at(index[0]) << " " << checkpoint  <<  '\n';

    /*
    if(checkpoint==1){
      uprange.push_back(i_event);
    }
    if(checkpoint==2){
      middlerange.push_back(i_event);
    }
    if(checkpoint==3){
      downrange.push_back(i_event);
    }
    */

    /*    if(GTrigTime->at(index[0])==2 && checkpoint == 1){
      double temp = abs(RSignalLeadTime->at(index[0]) - basetime);
      bunch_structure->Fill(temp);
      
    }
    */

          //****save the image****//
    
      /*
      TCanvas *monitor = new TCanvas("monitor", "monitor", 1000, 600);
      monitor->cd();
      */
    
   
    if(eventselection){
      
    //sleep(1000);
      TString Directory_main =
	"/Users/jinaren/Documents/T2K/BabyMIND/commissioning_run/event_estimation/macro/Myanalysis/Image/";
      TString Directory_part = "Eventdisp_" + sDirdate.str() + "_" + mon + "_" + sDirrun.str() + "/";
      TString Directory_image = (Directory_main + Directory_part);
      //cout << Directory_image << '\n';

     

       //**** fitting *****//

      
    double coefficient_c, coefficient_ud;
    int NofMod;
    //int limit_event = goodevent.size();
    //int limit_event =100;
    int NDF;
    double a = 0;

      ostringstream simagenum;
      string simagename;
      simagenum.str("");
      simagenum << spillnumber.at(count);
      simagename = "EvtDisp_" + simagenum.str();
      //TCanvas *monitor_fit = new TCanvas(simagename.c_str(), simagename.c_str(), 1000, 600);
      
      /*
      TCanvas *monitor_fit = new TCanvas("monitor_fit", "monitor_fit", 1000, 600);
      monitor_fit->cd();
      Recon_Track->Draw();
        
      Fit(i_event, Recon_Track, &coefficient_c, &coefficient_ud, &NDF);
	 if(NDF > 10){
	   if(coefficient_c > 0){
	     count_plus++;
	   }
	   
	   
	   if(coefficient_c < 0){
	     count_minus++;
	   }
	   coffa->Fill(coefficient_c);
	 }



	 monitor_fit->Modified();
	 monitor_fit->Update();
	 gSystem->ProcessEvents();
	 //monitor_fit->Clear();
	 
	 */
	  
        /*
    if(coefficient_ud > 0){
      count_plus++;
    }
    
    if(coefficient_ud < 0){
      count_minus++;
    }
      
      if(i_event%10==9){
	cout << "fitting process: " << i_event+1 << "/" << goodevent.size() << '\n'; 
	}
      
    }//i_event loop (inside 'analysis')
	*/
  
    // ****EventDisp**** //
      
      cout << "P.O.T = "  <<  Pot.at(count) << '\n';
      cout << "spill = "  <<  spillnumber.at(count) << '\n';
      TimingCheck(hitTimefromSpill->at(index[0])*2.5, &Bunch);
      cout << spillnumber.at(count) << " " << Bunch << '\n';
      BMdisp(index[0], index[1], *PosZ, *PosY, *PosX, *RSignalLeadTime, Bunch);
      gSystem->ProcessEvents();
      //Recon_Track->Draw();
      //monitor->SaveAs(Directory_image + simagename.c_str() + ".pdf");
      monitor->Modified();
      monitor->Update();
      // sleep(0.001);
      
      
      TImage *img = TImage::Create();
      //img->FromPad(c, 10, 10, 300, 200);
      img->FromPad(monitor);
      img->WriteImage(Directory_image + simagename.c_str() + ".png");
      //delete monitor;
      delete img;
      
    
    }

    
      
      /*
      for(int i=0; i<goodevent.size(); i++){
	//Recon_Track[int(goodevent.at(i))][0]->Draw();
      ostringstream simagenum;
      string simagename;
      simagenum.str("");
      simagenum << goodevent.at(i);
      simagename = "EvtDisp_" + simagenum.str();
      monitor->Print(Directory_image + simagename.c_str() + ".pdf");
      monitor->Clear();
      monitor->Modified();
      monitor->Update();
      gSystem->ProcessEvents();
      }
      */ 
	  
    }//i_event loop

  
  ostringstream sdate;
  ostringstream srun;
  string sdatename;
  sdate.str("");
  sdate << i_date;
  srun.str("");
  srun << i_run;
  sdatename = "5/" + sdate.str() + "-" + srun.str();

  DateLabel.push_back(sdatename);

  TString Badeventlist;
  ostringstream sbadnum;
  ostringstream sbadnumber;
  string sbadname;
 
  for(int i=0; i<Badtimingevent.size(); i++){
    sbadnum.str("");
    sbadnum << Badtimingevent.at(i);
    sbadnumber.str("");
    sbadnumber << Badtiming.at(i);
    sbadname = "EvtNum_" + sbadnum.str() + "(" + sbadnumber.str() + ")";
    if(i==Badtimingevent.size()-1){
      Badeventlist += sbadname;
    }
    else{
      Badeventlist += sbadname + ", ";
    } 
  }
  if(Badtimingevent.size()==0){
    Badeventlist = "No Bad Event!";
  }

  for(int i=firstcount; i<=count; i++){
    deliveredpot += Pot.at(i) * pow(10, 14);
  }

  eventrate = goodevent.size()/deliveredpot*pow(10, 17);
  EVENTRATE[i_count] = eventrate;
  erry[i_count] = sqrt(goodevent.size())/deliveredpot*pow(10, 17); 
  i_count++;

  Badtimingevent.clear();
  Badtiming.clear();

  ratio = (double)count_plus/((double)count_minus+(double)count_plus);

  cout << "mu+: " << count_plus << " mu-: " << count_minus << '\n'; 
  cout << "ratio= " << ratio << '\n';


  Fileinput->Close();
  
      cout << "********** Summary of Reconstruction **********" << '\n';
      cout << "\n";
      cout << "Input File = " << sFileName.c_str() << '\n';
      cout << "Output File = " << Filename_out << '\n';
      cout << "The Number of Event data = "  << numberOfeventdata << '\n';
      cout << "The Number Of Track Data = "  << numberOfhistgram << '\n';
      cout << "The Number of Good Event = "  << goodevent.size() << '\n';
      cout << "Delivered P.O.T. = " << deliveredpot << '\n';
      cout << "Total P.O.T. = " << totalpot << '\n';
      cout << "Good Event P.O.T. = " << goodeventpot << '\n';
      cout << "Event Rate (10^(-3)/10^14 P.O.T.) = " << eventrate << '\n';
      cout << "First Spill = " << spillnumber.at(firstcount) << '\n';
      cout << "Last Spill = " << spillnumber.at(count) << '\n';
      cout << "StartDate: " << Year.at(firstcount) 
	   << "年 " << Month.at(firstcount) << "月" << Date.at(firstcount) << "日" << '\n'; 
      cout << "EndDate: " << Year.at(count) << "年 " << Month.at(count) << "月" << Date.at(count) << "日" << '\n';
      cout << "BadEventList: " << Badeventlist << '\n';
      cout << '\n';
      cout <<"************************************************" << '\n';

      //****save the image****//
    
      /*
      TCanvas *monitor = new TCanvas("monitor", "monitor", 1000, 600);
      monitor->cd();
      */

      /*
      TString Directory_main =
	"/Users/jinaren/Documents/T2K/BabyMIND/commissioning_run/event_estimation/macro/Myanalysis/Image/";
      TString Directory_part = "Eventdisp_" + sDirdate.str() + "_" + mon + "_" + sDirrun.str() + "/";
      TString Directory_image = (Directory_main + Directory_part);
      cout << Directory_image << '\n';
      */
      /*
      for(int i=0; i<goodevent.size(); i++){
	//Recon_Track[int(goodevent.at(i))][0]->Draw();
      ostringstream simagenum;
      string simagename;
      simagenum.str("");
      simagenum << goodevent.at(i);
      simagename = "EvtDisp_" + simagenum.str();
      monitor->Print(Directory_image + simagename.c_str() + ".pdf");
      monitor->Clear();
      monitor->Modified();
      monitor->Update();
      gSystem->ProcessEvents();
      }
      */ 
      
      

    }
  }
  

  if(analysis){

    string sFileName;

    sDirdate.str("");
    sDirrun.str("");
    sDirdate << date;
    sDirrun << run;

      TString Directory_out =
    "/Users/jinaren/Documents/T2K/BabyMIND/commissioning_run/event_estimation/macro/Myanalysis/Recon/";
      TString Filename_out = "Recon_" + sDirdate.str() + "_" + mon + "_" + sDirrun.\
	str() + ".root";
      TString rootoutputFile = (Directory_out + Filename_out);

      TFile *Fileoutput = new TFile(rootoutputFile.Data(), "recreate");
       
      TCanvas *bunch = new TCanvas("bunch", "bunch", 1000, 600);
      //bunch->SetLogy();
      TCanvas *ER = new TCanvas("ER", "ER", 1000, 600);
      ER->SetGrid();

    // **** Start Analysis ****//
    ReconVec.Numofgoodevent->push_back(goodevent.size());
    
    for(int i=0; i<goodevent.size(); i++){
      ReconVec.goodeventnumber->push_back(goodevent.at(i));
    }
    
    //**** fitting *****//
    /*
    for(int i_event=0; i_event<limit_event; i_event++){
      eventid = goodevent.at(i_event);
        
	Fit(eventid, Recon_Track[eventid][1], &coefficient_c, &coefficient_ud, &NDF);
	 if(NDF > 10){
	   if(coefficient_c > 0){
	     count_minus++;
	   }
	   
	   
	   if(coefficient_c < 0){
	     count_plus++;
	   }
	 }
    */
	  
        /*
    if(coefficient_ud > 0){
      count_plus++;
    }
    
    if(coefficient_ud < 0){
      count_minus++;
    }
    */
      /*
      if(i_event%10==9){
	cout << "fitting process: " << i_event+1 << "/" << goodevent.size() << '\n'; 
	}
      
    }//i_event loop (inside 'analysis')
    //fitmonitor->Clear();
    ratio = (double)count_plus/((double)count_minus+(double)count_plus);

    cout << "mu+: " << count_plus << " mu-: " << count_minus << '\n'; 
    cout << "ratio= " << ratio << '\n';
 
    ReconVec.muplus->push_back(count_plus);
    ReconVec.muminus->push_back(count_minus);
    ReconVec.ratio->push_back(ratio);
      */

    ReconVec.Numofgoodevent = 0;
    ReconVec.goodeventnumber = 0;
    ReconVec.degree = 0;
    ReconVec.momentum = 0;
    ReconVec.muplus = 0;
    ReconVec.muminus = 0;
    ReconVec.ratio = 0;

    // **** Fill tree ****//
    Recontree->Fill();
    Recontree->Write();

    TGraphErrors *EventRate = new TGraphErrors(i_count, x, EVENTRATE, errx, erry);
    
    bunch->cd();
    //bunch_hist->Draw();
    coffa->Draw();
    ER->cd();
    EventRate->Draw("AP");
    EventRate->SetMarkerColor(4);
    EventRate->SetMarkerStyle(21);
    EventRate->GetXaxis()->SetLimits(-1, 19);
    EventRate->SetTitle("Event Rate");
    EventRate->GetYaxis()->SetTitleSize(0.04);
    EventRate->GetXaxis()->SetTitleSize(0.04);
    EventRate->GetYaxis()->SetLabelSize(0.05);
    EventRate->GetYaxis()->SetLabelSize(0.05);
    EventRate->GetXaxis()->SetNdivisions(20);
    EventRate->GetXaxis()->SetLabelOffset(99);
    Fileoutput->Close();

    /*
    //EventRate->GetXaxis()->SetBinLabel(0,"K_{L}#rightarrow3#pi^{0}");//第一引数はibin
    //EventRate->GetXaxis()->SetBinLabel(1,"K_{L}#rightarrow2#pi^{0}");// ibin=0 はunderflow
    //EventRate->GetXaxis()->SetBinLabel(2,"K_{L}#rightarrow2#gamma"); // ibin=nbin+1
    //EventRate->GetXaxis()->SetLabelSize(0.07);
    */
    
    TLatex *Ylabel = new TLatex();
    Ylabel->SetTextSize(0.05);
    Ylabel->SetTextAngle(90);
    Ylabel->DrawLatexNDC(0.04, 0.18, "10^{-3} Events/Iron 1500kg/10^{14}P.O.T.");
    TLatex *Xlabel = new TLatex();
    Xlabel->SetTextSize(0.04);
    Xlabel->SetTextAngle(60);
    Xlabel->DrawLatexNDC(0.90, 0.015, "Mon/Day-Run");
    

    TLatex *label = new TLatex();
    label->SetTextSize(0.04);
    label->SetTextAngle(60);
    cout << DateLabel.size() << '\n';
    for(int i=0; i<DateLabel.size(); i++){
      cout << (DateLabel.at(i)).data() << '\n';
      double xLabel = 0.14+0.04*i;
      label->DrawLatexNDC(xLabel, 0.015,(DateLabel.at(i)).data());
    }
    
    /*  
    ER->cd();
    TText t;
    t.SetTextAngle(0);
    t.SetTextSize(1);
    t.SetTextAlign(200);
    //t.SetTextColor(1);
    Float_t tx,ty;
    ty = gPad->GetUymin() - 0.06*EventRate->GetYaxis()->GetBinWidth(1);
    //ty = 1;
    for(int i=0;i<6;i++){
      //tx= EventRate->GetXaxis()->GetBinCenter(i+40);
      tx = i;
      cout << tx << " " << ty << '\n';
      //t.DrawText(tx,ty,(DateLabel.at(i)).c_str());
      t.DrawText(tx,ty,"ss");
    }
    */
   
    
    
    TF1 *constant = new TF1("constant", "[0]", 0, 100);
    constant->SetParameter(0, 6.0);
    EventRate->Fit(constant, "", "", -1, i_count);

    app.Run();
    return 0;
  }
  
    
   
    // **** Display ****//
    /*
    //monitor
    TCanvas *c1 = new TCanvas("c1", "c1", 1600, 900);
    c1->Divide(8, 8);
    TCanvas *c2 = new TCanvas("c2", "c2", 1600, 900);
    c2->Divide(3, 2);
    //TCanvas *c3 = new TCanvas("c3", "c3", 1600, 900);
   
    int eventid;

    for(Int_t ic=1; ic<=64; ic++){
      // eventid = ic;
      eventid = goodevent.at(ic-1);
      
      c1->cd(ic);      
      //Recon_Track[middlerange.at(ic+192)][0]->Draw("colz");
      Recon_Track[eventid][0]->Draw("colz");
    }
    gStyle->SetPalette(1);

    for(int ith_track=1; ith_track<=6; ith_track++){
      c2->cd(ith_track);
      //Recon_Track[middlerange.at(171)][ith_track-1]->Draw("colz");
      Recon_Track[1][ith_track-1]->Draw("colz");
    }
    */
    
    //bunch structure
    /*
    c3->cd();
    bunch_structure->Draw();
    bunch_structure->SetStats(0);
    bunch_structure->SetTitle("bunch structure");
    bunch_structure->SetTitleSize(0.07);
    bunch_structure->GetXaxis()->SetTitleSize(0.05);
    bunch_structure->GetXaxis()->SetLabelSize(0.05);
    bunch_structure->GetYaxis()->SetTitleSize(0.05);
    bunch_structure->GetYaxis()->SetLabelSize(0.05);
    bunch_structure->SetXTitle("TimeDifference (2.5*ns)");
    bunch_structure->SetYTitle("events (/25ns)");
    */


  //Baby-MIND display
  /*

  if(display){

    int check;
    bool loop = true;
    
    while(loop){
  
      cout << "Type -1 to quit the program" << '\n';
      cout << "Type -2 to save the image" << '\n';
      cout << "input number from" << 0 << " ~ " << Eventnumber.size() << '\n'; 
      
    if(cin >> check){
      if(check == -1){
	monitor->Clear();
	loop = false;
      }

      if(check>=0 && check <= Eventnumber.size()){
	int eventID = check;
	int data;
	auto bounds = std::equal_range(EventNum->begin(), EventNum->end(), Eventnumber.at(eventID));
	index[0] = bounds.first - EventNum->begin();
	index[1] = bounds.second - EventNum->begin();
	
	
	BMdisp(index[0], index[1], *PosZ, *PosY, *PosX, *RSignalLeadTime);
	gSystem->ProcessEvents();
	cout << "***** Track information *****" << '\n';
	cout << '\n';
	cout << "Spill Number: " << SpillNumber->at(eventID)  << '\n';
	cout << "EventNumber: " << Eventnumber.at((eventID)) << '\n';
	cout << "GTrigTime: " << GTrigTime->at(Eventnumber.at(eventID)) << '\n';
	cout << "The number of HitModule: " << HitModuleNum->at(Eventnumber.at(eventID)) << '\n';
	cout << "FirstModule: " << FirstModule->at(eventID) << '\n';
	cout << "*****************************" << '\n';

      cout << "Type -2 to save the program" << '\n';
      cout << "Otherwise Type any int number" << '\n';
      if(cin >> check){
	if(check == -2){
	  TString imagedir = "/Users/jinaren/Documents/T2K/BabyMIND/J-PARC_physics_run/image/2018_Mar_May/";
	  ostringstream simagenum;
	  string simagename;
	  simagenum.str("");
	  simagenum << eventID;
	  simagename = "EvtDisp_" + simagenum.str();
	  monitor->Print(imagedir + simagename.c_str() + ".pdf");

	}
      }
      else{
	continue;
      }

      }
	   
      if(check < 0 || check > Eventnumber.size()-1){
	continue;
      }
    }

    else{
      cout << "***** exception was found *****" << '\n';
      cout << "once more!";
      cout << '\n';
      cin.clear();
      cin.ignore();

    }


    }

    app.Run();

  }
 
  //cout << Eventnumber.size() << '\n';

  */

  //Fitting
  /*

  double coefficient_c, coefficient_ud;
  int NofMod;
  int limit_event = middlerange.size();
  //int limit_event =100;
  int eventid;
  int count_plus = 0;
  int count_minus = 0;
  int NDF;
  int firstcheck;
  bool Veto;
  
  if(fitting){
    for(int i_event=0; i_event<limit_event; i_event++){
      eventid = middlerange.at(i_event);
      Veto = false;

      firstcheck = FirstModule->at(eventid);
      if(firstcheck==1){
	Veto = true;
      }
      
      if(!Veto){       
	Fit(eventid, Recon_Track[eventid][1], &coefficient_c, &coefficient_ud, &NDF);
	 if(NDF > 10){
	   if(coefficient_c > 0){
	     count_minus++;
	   }
	   
	   
	   if(coefficient_c < 0){
	     count_plus++;
	   }
	 }
	  
      }
  */
    /*
    if(coefficient_ud > 0){
      count_plus++;
    }
    
    if(coefficient_ud < 0){
      count_minus++;
    }
    */
  /*
      gSystem->ProcessEvents();
    }
    //fitmonitor->Clear();

    cout << "muplus: " << count_plus << " mu-: " << count_minus << '\n'; 
    cout << "ratio= " << (double)count_plus/((double)count_minus+(double)count_plus) << '\n'; 
 
    app.Run();
    return 0;

  }
*/

/*

  if(recon){
    //int EventID = middlerange.at(1);
    int EventID = 1;
    Recon(Recon_Track[EventID][0]);    
    app.Run();
    return 0;
  }
*/

  //return 0;

  
}

  

