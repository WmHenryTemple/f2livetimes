#include "readReport.cpp"

Double_t calcBinomRatioErr(Double_t numerCnts, Double_t denomCnts) {
  return (0.5*(Double_t) numerCnts / (Double_t) denomCnts) * TMath::Sqrt((1./((Double_t) numerCnts)) + (1./((Double_t) denomCnts)));
}

void edtmVsMyTLT(){
gStyle->SetOptFit();
  FILE *fp = fopen("comp.txt","r");  
  Float_t rn, tlt, tlte, clt, clte, elt, elte;
  Float_t cutCurrent,current, denom, num, f, rmeas, ps, error, s1x;
  Int_t ncols; 
  vector <float> run, lt, lte, rep, repe, elec, elece, rate;

  TH1F*h=new TH1F("h","Calculated Elec. Livetime",100,70,100);

  while (1) { 
    ncols = fscanf(fp,"%f %f %f %f %f %f %f %f",&rn,&s1x, &clt, &clte, &elt, &elte,&tlt,&tlte);
    if (ncols < 0) break;
    //    cout << run <<endl;
    //comp.txt
    run.push_back(rn);
    rate.push_back(s1x);
    lt.push_back(tlt*100.);
    h->Fill(elt*100.);
    lte.push_back(tlte*100.);
    elec.push_back(elt*100.);
    elece.push_back(elte*100.);

    //report file
    cutCurrent=readReport(rn,"BCM4C cut current");
    current=readReport(rn,"BCM4C current");
    f=(current/cutCurrent);
    rmeas=readReport(rn,"ps2 lt edtm");
    //    f=1.;
    rep.push_back(100*(rmeas/100.-(1.-f))/f);
    denom=readReport(rn,"EDTM triggers");
    num=readReport(rn,"Accepted EDTM triggers");
    ps=readReport(rn,"Ps2 fact");
    error=TMath::Sqrt(num*(1-num/denom))*ps/denom;
    repe.push_back(error*100);
    cout <<"Run: "<<rn<<"\t"<< 100.*(rmeas/100.-(1.-f))/f << " +/- " << error*100. << "   vs   " << tlt*100 << " +/- "<<tlte*100 << endl;

    }

  Int_t pts=run.size();
  TGraphErrors *g=new TGraphErrors(pts,&rep[0],&lt[0],&repe[0],&lte[0]);
  g->GetYaxis()->SetTitle("New Total Live Time");
  g->GetXaxis()->SetTitle("Total LiveTime (EDTM) Report file corrected");

  g->GetYaxis()->SetRangeUser(00.,110.);
  g->GetXaxis()->SetRangeUser(00.,110.);
  //  g->SetMarkerStyle(20);
  TGraphErrors *ge=new TGraphErrors(pts, &rate[0], &elec[0], 0, &elece[0]);
  ge->GetYaxis()->SetTitle("Electronic Live Time (%)");
  ge->GetXaxis()->SetTitle("S1X rate");
  TCanvas *c1= new TCanvas();
  c1->Divide(1,3);
  c1->cd(1);
  g->Draw("ap");
  g->Fit("pol1");
  c1->cd(2);
  ge->Draw("ap");
  c1->cd(3);
  h->Draw();
  return ;
}

