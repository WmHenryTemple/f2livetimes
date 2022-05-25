
#include <iostream>
#include <iomanip>
#include <fstream>
#include "TPaveLabel.h"
#include "TH2F.h"
#include "TCanvas.h"

using namespace std;

TPaveText* labelWkine(Int_t irun=3021, Double_t x1=0.8,   Double_t y1=0.4,   Double_t x2=0.95,   Double_t y2=0.6){
  //  string froot;
  TString froot;
  ifstream file;
  string word, t, q, filename;
  string run, mom, tgt, ang, ene, tim, cur;
  froot = Form("/lustre/expphy/cache/hallc/E12-10-002/abishek/realpass-0-shms-report/replay_shms_production_%d_-1.report",irun);
  file.open(froot);
  cout <<" Is the File open?"<<  file.is_open()<<endl;

    if(file.is_open()==1)
      {
	cout<<froot<<endl;
	// extracting words from the file                                                  
	while (file >> word)
	  {
	    if (word=="Num"){
	      file >> word; //get colon                                                      
	      file >> run; //get value                                                       
	    }
	    if (word=="Momentum"){
	      file >> word; //get colon                                                      
	      file >> mom; //get value                                                       
	    }
	    if (word=="AMU"){
	      file >> word; //get colon                                                      
	      file >> tgt; //get value                                                       
	    }
	    if (word=="Theta"){
	      file >> word; //get colon                                                      
	      file >> ang; //get value                                                       
	    }
	    if (word=="Energy"){
	      file >> word; //get colon                                                      
	      file >> ene; //get value                                                       
	    }
	    if (word=="Length"){
	      file >> word; //get colon                                                      
	      file >> tim; //get value                                                       
	    }
	    if (word=="BCM1"){
	      file >> word; 
	      if (word=="Current:"){ //is the next word current
		file >> cur; //get value                                                       
	      }
	    }
	  }
      }
  cout << "Run"<<"\t"<<"Mom"<<"\t"<<"Tgt"<<"\t"<<"Theta"<<"\t"<<"Beam E"<<"\t"<<"BCM1"<<"\t"<<"time (s)"<<endl;
  cout << run<<"\t"<<mom<<"\t"<<tgt<<"\t"<<ang<<"\t"<<ene<<"\t"<<cur<<"\t"<<tim<<endl;
  file.close();

  TPaveText *tx=new TPaveText(x1,y1,x2,y2,"NDC");
  TString string;
  string = Form("Run:%s",run.c_str());
  tx->AddText(string);
  string = Form("P_{central}:%s",mom.c_str());
  tx->AddText(string);
  string = Form("Angle:%s",ang.c_str());
  tx->AddText(string);
  string = Form("Target:%s",tgt.c_str());
  tx->AddText(string);
  //  tx->Draw("same");





  return tx;



  
}
