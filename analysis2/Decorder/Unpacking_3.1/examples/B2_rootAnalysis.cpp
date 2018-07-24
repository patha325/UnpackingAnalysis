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
#include "TCanvas.h"
#include "TImage.h"
#include "TGraph.h"
#include "TF1.h"
#include "TFitResult.h"

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

struct eventvectorsTree
{
    vector<double> *GTrigTag;
    vector<double> *GTrigTime;
    
    vector<double> *hitEventNo;
    vector<double> *module;
    vector<double> *posX;
    vector<double> *posY;
    vector<double> *posZ;
    vector<double> *RsignalChannel;
    vector<double> *LsignalChannel;
    vector<double> *TsignalChannel;
    vector<double> *RsignalHGAmpl;
    vector<double> *LsignalHGAmpl;
    vector<double> *TsignalHGAmpl;
    vector<double> *RsignalLGAmpl;
    vector<double> *LsignalLGAmpl;
    vector<double> *TsignalLGAmpl;
    vector<double> *RsignalLeadTime;
    vector<double> *LsignalLeadTime;
    vector<double> *TsignalLeadTime;
    vector<double> *RsignalTrailTime;
    vector<double> *LsignalTrailTime;
    vector<double> *TsignalTrailTime;
    vector<double> *RsignalTimeDif;
    vector<double> *LsignalTimeDif;
    vector<double> *TsignalTimeDif;
    
    vector<double> *EventNo;
    vector<double> *EventHitsNo;
    vector<double> *Event_NoModBeenHit;
    vector<double> *Event_LastModule;
    vector<double> *Event_Mom_Range;
    
    vector<double> *B1Occupancy;
    vector<double> *B2Occupancy;
    vector<double> *B3Occupancy;
    vector<double> *B4Occupancy;
    vector<double> *B5Occupancy;
    vector<double> *B6Occupancy;
    vector<double> *B7Occupancy;
    vector<double> *B8Occupancy;
    vector<double> *B9Occupancy;
    vector<double> *B10Occupancy;
    vector<double> *B11Occupancy;
    vector<double> *B12Occupancy;
    vector<double> *B13Occupancy;
    vector<double> *B14Occupancy;
    vector<double> *B15Occupancy;
    vector<double> *B16Occupancy;
    vector<double> *B17Occupancy;
    vector<double> *B18Occupancy;
};


int main ()
{
    int NumberOfEB=65;
    int NumberOfMod = 18;
    int NumberofEventsMonitor = 10000;
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
    string plotsFolder=GetLocation (vFileNames[0].c_str());
    plotsFolder+="_plots/";
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
    
    ifstream Momentum_range("Mom_Range.txt");
    double mom_range[2][19];
    temp =0;
    while (! Momentum_range.eof()){
        Momentum_range >> mom_range[0][temp] >> mom_range[1][temp];
        //cout << mom_range[0][temp] <<" " << mom_range[1][temp] << endl;
        temp++;
    }
    Momentum_range.close();
    
    cout << rootFileOutput<<endl;
    TFile wfile(rootFileOutput.c_str(), "recreate");
    TDirectory *BeamProfMod = wfile.mkdir("BeamProfMod");
    TDirectory *eventsD = wfile.mkdir("eventsDispHor");
    TDirectory *eventsTime = wfile.mkdir("eventsDispTime");
    TDirectory *events3D = wfile.mkdir("events3D");
    TDirectory *graphs = wfile.mkdir("graphs");
    
    //      modules->cd();
    TH2F *BeamProf[NumberOfMod];
    ostringstream sModnum;
    string sMod;
    for (Int_t ih=1; ih <= NumberOfMod;ih++){
        sModnum.str("");
        sModnum << ih;
        sMod = "Module_d"+sModnum.str();
        BeamProf[ih]=new TH2F(sMod.c_str(),sMod.c_str(),  31, -1420.5, 1420.5, 95, -986.2, 986.2);
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
    
    TH2F *EventsMap = new TH2F("All_events_map","All_events_map",  118, -201, 4520, 95, -986.2, 986.2);
    TH3D *EventsMap3D = new TH3D ("All_events_map_3D","All_events_map_3D", 118, -201, 4520, 31, -1420.5, 1420.5, 95,  -986.2, 986.2);
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
        SingleEvent[ih] = new TH2F(sEvent.c_str(),sEvent.c_str(),  118, -201, 4520, 95, -986.2, 986.2);
        SingleEventTime[ih] = new TH1F((sEvent + "_Time_in_2.5ns").c_str(),(sEvent + "_Time_in_2.5ns").c_str(), 4096, 0, 4096);
        
        SingleEvent3D[ih] = new TH3F((sEvent +"_3D").c_str(),(sEvent+"_3D").c_str(),  118, -201, 4520, 31, -1420.5, 1420.5, 95,  -986.2, 986.2);
    }
    
    
    
    Int_t leftindex[2]={0,0};
    Int_t rightindex[2]={0,0};
    Int_t topindex[2]={0,0};
    Int_t eventNumber=0;
    
    eventvectorsTree eventVec;
    
    eventVec.GTrigTag=0;
    eventVec.GTrigTime=0;
    
    eventVec.hitEventNo=0;
    eventVec.module=0;
    eventVec.posX=0;
    eventVec.posY=0;
    eventVec.posZ=0;
    eventVec.RsignalChannel=0;
    eventVec.LsignalChannel=0;
    eventVec.TsignalChannel=0;
    eventVec.RsignalHGAmpl=0;
    eventVec.LsignalHGAmpl=0;
    eventVec.TsignalHGAmpl=0;
    eventVec.RsignalLeadTime=0;
    eventVec.LsignalLeadTime=0;
    eventVec.TsignalLeadTime=0;
    eventVec.RsignalLGAmpl=0;
    eventVec.LsignalLGAmpl=0;
    eventVec.TsignalLGAmpl=0;
    eventVec.RsignalTrailTime=0;
    eventVec.LsignalTrailTime=0;
    eventVec.TsignalTrailTime=0;
    eventVec.RsignalTimeDif=0;
    eventVec.LsignalTimeDif=0;
    eventVec.TsignalTimeDif=0;
    
    eventVec.EventNo=0;
    eventVec.EventHitsNo=0;
    eventVec.Event_NoModBeenHit=0;
    eventVec.Event_LastModule=0;
    eventVec.Event_Mom_Range=0;
    
    eventVec.B1Occupancy=0;
    eventVec.B2Occupancy=0;
    eventVec.B3Occupancy=0;
    eventVec.B4Occupancy=0;
    eventVec.B5Occupancy=0;
    eventVec.B6Occupancy=0;
    eventVec.B7Occupancy=0;
    eventVec.B8Occupancy=0;
    eventVec.B9Occupancy=0;
    eventVec.B10Occupancy=0;
    eventVec.B11Occupancy=0;
    eventVec.B12Occupancy=0;
    eventVec.B13Occupancy=0;
    eventVec.B14Occupancy=0;
    eventVec.B15Occupancy=0;
    eventVec.B16Occupancy=0;
    eventVec.B17Occupancy=0;
    eventVec.B18Occupancy=0;
    
    
    TTree *events;
    events = new TTree("events","a tree of hits");
    
    events->Branch("_GTrigTag",&eventVec.GTrigTag);
    events->Branch("_GTrigTime",&eventVec.GTrigTime);
    events->Branch("_hitEventNo",&eventVec.hitEventNo);
    events->Branch("_mod",&eventVec.module);
    
    
    events->Branch("_posX",&eventVec.posX);
    events->Branch("_posY",&eventVec.posY);
    events->Branch("_posZ",&eventVec.posZ);
    events->Branch("_RsignalChannel",&eventVec.RsignalChannel);
    events->Branch("_LsignalChannel",&eventVec.LsignalChannel);
    events->Branch("_TsignalChannel",&eventVec.TsignalChannel);
    events->Branch("_RsignalHGAmpl",&eventVec.RsignalHGAmpl);
    events->Branch("_LsignalHGAmpl",&eventVec.LsignalHGAmpl);
    events->Branch("_TsignalHGAmpl",&eventVec.TsignalHGAmpl);
    events->Branch("_RsignalLeadTime",&eventVec.RsignalLeadTime);
    events->Branch("_LsignalLeadTime",&eventVec.LsignalLeadTime);
    events->Branch("_TsignalLeadTime",&eventVec.TsignalLeadTime);
    events->Branch("_RsignalLGAmpl",&eventVec.RsignalLGAmpl);
    events->Branch("_LsignalLGAmpl",&eventVec.LsignalLGAmpl);
    events->Branch("_TsignalLGAmpl",&eventVec.TsignalLGAmpl);
    events->Branch("_RsignalTrailTime",&eventVec.RsignalTrailTime);
    events->Branch("_LsignalTrailTime",&eventVec.LsignalTrailTime);
    events->Branch("_TsignalTrailTime",&eventVec.TsignalTrailTime);
    events->Branch("_RsignalTimeDif",&eventVec.RsignalTimeDif);
    events->Branch("_LsignalTimeDif",&eventVec.LsignalTimeDif);
    events->Branch("_TsignalTimeDif",&eventVec.TsignalTimeDif);
    
    events->Branch("_EventNo",&eventVec.EventNo);
    events->Branch("_EventHitsNo",&eventVec.EventHitsNo);
    events->Branch("_Event_NoModBeenHit",&eventVec.Event_NoModBeenHit);
    events->Branch("_Event_LastModule",&eventVec.Event_LastModule);
    events->Branch("_Event_Mom_Range",&eventVec.Event_Mom_Range);
    
    events->Branch("_B1_Occupancy",&eventVec.B1Occupancy);
    events->Branch("_B2_Occupancy",&eventVec.B2Occupancy);
    events->Branch("_B3_Occupancy",&eventVec.B3Occupancy);
    events->Branch("_B4_Occupancy",&eventVec.B4Occupancy);
    events->Branch("_B5_Occupancy",&eventVec.B5Occupancy);
    events->Branch("_B6_Occupancy",&eventVec.B6Occupancy);
    events->Branch("_B7_Occupancy",&eventVec.B7Occupancy);
    events->Branch("_B8_Occupancy",&eventVec.B8Occupancy);
    events->Branch("_B9_Occupancy",&eventVec.B9Occupancy);
    events->Branch("_B10_Occupancy",&eventVec.B10Occupancy);
    events->Branch("_B11_Occupancy",&eventVec.B11Occupancy);
    events->Branch("_B12_Occupancy",&eventVec.B12Occupancy);
    events->Branch("_B13_Occupancy",&eventVec.B13Occupancy);
    events->Branch("_B14_Occupancy",&eventVec.B14Occupancy);
    events->Branch("_B15_Occupancy",&eventVec.B15Occupancy);
    events->Branch("_B16_Occupancy",&eventVec.B16Occupancy);
    events->Branch("_B17_Occupancy",&eventVec.B17Occupancy);
    events->Branch("_B18_Occupancy",&eventVec.B18Occupancy);
    
    Int_t nhit =0;
    Int_t eventHits=0;
    Int_t Occupancy[19] = {0};
    Int_t ModBeenHit =0;
    Int_t LastMod =0;
    
   
    vector <double> X_event[GTrigTagCoins.size()];
    vector <double> Y_event[GTrigTagCoins.size()];
    vector <double> Z_event[GTrigTagCoins.size()];
    
    
    bool mergeH =false;
    bool mergeV = false;
    
    Int_t mergeVindex = 0;
    Int_t t1_index = 0;
    Int_t t2_index = 0;
    Int_t t3_index = 0;
    Int_t t4_index = 0;
    double mergeXpos;
    
    Int_t r2_index =0;
    Int_t l2_index =0;
    double mergeYpos =0;
    
    Int_t Track_number = 0;
    double Track_time =0;
    
    for (Int_t index=0; index < GTrigTagCoins.size(); index++) {
        
        //initiallizing counters inside one event
        eventHits =0;
        ModBeenHit =0;
        LastMod =0;
        for (Int_t o=0; o<19; o++){
            Occupancy[o]=0;
        }
        cout<<"Event Number: "<<eventNumber <<endl;
        cout<<"Track Number: "<<Track_number <<endl;
        
        //loop all modules
        for (Int_t mod = 1; mod<=NumberOfMod;mod++){
            nhit = 0; //initiallize hit counter for each module
            
            //cout<<"mod : "<<mod<<endl;
            //if (mod == 11) mod++;
                //cout<<"mod 11 skipped"<<endl;
            
            auto boundsleft=std::equal_range (FEB[MapCon[1][mod]].GTrigTag->begin(), FEB[MapCon[1][mod]].GTrigTag->end(), GTrigTagCoins[index]);
            leftindex[0] = boundsleft.first - FEB[MapCon[1][mod]].GTrigTag->begin();
            leftindex[1] = boundsleft.second - FEB[MapCon[1][mod]].GTrigTag->begin();
            
            auto boundsright=std::equal_range (FEB[MapCon[2][mod]].GTrigTag->begin(), FEB[MapCon[2][mod]].GTrigTag->end(), GTrigTagCoins[index]);
            rightindex[0] = boundsright.first - FEB[MapCon[2][mod]].GTrigTag->begin();
            rightindex[1] = boundsright.second - FEB[MapCon[2][mod]].GTrigTag->begin();
            
            auto boundstop = std::equal_range (FEB[MapCon[3][mod]].GTrigTag->begin(), FEB[MapCon[3][mod]].GTrigTag->end(), GTrigTagCoins[index]);
            topindex[0] = boundstop.first - FEB[MapCon[3][mod]].GTrigTag->begin();
            topindex[1] = boundstop.second - FEB[MapCon[3][mod]].GTrigTag->begin();
            
            if (leftindex[0]>0 && rightindex[0]>0 && topindex[0]>0){ //check there is at least one left, right, top hit in this tag and module
                for (Int_t CoinsLeft = leftindex[0]; CoinsLeft < leftindex[1]; CoinsLeft++){
                    mergeH = false;
                    l2_index = 0;
                    for (Int_t CoinsRight = rightindex[0]; CoinsRight < rightindex[1]; CoinsRight++){
                        r2_index=0;
                        
                        if (FEB[MapCon[1][mod]].hitsChannel->at(CoinsLeft) == FEB[MapCon[2][mod]].hitsChannel->at(CoinsRight) &&
                            std::abs (FEB[MapCon[2][mod]].hitLeadTime->at(CoinsRight) - FEB[MapCon[1][mod]].hitLeadTime->at(CoinsLeft))<3){
                            
                            for (Int_t CoinsLeft2 = CoinsLeft+1; CoinsLeft2 < leftindex[1]; CoinsLeft2++){
                                for (Int_t CoinsRight2 = CoinsRight+1; CoinsRight2 < rightindex[1]; CoinsRight2++){
                                    
                                    
                                    if (FEB[MapCon[1][mod]].hitsChannel->at(CoinsLeft2) == FEB[MapCon[2][mod]].hitsChannel->at(CoinsRight2) &&
                                        std::abs (FEB[MapCon[2][mod]].hitLeadTime->at(CoinsRight2) - FEB[MapCon[1][mod]].hitLeadTime->at(CoinsLeft2))<3 &&
                                        abs(FEB[MapCon[2][mod]].hitsChannel->at(CoinsRight) - FEB[MapCon[2][mod]].hitsChannel->at(CoinsRight2))==1 &&
                                        abs(FEB[MapCon[1][mod]].hitsChannel->at(CoinsLeft) - FEB[MapCon[1][mod]].hitsChannel->at(CoinsLeft2))==1){
                                        
                                        r2_index = CoinsRight2;
                                        l2_index = CoinsLeft2;
                                        
                                        mergeH = true;
                                        
                                        mergeYpos = (geomHor[4][(int)FEB[MapCon[2][mod]].hitsChannel->at(CoinsRight)]+geomHor[4][(int)FEB[MapCon[2][mod]].hitsChannel->at(CoinsRight2)])/2;
                                    
                                        cout<<"merge for Right ch:"<< FEB[MapCon[2][mod]].hitsChannel->at(CoinsRight)<<" and ch :"<<FEB[MapCon[2][mod]].hitsChannel->at(r2_index)<<endl;
                                        //cout<<"indexes: "<<CoinsRight <<" and "<< CoinsRight2<< endl;
                                        cout<<"merge for left ch:"<< FEB[MapCon[1][mod]].hitsChannel->at(CoinsLeft)<<" and ch :"<<FEB[MapCon[1][mod]].hitsChannel->at(l2_index)<<endl;
                                        //cout<<"indexes: "<<CoinsLeft <<" and "<< CoinsLeft2<< endl;
                                    }
                                }
                            }
                            if (mergeH == false){
                                mergeYpos = (geomHor[4][(int)FEB[MapCon[2][mod]].hitsChannel->at(CoinsRight)]);
                            }
                            
                            if (mod==1){
                                mergeYpos += 12;
                            }
                            
                            //top loop
                            for (Int_t CoinsTop = topindex[0]; CoinsTop < topindex[1]; CoinsTop++){
                                mergeV = false;
                                
                                if (FEB[MapCon[3][mod]].hitsChannel->at(CoinsTop)>=32*MapCon[4][mod] && FEB[MapCon[3][mod]].hitsChannel->at(CoinsTop)<32*(1+MapCon[4][mod]) &&    std::abs (FEB[MapCon[2][mod]].hitLeadTime->at(CoinsRight) - FEB[MapCon[3][mod]].hitLeadTime->at(CoinsTop)) < 3){ // Top Hit condition
                                    t1_index = CoinsTop;
                                    mergeVindex = 1000;
                                    t2_index = 0;
                                    t3_index = 0;
                                    t4_index = 0;
                                    for (Int_t CoinsTop2 = CoinsTop+1; CoinsTop2 < topindex[1]; CoinsTop2++){
                                        
                                        if (FEB[MapCon[3][mod]].hitsChannel->at(CoinsTop2)>=32*MapCon[4][mod] && FEB[MapCon[3][mod]].hitsChannel->at(CoinsTop)<32*(1+MapCon[4][mod])){
                                            if ( abs(FEB[MapCon[3][mod]].hitsChannel->at(CoinsTop) - FEB[MapCon[3][mod]].hitsChannel->at(CoinsTop2))==1 && std::abs (FEB[MapCon[2][mod]].hitLeadTime->at(CoinsRight) - FEB[MapCon[3][mod]].hitLeadTime->at(CoinsTop2)) < 3){
                                                //cout<<"merge top in module "<< mod <<endl;99
                                                mergeV = true;
                                                t2_index = CoinsTop2;
                                                mergeVindex += 100;
                                            }
                                            if (abs(FEB[MapCon[3][mod]].hitsChannel->at(CoinsTop) - FEB[MapCon[3][mod]].hitsChannel->at(CoinsTop2))==2 && std::abs (FEB[MapCon[2][mod]].hitLeadTime->at(CoinsRight) - FEB[MapCon[3][mod]].hitLeadTime->at(CoinsTop2)) < 3){
                                                mergeV = true;
                                                t3_index = CoinsTop2;
                                                mergeVindex += 10;
                                            }
                                            if (abs(FEB[MapCon[3][mod]].hitsChannel->at(CoinsTop) - FEB[MapCon[3][mod]].hitsChannel->at(CoinsTop2))==3 && std::abs (FEB[MapCon[2][mod]].hitLeadTime->at(CoinsRight) - FEB[MapCon[3][mod]].hitLeadTime->at(CoinsTop2)) < 3){
                                                mergeV = true;
                                                t4_index = CoinsTop2;
                                                mergeVindex += 1;
                                            }
                                        }
                                    }
                                    if (mergeV ==true) {
                                        cout<<"merge top"<<endl;
                                        //cout<<"mergeV index:"<<mergeVindex<<endl;
                                        cout<<"chs "<<FEB[MapCon[3][mod]].hitsChannel->at(t1_index)<<endl;
                                        if (t2_index !=0) cout<<"chs "<<FEB[MapCon[3][mod]].hitsChannel->at(t2_index)<<endl;
                                        if (t3_index !=0) cout<<"chs "<<FEB[MapCon[3][mod]].hitsChannel->at(t3_index)<<endl;
                                        if (t4_index !=0) cout<<"chs "<<FEB[MapCon[3][mod]].hitsChannel->at(t4_index)<<endl;
                                        
                                        if (mergeVindex == 1111) {
                                            mergeXpos = (geomVer[4][(int)(FEB[MapCon[3] [mod]].hitsChannel->at(t1_index))%32] +
                                                         geomVer[4][(int)(FEB[MapCon[3] [mod]].hitsChannel->at(t2_index))%32] +
                                                         geomVer[4][(int)(FEB[MapCon[3] [mod]].hitsChannel->at(t3_index))%32] +
                                                         geomVer[4][(int)(FEB[MapCon[3] [mod]].hitsChannel->at(t4_index))%32] )/4;
                                        }
                                        if (mergeVindex == 1110) {
                                            mergeXpos = (geomVer[4][(int)(FEB[MapCon[3] [mod]].hitsChannel->at(t1_index))%32] +
                                                         geomVer[4][(int)(FEB[MapCon[3] [mod]].hitsChannel->at(t3_index))%32] )/2;
                                        }
                                        if (mergeVindex == 1101) {
                                            mergeXpos = (geomVer[4][(int)(FEB[MapCon[3] [mod]].hitsChannel->at(t1_index))%32] +
                                                         geomVer[4][(int)(FEB[MapCon[3] [mod]].hitsChannel->at(t4_index))%32] )/2;
                                        }
                                        if (mergeVindex == 1011) {
                                            mergeXpos = (geomVer[4][(int)(FEB[MapCon[3] [mod]].hitsChannel->at(t1_index))%32] +
                                                         geomVer[4][(int)(FEB[MapCon[3] [mod]].hitsChannel->at(t4_index))%32] )/2;
                                        }
                                        if (mergeVindex == 1100) {
                                            mergeXpos = (geomVer[4][(int)(FEB[MapCon[3] [mod]].hitsChannel->at(t1_index))%32]);
                                        }
                                        if (mergeVindex == 1001) {
                                            mergeXpos = (geomVer[4][(int)(FEB[MapCon[3] [mod]].hitsChannel->at(t1_index))%32] +
                                                         geomVer[4][(int)(FEB[MapCon[3] [mod]].hitsChannel->at(t4_index))%32] )/2;
                                        }
                                        if (mergeVindex == 1010) {
                                            mergeXpos = (geomVer[4][(int)(FEB[MapCon[3] [mod]].hitsChannel->at(t1_index))%32] +
                                                         geomVer[4][(int)(FEB[MapCon[3] [mod]].hitsChannel->at(t3_index))%32] )/2;
                                        }
                                        
                                    }else{ // MergeV is false
                                        mergeXpos = geomVer[4][(int)(FEB[MapCon[3] [mod]].hitsChannel->at(t1_index))%32];
                                    }
                                    
                                    
                                    nhit ++;
                                    Occupancy[mod] ++;
                                    eventHits ++;
                                    
                                    //Fill the tree
                                    eventVec.GTrigTag->push_back(FEB[MapCon[2][mod]].GTrigTag->at(CoinsRight));
                                    eventVec.GTrigTime->push_back(FEB[MapCon[2][mod]].GTrigTime->at(CoinsRight));
                                    eventVec.hitEventNo->push_back(index);
                                    eventVec.module->push_back(mod);
                                    eventVec.RsignalChannel->push_back(FEB[MapCon[2][mod]].hitsChannel->at(CoinsRight));
                                    eventVec.LsignalChannel->push_back(FEB[MapCon[1][mod]].hitsChannel->at(CoinsLeft));
                                    eventVec.TsignalChannel->push_back(FEB[MapCon[3][mod]].hitsChannel->at(CoinsTop));
                                    eventVec.RsignalHGAmpl->push_back(FEB[MapCon[2][mod]].hitAmpl->at(CoinsRight));
                                    eventVec.LsignalHGAmpl->push_back(FEB[MapCon[1][mod]].hitAmpl->at(CoinsLeft));
                                    eventVec.TsignalHGAmpl->push_back(FEB[MapCon[3][mod]].hitAmpl->at(CoinsTop));
                                    eventVec.RsignalLeadTime->push_back(FEB[MapCon[2][mod]].hitLeadTime->at(CoinsRight));
                                    eventVec.LsignalLeadTime->push_back(FEB[MapCon[1][mod]].hitLeadTime->at(CoinsLeft));
                                    eventVec.TsignalLeadTime->push_back(FEB[MapCon[3][mod]].hitLeadTime->at(CoinsTop));
                                    eventVec.RsignalLGAmpl->push_back(FEB[MapCon[2][mod]].hitLGAmpl->at(CoinsRight));
                                    eventVec.LsignalLGAmpl->push_back(FEB[MapCon[1][mod]].hitLGAmpl->at(CoinsLeft));
                                    eventVec.TsignalLGAmpl->push_back(FEB[MapCon[3][mod]].hitLGAmpl->at(CoinsTop));
                                    eventVec.RsignalTrailTime->push_back(FEB[MapCon[2][mod]].hitTrailTime->at(CoinsRight));
                                    eventVec.LsignalTrailTime->push_back(FEB[MapCon[1][mod]].hitTrailTime->at(CoinsLeft));
                                    eventVec.TsignalTrailTime->push_back(FEB[MapCon[3][mod]].hitTrailTime->at(CoinsTop));
                                    eventVec.RsignalTimeDif->push_back(FEB[MapCon[2][mod]].hitTimeDif->at(CoinsRight));
                                    eventVec.LsignalTimeDif->push_back(FEB[MapCon[1][mod]].hitTimeDif->at(CoinsLeft));
                                    eventVec.TsignalTimeDif->push_back(FEB[MapCon[3][mod]].hitTimeDif->at(CoinsTop));
                                    
                                    eventVec.posY->push_back(mergeYpos);
                                    Y_event[index].push_back(mergeYpos);
                                    
                                    eventVec.posZ->push_back(ModPos[3][mod]);
                                    Z_event[index].push_back(ModPos[3][mod]);
                                    
                                    if(mod == 2 || mod == 11 || mod == 13 || mod == 17 || mod == 18){
                                        BeamProf[mod]->Fill(-mergeXpos,mergeYpos,1);
                                        EventsMap3D->Fill(ModPos[3][mod],-mergeXpos ,mergeYpos,1);
                                        eventVec.posX->push_back(-mergeXpos);
                                        X_event[index].push_back(-mergeXpos);
                                    }else{
                                        BeamProf[mod]->Fill(mergeXpos ,mergeYpos,1);
                                        EventsMap3D->Fill(ModPos[3][mod],mergeXpos ,mergeYpos,1);
                                        eventVec.posX->push_back(mergeXpos );
                                        X_event[index].push_back(mergeXpos);
                                    }
                                    
                                    EventsMap->Fill(ModPos[3][mod],mergeYpos,1);
                                    
                                    /////// plots 1000 displays
                                    if (eventNumber<NumberofEventsMonitor){
                                        
                                        SingleEvent[eventNumber]->Fill(ModPos[3][mod],mergeYpos,FEB[MapCon[2][mod]].hitLeadTime->at(CoinsRight)) ;
                                        
                                        SingleEventTime[eventNumber] -> Fill(FEB[MapCon[2][mod]].hitLeadTime->at(CoinsRight));
                                        
                                        if(mod == 2 || mod == 11 || mod == 13 || mod == 17 || mod == 18){
                                            SingleEvent3D[eventNumber]->Fill(ModPos[3][mod],-mergeXpos ,mergeYpos,1);
                                        }
                                        else{
                                            
                                            SingleEvent3D[eventNumber]->Fill(ModPos[3][mod],mergeXpos ,mergeYpos,1);
                                        }
                                        
                                    } ///end 1000 plots*/
                                    if (mergeV == true){
                                        if (t2_index !=0) CoinsTop = t2_index;
                                        if (t3_index !=0) CoinsTop = t3_index;
                                        if (t4_index !=0) CoinsTop = t4_index;
                                    }
                                    
                                } // end if top conditions
                            }//end top loop
                            if (mergeH == true){
                                CoinsRight = r2_index;
                                CoinsLeft = l2_index;
                            } // end if mergeH true
                            
                        }// end if left/right coincidence
                    } //end R loop
                } //end left loop
            } //end if R,L,T exist
            
        }//end module loop
        eventVec.B1Occupancy->push_back(Occupancy[1]);
        eventVec.B2Occupancy->push_back(Occupancy[2]);
        eventVec.B3Occupancy->push_back(Occupancy[3]);
        eventVec.B4Occupancy->push_back(Occupancy[4]);
        eventVec.B5Occupancy->push_back(Occupancy[5]);
        eventVec.B6Occupancy->push_back(Occupancy[6]);
        eventVec.B7Occupancy->push_back(Occupancy[7]);
        eventVec.B8Occupancy->push_back(Occupancy[8]);
        eventVec.B9Occupancy->push_back(Occupancy[9]);
        eventVec.B10Occupancy->push_back(Occupancy[10]);
        eventVec.B11Occupancy->push_back(Occupancy[11]);
        eventVec.B12Occupancy->push_back(Occupancy[12]);
        eventVec.B13Occupancy->push_back(Occupancy[13]);
        eventVec.B14Occupancy->push_back(Occupancy[14]);
        eventVec.B15Occupancy->push_back(Occupancy[15]);
        eventVec.B16Occupancy->push_back(Occupancy[16]);
        eventVec.B17Occupancy->push_back(Occupancy[17]);
        eventVec.B18Occupancy->push_back(Occupancy[18]);
        
        for(Int_t i =1; i<19;i++){
            if(Occupancy[i]>0) {
                ModBeenHit ++;
            }
        }
        eventVec.Event_NoModBeenHit->push_back(ModBeenHit);
        for(Int_t i =18; i>0;i--){
            if (Occupancy[i]!=0){
                LastMod =i;
                break;
            }
        }
        eventVec.Event_LastModule->push_back(LastMod);
        eventVec.Event_Mom_Range->push_back(mom_range[1][LastMod]);
        
        
        
        eventNumber++;
        eventVec.EventNo->push_back(index);
        eventVec.EventHitsNo->push_back(eventHits);
        
        //cout<<"Y_event "<<index<< ": "<<Y_event[index].size() <<endl;
        
    } //GTrig loop
    //////////
    TH1F* TimeDifference2 = new TH1F ("HitsTimeDifference2","HitsTimeDifference2",200,-100,4000);
    TH1F* TimeDifference3 = new TH1F ("HitsTimeDifference3","HitsTimeDifference3",200,-100,4000);
    
    for (Int_t i=0; i<eventVec.RsignalLeadTime->size()-1; i++){
        for(Int_t j=i+1; j<eventVec.RsignalLeadTime->size(); j++){
            if (eventVec.GTrigTime->at(i)==2 && eventVec.GTrigTime->at(j)==2){
                //cout<<"test"<<endl;
                TimeDifference2->Fill(abs(eventVec.RsignalLeadTime->at(j)-eventVec.RsignalLeadTime->at(i)));
                i=j;
            }
        }
    }


    for (Int_t i=0; i<eventVec.RsignalLeadTime->size()-1; i++){
        for(Int_t j=i+1; j<eventVec.RsignalLeadTime->size(); j++){
            if (eventVec.GTrigTime->at(i)==3 && eventVec.GTrigTime->at(j)==3){
                //cout<<"test"<<endl;
                TimeDifference3->Fill(abs(eventVec.RsignalLeadTime->at(j)-eventVec.RsignalLeadTime->at(i)));
                i=j;
            }
        }
    }
        
    TimeDifference2->GetXaxis()->SetTitle("Hit Time Dif [2.5*ns]");
    TimeDifference3->GetXaxis()->SetTitle("Hit Time Dif [2.5*ns]");
    TimeDifference2->Write();
    TimeDifference3->Write();
    //cout<<"test"<<endl;
    
    //////////
    graphs->cd();
    Int_t graph_size =0;
    Double_t chi2;
    Double_t par0;
    Double_t par1;
    Double_t par2;
    Int_t mu_plus = 0;
    Int_t mu_minus =0;
    
    TF1 *f1 = new TF1("f1","pol2",-200,4000);
    
    for (Int_t c=0; c<GTrigTagCoins.size(); c++){
        graph_size = Y_event[c].size();
        if (graph_size >6){
            double x[graph_size],y[graph_size];

            for(Int_t i=0; i<graph_size; i++){
                x[i]=Z_event[c].at(i);
                y[i]=Y_event[c].at(i);
            }
            TGraph* gr = new TGraph(graph_size, x, y);
            
            TCanvas *C0 = new TCanvas("C0","c0",850,500);
            C0->cd();
            
            gr->GetXaxis()->SetRangeUser(-200,4500);
            gr->GetYaxis()->SetRangeUser(-1000,1000);
            gr->SetMarkerColor(1);
            gr->SetMarkerSize(1);
            gr->SetMarkerStyle(7);
            gr->SetTitle(Form("Event_%03d.png",c));
            gr->GetXaxis()->SetTitle("Z pos mm");
            gr->GetYaxis()->SetTitle("Y pos mm");
            gr->Draw("AP");
            
            gr ->Fit("f1","R");
            
            TFitResultPtr r = gr->Fit("f1""","S");  // TFitResultPtr contains the TFitResult
            //TMatrixDSym cov = r->GetCovarianceMatrix();   //  to access the covariance matrix
            
            chi2  = r->Chi2();                  // to retrieve the fit chi2
            par0   = r->Parameter(0);            // retrieve the value for the parameter 0
            par1   = r->Parameter(1);
            par2   = r->Parameter(2);
            //Double_t err0   = r->ParError(0);
            
           
            
            if (chi2 <1000 && chi2 != 0 ){
                gr->Draw("AP");
                f1->GetXaxis()->SetRangeUser(-200,4500);
                gr->GetXaxis()->SetRangeUser(-200,4500);
                f1->Draw("same");
                gr->Write();
                
                C0->SaveAs((plotsFolder+Form("Event_%03d.png",c)).c_str());
                if (par0 >= -500 && par0 <= 500){
                    if (par2 >=0){
                        mu_plus ++;
                    }else{
                        mu_minus ++;
                    }
                }else{
                    if (par2 >=0){
                        mu_minus ++;
                    }else{
                        mu_plus ++;
                    }
                }
                
            }
            delete C0;
        }
    }
    cout<<"Number of mu+ :"<<mu_plus<<endl;
    cout<<"Number of mu- :"<<mu_minus<<endl;
    
    wfile.cd();
    
    events->Fill();
    events->Write();
    
    EventsMap->GetYaxis()->SetTitle("Y [mm]");
    EventsMap->GetXaxis()->SetTitle("Z [mm]");
    EventsMap->Write();
    
    EventsMap3D->GetYaxis()->SetTitle("X position [mm]");
    EventsMap3D->GetXaxis()->SetTitle("Z position [mm]");
    EventsMap3D->GetZaxis()->SetTitle("Y position [mm]");
    EventsMap3D->Write();
    
    eventsD->cd();
    
    for (Int_t ih=0; ih < NumberofEventsMonitor;ih++){
        if (SingleEvent[ih]->GetEntries()>5) {
            SingleEvent[ih]->GetYaxis()->SetTitle("vertical position [mm]");
            SingleEvent[ih]->GetXaxis()->SetTitle("horizontal position [mm]");
            SingleEvent[ih]->Write();
            
            TCanvas *C0 = new TCanvas("C0","c0",850,500);
            C0->cd();
            
            SingleEvent[ih]->SetMarkerColor(2);
            SingleEvent[ih]->SetMarkerSize(10);
            SingleEvent[ih]->Draw("colz");
            
            C0->SaveAs((plotsFolder+Form("Event_%03d.png",ih)).c_str());
            
            delete C0;
            
        }
    }
    
    events3D->cd();
    for (Int_t ih=0; ih < NumberofEventsMonitor;ih++){
        if (SingleEvent[ih]->GetEntries()>5) {
            SingleEvent3D[ih]->GetYaxis()->SetTitle("X position [mm]");
            SingleEvent3D[ih]->GetXaxis()->SetTitle("Z position [mm]");
            SingleEvent3D[ih]->GetZaxis()->SetTitle("Y position [mm]");
            SingleEvent3D[ih]->Write();
        }
        delete SingleEvent3D[ih];
        
    }
    
    eventsTime->cd();
    
    for (Int_t ih=0; ih < NumberofEventsMonitor;ih++){
        if (SingleEvent[ih]->GetEntries()>3) {
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
    
    eventVec.GTrigTag=0;
    eventVec.GTrigTime=0;
    eventVec.hitEventNo=0;
    eventVec.module=0;
    eventVec.posX=0;
    eventVec.posY=0;
    eventVec.posZ=0;
    eventVec.RsignalChannel=0;
    eventVec.LsignalChannel=0;
    eventVec.TsignalChannel=0;
    eventVec.RsignalHGAmpl=0;
    eventVec.LsignalHGAmpl=0;
    eventVec.TsignalHGAmpl=0;
    eventVec.RsignalLeadTime=0;
    eventVec.LsignalLeadTime=0;
    eventVec.TsignalLeadTime=0;
    eventVec.RsignalLGAmpl=0;
    eventVec.LsignalLGAmpl=0;
    eventVec.TsignalLGAmpl=0;
    eventVec.RsignalTrailTime=0;
    eventVec.LsignalTrailTime=0;
    eventVec.TsignalTrailTime=0;
    eventVec.RsignalTimeDif=0;
    eventVec.LsignalTimeDif=0;
    eventVec.TsignalTimeDif=0;
    
    eventVec.Event_NoModBeenHit=0;
    eventVec.Event_NoModBeenHit=0;
    eventVec.Event_LastModule=0;
    eventVec.Event_Mom_Range=0;
    
    eventVec.B1Occupancy=0;
    eventVec.B2Occupancy=0;
    eventVec.B3Occupancy=0;
    eventVec.B4Occupancy=0;
    eventVec.B5Occupancy=0;
    eventVec.B6Occupancy=0;
    eventVec.B7Occupancy=0;
    eventVec.B8Occupancy=0;
    eventVec.B9Occupancy=0;
    eventVec.B10Occupancy=0;
    eventVec.B11Occupancy=0;
    eventVec.B12Occupancy=0;
    eventVec.B13Occupancy=0;
    eventVec.B14Occupancy=0;
    eventVec.B15Occupancy=0;
    eventVec.B16Occupancy=0;
    eventVec.B17Occupancy=0;
    eventVec.B18Occupancy=0;
    
    GTrigTagCoins.clear();
    wfile.Close();
    FileInput->Close();
    vFileNames.clear();
    fList.close();
    return 0;
}
