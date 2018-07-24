#include <vector>
#include <fstream>
#include <cstdio>
#include <stdlib.h>
#include <TColor.h>
//#include <TArc.c>

using namespace std;

//function for drawing hit
void hit(double x, double y, double r){
  TArc *arc = new TArc(x,y,r);
  arc->SetFillColor(kRed);
  arc->SetLineColor(kRed);
  arc->Draw("SAME");
}

//function for drawing module
void DetModule(double x1, double y1, double x2, double y2){
  TBox *b1 = new TBox(x1, y1, x2, y2);
  Int_t trans_blue = TColor::GetColorTransparent(kBlue, 0.5);
  b1->SetLineColor(trans_blue);
  b1->SetFillColor(trans_blue);
  b1->SetLineWidth(2);
  b1->SetFillStyle(1001);
  b1->Draw("SAME");
};

void IronModule(double x1, double y1, double x2, double y2){
  TBox *b1 = new TBox(x1, y1, x2, y2);
  Int_t trans_orange = TColor::GetColorTransparent(kOrange, 0.5); 
  b1->SetLineColor(trans_orange);
  b1->SetFillColor(trans_orange);
  b1->SetLineWidth(2);
  b1->SetFillStyle(1001);
  b1->Draw("SAME");
};

void drawsview(void){

  //drawing module

  const int NumberOfScintiModule = 18;
  const int NumberOfIronModule = 33;

 ifstream fin("Scin_Mod_position.txt");
 double z[4][NumberOfScintiModule];
   for(int i=0; i<NumberOfScintiModule; i++){
     fin >> z[0][i] >> z[1][i] >> z[2][i] >> z[3][i];
   } 
   
   ifstream fin2("Iron_Mod_position.txt");
   double zz[2][NumberOfIronModule];
   for(int i=0; i<NumberOfIronModule; i++){
     fin2 >> zz[0][i] >> zz[1][i];
   } 
   
 
   double Scin_thickness = 40; //cm
   double Iron_thickness = 40; //cm
 
  for(int i=0; i<18; i++){
    DetModule(z[3][i]-Scin_thickness/2, -986.2, z[3][i]+Scin_thickness/2, 986.2); 
  }

  for(int i=0; i<33; i++){
    IronModule(zz[1][i]-Iron_thickness/2-130, -986.2, zz[1][i]+Iron_thickness/2-130, 986.2); 
  }

  double x = -300;
  double y = -700;
  double y1 = 0;
  double y2 = 700;
  double r = 100;

  TArc *marrow1 = new TArc(x, y, r);
  TLine *t1 = new TLine(x-r/sqrt(2), y+r/sqrt(2), x+r/sqrt(2), y-r/sqrt(2)); 
  TLine *t2 = new TLine(x-r/sqrt(2), y-r/sqrt(2), x+r/sqrt(2), y+r/sqrt(2));

  TArc *marrow2 = new TArc(x, y1, r);
  TArc *marrow3 = new TArc(x, y1, r/10);

  TArc *marrow4 = new TArc(x, y2, r);
  TLine *t3 = new TLine(x-r/sqrt(2), y2+r/sqrt(2), x+r/sqrt(2), y2-r/sqrt(2)); 
  TLine *t4 = new TLine(x-r/sqrt(2), y2-r/sqrt(2), x+r/sqrt(2), y2+r/sqrt(2));

  marrow1->Draw("SAME");
  t1->Draw("SAME");
  t2->Draw("SAME");

  marrow2->Draw("SAME");
  marrow3->Draw("SAME");

  marrow4->Draw("SAME");
  t3->Draw("SAME");
  t4->Draw("SAME");

  fin.close();

}

void drawtview(void){

  //drawing module

  const int NumberOfScintiModule = 18;
  const int NumberOfIronModule = 33;

 ifstream fin("Scin_Mod_position.txt");
 double z[4][NumberOfScintiModule];
   for(int i=0; i<NumberOfScintiModule; i++){
     fin >> z[0][i] >> z[1][i] >> z[2][i] >> z[3][i];
   } 
   
   ifstream fin2("Iron_Mod_position.txt");
   double zz[2][NumberOfIronModule];
   for(int i=0; i<NumberOfIronModule; i++){
     fin2 >> zz[0][i] >> zz[1][i];
   } 
   
 
   double Scin_thickness = 40; //cm
   double Iron_thickness = 40; //cm
 
  for(int i=0; i<18; i++){
    DetModule(z[3][i]-Scin_thickness/2, -1315.2, z[3][i]+Scin_thickness/2, 1315.2); 
  }

  for(int i=0; i<33; i++){
    IronModule(zz[1][i]-Iron_thickness/2-130, -1750, zz[1][i]+Iron_thickness/2-130, 1750); 
  }



  fin.close();
  

}

TCanvas *monitor;
bool firstdraw=true;
 
//main program
void BMdisp(void){
  if(firstdraw){
  monitor = new TCanvas("monitor", "monitor", 1000, 800);
  monitor->Divide(1,2);
  firstdraw=0;
  }

  TH2F *h = new TH2F("","Side View", 5000, -100, 4900, 2172, -1086, 1086);
  //h->SetMinimum(0);
  //h->SetMaximum(1200);
  h->GetXaxis()->SetLabelSize(0);
  h->GetYaxis()->SetLabelSize(0);
  h->SetStats(0);
  h->GetXaxis()->SetNdivisions(0);
  h->GetYaxis()->SetNdivisions(0);

  TH2F *v = new TH2F("","Top View", 5000, -100, 4900, 3500, -1750, 1750 );
  //v->SetMinimum(0);
  //v->SetMaximum(1200);
  v->GetXaxis()->SetLabelSize(0);
  v->GetYaxis()->SetLabelSize(0);
  v->SetStats(0);
  v->GetXaxis()->SetNdivisions(0);
  v->GetYaxis()->SetNdivisions(0);

 

  monitor->cd(1);  
  v->Draw();
  drawtview();
  
  

  monitor->cd(2);
  h->Draw();
  drawsview();
  
  

  /*
  //drawing hit
  hit(300, 200, 15);
  */

  //monitor
  monitor->Update();
  monitor->Modified();


  /*  
  cout << "Type \'s\' to save the event display" << '\n';
  cout << "Type \'q\' to quit" << '\n';
 
  char ans[8];
  fgets(ans, 8, stdin);

  if( *ans == 's' ) monitor->Print("/Users/jinaren/Documents/T2K/BabyMIND/J-PARC_physics_run/image/image.pdf");
  */
  //monitor->Clear();
  

};
