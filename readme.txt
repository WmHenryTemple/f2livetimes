STEP ONE livetimes.cpp

*counts number of etdm and trigger hits after timing cut and bcm cut is applied
*outputs text file with followinf format
*run, prescale, trigger rate, s1x rate, edtm tdc hits beam on, edtm tdc hits beam off, edtm scaler beam on, edtm scaler beam off, trigger tdc hits beam on, trigger tdc hits beam off, trigger scaler beam on, trigger scaler beam off
*There are four versions of this code hms or shms and elreal or elclean
*The output is saved in plot/rawDiffCut/counters

STEP TWO ps.cpp and makeGr.cpp
* ps.cpp takes the output of livetimes.cpp and computes the computer livetime and total live time from the EDTM.  It then plots the electronic livetime as (TLT/CLT) and fits it to 1/(1+planerate*tau).  
* The fitted value for tau is used in the last step
* The output and fits are in plot/rawDiffCut/PDFs

STEP 3  finalResults.cpp
* Uses txt output from step 1 and tau value from step 2 to calculate final results
* CLT  = (trigger tdc hits beam on) / (trigger scaler beam on - edtm scaler beam on)
* ELT  = 1/(1+planerate*tau)
* TLT  = CLT * ELT
