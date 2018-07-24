#include <stdio.h>
#include <string.h>
#include <exception>
#include <fstream>
#include <vector>
#include <iterator>

#include "MDdataWordBM.h"
#include "MDargumentHandler.h"
#include "MDfragmentBM.h"

using namespace std;

string Getdot(string str)
{
     
    int i = str.rfind(".");
    string way = str.substr(0,i);  
    return way;
}

int main( int argc, char **argv ) { 
  string stringBuf;
  int    intBuf;

  // The following shows how to use the MDargumentHandler class
  // to deal with the main arguments
  // Define the arguments
  MDargumentHandler argh("Example of unpacking application.");
  argh.AddArgument("help","print this message","h");
  argh.AddArgument("directory","Path for a data file","d","<string>","." );
  argh.AddArgument("file","Name of a data file","f","<string>","mandatory");
  argh.AddArgument("begin","Initial position in input file","b","<int>","0");
  argh.AddArgument("nwords","Number of data words to be processed","n","<int>","0");

  // Check the user arguments consistancy
  // All mandatory arguments should be provided and
  // There should be no extra arguments
  if ( argh.ProcessArguments(argc, argv) ) {argh.Usage(); return -1;}

  // Treat arguments, obtain values to be used later
  if ( argh.GetValue("help") ) {argh.Usage(); return 0;}

  if ( argh.GetValue("directory", stringBuf) != MDARGUMENT_STATUS_OK ) return -1;
  string filepath = stringBuf;

  if ( argh.GetValue("file", stringBuf) != MDARGUMENT_STATUS_OK ) return -1;
  string filename = stringBuf;

  if ( argh.GetValue("begin", intBuf) != MDARGUMENT_STATUS_OK ) return -1;
  int pos = intBuf*4;

  if ( argh.GetValue("nwords", intBuf) != MDARGUMENT_STATUS_OK ) return -1;
  //int nWords = intBuf;

  //std::ifstream ifs((filepath + "/" + filename).c_str(),std::ifstream::binary);
  std::ifstream ifs((filename).c_str(),std::ifstream::binary);
  
  //if ( ifs.fail() ) {
    //cerr << "Can not open file " << filepath << filename << endl;
    //return 1;
  //}
  
  vector< vector <uint32_t> > slotdata;
  slotdata.resize(8);  
  
  uint32_t* dataPtr = new uint32_t;
  uint32_t l_CheckSumL;
  uint32_t l_CheckSumH;
  
  unsigned int TDMTag[7] = {0,0,0,0,0,0,0};
  unsigned int TDMSlotStart[7] = {0,0,0,0,0,0,0};
  int TDMmark = -1;
  bool DataCheck;
  
  //vector <int>::iterator it[7];
  
  ifs.seekg(pos);
  while (!ifs.eof()) {
    ifs.read((char*)dataPtr, 4);
    MDdataWordBM dw(dataPtr);
    TDMmark++;
    if (dw.GetDataType() == MDdataWordBM::TDM ){
        if (dw.GetTDMID()==0) {
            int slotID=dw.GetTDMSlotID();
            DataCheck = true;
            //cout <<"TDM Start: " <<dw.GetTDMSlotID()<<" TDM Tag: "<<dw.GetTDMTag()<<endl;

            if(dw.GetTDMTag() != TDMTag[dw.GetTDMSlotID()]){
                cout <<"Slot "<< dw.GetTDMSlotID() << " TDM Tag (data) " <<dw.GetTDMTag()<<" != "<<TDMTag[dw.GetTDMSlotID()]<<" (calculated);"<<endl;
                TDMTag[dw.GetTDMSlotID()] = dw.GetTDMTag();
            }
            //it[dw.GetTDMSlotID()] = std::prev(slotdata[slotID].end());
            
            TDMTag[dw.GetTDMSlotID()]++;
            if (TDMTag[dw.GetTDMSlotID()] == 256)
                TDMTag[dw.GetTDMSlotID()] = 0;
            
            TDMSlotStart[dw.GetTDMSlotID()] = TDMmark;
            l_CheckSumL = *dataPtr;
            l_CheckSumH = *dataPtr;
            
            ifs.read((char*)dataPtr, 4);
            MDdataWordBM dw(dataPtr);
            TDMmark++;
            while(dw.GetDataType() != MDdataWordBM::TDM && !ifs.eof()) {
                
                l_CheckSumL+=*dataPtr;
                l_CheckSumH += l_CheckSumL;
                
                slotdata[slotID].push_back(*dataPtr);
                ifs.read((char*)dataPtr, 4);
                MDdataWordBM dw(dataPtr);
                TDMmark++;
            }
            if(dw.GetDataType() == MDdataWordBM::TDM){
                if (dw.GetTDMID()==1){
                    //cout <<"TDM Stop: " <<dw.GetTDMSlotID()<<" TDM sumL: "<<dw.GetTDMsumL()<<" TDM sumH: "<<dw.GetTDMsumH()<<endl; 
                    if (dw.GetTDMSlotID()!=slotID){
                        cout<<dw<< " " <<TDMSlotStart[slotID]<<endl<<TDMmark<< " TDM Slot ID start: "<<slotID<<" TDM Slot ID end: "<<dw.GetTDMSlotID()<<" Unpacking Error!"<<endl;
                        //slotdata[slotID].push_back(*dataPtr);
                        DataCheck = false;
                        for (int i = TDMSlotStart[slotID]; i< TDMmark -1; i++) 
                            slotdata[slotID].pop_back();
                    }
                    if (dw.GetTDMsumL() != (((l_CheckSumL) & 0x7FF ) >> 0) || dw.GetTDMsumH() != (((l_CheckSumH>>22) & 0x3E0) | ((l_CheckSumH >>11) & 0x1F))) {
                        cout <<"TDM Stop: " <<dw.GetTDMSlotID()<<" TDM sumL: "<<dw.GetTDMsumL()<<" TDM sumH: "<<dw.GetTDMsumH()<<endl; 
                        cout<<(((l_CheckSumL) & 0x7FF ) >> 0) <<" "<< (((l_CheckSumH>>22) & 0x3E0) | ((l_CheckSumH >>11) & 0x1F)) <<endl;
                        if (DataCheck){
                            for (int i = TDMSlotStart[slotID]; i< TDMmark -1; i++) 
                            slotdata[slotID].pop_back();
                        }
                    }
                }
            }
        }
    }
    else { 
        cout << TDMmark <<" Data out from TMD slots: "<< dw<< endl;
    }
 }
 ifs.close();
 filename = Getdot(filename);
 stringstream slotnumber;
 string nCt;
 for (int k = 0; k<8;k++){
     if(slotdata[k].size()){
        nCt.empty();
        slotnumber.str("");
        slotnumber<<k;
        nCt = slotnumber.str();
        std::ofstream ofs((filename+"_Slot_"+nCt+".daq").c_str(),std::ofstream::binary);
        cout <<endl<<filename<<"_Slot_"<<nCt << ".daq ----- data for FEB on slot"<< k <<" in TDM mode."<<endl;
        for (int i=0;i<slotdata[k].size();i++){
            ofs.write((char*)&slotdata[k][i], 4); 
        }
        slotdata[k].clear();
        ofs.close();
     }
 }
 
 return 0;
    
}
