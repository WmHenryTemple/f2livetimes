
#include "makeGr.cpp"
#include "makeReportGr.cpp"

void eltRates(Int_t fact=99){
  gStyle->SetOptFit();
  TGraphErrors *gr1=makeGr(99,3,1);
  TGraphErrors *gr2=makeGr(99,3,2);
  TGraphErrors *gr3=makeGr(99,3,3);
  TGraphErrors *gr4=makeGr(99,3,4);
  TGraphErrors *gr5=makeGr(99,3,5);
  TGraphErrors *gr6=makeGr(99,3,6);
  TGraphErrors *gr7=makeGr(99,3,7);
  TGraphErrors *gr8=makeGr(99,3,8);

  gr1->SetTitle("Electronic Live Time (TLT/CLT)");
  gr2->SetTitle("Electronic Live Time (TLT/CLT)");
  gr3->SetTitle("Electronic Live Time (TLT/CLT)");
  gr4->SetTitle("Electronic Live Time (TLT/CLT)");
  gr5->SetTitle("Electronic Live Time (TLT/CLT)");
  gr6->SetTitle("Electronic Live Time (TLT/CLT)");
  gr7->SetTitle("Electronic Live Time (TLT/CLT)");
  gr8->SetTitle("Electronic Live Time (TLT/CLT)");

  gr1->GetXaxis()->SetTitle("S!X rate (Hz)");
  gr2->GetXaxis()->SetTitle("S!Y rate (Hz)");
  gr3->GetXaxis()->SetTitle("S2X rate (Hz)");
  gr4->GetXaxis()->SetTitle("S2Y rate (Hz)");
  gr6->GetXaxis()->SetTitle("S!XS2Y rate (Hz)");
  gr5->GetXaxis()->SetTitle("pTRIG1 rate (Hz)");
  gr7->GetXaxis()->SetTitle("elHi rate (Hz)");
  gr8->GetXaxis()->SetTitle("elLo rate (Hz)");

  TCanvas *c1=new TCanvas();
  c1->Divide(2,4);
  c1->cd(1);
  gr1->Draw("ap");
  c1->cd(2);
  gr2->Draw("ap");
  c1->cd(3);
  gr3->Draw("ap");
  c1->cd(4);
  gr4->Draw("ap");
  c1->cd(5);
  gr5->Draw("ap");
  c1->cd(6);
  gr6->Draw("ap");
  c1->cd(7);
  gr7->Draw("ap");
  c1->cd(8);
  gr8->Draw("ap");

  //  TF1 *flt=new TF1("flt","1/(1+[0]*x)",0,5);
  //  flt->SetLineStyle(7);
  //  flt->SetParName(0,"Busy Time");

  //  gr1->Fit("flt");
  return;
}
