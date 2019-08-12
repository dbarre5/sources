/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Daniel
 *
 * Created on January 23, 2018, 7:07 PM
 */

#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>
#include <cstdlib>
#include <string>


using namespace std;

/*
 * 
 */
int main() 
{
float shift;
ifstream inFile;
inFile.open("test.dat");


if (!inFile) 
{
cout << "Can't open or find file";
 // terminate with error
}

/*
 * Reads a text file and outputs the text on a screen
 */

string word;
string Search;
int Grid[3];
float Dxyz[3];
float Length[3];
float inj[3];
float injStart[3];
float injEnd[3];
float prod[3];
float prodStart[3];
float prodEnd[3];
float permX;
float por;
float dx;
float dy;
float dz;
float Tx;
float d;
float pInit;
int nt;
float endT;
float deltaT;
float vol;
float wellLoc;
float Q;
float conv;

 
 /*
 * Ask User what to search for
 */
 
 int count = 0;
 
  if (inFile.is_open())
  {
 /*
 * Some sort of loop that goes to end of file
 */
    while ( inFile.good() )
    {
        if (word == "GRID")
        {
            inFile >> Grid[0];
	    inFile >> Grid[1];
	    inFile >> Grid[2];		 
        }

	if (word == "DXYZ")
        {
            inFile >> Dxyz[0];
	    inFile >> Dxyz[1];
   	    inFile >> Dxyz[2];   
        }

	if (word == "INJ")
        {
            inFile >> inj[0];
	    inFile >> inj[1];
   	    inFile >> inj[2];
	    inFile >> inj[3];
        }

        if (word == "PROD")
        {
            inFile >> prod[0];
	    inFile >> prod[1];
   	    inFile >> prod[2];
            inFile >> prod[3];
        }
	if (word == "CONV")
        {
            inFile >> conv;
	  
        }
        inFile >> word;
    }
    inFile.close();
  }



/*Calculate volume of each block*/
float vol1 = 1/ (Dxyz[0]*Dxyz[1]*Dxyz[2] / inj[3]) / conv; /*0.2 is the porosity*/
float vol2 = 1/ (Dxyz[0]*Dxyz[1]*Dxyz[2] / prod[3]) / conv;/*5.614/3.28/3.28/3.28;*/

/*Use this to maintain precision of small number*/
ostringstream streamVolume2;
streamVolume2 <<setprecision(20);
streamVolume2 <<std::fixed;
streamVolume2 << vol2;
string Volume2 = streamVolume2.str();

ostringstream streamVolume1;
streamVolume1 <<setprecision(20);
streamVolume1 <<std::fixed;
streamVolume1 << vol1;
string Volume1 = streamVolume1.str();

/*Calculate the length of the system from e.g. dx * number of x blocks */
Length[0] = Grid[0] * Dxyz[0];
Length[1] = Grid[1] * Dxyz[1];
Length[2] = Grid[2] * Dxyz[2];

/*Calculate bounding locations of injections */
injStart[0] = Dxyz[0] * inj[0] - 3*Dxyz[0] / 2;
injStart[1] = Dxyz[1] * inj[1] - 3*Dxyz[1] / 2;
injStart[2] = Dxyz[2] * inj[2] - 3*Dxyz[2] / 2;
injEnd[0] = Dxyz[0] * inj[0] + Dxyz[0] / 2;
injEnd[1] = Dxyz[1] * inj[1] + Dxyz[1] / 2;
injEnd[2] = Dxyz[2] * inj[2] + Dxyz[2] / 2;

/*Calculate bounding locations of producers */
prodStart[0] = Dxyz[0] * prod[0] - 3*Dxyz[0] / 2;
prodStart[1] = Dxyz[1] * prod[1] - 3*Dxyz[1] / 2;
prodStart[2] = Dxyz[2] * prod[2] - 3*Dxyz[2] / 2;
prodEnd[0] = Dxyz[0] * prod[0] + Dxyz[0] / 2;
prodEnd[1] = Dxyz[1] * prod[1] + Dxyz[1] / 2;
prodEnd[2] = Dxyz[2] * prod[2] + Dxyz[2] / 2;


/*Commands to update mesh size and number*/
	string nx = "sed s/'NX'/"+to_string(Grid[0])+"/g blockMeshDictTemp > system/blockMeshDict";
	system(nx.c_str());

	string ny = "sed -i s/'NY'/"+to_string(Grid[1])+"/g system/blockMeshDict";
	system(ny.c_str());

	string nz = "sed -i s/'NZ'/"+to_string(Grid[2])+"/g system/blockMeshDict";
	system(nz.c_str());
	
	string x = "sed -i s/'LEN'/"+to_string(Length[0])+"/g system/blockMeshDict";
	system(x.c_str());	

	string y = "sed -i s/'WID'/"+to_string(Length[1])+"/g system/blockMeshDict";
	system(y.c_str());

	string z = "sed -i s/'THICK'/"+to_string(Length[2])+"/g system/blockMeshDict";
	system(z.c_str());

/*Commands to find locations of injections to update setFieldsDict*/
	string injx = "sed s/'INJSTX'/"+to_string(injStart[0])+"/g setFieldsTemp > system/setFieldsDict";
	system(injx.c_str());	

	string injy = "sed -i s/'INJSTY'/"+to_string(injStart[1])+"/g system/setFieldsDict";
	system(injy.c_str());	

	string injz = "sed -i s/'INJSTZ'/"+to_string(injStart[2])+"/g system/setFieldsDict";
	system(injz.c_str());	

        string injendx = "sed -i s/'INJENDX'/"+to_string(injEnd[0])+"/g system/setFieldsDict";
	system(injendx.c_str());	

	string injendy = "sed -i s/'INJENDY'/"+to_string(injEnd[1])+"/g system/setFieldsDict";
	system(injendy.c_str());	

	string injendz = "sed -i s/'INJENDZ'/"+to_string(injEnd[2])+"/g system/setFieldsDict";
	system(injendz.c_str());
        
        string prodx = "sed -i s/'PRODSTX'/"+to_string(prodStart[0])+"/g system/setFieldsDict";
	system(prodx.c_str());	

	string prody = "sed -i s/'PRODSTY'/"+to_string(prodStart[1])+"/g system/setFieldsDict";
	system(prody.c_str());	

	string prodz = "sed -i s/'PRODSTZ'/"+to_string(prodStart[2])+"/g system/setFieldsDict";
	system(prodz.c_str());

        string prodendx = "sed -i s/'PRODENDX'/"+to_string(prodEnd[0])+"/g system/setFieldsDict";
	system(prodendx.c_str());	

	string prodendy = "sed -i s/'PRODENDY'/"+to_string(prodEnd[1])+"/g system/setFieldsDict";
	system(prodendy.c_str());	

	string prodendz = "sed -i s/'PRODENDZ'/"+to_string(prodEnd[2])+"/g system/setFieldsDict";
	system(prodendz.c_str());

/*Command to specify volume to divide injection rate by*/
        string injVolume = "sed -i s/'INJRATE'/"+Volume1+"/g system/setFieldsDict";
	system(injVolume.c_str());

        string prodVolume = "sed -i s/'PRODRATE'/"+Volume2+"/g system/setFieldsDict";
	system(prodVolume.c_str()); 

}

/*a.out g++ -std=c++0x main.cpp */
