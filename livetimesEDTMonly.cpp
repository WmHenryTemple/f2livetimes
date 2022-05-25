#include "readReport.cpp"

Double_t calcBinomRatioErr(Double_t numerCnts, Double_t denomCnts) {
  return (0.5*(Double_t) numerCnts / (Double_t) denomCnts) * TMath::Sqrt((1./((Double_t) numerCnts)) + (1./((Double_t) denomCnts)));
}

void livetimesEDTMonly(Int_t run=2550){

    Double_t ps=readReport(run,"Ps2 fact");
    if(ps==3)
    {
  Double_t edtmHigh=111;
  Double_t edtmLow=109;
  Double_t rawLow=1400;
  Double_t rawHigh=1850;


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
  TString froot = Form("/lustre/expphy/cache/hallc/E12-10-002/abishek/realpass-3b-shms-data/shms_replay_production_%d_-1.root",run);
  if (!gSystem->AccessPathName(froot)==0){cout<<"Couldn't find file"<<endl;return;}
  if(ps<1)return;
  TFile *f=new TFile(froot);
  Double_t evNumber,edtm_scaler, edtm_tdc, trig_scaler, edtm_raw, bcm, bcm_scaler, trig_scalerRate;  
  TTree *T=(TTree*)f->Get("T");
  T->SetBranchAddress("T.shms.pEDTM_tdcTimeRaw", &edtm_raw);
  T->SetBranchAddress("T.shms.pEDTM_tdcTime", &edtm_tdc);
  T->SetBranchAddress("P.bcm.bcm4c.AvgCurrent", &bcm);

  TTree *TSP=(TTree*)f->Get("TSP");
  TSP->SetBranchAddress("P.pTRIG2.scaler", &trig_scaler);
  TSP->SetBranchAddress("P.pTRIG2.scalerRate", &trig_scalerRate);
  TSP->SetBranchAddress("P.EDTM.scaler", &edtm_scaler);
  TSP->SetBranchAddress("P.BCM4C.scalerCurrent", &bcm_scaler);
  TSP->SetBranchAddress("evNumber", &evNumber);

  //declare histos
  TH1D * hedtm=new TH1D("hedtm","EDTM TDC Time",500,90,180);
  TH1D * hraw=new TH1D("hraw","EDTM raw TDC Time",500,1300,1900);
  TH1D * htrigcut=new TH1D("htrigcut","pTRIG2 rate",500,0,100000);
  TH1D * hbcm=new TH1D("hbcm","BCM4C Current",500,0,80);


  //********  Event Tree  ************  
  Int_t nev=T->GetEntries();
  Int_t nevS=TSP->GetEntries();
  Double_t  bcmCut=5.;
 Double_t bcmS=0;
 Double_t ev=0;
 Double_t last=0;
 Double_t thisEntry=0;
 Int_t done=0;


 for(Int_t i=0;i<nev;i++){
    if(i%10000==1)cout<<i<<endl;
    T->GetEntry(i);
    done=0;

    if(i+1>last) // 1 > 1
      {
	for(Int_t j=0;j<nevS;j++)
	  {
	    if(done==0)
	      {
		TSP->GetEntry(j);
		ev=evNumber;//1
		if(evNumber==-1)ev=1e+30;
		if(ev>i+1)
		  {
		    done=1;
		    thisEntry=j;
		    bcmS=bcm_scaler;
		    last=evNumber;
		    hbcm->Fill(bcmS);
		  }
	      }
	  }
      }
    //    cout << "i: "<<i<<"    BCM: "<<bcmS<<endl;

    hedtm->Fill(edtm_tdc);
    hraw->Fill(edtm_raw);
    if(edtm_tdc > edtmLow && edtm_tdc < edtmHigh && edtm_raw<rawHigh && edtm_raw>rawLow){
      if(bcmS>bcmCut)edtm_tdc_beamOn++;
      if(bcmS<bcmCut)edtm_tdc_beamOff++;
    }
    else
      {
      if(bcmS>bcmCut)trig_tdc_beamOn++;
      if(bcmS<bcmCut)trig_tdc_beamOff++;
    }
    // cout<<"I made it here"<<endl;
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
    }
    if(bcm_scaler<bcmCut){
      edtm_scaler_beamOff = edtm_scaler - edtm_scaler_beamOn;
      trig_scaler_beamOff = trig_scaler - trig_scaler_beamOn;
    }

  }
 cout<<"I made it here"<<endl;
  //  Double_t lt_edtm=  edtmTdcHits * ps / edtmScalerCnts;
  //  Double_t lt_edtm_err=calcBinomRatioErr(edtmTdcHits, edtmScalerCnts);
  
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
  ofstream ofile;
  ofile.open("livetimesEDTMonly.txt",ios::app | ios::out );
  ofile << run <<"\t" << ps <<"\t" << trigRate << "\t";
  ofile<<edtm_tdc_beamOn<<"\t"<<edtm_tdc_beamOff<<"\t"<<edtm_scaler_beamOn<<"\t"<<edtm_scaler_beamOff<<"\t";
  ofile<<trig_tdc_beamOn<<"\t"<<trig_tdc_beamOff<<"\t"<<trig_scaler_beamOn<<"\t"<<trig_scaler_beamOff<<endl;


  TCanvas *c1=new TCanvas();

  c1->Divide(2,2);
  c1->cd(1);
  gPad->SetLogy();
    hraw->Draw();

    TLine *ttl=new TLine(rawLow,0,rawLow,hraw->GetMaximum());
    ttl->SetLineColor(kRed);
    ttl->Draw("same");
    TLine *tth=new TLine(rawHigh,0,rawHigh,hraw->GetMaximum());
    tth->SetLineColor(kRed);
    tth->Draw("same");

    c1->cd(2);
  gPad->SetLogy();
  hedtm->Draw();
    TLine *tel=new TLine(edtmLow,0,edtmLow,hedtm->GetMaximum());
    tel->SetLineColor(kRed);
    tel->Draw("same");
    TLine *teh=new TLine(edtmHigh,0,edtmHigh,hedtm->GetMaximum());
    teh->SetLineColor(kRed);
    teh->Draw("same");
    c1->cd(3);
  gPad->SetLogy();
    hbcm->Draw();
    TLine *tb=new TLine(bcmCut,0,bcmCut,hbcm->GetMaximum());
    tb->SetLineColor(kRed);
    tb->Draw("same");

    c1->cd(4);
    htrigcut->Draw();

    c1->cd(2);
 TPaveText *tx=new TPaveText(0.5,0.7,.9,1,"NDC");

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
 tx->Draw();
 c1->SaveAs(Form("PDFs/run%d.pdf",run));
  //  cout << "EDTM TDC" << "\t" << "EDTM scaler" << "\t" << "EDTM scaler CP" << "\t" << "EDTM scaler V2"<< endl;
  //  cout << edtmTdcHits << "\t" << edtmScalerCnts << "\t" << edtmScalerCntsCP << "\t" << edtmScalerCntsV2 << endl;

  //  cout << endl <<endl;

  //  cout << "Livetime:" << lt_edtm << " +/- " << lt_edtm_err*ps << endl;
 delete c1;
    }
return;
}
