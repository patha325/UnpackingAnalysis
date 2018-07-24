#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TH2.h"
#include "TH1.h"
//#include <vector>
using namespase std;

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

struct vectorsTree
{
  vector<double> *FEBSN=0;
  vector<double> *GTrigTag=0;
  vector<double> *GTrigTime=0;
  vector<double> *hitsChannel=0;
  vector<double> *hitAmpl=0;
  vector<double> *hitLGAmpl=0;
  vector<double> *hitLeadTime=0;
  vector<double> *hitTrailTime=0;
};



void t9rootFileanalysis()
{
    vector<string> vFileNames;
    string sFileName;
    ifstream fList("febs_files_list.list");
    while (!fList.eof()) {
        fList >> sFileName;
        //cout << sFileName << endl;
        vFileNames.push_back(sFileName);
    }
    string rootFileInput=GetLocation(vFileNames[0].c_str());
    string rootFileOutput=GetLocation (vFileNames[0].c_str());
    rootFileInput+="/all.root";
    rootFileOutput+="/histo.root";
    cout << rootFileInput<<endl;
    
    TFile *FileInput = new TFile(rootFileInput.c_str());
    
    vectorsTree FEB[65];
    
    TTree *FEBtree[65];
  
    ostringstream sFEBnum;
    string sFEB;
    for (Int_t ih=0; ih<64; ih++) {
        sFEBnum.str("");
        sFEBnum << ih;
        sFEB = "FEB_"+sFEBnum.str();
        FEBtree[ih] = (TTree*)FileInput->Get(sFEB.c_str());
        if (FEBtree[ih] = (TTree*)FileInput->Get(sFEB.c_str())){
            cout<<sFEB<<" ";
            FEBtree[ih]->SetBranchAddress((sFEB+"_SN").c_str(),&FEB[ih].FEBSN);
            /*FEBtree[ih]->SetBranchAddress((sFEB+"_GTrigTag").c_str(),&FEB[ih].GTrigTag);
            FEBtree[ih]->SetBranchAddress((sFEB+"_GTrigTime").c_str(),&FEB[ih].GTrigTime);
            FEBtree[ih]->SetBranchAddress((sFEB+"_hitsChannel").c_str(),&FEB[ih].hitsChannel);
            FEBtree[ih]->SetBranchAddress((sFEB+"_hitAmpl").c_str(),&FEB[ih].hitAmpl);
            FEBtree[ih]->SetBranchAddress((sFEB+"_hitLGAmpl").c_str(),&FEB[ih].hitLGAmpl);
            FEBtree[ih]->SetBranchAddress((sFEB+"_hitLeadTime").c_str(),&FEB[ih].hitLeadTime);
            FEBtree[ih]->SetBranchAddress((sFEB+"_hitTrailTime").c_str(),&FEB[ih].hitTrailTime);*/
           
            FEBtree[ih]->GetEntry();
            //cout << FEB[ih].FEBSN->size()<<endl;
        }
  }
 
  
  
  
  
//data check
  /* for (Int_t i=0; i<100; i++)
      {
          std::cout<<"FEB1: "<<FEB[1].FEBSN->at(i)<<" "<<FEB[1].GTrigTag->at(i)<<" "<<FEB[1].GTrigTime->at(i)<<" "<<FEB[1].hitsChannel->at(i)<<" "<<FEB[1].hitAmpl->at(i)<<" "<<FEB[1].hitLGAmpl->at(i)<<" "<<FEB[1].hitLeadTime->at(i)<<" "<<std::endl;
          std::cout<<"FEB9: "<<FEB[9].FEBSN->at(i)<<" "<<FEB[9].GTrigTag->at(i)<<" "<<FEB[9].GTrigTime->at(i)<<" "<<FEB[9].hitsChannel->at(i)<<" "<<FEB[9].hitAmpl->at(i)<<" "<<FEB[9].hitLGAmpl->at(i)<<" "<<FEB[9].hitLeadTime->at(i)<<" "<<std::endl<<std::endl;
      }
      */
   
   for (Int_t i=0;i<=64;i++){
    FEB[i].FEBSN=0;
    FEB[i].hitsChannel=0;
    FEB[i].hitAmpl=0;
    FEB[i].hitLeadTime=0;
    FEB[i].GTrigTag=0;
    FEB[i].GTrigTime=0;
    FEB[i].hitLGAmpl=0;
    FEB[i].hitTrailTime=0;
    //delete FEB[i];
    }
   

    FileInput->Close();
    vFileNames.clear();
    fList.close();
    return;
}
