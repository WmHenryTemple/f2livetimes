
#include "makeGr.cpp"
#include "makeReportGr.cpp"
void formatit(TGraphErrors *g)
{
  g->GetXaxis()->SetLabelSize(.05);
  g->GetYaxis()->SetLabelSize(.05);
  g->GetXaxis()->SetTitleSize(.04);
  g->GetYaxis()->SetTitleSize(.04);
  g->GetXaxis()->SetTitleOffset(1);
  g->GetYaxis()->SetTitleOffset(.8);
  g->SetMarkerStyle(33);
}
void clt(Int_t fact=1){
  gStyle->SetTitleFontSize(0.07);
  gStyle->SetOptFit();
  gStyle->SetFitFormat("4.6g");
  TGraphErrors *grCLT=makeGr(fact,1);

  grCLT->SetTitle("Total Live Time (EDTM)");
  grCLT->GetXaxis()->SetTitle("Trigger rate (Hz)");
  formatit(grCLT);
  grCLT->GetYaxis()->SetTitle("Live time");
  grCLT->GetYaxis()->SetRangeUser(.5,1.2);

  TPaveText *tx=new TPaveText(.1,.15,.3,.25,"NDC");
  TString tit;
  if(fact<99)tit=Form("Prescale factor %d",fact);
 else tit="All Prescales";
  tx->AddText(tit);
  TCanvas *c1=new TCanvas();

  grCLT->Draw("ap");
tx->Draw();
  TF1 *flt=new TF1("flt","1/(1+[0]*x)");
  TF1 *p1=new TF1("p1","[0]");
  p1->SetParameter(0,.8);
  flt->SetLineStyle(7);
  flt->SetLineColor(kRed);
  flt->SetParName(0,"Busy Time");
  if(fact==1){
  grCLT->Fit("flt");
  }

  return;
}
