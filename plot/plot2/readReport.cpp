
#include <iostream>
#include <iomanip>
#include <fstream>
#include "TPaveLabel.h"
#include "TH2F.h"
#include "TCanvas.h"

using namespace std;

Double_t readReport(Int_t irun=2524, TString what="p2x rate"){
  //  string froot;
  TString froot;
  ifstream file;

  string word;
  Double_t result;
  //  froot = Form("/lustre/expphy/cache/hallc/E12-10-002/abishek/realpass-2-hms-report/replay_hms_production_%d_-1.report",irun);
    froot = Form("/lustre/expphy/cache/hallc/E12-10-002/abishek/realpass-3-shms-report/replay_shms_production_%d_-1.report",irun);
  //  froot = Form("../reports/replay_shms_production_%d_-1.report",irun);
  //  froot = Form("reports/replay_shms_all_production_%d_200000.report",irun);

  file.open(froot);
  //   cout <<" Is the File open?"<<  file.is_open()<<endl;

  if(file.is_open()==1){
    ///////////////////////////
    if (what=="EDTM triggers"){
      while (file >> word){
	if(word=="EDTM"){
	  file>>word;
	if(word=="Triggers"){
	  file >>word >>result;
	  break;
	}}}}
    ///////////////////////////
    if (what=="Accepted EDTM triggers"){
      while (file >> word){
	if(word=="Accepted"){
	  file>>word;
	if(word=="EDTM"){
	  file>>word;
	if(word=="Triggers"){
	  file >> word>>result;
	}}}}}
    ///////////////////////////
    if (what=="beam over thresh"){
      while (file >> word){
	if(word=="Cut"){
	  file>>word;
	if(word=="on"){
	  file >> word >>word >>word >>word >>word>>word>>word;
	  file >> word >>word >>word >>word >>result;
	}}}}
    ///////////////////////////
    if (what=="energy"){
      while (file >> word){
	if (word=="Energy"){file >> word>>result;
	}}}
    ///////////////////////////
    if (what=="Spec Angle"){
      while (file >> word){
	  if (word=="Spec"){
	    file >> word; 
	    if (word=="Theta"){ 
	      file >> word >> result;
	    }}}}
    ///////////////////////////
    if (what=="mom"){
      while (file >> word){
	if (word=="Momentum"){
	  file >> word >>result; 
	}}}
    ///////////////////////////
      if (what=="target"){
	while (file >> word){
	  if (word=="Target"){
	    file >> word; 
	    if (word=="AMU"){ 
	      file >> word >> result; 
	    }}}}
    ///////////////////////////
      if (what=="BCM4C cut current"){
	while (file >> word){
	  if (word=="BCM4C"){
	    file >> word; 
	    if (word=="Beam"){ 
	      file >> word; 
	      if (word=="Cut"){ 
		file >> word; 
		if (word=="Current:"){ 
		  file >> result; 		
		}}}}}}
    ///////////////////////////////////
      if (what=="BCM4C current"){
	while (file >> word){
	  if (word=="BCM4C"){
	    file >> word; 
	    if (word=="Current:"){ 
	      file >> result; 
	    }}}}
    ///////////////////////////////////
      if (what=="BCM4C charge"){
	while (file >> word){
	  if (word=="BCM4C"){
	    file >> word; 
	    if (word=="Beam"){ 
	      file >> word; 
	      if (word=="Cut"){ 
		file >> word; 
		if (word=="Charge:"){ 
		  file >> result; 		
		}}}}}}
    ///////////////////////////////////
      if (what=="ps1 clt et"){
	while (file >> word){
	  if (word=="PS1"){
	    file >> word; 
	    if (word=="SHMS"){ 
	      file >> word >> word >> word >> word >> word >>result ;
	    }}}}
    ///////////////////////////////////
      if (what=="ps2 clt et"){
	while (file >> word){
	  if (word=="PS2"){
	    file >> word; 
	    if (word=="SHMS"){ 
	      file >> word >> word >> word >> word >> word >>result ;
	    }}}}
    ///////////////////////////////////
      if (what=="ps3 clt et"){
	while (file >> word){
	  if (word=="PS3"){
	    file >> word; 
	    if (word=="SHMS"){ 
	      file >> word >> word >> word >> word >> word >>result ;
	    }}}}
    ///////////////////////////////////
      if (what=="ps1 lt edtm"){
	while (file >> word){
	  if (word=="Pre-Scaled"){
	    file >> word;
	    if(word=="Ps1"){
	      file >> word  >> word;
	      if(word=="Live"){
		file >> word >> word >> word >>result;
	      }}}}}
    ///////////////////////////////////
      if (what=="ps2 lt edtm"){
	while (file >> word){
	  if (word=="Pre-Scaled"){
	    file >> word;
	    if(word=="Ps2"){
	      file >> word  >> word;
	      if(word=="Live"){
		file >> word >> word >> word >>result;
	      }}}}}
    ///////////////////////////////////
      if (what=="ps3 lt edtm"){
	while (file >> word){
	  if (word=="Pre-Scaled"){
	    file >> word;
	    if(word=="Ps3"){
	      file >> word  >> word;
	      if(word=="Live"){
		file >> word >> word >> word >>result;
	      }}}}}
    ///////////////////////////////////
      if (what=="ps1 clt"){
	while (file >> word){
	  if (word=="Pre-Scaled"){
	    file >> word;
	    if(word=="Ps1"){
	      file >> word >> word >> word;
	      if(word=="Live"){
		file >> word >> word >> result;
	      }}}}}
    ///////////////////////////////////
      if (what=="ps2 clt"){
	while (file >> word){
	  if (word=="Pre-Scaled"){
	    file >> word;
	    if(word=="Ps2"){
	      file >> word >> word >> word;
	      if(word=="Live"){
		file >> word >> word >> result;
	      }}}}}
    ///////////////////////////////////
      if (what=="ps3 clt"){
	while (file >> word){
	  if (word=="Pre-Scaled"){
	    file >> word;
	    if(word=="Ps3"){
	      file >> word >> word >> word;
	      if(word=="Live"){
		file >> word >> word >> result;
	      }}}}}
    ///////////////////////////////////
      if (what=="tr eff"){
	while (file >> word){
	  if (word=="E"){
	    file >> word;
	    if (word=="SING"){ 
	    // Get "FID     TRACK   EFFIC : "
	      file >> word >> word >> word >> word; 
	      file >> result;
	    }}}}
    ///////////////////////////////////
      if (what=="tr err"){
	while (file >> word){
	  if (word=="E"){
	    file >> word;
	    if (word=="SING"){ 
	    // Get "FID     TRACK   EFFIC : "
	      file >> word >> word >> word >> word; 
	      file >> word >> word>>result;
	    }}}}
    ///////////////////////////////////
      if (what=="p2x rate"){
	while (file >> word){
	  if (word=="P2X"){
	    	    cout << word << endl;
	    file >>word;
	  if (word==":"){
	    	    cout << word << endl;
	    file >> word >> word ;
	    	    cout << word << endl;
	  if (word=="["){
	    file>> result;
	    	    cout << result << endl;
	    //	    break;
	  }}}}}
    ///////////////////////////////////
      if (what=="lolo rate"){
	while (file >> word){
	  if (word=="pEL_LO_LO"){
	    file >> word >> word >>word>>result;
	  }}}
    ///////////////////////////////////
      if (what=="lo rate"){
	while (file >> word){
	  if (word=="pEL_LO"){
	    file >> word >> word >>word>>result;
	  }}}
    ///////////////////////////////////
      if (what=="hi rate"){
	while (file >> word){
	  //	    cout << word << endl;
	  if (word=="pEL_HI"){
	    file >> word >> word >>word>>result;
	  }}}
    ///////////////////////////////////
      if (what=="real rate"){
	while (file >> word){
	  if (word=="pEL_REAL"){
	    file >> word >> word >>word>>result;
	  }}}
    ///////////////////////////////////
      if (what=="clean rate"){
	while (file >> word){
	  if (word=="pEL_CLEAN"){
	    file >> word >> word >>word>>result;
	  }}}
    ///////////////////////////////////
      if (what=="stof rate"){
	while (file >> word){
	  if (word=="pSTOF"){
	    file >> word >> word >>word>>result;
	  }}}
    ///////////////////////////////////
      if (what=="pTRIG1 rate"){
	while (file >> word){
	  if (word=="pTRIG1"){
	    file >> word >> word >>word>>result;
	  }}}
    ///////////////////////////////////
      if (what=="pTRIG2 rate"){
	while (file >> word){
	  if (word=="pTRIG2"){
	    file >> word >> word >>word>>result;
	  }}}
    ///////////////////////////////////
      if (what=="pTRIG3 rate"){
	while (file >> word){
	  if (word=="pTRIG3"){
	    file >> word >> word >>word>>result;
	  }}}
    ///////////////////////////////////
      if (what=="Ps1 fact"){
	while (file >> word){
	  if (word=="Ps1_factor"){
	    file >> word >> result;
	  }}}
    ///////////////////////////////////
      if (what=="Ps2 fact"){
	while (file >> word){
	  if (word=="Ps2_factor"){
	    file >> word >> result;
	  }}}
    ///////////////////////////////////
      if (what=="Ps3 fact"){
	while (file >> word){
	  if (word=="Ps3_factor"){
	    file >> word >> result;
	  }}}
    ///////////////////////////////////
      if (what=="Ps4 fact"){
	while (file >> word){
	  if (word=="Ps4_factor"){
	    file >> word >> result;
	  }}}
    ///////////////////////////////////
      if (what=="edtm dt"){
	while (file >> word){
	  if (word=="Pre-Scaled"){
	    file >> word;
	    if(word=="Ps2"){
	      file >>word;
	      if (word=="Total"){
		file >>word;
		if (word=="Dead"){
		  file >>word;
		  if (word=="Time"){
		    file >>word;
		    if (word=="(EDTM)"){
		      cout << word<<endl;
		      file >>word>>result;	
		      cout << word<<endl;
		      cout << result<<endl;
		    }}}}}}}}
    ///////////////////////////////////
  }
  file.close();

  return result;
}
