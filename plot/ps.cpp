
#include "makeGr.cpp"
#include "makeReportGr.cpp"
void formatit(TGraphErrors *g)
{
  g->GetXaxis()->SetLabelSize(.05);
  g->GetYaxis()->SetLabelSize(.05);
  g->GetXaxis()->SetTitleSize(.055);
  g->GetYaxis()->SetTitleSize(.07);
  g->GetXaxis()->SetTitleOffset(.6);
  g->GetYaxis()->SetTitleOffset(.65);

}
void ps(Int_t fact=99){

  gStyle->SetTitleX(.1);
  gStyle->SetTitleW(.6);
  gStyle->SetTitleFontSize(0.07);
  gStyle->SetOptFit();
  gStyle->SetFitFormat("4.6g");
  TGraphErrors *grTLT=makeGr(fact,1);
  TGraphErrors *grCLT=makeGr(fact,2);
  TGraphErrors *grELT=makeGr(fact,3);

  grTLT->SetTitle("Total Live Time (EDTM)");
  grCLT->SetTitle("Computer Live Time");
  grELT->SetTitle("Electronic Live Time (TLT/CLT)");

  grTLT->GetXaxis()->SetTitle("Trigger rate (Hz)");
  grCLT->GetXaxis()->SetTitle("Trigger rate (Hz)");
  grELT->GetXaxis()->SetTitle("S1X rate (Hz)");
  formatit(grTLT);
  formatit(grCLT);
  formatit(grELT);
  grTLT->GetYaxis()->SetTitle("Live time");
  grCLT->GetYaxis()->SetTitle("Live time");
  grELT->GetYaxis()->SetTitle("Live time");

  grTLT->GetYaxis()->SetRangeUser(.5,1.3);
  grCLT->GetYaxis()->SetRangeUser(.5,1.1);
  grELT->GetYaxis()->SetRangeUser(.8,1.2);

  //  grTLT->SetMarkerStyle(33);
  //  grCLT->SetMarkerStyle(33);
  //  grELT->SetMarkerStyle(33);

  TPaveText *tx=new TPaveText(.1,.15,.3,.25,"NDC");
  TString tit;
  if(fact<99)tit=Form("Prescale factor %d",fact);
 else tit="All Prescales";
  tx->AddText(tit);
  TCanvas *c1=new TCanvas("c1","c1",600,800);

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
  TF1 *p1=new TF1("p1","[0]+[1]*x",0,600000);
  TF1 *p0=new TF1("p0","[0]",0,600000);
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


  grELT->Fit("p0");
  gPad->Update();
  TPaveStats *staty = (TPaveStats*)grELT->FindObject("stats");  
  staty->SetName("poFit");
  staty->SetTextColor(kRed);
  staty->SetY1NDC(.65);
  staty->SetY2NDC(.99);
  staty->SetX1NDC(.70);
  staty->SetX2NDC(.99);
  grELT->Fit("p1");

  //  staty->Draw("same");

  /*
  TGraphErrors *dumb=(TGraphErrors*)grELT->Clone();
  dumb->SetName("dumb");
  dumb->Draw("sp");
  dumb->Fit("p1");

  c1->Update();
  TPaveStats *stat2 = (TPaveStats*)c1->GetPrimitive("stats");  
  stat2->SetName("dummy");
  stat2->SetTextColor(kRed);
  stat2->SetY1NDC(.75);
  stat2->SetY2NDC(.85);
  stat2->SetX1NDC(.80);
  stat2->SetX2NDC(.95);
  */

  p1->Draw("same");
  p0->Draw("same");

  //  staty->Draw("same");
  c1->SaveAs(Form("prescale%d.pdf",fact));

  //  return;
}
