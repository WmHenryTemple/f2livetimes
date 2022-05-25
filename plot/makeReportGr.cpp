#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;
// plot three variables from readReport.cpp
// Plot clt and lt vs rate, with Markers to match Eric, Prescale=1
TGraphErrors* makeReportGr(Double_t f_cut=-1,Int_t option=1){
  gStyle->SetOptFit();
  vector<double> x1;
  vector<double> y1;
  vector<double> y1c;
  vector<double> y1e;

  Double_t fact,current,cutCurrent,rmeas,f,error,denom,numer;
  for(Int_t i=2484;i<2996;i++){
    {
      fact=readReport(i,"Ps2 fact");
      cutCurrent=readReport(i,"BCM4C cut current");
      current=readReport(i,"BCM4C current");
      f=(current/cutCurrent);

      if(fact==1)
	{
	  x1.push_back(readReport(i,"pTRIG2 rate"));
	rmeas=readReport(i,"ps2 lt edtm");
	y1.push_back(rmeas);
	y1c.push_back((rmeas/100-(1-f))/f);
	denom=readReport(i,"EDTM triggers");
	numer=readReport(i,"Accepted EDTM triggers");
	error=sqrt(numer*(1-numer/denom))/denom*fact;
	y1e.push_back(error);
	cout << i << "\t"<< (rmeas/100-(1-f))/f<<endl;
      }
    }
  }
  const Int_t arraySize1=x1.size();
  TGraphErrors *gr1=new TGraphErrors(arraySize1,&x1[0],&y1c[0],0,&y1e[0]);
  return gr1;
}
