#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <math.h>
#include <vector>
#include <stdlib.h>
using namespace std;
int main() 
{
	    


#include "Declarations.H"
#include "InputDeck.H"
#include "assignThetas.H"  /*Creates an array of theta values based on WellTrajectories*/


Pu = Pwf + 10000;
gammaO = 141.5 / (APIOil + 131.5);

while (Pu-PFinal>10){
	#include "IPR.H"
	#include "chokeEqn.H"
	double TestL = 0;

	/*--CLEAR----
	-----ALL-----
	---VECTORS---
	-----HERE--*/
	Tf.clear();
	TubingP.clear();
	Tf.push_back(TRes);

	/*Calculate some initial fluid properties at reservoir Temp because
	we need it to calculate density for the TEqn*/
	T = TRes;
	P = PRes;
	#include "FluidProperties.H"

	T1 = TRes;	

	
	for(int i = 0; i < WHL+1; i = i + 1 ) {
		if (i == 0) {
			TubingP.push_back(Pwf);
			Tf.push_back(TRes);
			TestL = TestL + dL;
                        qLi = qL;
                        rhoLi = rhoL;
		}
		else{
			POld = TubingP[i-1];
			PNext = POld - POld*dL / Length; /*For the guess, assume linear pressure distribution*/
			Pguess = PNext + 50;
			counter = 0;
			Tei = T1;
			T1 = T1 - gG*dL*sinThetas[i];
                        TEnv.push_back(T1);
			while (abs(Pguess - PNext) > 1 || counter > 10000){
	 			Pguess = PNext;
				/*Calculate the temperature based on analytical Solution*/
				#include "TEqn.H"
				/*Calculate Fluid Properties based on Temp and Pressure*/
				P = TubingP[i-1];
				T = Tf[i-1];
				#include "FluidProperties.H" /*use POld**/
				/*Calculate dPdL using H&G*/
				#include "HagedornAndBrown.H"
				PNext = TubingP[i-1] - dPdL * dL;
				counter = counter+1;
					cout << "counter ====================== " << counter << endl;
				cout << "TubingP= " << TubingP[i] << endl;
				cout << "PNext= " << PNext << endl;
				cout << "POld= " << POld << endl << endl;
				cout << "Pguess= " << Pguess << endl << endl;
				cout << "Temp= " << TemporaryT << endl << endl;
		      }
		
		      TubingP.push_back(PNext);
		      Tf.push_back(TemporaryT);
                      rhoLvec.push_back(rhoL);
			
		}
		
	}
	PFinal = TubingP[WHL-2];
	Pwf= Pwf+1;
}	




for(int i = WHL+1; i < N; i = i + 1 ) {
		
    if (T1 > 210){
        T1 = Tf[i-1];
    }
	Tei = T1;
	T1 = T1 - gG*dL*sinThetas[i];
        TEnv.push_back(T1);
	/*Calculate the temperature based on analytical Solution*/
	#include "TEqn.H"
	Tf.push_back(TemporaryT);
}

double PTemp = Psep;
vector<float> TTop; 

for(int i = N; i > WHL+1; i = i - 1 ) {
        #include "HagedornAndBrown.H"
	PTemp = PTemp + dPdL * dL;
	TTop.push_back(PTemp);
}

for(int i = N-WHL-2; i > 0; i = i - 1 ) {
	TubingP.push_back(TTop[i]);
}


cout << "temp | Location = " << endl;
for(int i = 0; i < N; i = i + 2 ) {
	cout << Tf[i] << "   "  << Location[i] <<endl;
}

cout << "Pressure | dens | Location = " << endl;
for(int i = 0; i < N; i = i + 1 ) {
	cout << TubingP[i] << "   "  << verti[i] <<endl;
}



/*
    if pu / pd < 0.5

	petroleum production systems
	chapter 3
	3-27 correct


	typo in appendix B-

*/
cout << Pwf << " Final Result" << endl;
cout << PFinal << " WellHead pressure" << endl;

cout << qL << " Fluid rate" << endl;
         
cout << WHL << endl;
	getchar();
    return 0;
}


// ************************************************************************* //