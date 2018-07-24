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
#include "TF1.h"
#include "TCanvas.h"
#include <iterator>
#include <algorithm>
#include "TImage.h"
#include "TStyle.h"

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
  vector<double> *SpillTag;
  vector<double> *GTrigTag;
  vector<double> *GTrigTime;
  vector<double> *hitsChannel;
  vector<double> *hitAmpl;
  vector<double> *hitLGAmpl;
  vector<double> *hitLeadTime;
  vector<double> *hitTrailTime;
  vector<double> *hitTimeDif;
};

int main ()
{
    int NumberOfEB = 64;
    vector<string> vFileNames;
    string sFileName;
    ifstream fList("febs_files_list.list");
    while (!fList.eof()) {
        fList >> sFileName;
        vFileNames.push_back(sFileName);
    }
    fList.close();
    
    string rootFileInput=GetLocation(vFileNames[0].c_str());
    string rootFileOutput=GetLocation (vFileNames[0].c_str());
    rootFileInput+="_all.root";
    rootFileOutput+="_histo.root";
    cout << rootFileInput<<endl;
    
    TFile *FileInput = new TFile(rootFileInput.c_str());
    
    vectorsTree FEB[NumberOfEB];
    
    for (Int_t i=0;i<NumberOfEB;i++){
        FEB[i].FEBSN=0;
        FEB[i].SpillTag=0;
        FEB[i].hitsChannel=0;
        FEB[i].hitAmpl=0;
        FEB[i].hitLeadTime=0;
        FEB[i].GTrigTag=0;
        FEB[i].GTrigTime=0;
        FEB[i].hitLGAmpl=0;
        FEB[i].hitTrailTime=0;
        FEB[i].hitTimeDif=0;
        
    }
    
    
    TTree *FEBtree[NumberOfEB];
  
    ostringstream sFEBnum;
    string sFEB;
    for (Int_t ih=0; ih<NumberOfEB; ih++) {
        sFEBnum.str("");
        sFEBnum << ih;
        sFEB = "FEB_"+sFEBnum.str();
        FEBtree[ih] = (TTree*)FileInput->Get(sFEB.c_str());
        if ((TTree*)FileInput->Get(sFEB.c_str())){
            std::cout<<sFEB<<" ";
            FEBtree[ih]->SetBranchAddress((sFEB+"_SN").c_str(),&FEB[ih].FEBSN);
            FEBtree[ih]->SetBranchAddress((sFEB+"_SpillTag").c_str(),&FEB[ih].SpillTag);
            FEBtree[ih]->SetBranchAddress((sFEB+"_GTrigTag").c_str(),&FEB[ih].GTrigTag);
            FEBtree[ih]->SetBranchAddress((sFEB+"_GTrigTime").c_str(),&FEB[ih].GTrigTime);
            FEBtree[ih]->SetBranchAddress((sFEB+"_hitsChannel").c_str(),&FEB[ih].hitsChannel);
            FEBtree[ih]->SetBranchAddress((sFEB+"_hitAmpl").c_str(),&FEB[ih].hitAmpl);
            FEBtree[ih]->SetBranchAddress((sFEB+"_hitLGAmpl").c_str(),&FEB[ih].hitLGAmpl);
            FEBtree[ih]->SetBranchAddress((sFEB+"_hitLeadTime").c_str(),&FEB[ih].hitLeadTime);
            FEBtree[ih]->SetBranchAddress((sFEB+"_hitTrailTime").c_str(),&FEB[ih].hitTrailTime);
            FEBtree[ih]->SetBranchAddress((sFEB+"_hitTimeDif").c_str(),&FEB[ih].hitTimeDif);
            
            FEBtree[ih]->GetEntry(0);
            std::cout << "Number of events = " <<FEB[ih].FEBSN->size()<<std::endl;
        }
    }
    FileInput->Close();
    
     cout << rootFileOutput<<endl;
     TFile wfile(rootFileOutput.c_str(), "recreate");
     
     vector<double> GTrigTagCoins;
     
     for (int i = 0; i < FEB[56].FEBSN->size();i++){
         if (FEB[56].hitAmpl->at(i)>500)
             GTrigTagCoins.push_back(FEB[56].GTrigTag->at(i));
     }
     
     
     cout <<" "<< GTrigTagCoins.size()<<" "<<GTrigTagCoins.back()<<endl;
     auto last = std::unique(GTrigTagCoins.begin(),GTrigTagCoins.end());
     GTrigTagCoins.erase(last, GTrigTagCoins.end()); 
     cout <<" "<< GTrigTagCoins.size()<<" "<<GTrigTagCoins.back()<<endl;
     
     TH2F *BeamProf=new TH2F("EventsMap","EventsMap",  16, 0, 16, 95, 0, 95);
     
     
     Int_t leftindex[2]={0,0};
     Int_t rightindex[2]={0,0};
     Int_t topindex[2]={0,0};
    
     Int_t numberevents = 0;
     for (Int_t index=0; index <= GTrigTagCoins.size(); index++) {
          auto boundsleft=std::equal_range (FEB[56].GTrigTag->begin(), FEB[56].GTrigTag->end(), GTrigTagCoins[index]);
          leftindex[0] = boundsleft.first - FEB[56].GTrigTag->begin();
          leftindex[1] = boundsleft.second - FEB[56].GTrigTag->begin();
                 
          auto boundsright=std::equal_range (FEB[57].GTrigTag->begin(), FEB[57].GTrigTag->end(), GTrigTagCoins[index]);
          rightindex[0] = boundsright.first - FEB[57].GTrigTag->begin();
          rightindex[1] = boundsright.second - FEB[57].GTrigTag->begin();
                 
          auto boundstop = std::equal_range (FEB[58].GTrigTag->begin(), FEB[58].GTrigTag->end(), GTrigTagCoins[index]);
          topindex[0] = boundstop.first - FEB[58].GTrigTag->begin();
          topindex[1] = boundstop.second - FEB[58].GTrigTag->begin();
          
          if ( rightindex[0] != rightindex[1] && leftindex[0] != leftindex[1] && topindex[0]!=topindex[1])
              for (Int_t CoinsLeft = leftindex[0]; CoinsLeft < leftindex[1]; CoinsLeft++){
                          for (Int_t CoinsRight = rightindex[0]; CoinsRight < rightindex[1]; CoinsRight++){
                              if (abs(FEB[56].hitLeadTime->at(CoinsLeft) - FEB[57].hitLeadTime->at(CoinsRight))< 40){
                              if (FEB[56].hitsChannel->at(CoinsLeft) == FEB[57].hitsChannel->at(CoinsRight)){
                                  if (FEB[56].hitAmpl->at(CoinsLeft) > 400 && FEB[57].hitAmpl->at(CoinsRight)>400) {
                                      for (Int_t CoinsTop = topindex[0]; CoinsTop< topindex[1]; CoinsTop++){
                                          for (Int_t CoinsTop2 = CoinsTop; CoinsTop2 < topindex[1]; CoinsTop2++) {
                                                if (FEB[58].hitsChannel->at(CoinsTop) == FEB[58].hitsChannel->at(CoinsTop2)-1) {
                                                    if (FEB[58].hitAmpl->at(CoinsTop) > 300) {
                                                        if (abs(FEB[56].hitLeadTime->at(CoinsLeft) - FEB[58].hitLeadTime->at(CoinsTop))< 40){
                                                        if ( (int)(FEB[58].hitsChannel->at(CoinsTop)) % 2 == 0){
                                                            BeamProf->Fill((FEB[58].hitsChannel->at(CoinsTop)-64)/2,FEB[56].hitsChannel->at(CoinsLeft),1);
                                                            numberevents++;
                                                        }
                                                        }
                                                    }
                                                }
                                            }
                                      }
                                  }
                              }
                          }
                        }
              }
                          
          
     }
         
     cout<< numberevents<<endl;
    BeamProf->Write();
    return 0;
}
