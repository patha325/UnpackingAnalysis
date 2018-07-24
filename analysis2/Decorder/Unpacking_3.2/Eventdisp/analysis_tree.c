#include <unistd.h>
#include <vector>
#include "BMdisp.h"

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
    

void analysis_tree(){

  //monitor
  TCanvas *c1 = new TCanvas("c1", "c1", 1600, 900);
  c1->Divide(8, 8);
  TCanvas *c2 = new TCanvas("c2", "c2", 1600, 900);
  c2->Divide(3, 2);
  TCanvas *c3 = new TCanvas("c3", "c3", 1000, 1200);



  const int NumberOfHor = 95;
  const int NumberOfVer = 16;
  const int NumberOfModule = 18;
  const int entry_limit = 1;

  int track_flag;

  TString inputFile = "Event.root";

  TFile *Fileinput = new TFile(inputFile);
  TTree *t = (TTree*)Fileinput->Get("events");

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
           
  } //i_entry

  
  const int numberOfeventdata = PosX->size(); 
  //cout << numberOfeventdata << '\n';
  
  vector <double> Eventnumber;
  Eventnumber.clear();

  vector <double> tracktime;
  tracktime.clear();

  
  for(Int_t i=0; i<numberOfeventdata; i++){
    Eventnumber.push_back(EventNum->at(i));
  }


  auto last = std::unique(Eventnumber.begin(), Eventnumber.end());
  Eventnumber.erase(last, Eventnumber.end());


  ostringstream shistnum;
  string shist;
  const int numberOfhistgram = Eventnumber.size();
  TH2D *Recon_Track[numberOfhistgram][6];   
  TH1D *bunch_structure = new TH1D("bunch_strunture", "bunch_structure",
				   480, -200, 4600);
  const int numberOftrack = 10;
  int checkpoint;
  double basetime = 0;
    
  vector <int> uprange;
  vector <int> middlerange;
  vector <int> downrange;

  uprange.clear();
  middlerange.clear();
  downrange.clear();

  
  Int_t index[2] ={0, 0};
  for(int i_event=0; i_event<numberOfhistgram; i_event++){
    checkpoint = 0;
    tracktime.clear();
    //for(int i_event=0; i_event<3; i_event++){
    //cout << i_event << '\n';
    
    auto bounds = std::equal_range(EventNum->begin(), EventNum->end(), Eventnumber.at(i_event));
    index[0] = bounds.first - EventNum->begin();
    index[1] = bounds.second - EventNum->begin();

    
   //histgram
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
				      50, -60, 4520, 95, -986.2, 986.2);

      Recon_Track[i_event][i_track]->SetStats(0);
      Recon_Track[i_event][i_track]->SetTitle(shist.c_str());
      Recon_Track[i_event][i_track]->SetTitleSize(0.07);
      Recon_Track[i_event][i_track]->SetMarkerStyle(8);
      Recon_Track[i_event][i_track]->SetMarkerSize(8);
      Recon_Track[i_event][i_track]->SetXTitle("Z [mm]");
      Recon_Track[i_event][i_track]->SetYTitle("Y [mm]");
      Recon_Track[i_event][i_track]->GetXaxis()->SetTitleSize(0.05);
      Recon_Track[i_event][i_track]->GetXaxis()->SetLabelSize(0.05);
      Recon_Track[i_event][i_track]->GetYaxis()->SetTitleSize(0.05);
      Recon_Track[i_event][i_track]->GetYaxis()->SetLabelSize(0.05);
      Recon_Track[i_event][i_track]->GetZaxis()->SetLabelSize(0.03);


    }//i_track loop
     
      
     
    for(Int_t i_data=index[0]; i_data<index[1]; i_data++){

      track_flag=0;
          
      //  cout << "Eventnumber= "  <<Eventnumber.at(i_event) << " " << PosZ->at(i_data) << " " << PosY->at(i_data) << " " << RSignalLeadTime->at(i_data) << '\n';

      if(i_data==index[0]){
	tracktime.push_back(RSignalLeadTime->at(i_data));
	Recon_Track[i_event][1]->Fill(PosZ->at(i_data), PosY->at(i_data), RSignalLeadTime->at(i_data));
	Recon_Track[i_event][0]->Fill(PosZ->at(i_data), PosY->at(i_data), RSignalLeadTime->at(i_data));
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

	}//j_size loop
	if(track_flag==0){
	  tracktime.push_back(RSignalLeadTime->at(i_data));
	  track_flag = tracktime.size();

	  //  cout << "former " << i_event  << " error "  << track_flag << "\n";
       
	} //track_flag condition
      
      } //i_data condition

      //   cout << "latter " << i_event  << " error "  << track_flag << "\n";

      Recon_Track[i_event][track_flag]->Fill(PosZ->at(i_data), PosY->at(i_data), RSignalLeadTime->at(i_data));
      Recon_Track[i_event][0]->Fill(PosZ->at(i_data), PosY->at(i_data), RSignalLeadTime->at(i_data));

      
 
    } //i_data loop

    eventchecker(HitModuleNum->at(Eventnumber.at(i_event)), PosY->at(index[0]), &checkpoint);
    
    //  cout << Eventnumber.at(i_event)  <<   " " << HitModuleNum->at(Eventnumber.at(i_event)) << " " << PosY->at(index[0]) << " " << checkpoint  <<  '\n';


    if(checkpoint==1){
      uprange.push_back(i_event);
    }
    if(checkpoint==2){
      middlerange.push_back(i_event);
    }
    if(checkpoint==3){
      downrange.push_back(i_event);
    }

    /*    if(GTrigTime->at(index[0])==2 && checkpoint == 1){
      double temp = abs(RSignalLeadTime->at(index[0]) - basetime);
      bunch_structure->Fill(temp);
      
    }
    */

  }//i_event loop

  for(int i=0; i<RSignalLeadTime->size()-1; i++){
    for(int j=i+1; j<RSignalLeadTime->size(); j++){
	if(GTrigTime->at(i) == 2 && GTrigTime->at(j) == 2){
	  double temp = abs(RSignalLeadTime->at(j) - RSignalLeadTime->at(i));
	  bunch_structure->Fill(temp);
	  i=j;
	}
      }
    }
  

  for(Int_t ic=1; ic<=64; ic++){
    c1->cd(ic);      
    Recon_Track[middlerange.at(ic+100)][0]->Draw("colz");
  }
  gStyle->SetPalette(1);

  //Fileinput->Close();  

  for(int ith_track=1; ith_track<=6; ith_track++){
    c2->cd(ith_track);
    Recon_Track[uprange.at(50)][ith_track-1]->Draw("colz");
  }

  //bunch structure
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

  //Baby-MIND display
  
  BMdisp();
  int eventid =148;
  auto bounds = std::equal_range(EventNum->begin(), EventNum->end(), Eventnumber.at(middlerange.at(eventid)));
  index[0] = bounds.first - EventNum->begin();
  index[1] = bounds.second - EventNum->begin();
  
  for(Int_t i_data=index[0]; i_data<index[1]; i_data++){
    monitor->cd(2);
    hit(PosZ->at(i_data), PosY->at(i_data), 30);
    monitor->cd(1);
    hit(PosZ->at(i_data), PosX->at(i_data), 30);
  }
  
 
  //cout << Eventnumber.size() << '\n';
  
}
  

