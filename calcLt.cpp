#include "readReport.cpp"

Double_t calcBinomRatioErr(Double_t numerCnts, Double_t denomCnts) {
  return (0.5*(Double_t) numerCnts / (Double_t) denomCnts) * TMath::Sqrt((1./((Double_t) numerCnts)) + (1./((Double_t) denomCnts)));
}

void calcLt(Int_t run=2550){

  Double_t ps=readReport(run,"Ps2 fact");
  TString froot = Form("/lustre/expphy/cache/hallc/E12-10-002/abishek/realpass-3b-shms-data/shms_replay_production_%d_-1.root",run);

  if (!gSystem->AccessPathName(froot)==0){cout<<"Couldn't find file"<<endl;return;}
  if (ps<0)return;
  Double_t edtm_scaler, edtm_tdc, trig_scaler, trig_tdc;
  Double_t edtm_scaler_cp, edtm_scaler_v2;
  TFile *f=new TFile(froot);
  f->Print();
  
  TTree *T=(TTree*)f->Get("T");
  TTree *TSP=(TTree*)f->Get("TSP");
  T->SetBranchAddress("T.shms.pTRIG2_tdcTime", &trig_tdc);
  T->SetBranchAddress("T.shms.pEDTM_tdcTime", &edtm_tdc);

  TSP->SetBranchAddress("P.pTRIG2.scaler", &trig_scaler);
  TSP->SetBranchAddress("P.EDTM.scaler", &edtm_scaler);
  TSP->SetBranchAddress("P.EDTM_CP.scaler", &edtm_scaler_cp);
  TSP->SetBranchAddress("P.pEDTM_V2.scaler", &edtm_scaler_v2);

  Double_t edtmTdcHits=0;
  Double_t edtmScalerCnts=0;
  Double_t edtmScalerCntsCP=0;
  Double_t edtmScalerCntsV2=0;

  //********  Event Tree  ************  
  Int_t nev=T->GetEntries();
  //  nev=100;
  for(Int_t i=0;i<nev;i++){
    if(i%10000==1)cout<<i<<endl;
    T->GetEntry(i);
    //    if(edtm_tdc>0)edtmTdcHits++;
    if(edtm_tdc > 109 && edtm_tdc < 113)edtmTdcHits++;
      
  }
  //********  Scaler Tree  ************  
  nev=TSP->GetEntries();
  //  nev=100;

  for(Int_t i=0;i<nev;i++){
    TSP->GetEntry(i);
    edtmScalerCnts=edtm_scaler;
    edtmScalerCntsCP=edtm_scaler_cp;
    edtmScalerCntsV2=edtm_scaler_v2;
  }
  Double_t lt_edtm=  edtmTdcHits * ps / edtmScalerCnts;
  Double_t lt_edtm_err=calcBinomRatioErr(edtmTdcHits, edtmScalerCnts);
  

  cout << "EDTM TDC" << "\t" << "EDTM scaler" << "\t" << "EDTM scaler CP" << "\t" << "EDTM scaler V2"<< endl;
  cout << edtmTdcHits << "\t" << edtmScalerCnts << "\t" << edtmScalerCntsCP << "\t" << edtmScalerCntsV2 << endl;

  cout << endl <<endl;

  cout << "Livetime:" << lt_edtm << " +/- " << lt_edtm_err*ps << endl;

return;
}
