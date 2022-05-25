#include "makeGr.cpp"
Double_t myFunc(Double_t *x, Double_t *par)
{
  Double_t xx=x[0];
  Double_t answer=0;
  //  answer=1/(1+par[1]*xx);
  for(Int_t i=0;i<par[0];i++)
    {

answer+=1/TMath::Factorial(i)*pow((par[1]*xx),i)*TMath::Exp(-par[1]*xx);
    }
  return answer;
}


void modelCLT2(){
  //  gStyle->SetOptFit();
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
  gr1t->GetXaxis()->SetTitle("pTRIG2 rate");
  gr1t->GetYaxis()->SetTitle("Livetime");
  //  gr1e->Draw("ap");
  gr1t->GetYaxis()->SetRangeUser(.5,1.05);
  gr1t->GetXaxis()->SetLimits(0,60000);
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


  TF1 *f1=new TF1("f1",myFunc,0,50000,2);
  f1->FixParameter(0,1);
  f1->SetParameter(1,.0002);


  TF1 *f2=new TF1("f2",myFunc,0,50000,2);
  f2->FixParameter(0,2);
  f2->SetParameter(1,.0002);


  TF1 *f3=new TF1("f3",myFunc,0,50000,2);
  f3->FixParameter(0,3);
  f3->SetParameter(1,.0002);


  TF1 *f5=new TF1("f5",myFunc,0,50000,2);
  f5->FixParameter(0,5);
  f5->SetParameter(1,.0002);


  TF1 *f9=new TF1("f9",myFunc,0,50000,2);
  f9->FixParameter(0,9);
  f9->SetParameter(1,.0002);

  TF1 *f17=new TF1("f17",myFunc,0,50000,2);
  f17->FixParameter(0,17);
  f17->SetParameter(1,.0002);



  f1->SetLineStyle(7);
  f1->SetLineColor(kRed);
  f2->SetLineStyle(7);
  f3->SetLineStyle(7);
  f5->SetLineStyle(7);
  f9->SetLineStyle(7);
  f17->SetLineStyle(7);

  f2->SetLineColor(kBlue);
  f3->SetLineColor(kBlack);
  f5->SetLineColor(kMagenta);
  f9->SetLineColor(kGreen+3);
  f17->SetLineColor(kOrange);


  gr1t->Fit("f1");
  gr2t->Fit("f2");
  gr3t->Fit("f3");
  gr5t->Fit("f5");
  gr9t->Fit("f9");
  gr17t->Fit("f17");

  gPad->Update();
  TLegend *leg=new TLegend(.6,.1,.9,.4);
  //  leg->AddEntry(gr1e,"EDTM_{tdc hits}/EDTM_{scalers}","p");
  leg->AddEntry(gr1t,"CLT_{A} ps=1","p");


  leg->AddEntry(gr2t,"CLT_{A} ps=2","p");

  leg->AddEntry(gr3t,"CLT_{A} ps=3","p");

  leg->AddEntry(gr5t,"CLT_{A} ps=5","p");

  leg->AddEntry(gr9t,"CLT_{A} ps=9","p");

  leg->AddEntry(gr17t,"CLT_{A} ps=17","p");
  
  leg->Draw();
}
