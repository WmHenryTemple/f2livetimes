#include <iomanip>
#include <fstream>
#include "readReport.cpp"
#include <vector>
using namespace std;
// plot three variables from readReport.cpp
// Plot clt and lt vs rate, with Markers to match Eric, Prescale=1
void reportEdtm(Double_t f_cut=0.0){
  gStyle->SetOptFit();
  vector<double> x1;
  vector<double> y1;
  vector<double> y1c;
  vector<double> y1e;

  Double_t fact,current,cutCurrent,rmeas,f,error,denom,numer;
  for(Int_t i=2400;i<3200;i++){
    {
      fact=readReport(i,"Ps2 fact");
      cutCurrent=readReport(i,"BCM4C cut current");
      current=readReport(i,"BCM4C current");
      f=(current/cutCurrent);
      if(fact<18&& fact>0 && f>f_cut)
	{
	rmeas=readReport(i,"ps2 lt edtm");
	x1.push_back(readReport(i,"pTRIG2 rate")/fact);
	y1.push_back(rmeas);
	y1c.push_back(100*(rmeas/100-(1-f))/f);
	denom=readReport(i,"EDTM triggers");
	numer=readReport(i,"Accepted EDTM triggers");
	error=0.5*numer/denom*TMath::Sqrt(1/denom+1/numer);
	y1e.push_back(error*100);
      }
    }
  }
  const Int_t arraySize1=x1.size();
  TCanvas *c1=new TCanvas();
  TF1 *flt=new TF1("flt","100/(1+[0]*x)",0,5);
  // flt->SetLineColor(kBlue);
  flt->SetLineStyle(7);
  //  flt1->SetLineStyle(10);
  flt->SetParName(0,"Busy Time");
  TGraphErrors *gr1=new TGraphErrors(arraySize1,&x1[0],&y1[0],0,&y1e[0]);
  gr1->SetTitle("EDTM livetime  corrected for beam off time"); 
  gr1->SetMarkerStyle(20);
  gr1->GetXaxis()->SetTitle("EL-Real Trigger Rate (kHz)");
  gr1->GetYaxis()->SetTitle("EDTM Livetime (%)");
  gr1->GetYaxis()->SetRangeUser(50,125);
  gr1->GetXaxis()->SetLimits(0,6);
  gr1->SetMarkerStyle(43);
  //  gr1->SetMarkerColor(kBlue);

  gr1->Draw("ap");
  gr1->Fit("flt");
  flt->Draw("same");
  c1->SaveAs("reportEdtm.pdf");
  return;

}
