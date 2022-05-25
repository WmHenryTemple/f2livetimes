
#include "makeGr.cpp"
#include "makeReportGr.cpp"
void formatit(TGraphErrors *g)
{
  g->GetXaxis()->SetLabelSize(.05);
  g->GetYaxis()->SetLabelSize(.05);
  g->GetXaxis()->SetTitleSize(.065);
  g->GetYaxis()->SetTitleSize(.07);
  g->GetXaxis()->SetTitleOffset(.6);
  g->GetYaxis()->SetTitleOffset(.25);

}
void ps2(Int_t fact=99){
  gStyle->SetTitleFontSize(0.07);
  gStyle->SetOptFit();
  gStyle->SetFitFormat("4.6g");
  TGraphErrors *grTLT=makeGr(fact,1);
  TGraphErrors *grCLT=makeGr(fact,2);
  TGraphErrors *grELT=makeGr(fact,3);
  TGraphErrors *grELT2=makeGr(fact,3);

  grTLT->SetTitle("Total Live Time (EDTM)");
  grCLT->SetTitle("Computer Live Time");
  grELT->SetTitle("Electronic Live Time (TLT/CLT)");
  grELT2->SetTitle("Electronic Live Time (TLT/CLT)");

  grTLT->GetXaxis()->SetTitle("Trigger rate (Hz)");
  grCLT->GetXaxis()->SetTitle("Trigger rate (Hz)");
  grELT->GetXaxis()->SetTitle("S1X rate (Hz)");
  grELT2->GetXaxis()->SetTitle("S1X rate (Hz)");
  formatit(grTLT);
  formatit(grCLT);
  formatit(grELT);
  formatit(grELT2);
  grTLT->GetYaxis()->SetTitle("Live time");
  grCLT->GetYaxis()->SetTitle("Live time");
  grELT->GetYaxis()->SetTitle("Live time");
  grELT2->GetYaxis()->SetTitle("Live time");

  grTLT->GetYaxis()->SetRangeUser(.5,1.2);
  grCLT->GetYaxis()->SetRangeUser(.5,1.2);
  grELT->GetYaxis()->SetRangeUser(.9,1.1);
  grELT2->GetYaxis()->SetRangeUser(.9,1.1);

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
  grELT2->Draw("sp");
  tx->Draw();
  TF1 *flt=new TF1("flt","1/(1+[0]*x)");  
  TF1 *p1=new TF1("p1","[0]+[1]*x");
  p1->SetLineColor(kRed);
  p1->SetParameter(1,-30E-9);
  flt->SetLineStyle(7);
  flt->SetParName(0,"Busy Time");
  if(fact==1){
  grTLT->Fit("flt");
  grCLT->Fit("flt");
  }
  flt->SetParameter(0,50e-9);
  ////    grELT->Fit("flt");
  grELT->Fit("p1");
  grELT2->Fit("pol0");
  gPad->Update();
  TPaveStats *stats2 = (TPaveStats*)grELT2->FindObject("stats");
  TPaveStats *stats = (TPaveStats*)grELT->FindObject("stats");
  stats->SetY1NDC(.6);
  stats->SetY2NDC(.95);
  stats2->SetY1NDC(.7);
  stats2->SetY2NDC(.95);

  stats2->SetX1NDC(.6);
  stats2->SetX2NDC(.75);
  stats->SetX1NDC(.75);
  stats->SetX2NDC(.95);


  stats->SetTextColor(kRed);
  stats->Draw("same");
  stats2->Draw("same");
  p1->Draw("same");
  c1->SaveAs(Form("prescale%d.pdf",fact));

  return;
}
