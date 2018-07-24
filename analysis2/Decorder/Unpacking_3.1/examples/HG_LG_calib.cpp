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
#include "TF1.h"
#include "TH3.h"
#include <iterator>
#include <algorithm>


using namespace std;


string GetLocation(string str)
{
     
    int i = str.rfind("_Slot_");
    string way = str.substr(0,i);  
    return way;
}

struct vectorsTree
{
  vector<double> *FEBSN;
  vector<double> *SpillNum;
  vector<double> *GTrigTag;
  vector<double> *GTrigTime;
  vector<double> *hitsChannel;
  vector<double> *hitAmpl;
  vector<double> *hitLGAmpl;
  vector<double> *hitLeadTime;
  vector<double> *hitTrailTime;
  vector<double> *hitTimeDif;
  vector<double> *hitTimeAvr;
};

int main ()
{
    int NumberOfFEB=65;
    
    vector<string> vFileNames;
    string sFileName;
    ifstream fList("febs_files_list.list");
    while (!fList.eof()) {
        fList >> sFileName;
        vFileNames.push_back(sFileName);
    }
    string rootFileInput=GetLocation(vFileNames[0].c_str());
    string rootFileOutput=GetLocation (vFileNames[0].c_str());
    rootFileInput+="_all.root";
    rootFileOutput+="_HG_LG_calib.root";
    cout << rootFileInput<<endl;
    cout << rootFileOutput<<endl;
    TFile *FileInput = new TFile(rootFileInput.c_str());
    
    vectorsTree FEB[NumberOfFEB];
    
    for (Int_t i=0;i<NumberOfFEB;i++){
        FEB[i].FEBSN=0;
        FEB[i].SpillNum=0;
        FEB[i].hitsChannel=0;
        FEB[i].hitAmpl=0;
        FEB[i].hitLeadTime=0;
        FEB[i].GTrigTag=0;
        FEB[i].GTrigTime=0;
        FEB[i].hitLGAmpl=0;
        FEB[i].hitTrailTime=0;
        FEB[i].hitTimeDif=0;
        FEB[i].hitTimeAvr=0;
    }
    
    TTree *FEBtree[NumberOfFEB];
    vector<int> FEBnumbers;
    FEBnumbers.clear();
    
    ostringstream sFEBnum;
    string sFEB;
    for (Int_t ih=0; ih<NumberOfFEB; ih++) {
        sFEBnum.str("");
        sFEBnum << ih;
        sFEB = "FEB_"+sFEBnum.str();
        FEBtree[ih] = (TTree*)FileInput->Get(sFEB.c_str());
        if ((TTree*)FileInput->Get(sFEB.c_str())){
            FEBnumbers.push_back(ih);
            std::cout<<sFEB<<" ";
            FEBtree[ih]->SetBranchAddress((sFEB+"_SN").c_str(),&FEB[ih].FEBSN);
            FEBtree[ih]->SetBranchAddress((sFEB+"_SpillTag").c_str(),&FEB[ih].SpillNum);
            FEBtree[ih]->SetBranchAddress((sFEB+"_GTrigTag").c_str(),&FEB[ih].GTrigTag);
            FEBtree[ih]->SetBranchAddress((sFEB+"_GTrigTime").c_str(),&FEB[ih].GTrigTime);
            FEBtree[ih]->SetBranchAddress((sFEB+"_hitsChannel").c_str(),&FEB[ih].hitsChannel);
            FEBtree[ih]->SetBranchAddress((sFEB+"_hitAmpl").c_str(),&FEB[ih].hitAmpl);
            FEBtree[ih]->SetBranchAddress((sFEB+"_hitLGAmpl").c_str(),&FEB[ih].hitLGAmpl);
            FEBtree[ih]->SetBranchAddress((sFEB+"_hitLeadTime").c_str(),&FEB[ih].hitLeadTime);
            FEBtree[ih]->SetBranchAddress((sFEB+"_hitTrailTime").c_str(),&FEB[ih].hitTrailTime);
            FEBtree[ih]->SetBranchAddress((sFEB+"_hitTimeDif").c_str(),&FEB[ih].hitTimeDif);
            FEBtree[ih]->SetBranchAddress((sFEB+"_hitTimeAvr").c_str(),&FEB[ih].hitTimeAvr);
            
            FEBtree[ih]->GetEntry(0);
            std::cout << "Number of events = " <<FEB[ih].FEBSN->size()<<std::endl;
        }
  }
  FileInput->Close();
  TFile wfile(rootFileOutput.c_str(), "recreate");
  TH2F *HG_vs_LG[NumberOfFEB][96];
  Double_t fitPar[2];
  TF1 *f = new TF1("f","pol1",500,2500);
  
  for (int ih = 0; ih<FEBnumbers.size();ih++) {
        cout <<"FEB " <<FEBnumbers.at(ih)<<" in process."<<endl;
        sFEBnum.str("");
        sFEBnum << FEBnumbers.at(ih);
        sFEB = "FEB_"+sFEBnum.str();
        
        //string fouttxt = "HG_LG_calib/" + sFEB.c_str() + "HG_LG_calib.txt";
        string fouttxt = "HG_LG_calib/";
        fouttxt+=sFEB.c_str();
        fouttxt+="_HG_LG_calib.txt";
        ofstream foutDat(fouttxt.c_str());
        TDirectory *FEB_HG_LG = wfile.mkdir(sFEB.c_str());
        
        ostringstream sChnum;
        string sCh;
        
        for (Int_t ich=0; ich < 96;ich++){
            sChnum.str("");
            sChnum << ich;
            sCh =  "FEB_" + sFEBnum.str() + "_channel_" + sChnum.str();
            HG_vs_LG[FEBnumbers.at(ih)][ich]=new TH2F(sCh.c_str(),sCh.c_str(),  4096, 0, 4095, 4096, 0, 4095);
        }
        
        for (Int_t i = 0; i<FEB[FEBnumbers.at(ih)].hitTimeDif->size(); i++){
            if (FEB[FEBnumbers.at(ih)].hitAmpl->at(i)>0)
                //cout<< FEB[FEBnumbers.at(ih)].hitAmpl->at(i)<< " "<< FEB[FEBnumbers.at(ih)].hitLGAmpl->at(i)<<endl;
                HG_vs_LG[FEBnumbers.at(ih)][(int)FEB[FEBnumbers.at(ih)].hitsChannel->at(i)]-> Fill(FEB[FEBnumbers.at(ih)].hitAmpl->at(i) , FEB[FEBnumbers.at(ih)].hitLGAmpl->at(i),1);
        }
        
        
        
        FEB_HG_LG->cd();
        for (Int_t ich=0; ich < 96;ich++){
            if (HG_vs_LG[FEBnumbers.at(ih)][ich]->GetEntries()>1) {
                HG_vs_LG[FEBnumbers.at(ih)][ich]->GetYaxis()->SetTitle("LG [ADC]");
                HG_vs_LG[FEBnumbers.at(ih)][ich]->GetXaxis()->SetTitle("HG [ADC]");
                HG_vs_LG[FEBnumbers.at(ih)][ich]->Fit("f","MER");
	
                fitPar[0]=0;
                fitPar[1]=0;
                f->GetParameters(&fitPar[0]);
                cout<<"Channel "<< ich <<" fit par "<< fitPar[0]<<" "<< fitPar[1]<<endl;
                foutDat << ich<<" "<<fitPar[0]<<" "<< fitPar[1]<<endl;
                HG_vs_LG[FEBnumbers.at(ih)][ich]->Write();
            }
            delete HG_vs_LG[FEBnumbers.at(ih)][ich];
        }
        foutDat.close();
        
        FEB[FEBnumbers.at(ih)].FEBSN->clear();
        FEB[FEBnumbers.at(ih)].SpillNum->clear();
        FEB[FEBnumbers.at(ih)].hitsChannel->clear();
        FEB[FEBnumbers.at(ih)].hitAmpl->clear();
        FEB[FEBnumbers.at(ih)].hitLeadTime->clear();
        FEB[FEBnumbers.at(ih)].hitTrailTime->clear();
        FEB[FEBnumbers.at(ih)].hitTimeDif->clear();
        FEB[FEBnumbers.at(ih)].hitTimeAvr->clear();
        FEB[FEBnumbers.at(ih)].GTrigTag->clear();
        FEB[FEBnumbers.at(ih)].GTrigTime->clear();
        FEB[FEBnumbers.at(ih)].hitLGAmpl->clear();
  }
  wfile.Close();
  return 0;
}
