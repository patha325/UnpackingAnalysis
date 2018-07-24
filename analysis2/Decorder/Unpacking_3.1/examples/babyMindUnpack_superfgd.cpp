/* This file is part of BabyMINDdaq software package. This software
 * package is designed for internal use for the Baby MIND detector
 * collaboration and is tailored for this use primarily.
 *
 * BabyMINDdaq is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * BabyMINDdaq is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with BabyMINDdaq.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

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
#include "MDfragmentBM.h"
#include "MDpartEventBM.h"
#include "MDargumentHandler.h"
#include "MDdataFile.h"

using namespace std;

string GetLocation(string str)
{
     
    int i = str.rfind("_Slot_");
    string way = str.substr(0,i);  
    return way;
}

struct vectorsTree
{
  vector<double> FEBSN;
  vector<double> SpillNum;
  vector<double> SpillTime;
  //vector<double> SpillTimeUs;
  vector<double> GTrigTag;
  vector<double> GTrigTime;
  vector<double> hitsChannel;
  vector<double> hitAmpl;
  vector<double> hitLGAmpl;
  vector<double> hitLeadTime;
  vector<double> hitTrailTime;
  vector<double> hitTimeDif;
  vector<double> hitTimeAvr;
  vector<double> hitGlobalTime;
};



char *dataBuff;
uint32_t* dataPtr;

int main( int argc, char **argv ) {
 string sFileName;
  
  vector<string> vFileNames;
  ifstream fList("febs_files_list.list");
  while (!fList.eof()) {
    fList >> sFileName;
    cout << sFileName << endl;
    vFileNames.push_back(sFileName);
  }
  
   vectorsTree FEB[65];
   
   string rootFileOutput=GetLocation(vFileNames[0].c_str());
  rootFileOutput+="_all.root";
  cout << rootFileOutput<<endl;
  
  TFile rfile(rootFileOutput.c_str(), "recreate");
  
  for (vector<string>::iterator itFileName=vFileNames.begin(); itFileName != vFileNames.end(); itFileName++) {
    sFileName = *itFileName;
    cout <<endl<< sFileName << endl;
    
    ifstream finData(sFileName.c_str());
    string stringBuf;
    string filepath;
    string filename;
  
  // The following shows how to use the MDargumentHandler class
  // to deal with the main arguments
  // Define the arguments
  MDargumentHandler argh("Example of unpacking application.");
  argh.AddArgument("help","print this message","h");
  argh.AddArgument("directory","path for the data file","d","<string>","." );
  argh.AddArgument("file","Name of a data file","f","<string>","mandatory");
  

  // Check the user arguments consistancy
  // All mandatory arguments should be provided and
  // There should be no extra arguments
  if ( argh.ProcessArguments(argc, argv) ) {argh.Usage(); return -1;}

  // Treat arguments, obtain values to be used later
  if ( argh.GetValue("help") ) {argh.Usage(); return 0;}
  if ( argh.GetValue("directory", stringBuf) != MDARGUMENT_STATUS_OK ) return -1;
  filepath = stringBuf;
  if ( argh.GetValue("file", stringBuf) != MDARGUMENT_STATUS_OK ) return -1;
  filename = stringBuf;
  filename = sFileName;
  string rootFilename = sFileName;
 
  rootFilename = rootFilename.substr(0, rootFilename.size()-4);
  rootFilename+=".root";
  
  
  //TFile rfile("histos.root", "recreate");

 
  
  for (Int_t i=0;i<=64;i++){
    FEB[i].FEBSN.clear();
    FEB[i].SpillNum.clear();
    FEB[i].SpillTime.clear();
    //FEB[i].SpillTimeUs.clear();
    FEB[i].hitsChannel.clear();
    FEB[i].hitAmpl.clear();
    FEB[i].hitLeadTime.clear();
    FEB[i].GTrigTag.clear();
    FEB[i].GTrigTime.clear();
    FEB[i].hitLGAmpl.clear();
    FEB[i].hitTrailTime.clear();
    FEB[i].hitTimeDif.clear();
    FEB[i].hitTimeAvr.clear();
    FEB[i].hitGlobalTime.clear();
    }
  
  MDdateFile dfile(filename, filepath);
// Open the file and loop over events.
  char *eventBuffer;
  if ( dfile.open() ) { // There is a valid files to unpack
    dfile.init();

    int xEv(0);
    do { // Loop over all spills
      eventBuffer =  dfile.GetNextEvent();
      try {
        MDfragmentBM spill;
        spill.SetDataPtr(eventBuffer);

        MDpartEventBM *event;
        int nTr = spill.GetNumOfTriggers();
        for (int i=0; i<nTr; ++i) {
          event = spill.GetTriggerEventPtr(i);
          //event->Dump();
          for (int ich=0; ich<BM_FEB_NCHANNELS; ++ich) {
              int nlHits = 0;
              int ntHits = 0;
              nlHits = event->GetNLeadingEdgeHits(ich);
              for (unsigned int ih=0; ih<nlHits; ++ih) {
                  bool TrailTimeExist = false;
                  int IDevent = event->GetHitTimeId(ih, ich, 'l');
                  FEB[spill.GetBoardId()].FEBSN.push_back(spill.GetBoardId());
                  FEB[spill.GetBoardId()].SpillNum.push_back(spill.GetSpillTag());
                  FEB[spill.GetBoardId()].SpillTime.push_back(spill.GetSpillTime());
                  //FEB[spill.GetBoardId()].SpillTimeUs.push_back(spill.GetSpillTimeUs());
                  FEB[spill.GetBoardId()].GTrigTag.push_back(event->GetTriggerTag());
                  FEB[spill.GetBoardId()].GTrigTime.push_back(event->GetTriggerTime());
                  FEB[spill.GetBoardId()].hitsChannel.push_back(ich);
                  FEB[spill.GetBoardId()].hitLeadTime.push_back(event->GetLeadingTime(ih, ich));
                  
                  //FEB[spill.GetBoardId()].hitGlobalTime.push_back();
                      
                  ntHits = event->GetNTrailingEdgeHits(ich);
                  for(unsigned int ith=0; ith < ntHits; ith++){
                      if (IDevent==event->GetHitTimeId(ith, ich, 't') && TrailTimeExist==false){
                          FEB[spill.GetBoardId()].hitTrailTime.push_back(event->GetTrailingTime(ith, ich));
                          FEB[spill.GetBoardId()].hitTimeDif.push_back(FEB[spill.GetBoardId()].hitTrailTime.back() - FEB[spill.GetBoardId()].hitLeadTime.back() );
                          FEB[spill.GetBoardId()].hitTimeAvr.push_back((FEB[spill.GetBoardId()].hitTrailTime.back() + FEB[spill.GetBoardId()].hitLeadTime.back())/2 );
                          TrailTimeExist = true;
                      }
                  }
                  if (TrailTimeExist==false){
                      if (i+1 <nTr){
                        event = spill.GetTriggerEventPtr(i+1);
                        ntHits = event->GetNTrailingEdgeHits(ich);
                        unsigned int ith=0;
                            while (TrailTimeExist==false && ith < ntHits){
                                if (IDevent==event->GetHitTimeId(ith, ich, 't')){
                                    FEB[spill.GetBoardId()].hitTrailTime.push_back(event->GetTrailingTime(ith, ich));
                                    FEB[spill.GetBoardId()].hitTimeDif.push_back(FEB[spill.GetBoardId()].hitTrailTime.back() - FEB[spill.GetBoardId()].hitLeadTime.back() + 4000);
                                    FEB[spill.GetBoardId()].hitTimeAvr.push_back((FEB[spill.GetBoardId()].hitTrailTime.back() + 4000 + FEB[spill.GetBoardId()].hitLeadTime.back())/2 );
                                    TrailTimeExist = true;
                                }
                            ith++;
                            }
                        event = spill.GetTriggerEventPtr(i);
                      }
                  }
                  if (TrailTimeExist==false){
                            FEB[spill.GetBoardId()].hitTrailTime.push_back(-1);
                            FEB[spill.GetBoardId()].hitTimeDif.push_back(-1);
                            FEB[spill.GetBoardId()].hitTimeAvr.push_back(-1);
                            TrailTimeExist = true;
                        }
                    
                
                  
                  
                  bool HGAmplExist = false;
                  
                  if (IDevent == event-> GetHitAmplitudeId(ich, 'h') ){
                      FEB[spill.GetBoardId()].hitAmpl.push_back(event->GetHitAmplitude(ich, 'h'));
                      HGAmplExist = true;
                  }
                  
                  if ( HGAmplExist == false){
                      if (i+1 <nTr){
                        event = spill.GetTriggerEventPtr(i+1);
                        if (event-> HGAmplitudeHitExists(ich)){
                            if (IDevent==event-> GetHitAmplitudeId(ich, 'h')){
                                FEB[spill.GetBoardId()].hitAmpl.push_back(event->GetHitAmplitude(ich, 'h'));
                                HGAmplExist = true;
                            }
                        }
                      event = spill.GetTriggerEventPtr(i);
                    }
                  }
                  
                  if (HGAmplExist==false){
                        FEB[spill.GetBoardId()].hitAmpl.push_back(0);
                        HGAmplExist = true;
                  }
                  
                  
                  bool LGAmplExist = false;
                  if (IDevent==event-> GetHitAmplitudeId(ich, 'l')){
                      FEB[spill.GetBoardId()].hitLGAmpl.push_back(event->GetHitAmplitude(ich, 'l'));
                      LGAmplExist = true;
                  }
                  if ( LGAmplExist == false){
                      if (i+1 <nTr){
                            event = spill.GetTriggerEventPtr(i+1);
                            if (event-> LGAmplitudeHitExists(ich)){
                                if (IDevent==event-> GetHitAmplitudeId(ich, 'l')){
                                    FEB[spill.GetBoardId()].hitLGAmpl.push_back(event->GetHitAmplitude(ich, 'l'));
                                    LGAmplExist = true;
                                }
                            }
                            event = spill.GetTriggerEventPtr(i);
                      }
                  }
                  if ( LGAmplExist == false){
                        FEB[spill.GetBoardId()].hitLGAmpl.push_back(0);
                  }
                  
                  
              if (FEB[spill.GetBoardId()].FEBSN.size() !=  FEB[spill.GetBoardId()].SpillNum.size()    ||
                  FEB[spill.GetBoardId()].FEBSN.size() !=  FEB[spill.GetBoardId()].hitsChannel.size() || 
                  FEB[spill.GetBoardId()].FEBSN.size() !=  FEB[spill.GetBoardId()].hitAmpl.size()     || 
                  FEB[spill.GetBoardId()].FEBSN.size() !=  FEB[spill.GetBoardId()].hitLeadTime.size() || 
                  FEB[spill.GetBoardId()].FEBSN.size() !=  FEB[spill.GetBoardId()].GTrigTag.size()    ||  
                  FEB[spill.GetBoardId()].FEBSN.size() !=  FEB[spill.GetBoardId()].GTrigTime.size()   ||  
                  FEB[spill.GetBoardId()].FEBSN.size() !=  FEB[spill.GetBoardId()].hitLGAmpl.size()   || 
                  FEB[spill.GetBoardId()].FEBSN.size() !=  FEB[spill.GetBoardId()].hitTrailTime.size()||
                  FEB[spill.GetBoardId()].FEBSN.size() !=  FEB[spill.GetBoardId()].hitTimeDif.size()  ||
                  FEB[spill.GetBoardId()].FEBSN.size() !=  FEB[spill.GetBoardId()].hitTimeAvr.size()) {
                  
                 cout <<FEB[spill.GetBoardId()].GTrigTag.back()<<endl;
                 cout <<FEB[spill.GetBoardId()].FEBSN.size()<< " " <<FEB[spill.GetBoardId()].SpillNum.size()<<" "<<FEB[spill.GetBoardId()].hitAmpl.size()<<" " <<FEB[spill.GetBoardId()].hitTrailTime.size()<<endl;
                 //return 0;
                 }
                  
              }
          }
        }
      } catch (MDexception & lExc)  {
        std::cerr <<  lExc.GetDescription() << endl
                  << "Unpacking exception\n"
                  << "Spill skipped!\n\n";
      } catch(std::exception & lExc) {
        std::cerr << lExc.what() << std::endl
                  << "Standard exception\n"
                  << "Spill skipped!\n\n";
      } catch(...) {
        std::cerr << "Unknown exception occurred...\n"
                  << "Spill skipped!\n\n";
      }

      ++xEv;
//       } while (xEv < 5);
    } while ( eventBuffer );
  }
 
     
  
  TTree* FEBtree[65];
  
  ostringstream sFEBnum;
  string sFEB;

  for (Int_t ih=0; ih<=64; ih++) {
      if (FEB[ih].FEBSN.size()){
        sFEBnum.str("");
        sFEBnum << ih;
        sFEB = "FEB_"+sFEBnum.str();
        FEBtree[ih] = new TTree(sFEB.c_str(),sFEB.c_str()); 
        
        FEBtree[ih]->Branch((sFEB+"_SN").c_str(),"vector<double>",&FEB[ih].FEBSN);
        FEBtree[ih]->Branch((sFEB+"_SpillTag").c_str(),"vector<double>",&FEB[ih].SpillNum);
        FEBtree[ih]->Branch((sFEB+"_SpillTime").c_str(),"vector<double>",&FEB[ih].SpillTime);
        //FEBtree[ih]->Branch((sFEB+"_SpillTimeUs").c_str(),"vector<double>",&FEB[ih].SpillTimeUs);
        FEBtree[ih]->Branch((sFEB+"_GTrigTag").c_str(),"vector<double>",&FEB[ih].GTrigTag);
        FEBtree[ih]->Branch((sFEB+"_GTrigTime").c_str(),"vector<double>",&FEB[ih].GTrigTime);
        FEBtree[ih]->Branch((sFEB+"_hitsChannel").c_str(),"vector<double>",&FEB[ih].hitsChannel);
        FEBtree[ih]->Branch((sFEB+"_hitAmpl").c_str(),"vector<double>",&FEB[ih].hitAmpl);
        FEBtree[ih]->Branch((sFEB+"_hitLGAmpl").c_str(),"vector<double>",&FEB[ih].hitLGAmpl);
        FEBtree[ih]->Branch((sFEB+"_hitLeadTime").c_str(),"vector<double>",&FEB[ih].hitLeadTime);
        FEBtree[ih]->Branch((sFEB+"_hitTrailTime").c_str(),"vector<double>",&FEB[ih].hitTrailTime);
        FEBtree[ih]->Branch((sFEB+"_hitTimeDif").c_str(),"vector<double>",&FEB[ih].hitTimeDif);
        FEBtree[ih]->Branch((sFEB+"_hitTimeAvr").c_str(),"vector<double>",&FEB[ih].hitTimeAvr);
      }
  }
  
  for (Int_t i=0; i<=64; i++){
        if (FEB[i].FEBSN.size()){
            cout<<"Number of events on FEB "<< i <<" is "<< FEB[i].FEBSN.size()<<endl;
            FEBtree[i]->Fill();
            FEBtree[i]-> Write();
            FEBtree[i]->Delete();
            
            FEB[i].FEBSN.clear();
            FEB[i].SpillNum.clear();
            FEB[i].SpillTime.clear();
            //FEB[i].SpillTimeUs.clear();
            FEB[i].hitsChannel.clear();
            FEB[i].hitAmpl.clear();
            FEB[i].hitLeadTime.clear();
            FEB[i].hitTrailTime.clear();
            FEB[i].hitTimeDif.clear();
            FEB[i].hitTimeAvr.clear();
            FEB[i].GTrigTag.clear();
            FEB[i].GTrigTime.clear();
            FEB[i].hitLGAmpl.clear();
        }
    }
  


  dfile.close();
  delete dataBuff;
  }
  rfile.Close();
  fList.close();
  return 0;
}



