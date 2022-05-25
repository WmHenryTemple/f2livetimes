
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
void systematics(Int_t fact=1){
  gStyle->SetTitleFontSize(0.07);
  gStyle->SetOptFit();
  gStyle->SetFitFormat("4.6g");
  TGraphErrors *grCLT=makeGr(fact,2);
  grCLT->SetTitle("Computer Live Time");
  grCLT->GetXaxis()->SetTitle("Trigger rate (Hz)");
  //  formatit(grCLT);
  grCLT->GetYaxis()->SetTitle("Live time");
  grCLT->GetYaxis()->SetRangeUser(.5,1.);
  grCLT->SetMarkerStyle(33);

  TPaveText *tx=new TPaveText(.1,.15,.3,.25,"NDC");
  TString tit;
  tit="Prescale factor 1";
  tx->AddText(tit);
  TCanvas *c1=new TCanvas();
  c1->Divide(1,2);
  c1->cd(1);
  grCLT->Draw("ap");
  tx->Draw();
  TF1 *flt=new TF1("flt","1/(1+[0]*x)");
  flt->SetLineStyle(7);
  flt->SetParName(0,"Busy Time");
  grCLT->Fit("flt");
  double t=flt->GetParameter(0);

  int n=grCLT->GetN();
  vector <double> res;
  double xx,yy,rr,ycalc,num;
  for(int i=0;i<n;i++)
    {
      grCLT->GetPoint(i,xx,yy);
      ycalc=1/(1+xx*t);
      num=(ycalc-yy)/yy;
      res.push_back(num);
      //      cout << num << endl;
    }
  gStyle->SetOptStat("nemrou");

  TH1D *h=new TH1D("h","Residuals from Fit",100,-.02,.08);
  n=res.size();
  for (int i=0;i<n;i++)h->Fill(res.at(i));
  c1->cd(2);
  h->Draw();



  return;
}
