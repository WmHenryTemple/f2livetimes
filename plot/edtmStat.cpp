#include <iomanip>
#include <fstream>
#include "readReport.cpp"
#include <vector>
using namespace std;
// plot three variables from readReport.cpp
// Plot clt and lt vs rate, with Markers to match Eric, Prescale=1
void nimEdtm(Double_t f_cut=0.5){
  gStyle->SetOptFit();
  vector<double> x;
  vector<double> y;

  Double_t fact,current,cutCurrent,rmeas,f,error,denom,numer;
  for(Int_t i=2400;i<3200;i++){
    {
      fact=readReport(i,"Ps2 fact");
      if(fact>0&&fact<20)
	{
	rmeas=readReport(i,"ps2 lt edtm");
	x.push_back(i);
	y.push_back(1./sqrt(readReport(i,"Accepted EDTM triggers")));
      }
    }
  }
  const Int_t arraySize1=x.size();
  TGraph *gr1=new TGraph(arraySize1,&x[0],&y[0]);
  gr1->SetTitle("1/sqrt(EDTM accepted triggers)"); 
  gr1->SetMarkerStyle(20);
  gr1->GetXaxis()->SetTitle("Run Number");
  TCanvas *c1=new TCanvas();
  gr1->Draw("ap");
  c1->SaveAs("edtmStat.pdf");
  return;

}
