void plot(){

  FILE *fp = fopen("livetimes.txt","r");  
  Float_t rn, ps, rt, eto, etf,eso, esf, tto, ttf, tso, tsf;
  Int_t ncols; 
  vector <float> rate, run, dt1,dt2,dt5;
  while (1) { 
    ncols = fscanf(fp,"%f %f %f %f %f %f %f %f %f %f %f",&rn,&ps,&rt,&eto,&etf,&eso,&esf,&tto,&ttf,&tso,&tsf);
    //    cout << run <<endl;
    if (ncols < 0) break;
    rate.push_back(rt);
    run.push_back(rn);
    dt.push_back(eto/eso*ps);
  }
  Int_t pts=run.size();
  TGraph *g1=new TGraph(pts,&rate[0],&dt1[0]);
  g->SetMarkerStyle(20);
  g->Draw();
  return;
}

