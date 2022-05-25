#include "makeGr2.cpp"

void plotPs(){
  gStyle->SetOptFit();
  TGraphErrors* gr1e=makeGr2(1,1);
  TGraphErrors* gr2e=makeGr2(2,1);
  TGraphErrors* gr3e=makeGr2(3,1);
  TGraphErrors* gr5e=makeGr2(5,1);
  TGraphErrors* gr9e=makeGr2(9,1);
  TGraphErrors* gr17e=makeGr2(17,1);

  TGraphErrors* gr1t=makeGr2(1,2);
  TGraphErrors* gr2t=makeGr2(2,2);
  TGraphErrors* gr3t=makeGr2(3,2);
  TGraphErrors* gr5t=makeGr2(5,2);
  TGraphErrors* gr9t=makeGr2(9,2);
  TGraphErrors* gr17t=makeGr2(17,2);
  //  gr5=makeGr(5);

  gr1e->SetMarkerStyle(20);
  gr2e->SetMarkerStyle(20);
  gr3e->SetMarkerStyle(20);
  gr5e->SetMarkerStyle(20);
  gr9e->SetMarkerStyle(20);
  gr17e->SetMarkerStyle(20);

  gr1t->SetMarkerStyle(25);
  gr2t->SetMarkerStyle(25);
  gr3t->SetMarkerStyle(25);
  gr5t->SetMarkerStyle(25);
  gr9t->SetMarkerStyle(25);
  gr17t->SetMarkerStyle(25);


  gr1e->SetMarkerColor(kRed);
  gr2e->SetMarkerColor(kBlue);
  gr3e->SetMarkerColor(kBlack);
  gr5e->SetMarkerColor(kMagenta);
  gr9e->SetMarkerColor(kGreen+3);
  gr17e->SetMarkerColor(kOrange);


  gr1t->SetMarkerColor(kRed);
  gr2t->SetMarkerColor(kBlue);
  gr3t->SetMarkerColor(kBlack);
  gr5t->SetMarkerColor(kMagenta);
  gr9t->SetMarkerColor(kGreen+3);
  gr17t->SetMarkerColor(kOrange);

  gr1e->Draw("ap");
  gr1e->GetYaxis()->SetRangeUser(.5,1.05);
  gr1e->GetXaxis()->SetLimits(0,60000);
  gr1e->Draw("ap");
  gr2e->Draw("sp");
  gr3e->Draw("sp");
  gr5e->Draw("sp");
  gr9e->Draw("sp");
  gr17e->Draw("sp");

  gr1t->Draw("sp");
  gr2t->Draw("sp");
  gr3t->Draw("sp");
  gr5t->Draw("sp");
  gr9t->Draw("sp");
  gr17t->Draw("sp");

  TF1 *flt=new TF1("flt","1/(1+[0]*x)",0,60000);
  TF1 *flt2=new TF1("flt2","1/(1+[0]*x/2)",0,60000);
  TF1 *flt3=new TF1("flt3","1/(1+[0]*x/2)",0,60000);
  TF1 *flt5=new TF1("flt5","1/(1+[0]*x/2)",0,60000);
  TF1 *flt9=new TF1("flt9","1/(1+[0]*x/2)",0,60000);
  TF1 *flt17=new TF1("flt17","1/(1+[0]*x/2)",0,60000);
  flt->SetLineStyle(7);
  flt2->SetLineStyle(7);
  flt3->SetLineStyle(7);
  flt5->SetLineStyle(7);
  flt9->SetLineStyle(7);
  flt17->SetLineStyle(7);
  flt->SetLineColor(kRed);
  flt2->SetLineColor(kBlue);
  flt3->SetLineColor(kBlack);
  flt5->SetLineColor(kMagenta);
  flt9->SetLineColor(kGreen+3);
  flt17->SetLineColor(kOrange);

    flt->SetParName(0,"Busy Time");


  gr1e->Fit("flt");
  flt->Draw("same");
  Double_t busy=flt->GetParameter(0);
  busy=270./1E6;
  flt2->SetParameter(0,busy/2.);
  flt3->SetParameter(0,busy/3.);
  flt5->SetParameter(0,busy/5.);
  flt9->SetParameter(0,busy/9.);
  flt17->SetParameter(0,busy/17.);

  flt2->Draw("same");
  flt3->Draw("same");
  flt5->Draw("same");
  flt9->Draw("same");
  flt17->Draw("same");

  TLegend *leg=new TLegend(.6,.1,.9,.6);
  leg->AddEntry(gr1e,"EDTM ps fact=1","p");
  leg->AddEntry(gr1t,"TRIG ps fact=1","p");
  leg->AddEntry(gr2e,"EDTM ps fact=2","p");
  leg->AddEntry(gr2t,"TRIG ps fact=2","p");
  leg->AddEntry(gr3e,"EDTM ps fact=3","p");
  leg->AddEntry(gr3t,"TRIG ps fact=3","p");
  leg->AddEntry(gr5e,"EDTM ps fact=5","p");
  leg->AddEntry(gr5t,"TRIG ps fact=5","p");
  leg->AddEntry(gr9e,"EDTM ps fact=9","p");
  leg->AddEntry(gr9t,"TRIG ps fact=9","p");
  leg->AddEntry(gr17e,"EDTM ps fact=17","p");
  leg->AddEntry(gr17t,"TRIG ps fact=17","p");
  leg->Draw();
}
