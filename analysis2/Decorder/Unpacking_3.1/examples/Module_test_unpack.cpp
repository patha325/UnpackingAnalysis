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
     
    int i = str.rfind("/");
    string way = str.substr(0,i);  
    return way;
}


char *dataBuff;
uint32_t* dataPtr;

int main( int argc, char **argv ) {
  string stringBuf;
  string filepath;
  string sFileName;
  
  
  vector<string> vFileNames;
  ifstream fList("module.list");
  while (!fList.eof()) {
    fList >> sFileName;
    cout << sFileName << endl;
    vFileNames.push_back(sFileName);
  }
  
  
  
  
  string rootFileOutput=GetLocation(GetLocation (vFileNames[0].c_str()));
  rootFileOutput+="/all.root";
  cout << rootFileOutput<<endl;
  
  TFile rfile(rootFileOutput.c_str(), "recreate");
  
  
  TH1I  h_lgah("h_lg_amp_hit_ch", "hit channels", 100, 0, 100);
  TH1I  h_hgah("h_lh_amp_hit_ch", "hit channels", 100, 0, 100);
  TH1I  h_lth("h_le_time_hit_ch", "hit channels", 100, 0, 100);
  TH1I  h_tth("h_te_time_hit_ch", "hit channels", 100, 0, 100);
  TH1I  h_lga("h_lg_ampl", "hit ampl.", 200, 0, 5000);
  TH1I  h_hga("h_hg_ampl", "hit ampl.", 200, 0, 5000);
  
   TTree* FEB3 = new TTree("FEB3","Per spill tree");
  
  vector<double> FEBSN3;
  FEB3->Branch("FEBSN3","vector<double>",&FEBSN3);
  
  vector<double> GTrigTag3;
  FEB3->Branch("GTrigTag3","vector<double>",&GTrigTag3);
  
  vector<double> GTrigTime3;
  FEB3->Branch("GTrigTime3","vector<double>",&GTrigTime3);
  
  vector<double> hitsChannel3;
  FEB3->Branch("hitsChannel3","vector<double>",&hitsChannel3);
  
  vector<double> hitAmpl3;
  FEB3->Branch("hitAmpl3","vector<double>",&hitAmpl3);
  
  vector<double> hitLGAmpl3;
  FEB3->Branch("hitLGAmpl3","vector<double>",&hitLGAmpl3);
  
  vector<double> hitLeadTime3;
  FEB3->Branch("hitLeadTime3","vector<double>",&hitLeadTime3);
  
  
  
  TTree* FEB4 = new TTree("FEB4","Per spill tree");
  
  vector<double> FEBSN4;
  FEB4->Branch("FEBSN4","vector<double>",&FEBSN4);
  
  vector<double> GTrigTag4;
  FEB4->Branch("GTrigTag4","vector<double>",&GTrigTag4);
  
  vector<double> GTrigTime4;
  FEB4->Branch("GTrigTime4","vector<double>",&GTrigTime4);
  
  vector<double> hitsChannel4;
  FEB4->Branch("hitsChannel4","vector<double>",&hitsChannel4);
  
  vector<double> hitAmpl4;
  FEB4->Branch("hitAmpl4","vector<double>",&hitAmpl4);
  
  vector<double> hitLGAmpl4;
  FEB4->Branch("hitLGAmpl4","vector<double>",&hitLGAmpl4);
  
  vector<double> hitLeadTime4;
  FEB4->Branch("hitLeadTime4","vector<double>",&hitLeadTime4);
  

  TTree* FEB5 = new TTree("FEB5","Per spill tree");
  
  vector<double> FEBSN5;
  FEB5->Branch("FEBSN5","vector<double>",&FEBSN5);
  
  vector<double> GTrigTag5;
  FEB5->Branch("GTrigTag5","vector<double>",&GTrigTag5);
  
  vector<double> GTrigTime5;
  FEB5->Branch("GTrigTime5","vector<double>",&GTrigTime5);
  
  vector<double> hitsChannel5;
  FEB5->Branch("hitsChannel5","vector<double>",&hitsChannel5);
  
  vector<double> hitAmpl5;
  FEB5->Branch("hitAmpl5","vector<double>",&hitAmpl5);
  
  vector<double> hitLGAmpl5;
  FEB5->Branch("hitLGAmpl5","vector<double>",&hitLGAmpl5);
  
  vector<double> hitLeadTime5;
  FEB5->Branch("hitLeadTime5","vector<double>",&hitLeadTime5);

    
  
  
  /*vector<string> vFileNames;
  ifstream fList("module.list");
  while (!fList.eof()) {
    fList >> sFileName;
    cout << sFileName << endl;
    vFileNames.push_back(sFileName);
  }*/
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
  filename = sFileName;
  string rootFilename = sFileName;
 
  rootFilename = rootFilename.substr(0, rootFilename.size()-4);
  rootFilename+=".root";
 

 
  //TFile rfile(rootFilename.c_str(), "recreate");
  /*TDirectory *top = gDirectory;
  TDirectory *cdall = top->mkdir("all");
  cdall->cd();*/
  
  
  
  
  
  
 
  MDdateFile dfile(filename, filepath);
// Open the file and loop over events.
  char *eventBuffer;
  if ( dfile.open() ) { // There is a valid files to unpack
    dfile.init();

    int xEv(0);
    do { // Loop over all spills
      eventBuffer =  dfile.GetNextEvent();
      try {
        MDfragmentBM   spill;
        spill.SetDataPtr(eventBuffer);

        MDpartEventBM *event;
        int nTr = spill.GetNumOfTriggers();
        for (int i=0; i<nTr; ++i) {
          event = spill.GetTriggerEventPtr(i);
//           event->Dump();
          for (int ich=0; ich<BM_FEB_NCHANNELS; ++ich) {
            int nHits = event->GetNLeadingEdgeHits(ich);
            if (nHits)
              h_lth.Fill(ich, nHits);

            nHits = event->GetNTrailingEdgeHits(ich);
            if (nHits)
              h_tth.Fill(ich, nHits);

            if (event->LGAmplitudeHitExists(ich) && event->HGAmplitudeHitExists(ich)) {
              int q = event->GetHitAmplitude(ich, 'l');
                if (spill.GetBoardId()==3){
                    hitsChannel3.push_back(ich);
                    hitAmpl3.push_back(event->GetHitAmplitude(ich, 'h'));
                    hitLGAmpl3.push_back(event->GetHitAmplitude(ich, 'l'));
                    hitLeadTime3.push_back(event->GetNLeadingEdgeHits(ich));
                    FEBSN3.push_back(spill.GetBoardId());
                    GTrigTag3.push_back(event->GetTriggerTag());
                    GTrigTime3.push_back(event->GetTriggerTime());}
                    
                if (spill.GetBoardId()==4){
                    hitsChannel4.push_back(ich);
                    hitAmpl4.push_back(event->GetHitAmplitude(ich, 'h'));
                    hitLGAmpl4.push_back(event->GetHitAmplitude(ich, 'l'));
                    hitLeadTime4.push_back(event->GetNLeadingEdgeHits(ich));
                    FEBSN4.push_back(spill.GetBoardId());
                    GTrigTag4.push_back(event->GetTriggerTag());
                    GTrigTime4.push_back(event->GetTriggerTime());}
                    
                if (spill.GetBoardId()==5){
                    hitsChannel5.push_back(ich);
                    hitAmpl5.push_back(event->GetHitAmplitude(ich, 'h'));
                    hitLGAmpl5.push_back(event->GetHitAmplitude(ich, 'l'));
                    hitLeadTime5.push_back(event->GetNLeadingEdgeHits(ich));
                    FEBSN5.push_back(spill.GetBoardId());
                    GTrigTag5.push_back(event->GetTriggerTag());
                    GTrigTime5.push_back(event->GetTriggerTime());}
                
              h_lga.Fill(q);
              h_lgah.Fill(ich);
            }

            if (event->HGAmplitudeHitExists(ich)) {
              int q = event->GetHitAmplitude(ich, 'h');
              h_hga.Fill(q);
              h_hgah.Fill(ich);
	      
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
  
    
    dfile.close();
    delete dataBuff;
      
}
    FEB3->Fill();
    FEB4->Fill();
    FEB5->Fill();
    FEB3->Write();
    FEB4->Write();
    FEB5->Write();
  
    if (GTrigTag3.size()>0)
    {
        cout <<"FEB3 last GTrigTag: "<< GTrigTag3.back()<<endl;
    }
    else 
    {
        cout<< "Wrong data from FEB3!!! Please check config file."<<endl;
    }
    
    if (GTrigTag4.size()>0)
    {
        cout<<"FEB4 last GTrigTag: " << GTrigTag4.back()<<endl;
    }
    else 
    {
        cout<< "Wrong data from FEB4!!! Please check config file."<<endl;
    }
    
    if (GTrigTag5.size()>0)
    {
        cout <<"FEB4 last GTrigTag: "<< GTrigTag5.back()<<endl;
    }
    else 
    {
        cout<< "Wrong data from FEB5!!! Please check config file."<<endl;
    }
    if (GTrigTag3.size()>0 && GTrigTag4.size()>0 && GTrigTag5.size()>0)
    {
        cout << GTrigTag3.front()<<endl;
        cout << GTrigTag4.front()<<endl;
        cout << GTrigTag5.front()<<endl;
    }
    else
    {
        cout << endl<< "Wrong data!!! Please check FEBs config files."<<endl<<endl;
    }    
    
  /*  Int_t Lastchecked;
    
    Int_t MinLastGTrigTag = min(GTrigTag3.back(), min(GTrigTag4.back(),GTrigTag5.back()));
    
    for (Int_t i=0; GTrigTag3[i]<=MinLastGTrigTag;i++)
    {
        //Lastchecked = GTrigTag3[i];
        for (Int_t k=0; k<GTrigTag4.back(); k++)
        {
            if (GTrigTag3[i]==GTrigTag4[k] || GTrigTag3[i]==GTrigTag4[k]-1 || GTrigTag3[i]==GTrigTag4[k]+1 )
            {
             if (hitsChannel3[i]==hitsChannel4[k])
             {
                 
             }
            }
        }
    }*/
    
   // cout<<MinLastGTrigTag<<endl;
    
  rfile.Close();
  fList.close();
  return 0;
}



