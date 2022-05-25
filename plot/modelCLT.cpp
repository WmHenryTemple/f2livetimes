#include "makeGr.cpp"

Double_t myFunc(Double_t n, Double_t tau, Double_t x)
{
Double_t answer=1/TMath::Factorial(n)*pow((tau*x),n)*TMath::Exp(-tau*x);
// if(n==0)answer=0;
  return answer;
}



void plotCLT(){
  gStyle->SetOptFit();
  TGraphErrors* gr1e=makeGr(1,1);
  TGraphErrors* gr2e=makeGr(2,1);
  TGraphErrors* gr3e=makeGr(3,1);
  TGraphErrors* gr5e=makeGr(5,1);
  TGraphErrors* gr9e=makeGr(9,1);
  TGraphErrors* gr17e=makeGr(17,1);

  TGraphErrors* gr1t=makeGr(1,2);
  TGraphErrors* gr2t=makeGr(2,2);
  TGraphErrors* gr3t=makeGr(3,2);
  TGraphErrors* gr5t=makeGr(5,2);
  TGraphErrors* gr9t=makeGr(9,2);
  TGraphErrors* gr17t=makeGr(17,2);
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

  gr1t->SetTitle("Computer Live Time");
  gr1t->GetXaxis()->SetTitle("Input rate (TRIG2/prescale)");
  gr1t->GetYaxis()->SetTitle("Livetime");
  //  gr1e->Draw("ap");
  gr1t->GetYaxis()->SetRangeUser(.5,1.05);
  gr1t->GetXaxis()->SetLimits(0,100000);
  /*
  gr1e->Draw("ap");
  gr2e->Draw("sp");
  gr3e->Draw("sp");
  gr5e->Draw("sp");
  gr9e->Draw("sp");
  gr17e->Draw("sp");
  */
  gr1t->Draw("ap");
  gr2t->Draw("sp");
  gr3t->Draw("sp");
  gr5t->Draw("sp");
  gr9t->Draw("sp");
  gr17t->Draw("sp");

  Double_t tau=0.100;

  TF1 *f1=new TF1("f1","myFunc(0,.00030,x)+myFunc(1,.00030,x)",0,100000);
  TF1 *f2=new TF1("f2","myFunc(0,.00030,x)+myFunc(1,.00030,x)+myFunc(2,.00030,x)",0,100000);
  TF1 *f3=new TF1("f3","myFunc(0,.00030,x)+myFunc(1,.00030,x)+myFunc(2,.00030,x)+myFunc(3,.00030,x)",0,100000);
  TF1 *f5=new TF1("f5","myFunc(0,.00030,x)+myFunc(1,.00030,x)+myFunc(2,.00030,x)+myFunc(3,.00030,x)+myFunc(4,.00030,x)+myFunc(5,.00030,x)",0,100000);
  TF1 *f9=new TF1("f9","myFunc(0,.00030,x)+myFunc(1,.00030,x)+myFunc(2,.00030,x)+myFunc(3,.00030,x)+myFunc(4,.00030,x)+myFunc(5,.00030,x)+myFunc(6,.00030,x)+myFunc(7,.00030,x)+myFunc(8,.00030,x)+myFunc(9,.00030,x)",0,100000);
  TF1 *f17=new TF1("f9","myFunc(0,.00030,x)+myFunc(1,.00030,x)+myFunc(2,.00030,x)+myFunc(3,.00030,x)+myFunc(4,.00030,x)+myFunc(5,.00030,x)+myFunc(6,.00030,x)+myFunc(7,.00030,x)+myFunc(8,.00030,x)+myFunc(9,.00030,x)+myFunc(10,.00030,x)+myFunc(11,.00030,x)+myFunc(12,.00030,x)+myFunc(13,.00030,x)+myFunc(14,.00030,x)+myFunc(15,.00030,x)+myFunc(16,.00030,x)+myFunc(17,.00030,x)",0,100000);      

  /*
  TF1 *f1=new TF1("f1","1-1/TMath::Factorial(2)*([0]*x)^2*TMath::Exp(-[0]*x)",0,3000);
  TF1 *f2=new TF1("f2","1-1/TMath::Factorial(3)*([0]*x)^3*TMath::Exp(-[0]*x)",0,12000);
  TF1 *f3=new TF1("f3","1-1/TMath::Factorial(4)*([0]*x)^4*TMath::Exp(-[0]*x)",0,20000);
  TF1 *f5=new TF1("f5","1-1/TMath::Factorial(6)*([0]*x)^6*TMath::Exp(-[0]*x)",0,25000)  ;
  TF1 *f9=new TF1("f9","1-1/TMath::Factorial(10)*([0]*x)^10*TMath::Exp(-[0]*x)",0,30000);
  TF1 *f17=new TF1("f17","1-1/TMath::Factorial(18)*([0]*x)^18*TMath::Exp(-[0]*x)",0,100000);
  */

  f1->SetLineStyle(7);
  f2->SetLineStyle(7);
  f3->SetLineStyle(7);
  f5->SetLineStyle(7);
  f9->SetLineStyle(7);
  f17->SetLineStyle(7);
  f1->SetLineColor(kRed);
  f2->SetLineColor(kBlue);
  f3->SetLineColor(kBlack);
  f5->SetLineColor(kMagenta);
  f9->SetLineColor(kGreen+3);
  f17->SetLineColor(kOrange);

  f1->SetParName(0,"Busy Time");


  //  gr1t->Fit("f1");

  //Double_t busy=f1->GetParameter(0);
  /*
  Double_t busy=320./1E6;
  f1->SetParameter(0,busy);
  f2->SetParameter(0,busy);
  f3->SetParameter(0,busy);
  f5->SetParameter(0,busy);
  f9->SetParameter(0,busy);
  f17->SetParameter(0,busy);
  */
  f1->Draw("same");  
  f2->Draw("same");
  f3->Draw("same");
  f5->Draw("same");
  f9->Draw("same");
  f17->Draw("same");

  TLegend *leg=new TLegend(.1,.1,.4,.4);
  //  leg->AddEntry(gr1e,"EDTM_{tdc hits}/EDTM_{scalers}","p");
  leg->AddEntry(gr1t,"CLT_{A} ps=1","p");


  leg->AddEntry(gr2t,"CLT_{A} ps=2","p");

  leg->AddEntry(gr3t,"CLT_{A} ps=3","p");

  leg->AddEntry(gr5t,"CLT_{A} ps=5","p");

  leg->AddEntry(gr9t,"CLT_{A} ps=9","p");

  leg->AddEntry(gr17t,"CLT_{A} ps=17","p");
  
  leg->Draw();
}
