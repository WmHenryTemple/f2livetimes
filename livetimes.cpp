#include "readReport.cpp"
#include "TROOT.h"
#include "TSystem.h"
#include "TFile.h"
#include "TLine.h"
#include "TPaveText.h"
#include "TMath.h"
#include "TTree.h"

Double_t calcBinomRatioErr(Double_t numerCnts, Double_t denomCnts) {
  return (0.5*(Double_t) numerCnts / (Double_t) denomCnts) * TMath::Sqrt((1./((Double_t) numerCnts)) + (1./((Double_t) denomCnts)));
}

void livetimes(Int_t run=2484){
  string spec="shms";
  string arm="P";
  string lcase="p";
  if(run<2200){spec="hms";arm="H";lcase="h";}

  int tightCut=0;
  clock_t t=clock();
  Double_t ps=readReport(run,"Ps2 fact");
  //  if(ps<9)return;
  Double_t tdc2ns=0.09766;//corrected cuts below will change
  //  Double_t edtmHigh=113;
  //  Double_t edtmLow=109;
  Double_t edtmHigh=181;
  Double_t edtmLow=151;
  Double_t edtmRefHigh=111.25;
  Double_t edtmRefLow=109.25;
  Double_t edtmRefHigh2=156.75;
  Double_t edtmRefLow2=154.75;
  Double_t trigHigh=371;
  Double_t trigLow=340;
  Double_t diffCut=189;

  // declare and intialize variables
  UInt_t edtm_scaler_beamOn, edtm_tdc_beamOn, trig_scaler_beamOn, trig_tdc_beamOn;
  UInt_t edtm_scaler_beamOff, edtm_tdc_beamOff, trig_scaler_beamOff, trig_tdc_beamOff;
  edtm_scaler_beamOn = 0;
  edtm_tdc_beamOn = 0;
  trig_scaler_beamOn = 0;
  trig_tdc_beamOn = 0;

  edtm_scaler_beamOff = 0;
  edtm_tdc_beamOff = 0;
  trig_scaler_beamOff = 0;
  trig_tdc_beamOff = 0;

  // get trees and set branch addresses
  TString froot;
  if(spec=="shms"){
    froot = Form("/lustre/expphy/cache/hallc/E12-10-002/abishek/realpass-3c-shms-data/shms_replay_production_%d_-1.root",run);
  }
  if(spec=="hms"){  
froot = Form("/lustre/expphy/cache/hallc/E12-10-002/abishek/realpass-3b-hms-data/hms_replay_production_%d_-1.root",run);
 if(run>2005)froot = Form("/lustre/expphy/cache/hallc/E12-10-002/cmorean/realpass-3c-boiling/hms_replay_production_%d_-1.root",run);
  }

  if (!gSystem->AccessPathName(froot)==0){cout<<"Couldn't find file"<<endl;return;}

  if(ps<1)return;
  TFile *f=new TFile(froot);
  Double_t edtm_scaler, edtm_tdc, trig_scaler, trig_tdc, bcm, bcm_scaler, trig_scalerRate, evNumber, trig_tdc_raw, edtm_tdc_raw,s1x_scalerRate;  

  TTree *T=(TTree*)f->Get("T");
  T->SetBranchAddress(Form("T.%s.%sTRIG2_tdcTime",spec.c_str(),lcase.c_str()), &trig_tdc);
  T->SetBranchAddress(Form("T.%s.%sEDTM_tdcTime",spec.c_str(),lcase.c_str()), &edtm_tdc);
  T->SetBranchAddress(Form("T.%s.%sTRIG2_tdcTimeRaw",spec.c_str(),lcase.c_str()), &trig_tdc_raw);
  T->SetBranchAddress(Form("T.%s.%sEDTM_tdcTimeRaw",spec.c_str(),lcase.c_str()), &edtm_tdc_raw);
  T->SetBranchAddress(Form("%s.bcm.bcm4c.AvgCurrent",arm.c_str()), &bcm);

  TTree *TSP;
  if(spec=="shms")TSP=(TTree*)f->Get("TSP");
  if(spec=="hms")TSP=(TTree*)f->Get("TSH");
  TSP->SetBranchAddress(Form("%s.%sTRIG2.scaler",arm.c_str(),lcase.c_str()), &trig_scaler);
  TSP->SetBranchAddress(Form("%s.%sTRIG2.scalerRate",arm.c_str(),lcase.c_str()), &trig_scalerRate);
  //  TSP->SetBranchAddress(Form("%s.pTRIG1.scalerRate",arm.c_str()), &trig1_scalerRate);
  TSP->SetBranchAddress(Form("%s.S1X.scalerRate",arm.c_str()), &s1x_scalerRate);
  TSP->SetBranchAddress(Form("%s.EDTM.scaler",arm.c_str()), &edtm_scaler);
  TSP->SetBranchAddress(Form("%s.BCM4C.scalerCurrent",arm.c_str()), &bcm_scaler);
  TSP->SetBranchAddress("evNumber", &evNumber);

  //declare histos
  const Double_t rawmin=0*tdc2ns;
  const Double_t rawmax=4000*tdc2ns;
  const Double_t refmin=0;
  const Double_t refmax=800;
  const Double_t diffmin=0;
  const Double_t diffmax=300;

  TH1D * hedtm=new TH1D("hedtm","EDTM TDC Time",300,refmin,refmax);
  TH1D * htrig=new TH1D("htrig","TRIG2 TDC Time",300,refmin,refmax);
  TH1D * hedtm_raw=new TH1D("hedtm_raw","EDTM RAW TDC Time",300,rawmin,rawmax);
  TH1D * htrig_raw=new TH1D("htrig_raw","TRIG2 RAW TDC Time",300,rawmin,rawmax);
  TH1D * hdiff=new TH1D("hdiff","Trig2 raw - EDTM raw",300,diffmin,diffmax);

  TH1D * hedtm_cut=new TH1D("hedtm_cut","EDTM TDC Time",300,refmin,refmax);
  TH1D * htrig_cut=new TH1D("htrig_cut","TRIG2 TDC Time",300,refmin,refmax);
  TH1D * hedtm_raw_cut=new TH1D("hedtm_raw_cut","EDTM TDC Time",300,rawmin,rawmax);
  TH1D * htrig_raw_cut=new TH1D("htrig_raw_cut","TRIG2 TDC Time",300,rawmin,rawmax);  
  TH1D * hdiff_cut=new TH1D("hdiff_cut","Trig2 raw - EDTM raw",300,diffmin,diffmax);
  TH1D * htrigcut=new TH1D("htrigcut","TRIG2 rate",500,0,100000);
  TH1D * hs1xcut=new TH1D("hs1xcut","S1X rate",500,0,1000000);
  TH1D * hbcm=new TH1D("hbcm","BCM4C Current",500,2,85);


  //********  Event Tree  ************  
  Int_t nev=T->GetEntries();
  Double_t bcmCut=5.;
  const Int_t nevS=TSP->GetEntries();
  vector <double> eventNum;
  vector <double> bcmRead;

      //Need to find current cut first
      for(Int_t i=0;i<nevS;i++){
	if(i%10000==1)cout<<i<<endl;
	TSP->GetEntry(i);
	eventNum.push_back(evNumber);
	bcmRead.push_back(bcm_scaler);
	//    hedtm->Fill(edtm_tdc);
	//    htrig->Fill(trig_tdc);
	hbcm->Fill(bcm_scaler);
      }

      if(tightCut==1)
	{
	  bcmCut=hbcm->GetBinCenter(hbcm->GetMaximumBin())-2;
	}


  Double_t bcmS=0;
  Double_t ev=0;
  Double_t last=0;
  Int_t done=0;
  // nev=10000;
  for(Int_t i=0;i<nev;i++){
    if(i%10000==1)cout<<i<<endl;
    T->GetEntry(i);

    // Assign current to event # from scaler tree
    done=0;
   if(i+1>last)  //if the event number has passed the scaler event asoociated with current bcm value then time to get new value 
     {
       for(Int_t j=0;j<nevS;j++)
	 {
	   if(done==0)
	     {
	       //	       TSP->GetEntry(j);
	       //	       ev=evNumber;//1
	       if(eventNum.at(j)!=-1)ev=eventNum.at(j);
	       else ev=1e+30;
	       //	       if(ev==-1)ev=1e+30;// deal with last scaler read
	       if(ev>i+1)// this is the scaler ev i should use
		 {
		   done=1;
		   bcmS=bcmRead.at(j);
		   last=ev;
		   //		   cout << "i \t j \t bcmS \t ev"<<endl;
		   cout << std::fixed;
		   //		   cout << i <<"\t"<< j <<"\t"<< bcmS <<"\t"<<ev<<endl;
		  }
	      }
	  }
      }
  // *************************************************************
  // ************    DOne with finding current (bcms)  ***********
  // *************************************************************


   if(edtm_tdc_raw>0)
     {
   htrig->Fill(trig_tdc);
   htrig_raw->Fill(trig_tdc_raw*tdc2ns);
   hedtm->Fill(edtm_tdc);
   hedtm_raw->Fill(edtm_tdc_raw*tdc2ns);
   hdiff->Fill((trig_tdc_raw-edtm_tdc_raw)*tdc2ns);
     }
   if(tightCut!=1)hbcm->Fill(bcmS);



      // EDTM Event?
   //     if(abs(diffCut-tdc2ns*(-edtm_tdc_raw+trig_tdc_raw)) < 1 && edtm_tdc!=0){
   //   if(edtm_tdc_raw*tdc2ns>edtmLow && edtm_tdc_raw*tdc2ns<edtmHigh){
   //   if((edtm_tdc>edtmRefLow && edtm_tdc<edtmRefHigh)){//||(edtm_tdc>edtmRefLow2 && edtm_tdc<edtmRefHigh2)){
       if(edtm_tdc!=0){

      hedtm_cut->Fill(edtm_tdc);
      hedtm_raw_cut->Fill(edtm_tdc_raw*tdc2ns);
      hdiff_cut->Fill((trig_tdc_raw-edtm_tdc_raw)*tdc2ns);
      htrig_cut->Fill(trig_tdc);
      htrig_raw_cut->Fill(trig_tdc_raw*tdc2ns);
      if(bcmS>bcmCut)edtm_tdc_beamOn++;
      if(bcmS<bcmCut)edtm_tdc_beamOff++;
    }
    else{
    // if(trig_tdc > trigLow && trig_tdc < trigHigh){
      //   if(trig_tdc_raw*tdc2ns>trigLow && trig_tdc_raw*tdc2ns<trigHigh){
      if(bcmS>bcmCut)trig_tdc_beamOn++;
      if(bcmS<bcmCut)trig_tdc_beamOff++;
      //    }
  }
  }
  //********  Scaler Tree  ************  
  nev=TSP->GetEntries();
  //  nev=100;

  for(Int_t i=0;i<nev;i++){
    TSP->GetEntry(i);
    if(bcm_scaler>bcmCut){
      edtm_scaler_beamOn = edtm_scaler - edtm_scaler_beamOff;
      trig_scaler_beamOn = trig_scaler - trig_scaler_beamOff;
      htrigcut->Fill(trig_scalerRate);
      hs1xcut->Fill(s1x_scalerRate);
    }
    if(bcm_scaler<bcmCut){
      edtm_scaler_beamOff = edtm_scaler - edtm_scaler_beamOn;
      trig_scaler_beamOff = trig_scaler - trig_scaler_beamOn;
    }

  }
  
  cout << "\n=:=:=:=:=:=:=:=:=:=:=: EDTM =:=:=:=:=:=:=:=:=:=:=:\n" << endl;
  cout << "Beam On  TDC Counter    = " << edtm_tdc_beamOn    << endl;
  cout << "Beam Off TDC Counter    = " << edtm_tdc_beamOff   << endl;
  cout << "Beam On  Scaler Counter = " << edtm_scaler_beamOn    << endl;
  cout << "Beam Off Scaler Counter = " << edtm_scaler_beamOff   << endl;
  cout << "End of Run Scaler Read  = " << edtm_scaler               << endl;
  cout << "\n=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:\n" << endl;

  cout << "\n|-|-|-|-|-|-|-|-|-|-|- TRIG |-|-|-|-|-|-|-|-|-|-|-\n"             << endl;
  cout << "Beam On  TDC Counter            = " << trig_tdc_beamOn    << endl;
  cout << "Beam Off TDC Counter            = " << trig_tdc_beamOff    << endl;
  cout << "Beam On  Scaler Counter         = " << trig_scaler_beamOn    << endl;
  cout << "Beam Off Scaler Counter         = " << trig_scaler_beamOff    << endl;
  cout << "End of Run Scaler Read          = " << trig_scaler         << endl;
  cout << "\n|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-\n"             << endl;
  Double_t trigRate=htrigcut->GetMean();
  Double_t s1xrate=hs1xcut->GetMean();
  ofstream ofile;
  ofile.open("test.txt",ios::app | ios::out );
  ofile << run <<"\t" << ps <<"\t" << trigRate << "\t"<<s1xrate << "\t" << bcmCut << "\t";
  ofile<<edtm_tdc_beamOn<<"\t"<<edtm_tdc_beamOff<<"\t"<<edtm_scaler_beamOn<<"\t"<<edtm_scaler_beamOff<<"\t";
  ofile<<trig_tdc_beamOn<<"\t"<<trig_tdc_beamOff<<"\t"<<trig_scaler_beamOn<<"\t"<<trig_scaler_beamOff<<endl;


  htrig_cut->SetLineColor(kRed);
  hedtm_cut->SetLineColor(kRed);
  htrig_raw_cut->SetLineColor(kRed);
  hedtm_raw_cut->SetLineColor(kRed);
  hdiff_cut->SetLineColor(kRed);
  TCanvas *c1=new TCanvas();

  c1->Divide(4,2);
 
  c1->cd(1);
  gPad->SetLogy();
  htrig->Draw();
  htrig_cut->Draw("same");
  /*
  TLine *ttl=new TLine(trigLow,0,trigLow,htrig->GetMaximum());
  ttl->SetLineColor(kRed);
  ttl->Draw("same");
  TLine *tth=new TLine(trigHigh,0,trigHigh,htrig->GetMaximum());
  tth->SetLineColor(kRed);
  tth->Draw("same");
  */
    c1->cd(2);
  gPad->SetLogy();
  hedtm->Draw();
  hedtm_cut->Draw("same");
  /*
    TLine *tel=new TLine(edtmLow,0,edtmLow,hedtm->GetMaximum());
    tel->SetLineColor(kRed);
    tel->Draw("same");
    TLine *teh=new TLine(edtmHigh,0,edtmHigh,hedtm->GetMaximum());
    teh->SetLineColor(kRed);
    teh->Draw("same");
  */
  c1->cd(3);
  gPad->SetLogy();
  htrig_raw_cut->Draw();
  htrig_raw->Draw("same");
  c1->cd(4);
  gPad->SetLogy();
  hedtm_raw->Draw();
  hedtm_raw_cut->Draw("same");
  c1->cd(5);
  gPad->SetLogy();
  hdiff->Draw();
  hdiff_cut->Draw("same");
  c1->cd(6);
  gPad->SetLogy();
  hbcm->Draw();
  TLine *tb=new TLine(bcmCut,0,bcmCut,hbcm->GetMaximum());
  tb->SetLineColor(kRed);
  tb->Draw("same");

  c1->cd(7);
  htrigcut->Draw();

  c1->cd(8);
  hs1xcut->Draw();
 TPaveText *tx=new TPaveText(0.1,0.6,.5,.9,"NDC");

 TString string = Form("Run:%d",run);
 tx->AddText(string);
 string = Form("P_{central}:%2.2f",readReport(run,"mom"));
 tx->AddText(string);
 string = Form("Angle:%2.2f",readReport(run,"Spec Angle"));
 tx->AddText(string);
 string = Form("Target:%2.2f",readReport(run,"target"));
 tx->AddText(string);
 string = Form("pTRIG2 rate:%4.2f",readReport(run,"pTRIG2 rate"));
 tx->AddText(string);
 string = Form("Prescale fact:%2.1f",readReport(run,"Ps2 fact"));
 tx->AddText(string);
 string = Form("BCM cut:%2.3f",bcmCut);
 tx->AddText(string);
 tx->Draw();
 c1->SaveAs(Form("PDFs/SHMS_5uA_NE0_run%d.pdf",run));
  //  cout << "EDTM TDC" << "\t" << "EDTM scaler" << "\t" << "EDTM scaler CP" << "\t" << "EDTM scaler V2"<< endl;
  //  cout << edtmTdcHits << "\t" << edtmScalerCnts << "\t" << edtmScalerCntsCP << "\t" << edtmScalerCntsV2 << endl;

  //  cout << endl <<endl;

  //  cout << "Livetime:" << lt_edtm << " +/- " << lt_edtm_err*ps << endl;
 delete c1;
 t = clock()-t;
 printf("The Anaylsis took %.1f seconds \n",((float) t)/CLOCKS_PER_SEC);
return;
}
