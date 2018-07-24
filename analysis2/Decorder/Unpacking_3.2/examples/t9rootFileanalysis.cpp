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
#include <algorithm>


using namespace std;




double min(double x, double y)
{
    if ( x < y ) {
        return x;
    } else {
        return y;
    }
}

string GetLocation(string str)
{
     
    int i = str.rfind("_Slot_");
    string way = str.substr(0,i);  
    return way;
}

struct vectorsTree
{
  vector<double> *FEBSN;
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
    int NumberOfEB=65;
    int NumberOfMod = 18;
    int NumberofEventsMonitor = 1000;
    int firstModule = 1;
    
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
    rootFileOutput+="_histo.root";
    cout << rootFileInput<<endl;
    
    TFile *FileInput = new TFile(rootFileInput.c_str());
    
    vectorsTree FEB[NumberOfEB];
    
    for (Int_t i=0;i<NumberOfEB;i++){
        FEB[i].FEBSN=0;
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
    
    //data check
    /*for (Int_t i=0; i<300; i++)
      {
          //std::cout<<"FEB1: "<<FEB[1].FEBSN->at(i)<<" "<<FEB[1].GTrigTag->at(i)<<" "<<FEB[1].GTrigTime->at(i)<<" "<<FEB[1].hitsChannel->at(i)<<" "<<FEB[1].hitAmpl->at(i)<<" "<<FEB[1].hitLGAmpl->at(i)<<" "<<FEB[1].hitLeadTime->at(i)<<" "<<std::endl;
          std::cout<<"FEB27: "<<FEB[27].FEBSN->at(i)<<" "<<FEB[27].GTrigTag->at(i)<<" "<<FEB[27].GTrigTime->at(i)<<" "<<FEB[27].hitsChannel->at(i)<<" "<<FEB[27].hitAmpl->at(i)<<" "<<FEB[27].hitLGAmpl->at(i)<<" "<<FEB[27].hitLeadTime->at(i)<<" "
          <<FEB[27].hitTrailTime->at(i)<<std::endl<<std::endl;
      }*/
      
      //cout<< FEB[9].GTrigTag->find(771)<<" "<<endl;

   ifstream fmap("B2-connection.map");
   int MapCon[5][19];
   int temp=firstModule;
    while (!fmap.eof()) {
        fmap >> MapCon[0][temp] >> MapCon[1][temp] >>MapCon[2][temp] >>MapCon[3][temp] >>MapCon[4][temp] ;
        //cout<<MapCon[0][temp]<<" "<<MapCon[1][temp]<<" "<<MapCon[2][temp]<<" "<<MapCon[3][temp]<<" "<<MapCon[4][temp]<<endl;
        temp++;
    }
    fmap.close();
    
    ifstream horizontalgeometry("v1_horizontal_from_center.txt");
    double geomHor[5][95];
    temp = 0;
    while (!horizontalgeometry.eof()){
        horizontalgeometry >> geomHor[0][temp] >> geomHor[1][temp] >> geomHor[2][temp] >> geomHor[3][temp] >> geomHor[4][temp] ;
        //cout << geomHor[0][temp]<<" " << geomHor[1][temp]<<" " << geomHor[2][temp]<<" " << geomHor[3][temp]<<" " << geomHor[4][temp] << endl;
        temp++;
    }
    horizontalgeometry.close();
    
     ifstream verticalgeometry("v1_vertical_from_center.txt");
    double geomVer[5][32];
    temp = 0;
    while (!verticalgeometry.eof()){
        verticalgeometry >> geomVer[0][temp] >> geomVer[1][temp] >> geomVer[2][temp] >> geomVer[3][temp] >> geomVer[4][temp] ;
        //cout << geomVer[0][temp]<<" " << geomVer[1][temp]<<" " << geomVer[2][temp]<<" " << geomVer[3][temp]<<" " << geomVer[4][temp] << endl;
        temp++;
    }
    verticalgeometry.close();
    
    
    ifstream ScinModPos("B2_Scin_Mod_position.txt");
    double ModPos[4][19];
    temp = firstModule;
    while(!ScinModPos.eof()){
        ScinModPos >> ModPos[0][temp] >> ModPos[1][temp] >> ModPos[2][temp] >> ModPos[3][temp];
        //cout << ModPos[0][temp] <<" " << ModPos[1][temp] <<" " << ModPos[2][temp] <<" " << ModPos[3][temp] << endl;
        temp++;
    }
    
     cout << rootFileOutput<<endl;
     TFile wfile(rootFileOutput.c_str(), "recreate");
     TDirectory *BeamProfMod = wfile.mkdir("BeamProfMod");
     TDirectory *eventsD = wfile.mkdir("eventsDispHor");
     TDirectory *eventsTime = wfile.mkdir("eventsDispTime");
     TDirectory *events3D = wfile.mkdir("events3D");
     
     
//      modules->cd();
     TH2F *BeamProf[NumberOfMod];
     ostringstream sModnum;
     string sMod;
     for (Int_t ih=1; ih <= NumberOfMod;ih++){
        sModnum.str("");
        sModnum << ih;
        sMod = "Module_d"+sModnum.str();
        BeamProf[ih]=new TH2F(sMod.c_str(),sMod.c_str(),  16, -1420.5, 1420.5, 95, -986.2, 986.2);
     }
     
     Int_t numberevents = 0;
     vector <double> GTrigTagCoins;
     GTrigTagCoins.clear();
     
     Int_t verticcheck = 1;
     
     
     for (Int_t i =0; i < (FEB[MapCon[3][verticcheck]].GTrigTag->size() - 5); i++){
        if (FEB[MapCon[3][verticcheck]].GTrigTag->at(i) == FEB[MapCon[3][verticcheck]].GTrigTag->at(i+4)) {
            GTrigTagCoins.push_back(FEB[MapCon[3][verticcheck]].GTrigTag->at(i));
            numberevents++;
        }
     }
     
     cout << numberevents<<" "<< GTrigTagCoins.size()<<" "<<GTrigTagCoins[0]<<" "<<GTrigTagCoins.back()<<endl;
     auto last = std::unique(GTrigTagCoins.begin(),GTrigTagCoins.end());
     GTrigTagCoins.erase(last, GTrigTagCoins.end()); 
     cout << numberevents<<" "<< GTrigTagCoins.size()<<" "<<GTrigTagCoins[0]<<" "<<GTrigTagCoins.back()<<endl;
     
     NumberofEventsMonitor = min (NumberofEventsMonitor,GTrigTagCoins.size());
     
     TH2F *EventsMap = new TH2F("All_events_map","All_events_map",  103, -60, 4064, 95, -986.2, 986.2);
     TH3D *EventsMap3D = new TH3D ("All_events_map_3D","All_events_map_3D", 103, -60, 4064, 16, -1420.5, 1420.5, 95,  -986.2, 986.2);
     //Int_t EvPerGT =20;
     
     TH2F *SingleEvent[NumberofEventsMonitor];
     TH1F *SingleEventTime[NumberofEventsMonitor];
     TH3F *SingleEvent3D[NumberofEventsMonitor];
     ostringstream sEventnum;
     string sEvent;
     for (Int_t ih=0; ih < NumberofEventsMonitor;ih++){
        sEventnum.str("");
        sEventnum << ih;
        sEvent = "Event_"+sEventnum.str();
        SingleEvent[ih] = new TH2F(sEvent.c_str(),sEvent.c_str(),  103, -60, 4064, 95, -986.2, 986.2);
        SingleEventTime[ih] = new TH1F((sEvent + "_Time_in_2.5ns").c_str(),(sEvent + "_Time_in_2.5ns").c_str(), 4096, 0, 4096);
        
        SingleEvent3D[ih] = new TH3F((sEvent +"_3D").c_str(),(sEvent+"_3D").c_str(),  103, -60, 4064, 16, -1420.5, 1420.5, 95,  -986.2, 986.2);
     }
     
     
   
     Int_t leftindex[2]={0,0};
     Int_t rightindex[2]={0,0};
     Int_t topindex[2]={0,0};
     Int_t eventNumber=0;
     
     for (Int_t index=0; index <= GTrigTagCoins.size(); index++) {
         for (Int_t mod = 1; mod<=NumberOfMod;mod++){
             
               
                 /*auto bounds=std::equal_range (FEB[MapCon[1][mod]].GTrigTag->begin(), FEB[MapCon[1][mod]].GTrigTag->end(), GTrigTagCoins[index]);
                 std::cout << "bounds at positions " << (bounds.first - FEB[MapCon[1][mod]].GTrigTag->begin());
                 std::cout << " and " << (bounds.second - FEB[MapCon[1][mod]].GTrigTag->begin()) << '\n';
                 leftindex[0] = bounds.first - FEB[MapCon[1][mod]].GTrigTag->begin();
                 leftindex[1] = bounds.second - FEB[MapCon[1][mod]].GTrigTag->begin();
                 std::cout << FEB[MapCon[1][mod]].GTrigTag->at(leftindex[0])<<" "<< FEB[MapCon[1][mod]].GTrigTag->at(leftindex[1]-1)<<endl;
                 
                  bounds=std::equal_range (FEB[MapCon[2][mod]].GTrigTag->begin(), FEB[MapCon[2][mod]].GTrigTag->end(), GTrigTagCoins[index]);
                  rightindex[0] = bounds.first - FEB[MapCon[2][mod]].GTrigTag->begin();
                  rightindex[1] = bounds.second - FEB[MapCon[2][mod]].GTrigTag->begin();
                  std::cout << "bounds at positions " << (bounds.first - FEB[MapCon[2][mod]].GTrigTag->begin());
                  std::cout << " and " << (bounds.second - FEB[MapCon[2][mod]].GTrigTag->begin()) << '\n';
                   std::cout << FEB[MapCon[2][mod]].GTrigTag->at(rightindex[0])<<" "<< FEB[MapCon[2][mod]].GTrigTag->at(rightindex[1]-1)<<endl;*/
                 
                 auto boundsleft=std::equal_range (FEB[MapCon[1][mod]].GTrigTag->begin(), FEB[MapCon[1][mod]].GTrigTag->end(), GTrigTagCoins[index]);
                 leftindex[0] = boundsleft.first - FEB[MapCon[1][mod]].GTrigTag->begin();
                 leftindex[1] = boundsleft.second - FEB[MapCon[1][mod]].GTrigTag->begin();
                 
                 auto boundsright=std::equal_range (FEB[MapCon[2][mod]].GTrigTag->begin(), FEB[MapCon[2][mod]].GTrigTag->end(), GTrigTagCoins[index]);
                 rightindex[0] = boundsright.first - FEB[MapCon[2][mod]].GTrigTag->begin();
                 rightindex[1] = boundsright.second - FEB[MapCon[2][mod]].GTrigTag->begin();
                 
                 auto boundstop = std::equal_range (FEB[MapCon[3][mod]].GTrigTag->begin(), FEB[MapCon[3][mod]].GTrigTag->end(), GTrigTagCoins[index]);
                 topindex[0] = boundstop.first - FEB[MapCon[3][mod]].GTrigTag->begin();
                 topindex[1] = boundstop.second - FEB[MapCon[3][mod]].GTrigTag->begin();
                 
                  if (leftindex[0]>0 && rightindex[0]>0){
                        for (Int_t CoinsLeft = leftindex[0]; CoinsLeft < leftindex[1]; CoinsLeft++){
                          for (Int_t CoinsRight = rightindex[0]; CoinsRight < rightindex[1]; CoinsRight++){
                              if (FEB[MapCon[1][mod]].hitsChannel->at(CoinsLeft) == FEB[MapCon[2][mod]].hitsChannel->at(CoinsRight)){
                                  if (FEB[MapCon[1][mod]].hitAmpl->at(CoinsLeft) > 500 && FEB[MapCon[2][mod]].hitAmpl->at(CoinsRight)>500) {
                                      
                                      
                                      if (eventNumber<NumberofEventsMonitor){
                                        SingleEvent[eventNumber]->Fill(ModPos[3][mod],geomHor[4][(int)FEB[MapCon[2][mod]].hitsChannel->at(CoinsRight)],1) ; 
                                        
                                        SingleEventTime[eventNumber] -> Fill(FEB[MapCon[1][mod]].hitLeadTime->at(CoinsLeft));
                                        SingleEventTime[eventNumber] -> Fill(FEB[MapCon[2][mod]].hitLeadTime->at(CoinsRight));
                                        for (Int_t CoinsTop = topindex[0]; CoinsTop < topindex[1]; CoinsTop++){
                                            for (Int_t CoinsTop2 = CoinsTop; CoinsTop2 < topindex[1]; CoinsTop2++) {
                                                if ((int)(FEB[MapCon[3][mod]].hitsChannel->at(CoinsTop2)) == (int)(FEB[MapCon[3][mod]].hitsChannel->at(CoinsTop))){
                                                    if (FEB[MapCon[3][mod]].hitsChannel->at(CoinsTop)>=32*MapCon[4][mod] && FEB[MapCon[3][mod]].hitsChannel->at(CoinsTop)<32*(1+MapCon[4][mod])){
                                                        if (FEB[MapCon[3][mod]].hitAmpl->at(CoinsTop) > 200){
                                                            SingleEventTime[eventNumber] -> Fill(FEB[MapCon[3][mod]].hitLeadTime->at(CoinsTop));
                                                            // BeamProf[mod]->Fill(geomVer[4][(int)(FEB[MapCon[3][mod]].hitsChannel->at(CoinsTop))%32],geomHor[4][(int)FEB[MapCon[2][mod]].hitsChannel->at(CoinsRight)],1);
                                                            if(mod == 2 || mod == 4 || mod == 14 || mod == 16 || mod == 18){
                                                                SingleEvent3D[eventNumber]->Fill(ModPos[3][mod],-geomVer[4][(int)(FEB[MapCon[3][mod]].hitsChannel->at(CoinsTop))%32],geomHor[4][(int)FEB[MapCon[2][mod]].hitsChannel->at(CoinsRight)],1);
                                                            }
                                                            else{
                                                                SingleEvent3D[eventNumber]->Fill(ModPos[3][mod],geomVer[4][(int)(FEB[MapCon[3][mod]].hitsChannel->at(CoinsTop))%32],geomHor[4][(int)FEB[MapCon[2][mod]].hitsChannel->at(CoinsRight)],1);
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                      }
                                      
                                      EventsMap->Fill(ModPos[3][mod],geomHor[4][(int)FEB[MapCon[2][mod]].hitsChannel->at(CoinsRight)],1);
                                      
                                      
                                      for (Int_t CoinsTop = topindex[0]; CoinsTop < topindex[1]; CoinsTop++){
                                           for (Int_t CoinsTop2 = CoinsTop; CoinsTop2 < topindex[1]; CoinsTop2++) {
                                                if (FEB[MapCon[3][mod]].hitsChannel->at(CoinsTop)>=32*MapCon[4][mod] && FEB[MapCon[3][mod]].hitsChannel->at(CoinsTop)<32*(1+MapCon[4][mod])){
                                                    if (FEB[MapCon[3][mod]].hitAmpl->at(CoinsTop) > 200){
                                                        if(mod == 2 || mod == 4 || mod == 14 || mod == 16 || mod == 18){
                                                            BeamProf[mod]->Fill(-geomVer[4][(int)(FEB[MapCon[3][mod]].hitsChannel->at(CoinsTop))%32],geomHor[4][(int)FEB[MapCon[2][mod]].hitsChannel->at(CoinsRight)],1);
                                                            EventsMap3D->Fill(ModPos[3][mod],-geomVer[4][(int)(FEB[MapCon[3][mod]].hitsChannel->at(CoinsTop))%32],geomHor[4][(int)FEB[MapCon[2][mod]].hitsChannel->at(CoinsRight)],1);
                                                        }
                                                        else{
                                                            BeamProf[mod]->Fill(geomVer[4][(int)(FEB[MapCon[3][mod]].hitsChannel->at(CoinsTop))%32],geomHor[4][(int)FEB[MapCon[2][mod]].hitsChannel->at(CoinsRight)],1);
                                                            EventsMap3D->Fill(ModPos[3][mod],geomVer[4][(int)(FEB[MapCon[3][mod]].hitsChannel->at(CoinsTop))%32],geomHor[4][(int)FEB[MapCon[2][mod]].hitsChannel->at(CoinsRight)],1);
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
                      
                //return 0;
           
         }
         eventNumber++;
     }
      
      //auto it = std::adjacent_find(FEB[9].GTrigTime->cbegin(), FEB[9].GTrigTime->cend());
 
      //if(it != FEB[9].GTrigTime->cend())
      //std::cout << *it << " found at index "<< std::distance(FEB[9].GTrigTime->cbegin(), it);*/

     EventsMap->GetYaxis()->SetTitle("Y [mm]");
     EventsMap->GetXaxis()->SetTitle("Z [mm]");           
     EventsMap->Write();
     
     EventsMap3D->GetYaxis()->SetTitle("X position [mm]");
     EventsMap3D->GetXaxis()->SetTitle("Z position [mm]");  
     EventsMap3D->GetZaxis()->SetTitle("Y position [mm]");  
     EventsMap3D->Write();
     
     eventsD->cd();
     for (Int_t ih=0; ih < NumberofEventsMonitor;ih++){
         if (SingleEvent[ih]->GetEntries()>1) {
            SingleEvent[ih]->GetYaxis()->SetTitle("vertical position [mm]");
            SingleEvent[ih]->GetXaxis()->SetTitle("horizontal position [mm]");
            SingleEvent[ih]->Write();
         }
     }
     
     events3D->cd();
     for (Int_t ih=0; ih < NumberofEventsMonitor;ih++){
         if (SingleEvent[ih]->GetEntries()>1) {
            SingleEvent3D[ih]->GetYaxis()->SetTitle("X position [mm]");
            SingleEvent3D[ih]->GetXaxis()->SetTitle("Z position [mm]");  
            SingleEvent3D[ih]->GetZaxis()->SetTitle("Y position [mm]");  
            SingleEvent3D[ih]->Write();
         }
         delete SingleEvent3D[ih];
         
     }
     
     eventsTime->cd();
     
     for (Int_t ih=0; ih < NumberofEventsMonitor;ih++){
         if (SingleEvent[ih]->GetEntries()>1) {
            SingleEventTime[ih]->GetYaxis()->SetTitle("Number of events");
            SingleEventTime[ih]->GetXaxis()->SetTitle("Hit time [2.5ns]");
            SingleEventTime[ih]->Write();
         }
        delete SingleEvent[ih];
        delete SingleEventTime[ih];
     }
     
     
     BeamProfMod->cd(); 
    for (Int_t ih=1; ih <= NumberOfMod;ih++){
        BeamProf[ih]->GetYaxis()->SetTitle("Y position [mm]");
        BeamProf[ih]->GetXaxis()->SetTitle("X position [mm]");
        BeamProf[ih]->Write();
        delete BeamProf[ih];
    }
    ////////////////////
    
       
    
      
    for (Int_t i=0;i<NumberOfEB;i++){
        //FEBtree[i]->Delete();
        FEB[i].FEBSN=0;
        FEB[i].hitsChannel=0;
        FEB[i].hitAmpl=0;
        FEB[i].hitLeadTime=0;
        FEB[i].GTrigTag=0;
        FEB[i].GTrigTime=0;
        FEB[i].hitLGAmpl=0;
        FEB[i].hitTrailTime=0;
        FEB[i].hitTimeDif=0;
        
    }
    
    
    GTrigTagCoins.clear();
    wfile.Close();
    FileInput->Close();
    vFileNames.clear();
    fList.close();
    return 0;
}
