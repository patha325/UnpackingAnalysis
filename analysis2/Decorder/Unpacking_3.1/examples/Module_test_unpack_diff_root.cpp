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
  for (vector<string>::iterator itFileName=vFileNames.begin(); itFileName != vFileNames.end(); itFileName++) {
    sFileName = *itFileName;
    cout << sFileName << endl;
    
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
 

 
  TFile rfile(rootFilename.c_str(), "recreate");
  /*TDirectory *top = gDirectory;
  TDirectory *cdall = top->mkdir("all");
  cdall->cd();*/
  
  TH1I  h_lgah("h_lg_amp_hit_ch", "hit channels", 100, 0, 100);
  TH1I  h_hgah("h_lh_amp_hit_ch", "hit channels", 100, 0, 100);
  TH1I  h_lth("h_le_time_hit_ch", "hit channels", 100, 0, 100);
  TH1I  h_tth("h_te_time_hit_ch", "hit channels", 100, 0, 100);
  TH1I  h_lga("h_lg_ampl", "hit ampl.", 200, 0, 5000);
  TH1I  h_hga("h_hg_ampl", "hit ampl.", 200, 0, 5000);
  TTree* t1 = new TTree("t1","Per spill tree");


  vector<double> FEBSN;
  t1->Branch("FEBSN","vector<double>",&FEBSN);
  
  vector<double> GTrigTag;
  t1->Branch("GTrigTag","vector<double>",&GTrigTag);
  
  vector<double> GTrigTime;
  t1->Branch("GTrigTime","vector<double>",&GTrigTime);
  
  vector<double> hitsChannel;
  t1->Branch("hitsChannel","vector<double>",&hitsChannel);
  
  vector<double> hitAmpl;
  t1->Branch("hitAmpl","vector<double>",&hitAmpl);
  
  vector<double> hitLGAmpl;
  t1->Branch("hitLGAmpl","vector<double>",&hitLGAmpl);
  
  vector<double> hitLeadTime;
  t1->Branch("hitLeadTime","vector<double>",&hitLeadTime);


    
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

            if (event->LGAmplitudeHitExists(ich)) {
              int q = event->GetHitAmplitude(ich, 'l');
	      
                hitsChannel.push_back(ich);
                hitAmpl.push_back(event->GetHitAmplitude(ich, 'h'));
                hitLGAmpl.push_back(event->GetHitAmplitude(ich, 'l'));
                hitLeadTime.push_back(event->GetNLeadingEdgeHits(ich));
                FEBSN.push_back(spill.GetBoardId());
                GTrigTag.push_back(event->GetTriggerTag());
                GTrigTime.push_back(event->GetTriggerTime());
                
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
  
 
  
  
  t1->Fill();
   t1->Write();
 
  h_lgah.Write();
  h_hgah.Write();
  h_lth.Write();
  h_tth.Write();
  h_lga.Write();
  h_hga.Write();

  
  // top->cd();
  // top->Write();
  //delete top;
  
  rfile.Close();
  dfile.close();
  delete dataBuff;
  }
  fList.close();
  return 0;
}



