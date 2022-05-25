
#include "makeGr3.cpp"
#include "makeReportGr.cpp"

void ps3(Int_t fact=1){
  gStyle->SetOptFit();
  gStyle->SetFitFormat("4.6g");
  TGraphErrors *grTLT=makeGr3(fact,1);
  TGraphErrors *grCLT=makeGr3(fact,2);
  TGraphErrors *grELT=makeGr3(fact,3);

  grTLT->SetTitle("Total Live Time (EDTM)");
  grCLT->SetTitle("Computer Live Time");
  grELT->SetTitle("Electronic Live Time (TLT/CLT)");

  grTLT->GetXaxis()->SetTitle("Trigger rate (Hz)");
  grCLT->GetXaxis()->SetTitle("Trigger rate (Hz)");
  grELT->GetXaxis()->SetTitle("S1X rate (Hz)");

  grTLT->GetYaxis()->SetTitle("Live time");
  grCLT->GetYaxis()->SetTitle("Live time");
  grELT->GetYaxis()->SetTitle("Live time");

  grTLT->GetYaxis()->SetRangeUser(.5,1.2);
  grCLT->GetYaxis()->SetRangeUser(.5,1.2);
  grELT->GetYaxis()->SetRangeUser(.5,1.2);

  //  grTLT->SetMarkerStyle(33);
  //  grCLT->SetMarkerStyle(33);
  //  grELT->SetMarkerStyle(33);

  TPaveText *tx=new TPaveText(.1,.15,.3,.25,"NDC");
  TString tit;
  if(fact<99)tit=Form("Prescale factor %d",fact);
 else tit="All Prescales";
  tx->AddText(tit);
  TCanvas *c1=new TCanvas();

  c1->SetTitle(Form("Prescale factor %d",fact));
  c1->Divide(1,3);
  c1->cd(1);
  grTLT->Draw("ap");
  c1->cd(2);
  grCLT->Draw("ap");

  c1->cd(3);
  grELT->Draw("ap");
tx->Draw();
  TF1 *flt=new TF1("flt","1/(1+[0]*x)");
  TF1 *p1=new TF1("p1","[0]");
  p1->SetParameter(0,.8);
  flt->SetLineStyle(7);
  flt->SetParName(0,"Busy Time");
  if(fact==1){
  grTLT->Fit("flt");
  grCLT->Fit("flt");
  }
  flt->SetParameter(0,50e-9);
    grELT->Fit("flt");
  //  grELT->Fit("p1");
  c1->SaveAs(Form("prescale%dcut7.pdf",fact));

  return;
}
