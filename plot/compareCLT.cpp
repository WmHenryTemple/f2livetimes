#include "readReport.cpp"

Double_t calcBinomRatioErr(Double_t numerCnts, Double_t denomCnts) {
  return (0.5*(Double_t) numerCnts / (Double_t) denomCnts) * TMath::Sqrt((1./((Double_t) numerCnts)) + (1./((Double_t) denomCnts)));
}

void compareCLT(Double_t fact=1,Int_t option=1){
gStyle->SetOptFit();
 TH1F *h=new TH1F("h","Calculate/ReportFile",100,.98,1.02);
  FILE *fp = fopen("livetimes.txt","r");  
  Float_t rn, ps, rt, eto, etf,eso, esf, tto, ttf, tso, rt1,tsf;
  Float_t deno,num;
  Double_t cutCurrent,current,f,denom,numer,error,rmeas;
  Int_t ncols; 
  vector <float> rate, run, dt, err,x,xe;
  while (1) { 
    ncols = fscanf(fp,"%f %f %f %f %f %f %f %f %f %f %f %f",&rn,&ps,&rt1,&rt,&eto,&etf,&eso,&esf,&tto,&ttf,&tso,&tsf);
    //    cout << run <<endl;
    if (ncols < 0) break;
      num=tto+eto;
      denom=tso;       
      Double_t val1=num/denom*ps*100;
      dt.push_back(val1);
      Double_t did=num;
      Double_t should=denom;
      Double_t fid=did/should;
      Double_t error=TMath::Sqrt(num*(1-num/denom))*ps/denom*100;
      err.push_back(error);   
      Double_t val2=readReport(rn,"ps2 clt");
      x.push_back(val2);
      xe.push_back(error);
      h->Fill(val1/val2);
  }
  Int_t pts=dt.size();
  TGraphErrors *g=new TGraphErrors(pts,&x[0],&dt[0],&xe[0],&err[0]);
  g->GetYaxis()->SetTitle("Calculated LiveTime");
  g->GetXaxis()->SetTitle("LiveTime Report file");

  g->GetYaxis()->SetRangeUser(50.,100.);
  g->GetXaxis()->SetRangeUser(50.,100.);
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

