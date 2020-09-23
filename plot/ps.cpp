
#include "makeGr.cpp"
#include "makeReportGr.cpp"

void ps(Int_t fact=1){
  gStyle->SetOptFit();
  TGraphErrors *grTLT=makeGr(fact,1);
  TGraphErrors *grCLT=makeGr(fact,2);
  TGraphErrors *grELT=makeGr(fact,3);

  grTLT->SetTitle("Total Live Time (EDTM)");
  grCLT->SetTitle("Computer Live Time");
  grELT->SetTitle("Electronic Live Time (TLT/CLT)");

  grTLT->GetXaxis()->SetTitle("Trigger rate (Hz)");
  grCLT->GetXaxis()->SetTitle("Trigger rate (Hz)");
  grELT->GetXaxis()->SetTitle("S1X rate (Hz)");

  grTLT->GetYaxis()->SetTitle("Live time");
  grCLT->GetYaxis()->SetTitle("Live time");
  grELT->GetYaxis()->SetTitle("Live time");

  //  grTLT->SetMarkerStyle(33);
  //  grCLT->SetMarkerStyle(33);
  //  grELT->SetMarkerStyle(33);

  TCanvas *c1=new TCanvas();

  c1->SetTitle(Form("Prescale factor %d",fact));
  c1->Divide(1,3);
  c1->cd(1);
  grTLT->Draw("ap");
  c1->cd(2);
  grCLT->Draw("ap");
  c1->cd(3);
  grELT->Draw("ap");

  TF1 *flt=new TF1("flt","1/(1+[0]*x)");
  flt->SetLineStyle(7);
  flt->SetParName(0,"Busy Time");
  if(fact==1){
  grTLT->Fit("flt");
  grCLT->Fit("flt");
  }
  flt->SetParameter(0,50e-9);
  grELT->Fit("flt");
  c1->SaveAs(Form("prescale%d.pdf",fact));

  return;
}
