#include "../readReport.cpp"
#include "getLivetime.cpp"

Double_t calcBinomRatioErr(Double_t numerCnts, Double_t denomCnts) {
  return (0.5*(Double_t) numerCnts / (Double_t) denomCnts) * TMath::Sqrt((1./((Double_t) numerCnts)) + (1./((Double_t) denomCnts)));
}

void compareCLT(Double_t fact=1,Int_t option=1){
gStyle->SetOptFit();
 TH1F *h=new TH1F("h","Calculate/ReportFile",100,.98,1.02);

 vector <float> rate, run, dt, err,x,xe;
 for(int i=1565;i<3227;i++)

   {
     //     cout << i << endl;
     Double_t val2=readReport(i,"ps2 clt")/100.;
     Double_t val1=getLivetime(i,"clt");

     if(val1!=-99. && !TMath::IsNaN(val1))
       {
	 if(val1/val2<.995)cout << i<<"\t" << val1 << "\t"<< val2 << "\t" << val1/val2 << endl;
	 dt.push_back(val1);
	 x.push_back(val2);
	 h->Fill(val1/val2);

       }
   }
  Int_t pts=dt.size();
  cout << "There were this many:" << pts<<endl;

TGraphErrors *g=new TGraphErrors(pts,&x[0],&dt[0],0,0);
  g->GetYaxis()->SetTitle("Calculated LiveTime");
  g->GetXaxis()->SetTitle("LiveTime Report file");
  g->Draw("ap");
  g->GetYaxis()->SetRangeUser(0.,1.1);
  g->GetXaxis()->SetRangeUser(0.,1.1);
  g->SetMarkerStyle(20);

TCanvas *c1=new TCanvas();
c1->Divide(1,2);
c1->cd(1);
  g->Draw("ap");
  g->Fit("pol1");
c1->cd(2);
h->Draw();
 
  return ;
}

