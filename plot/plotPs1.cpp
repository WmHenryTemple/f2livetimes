#include "makeGr.cpp"
#include "makeReportGr.cpp"

void plotPs1(){
  gStyle->SetOptFit();
  TGraphErrors *grTLT=makeGr(1,1);
  TGraphErrors *grCLT=makeGr(1,2);
  TGraphErrors *grELT=makeGr(1,3);
  TGraphErrors *grRTLT=makeReportGr();

  grTLT->SetTitle("Total Live Time (EDTM)");
  grCLT->SetTitle("Computer Live Time");
  grELT->SetTitle("Electronic Live Time (TLT/CLT)");
  grRTLT->SetTitle("Total Live Time (EDTM), Report File, Beam off corrected;");

  grTLT->GetXaxis()->SetTitle("Trigger rate (Hz)");
  grRTLT->GetXaxis()->SetTitle("Trigger rate (Hz)");
  grCLT->GetXaxis()->SetTitle("Trigger rate (Hz)");
  grELT->GetXaxis()->SetTitle("S1X rate (Hz)");

  grTLT->GetYaxis()->SetTitle("Live time");
  grCLT->GetYaxis()->SetTitle("Live time");
  grELT->GetYaxis()->SetTitle("Live time");

  //  grTLT->SetMarkerStyle(33);
  //  grCLT->SetMarkerStyle(33);
  //  grELT->SetMarkerStyle(33);

  TCanvas *c1=new TCanvas();
  c1->Divide(2,3);
  c1->cd(1);
  grTLT->Draw("ap");
  c1->cd(3);
  grCLT->Draw("ap");
  c1->cd(5);
  grELT->Draw("ap");
  c1->cd(2);
  grRTLT->Draw("ap");

  TF1 *flt=new TF1("flt","1/(1+[0]*x)",0,5);
  flt->SetLineStyle(7);
  flt->SetParName(0,"Busy Time");
  grTLT->Fit("flt");
  grRTLT->Fit("flt");
  grCLT->Fit("flt");
  flt->SetParameter(0,50e-9);
  grELT->Fit("flt");
  return;
}
