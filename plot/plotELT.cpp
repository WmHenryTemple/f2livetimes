#include "makeGr.cpp"

void plotELT(){
  //  gStyle->SetOptFit();

  TGraphErrors* grt=makeGr(99,3);
  TGraphErrors* gr1t=makeGr(1,3);
  TGraphErrors* gr2t=makeGr(2,3);
  TGraphErrors* gr3t=makeGr(3,3);
  TGraphErrors* gr5t=makeGr(5,3);
  TGraphErrors* gr9t=makeGr(9,3);
  TGraphErrors* gr17t=makeGr(17,3);
  //  gr5=makeGr(5);

  gr1t->SetMarkerStyle(33);
  gr2t->SetMarkerStyle(33);
  gr3t->SetMarkerStyle(33);
  gr5t->SetMarkerStyle(33);
  gr9t->SetMarkerStyle(33);
  gr17t->SetMarkerStyle(33);


  gr1t->SetMarkerColor(kRed);
  gr2t->SetMarkerColor(kBlue);
  gr3t->SetMarkerColor(kBlack);
  gr5t->SetMarkerColor(kMagenta);
  gr9t->SetMarkerColor(kGreen+3);
  gr17t->SetMarkerColor(kOrange);

  grt->SetTitle("Electronic Live Time");
  grt->GetXaxis()->SetTitle("Trigger rate");
  grt->GetYaxis()->SetTitle("Livetime");

  grt->GetYaxis()->SetRangeUser(0,1.3);
  grt->GetXaxis()->SetLimits(0,1000000);

  //  grt->Draw("ap");
  gr1t->Draw("ap");
  //  gr2t->Draw("sp");
  //  gr3t->Draw("sp");
  //  gr5t->Draw("sp");
  //  gr9t->Draw("sp");
  //  gr17t->Draw("sp");


  TLegend *leg=new TLegend(.1,.1,.4,.4);

  leg->AddEntry(gr1t,"ELT ps=1","p");


  leg->AddEntry(gr2t,"ELT ps=2","p");

  leg->AddEntry(gr3t,"ELT ps=3","p");

  leg->AddEntry(gr5t,"ELT ps=5","p");

  leg->AddEntry(gr9t,"ELT ps=9","p");

  leg->AddEntry(gr17t,"ELT ps=17","p");

  TF1 *fitFunc=new TF1("fitFunc","TMath::Exp(-[0]*x)",0,100000);  
  //    grt->Fit("fitFunc");
  gr1t->Fit("pol1");
    //    gr2t->Fit("pol1");
    //    gr3t->Fit("pol1");
    //    gr5t->Fit("pol1");
    //    gr9t->Fit("pol1");
    //    gr17t->Fit("pol1");

  leg->Draw();
}
