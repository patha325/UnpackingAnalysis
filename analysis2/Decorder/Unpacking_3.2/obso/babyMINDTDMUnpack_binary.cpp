#include <stdio.h>
#include <string.h>
#include <exception>
#include <fstream>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <vector>

#include "MDdataWordBM.h"
#include "MDargumentHandler.h"
#include "MDfragmentBM.h"

using namespace std;

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

  std::ifstream ifs((filepath + "/" + filename).c_str(),std::ifstream::binary);
  std::ofstream ofs((filepath + "/daq" + filename).c_str(),std::ofstream::binary);
  if ( ifs.fail() ) {
    cerr << "Can not open file " << filepath << filename << endl;
    return 1;
  }
  
  vector <uint32_t> slotdata;
  
  uint32_t* dataPtr = new uint32_t;
  uint32_t *dataPtr1= new uint32_t;
  
  ifs.seekg(pos);
  int i = 0;
  while (i<20) {
    i++;
    ifs.read((char*)dataPtr, 4);
   // MDdataWordBM dw(dataPtr);
    //printf(ofs," %02X", *dataPtr);
    cout<<hex<<*dataPtr;
    ofs.write((char*)dataPtr, 4); 
  }
 return 0;
}
