ifstream inFile;
inFile.open("inputDeck.dat");
string vert;
string hor;

int vectorSize = 0;

if (!inFile) 
	{
	cout << "Can't open or find inputDeck.dat";
	 // terminate with error
	}

	/*
	 * Reads a text file and outputs the text on a screen
	 */

	string word;
	string Search;
 
	int count = 0;
 	
  	if (inFile.is_open())
  	{
 		/*
 		* Loop that goes to end of file
 		*/
	    	while ( inFile.good() )
	    	{
			if (word == "WELL_LENGTH")
			{
			    inFile >> Length;		 
			}

			if (word == "NUMBER_OF_DIVISIONS")
			{
			    inFile >> N;		 
			}
			
			if (word == "WellTrajectory")
			{
				while (vert != "END")
				{
					inFile >> hor;
						if (hor == "END"){
							break;
						}
					inFile >> vert;
		    			vertLoc.push_back(strtof((vert).c_str(),0));
					horLoc.push_back(strtof((hor).c_str(),0));
					vectorSize = vectorSize + 1;
				}
			}

                        if (word == "TubingID")
			{
			    inFile >> TubingID;		 
			}

			if (word == "CasingID")
			{
			    inFile >> CasingID; 
			}

			if (word == "SeaBedTemp")
			{
			    inFile >> TSeaBed;
			}

			if (word == "SeaLevelTemp")
			{
			    inFile >> TSeaLevel;
			}

                        if (word == "USEA")
			{
			    inFile >> USea;		 
			}

			if (word == "USURROUNDING")
			{
			    inFile >> USurr; 
			}

			if (word == "PERM")
			{
			    inFile >> Perm;
			}

			if (word == "THICKNESS")
			{
			    inFile >> thickness;
			}

                        if (word == "DRAINAGE")
			{
			    inFile >> DrainageArea;		 
			}

			if (word == "RWB")
			{
			    inFile >> rwb; 
			}

			if (word == "DAMAGELENGTH")
			{
			    inFile >> DLength;
			}

			if (word == "DAMAGEPERM")
			{
			    inFile >> DPerm;
			}

                        if (word == "RESERVOIRTEMP")
			{
			    inFile >> TRes;		 
			}

			if (word == "RESERVOIRPRESSURE")
			{
			    inFile >> PRes; 
			}

			if (word == "POROSITY")
			{
			    inFile >> Porosity;
			}

			if (word == "WATERSATURATION")
			{
			    inFile >> Sw;
			}

                        if (word == "PRODUCINGWATERCUT")
			{
			    inFile >> WCut;		 
			}

			if (word == "PRODUCINGGOR")
			{
			    inFile >> Rp; 
			}

			if (word == "OILGRAVITY")
			{
			    inFile >> APIOil;
			}

			if (word == "GASGRAVITY")
			{
			    inFile >> gammaG;
			}

			if (word == "FORMATIONWATERGRAVITY")
			{
			    inFile >> gammaW;		 
			}

			if (word == "WAXTEMP")
			{
			    inFile >> TWax; 
			}

			if (word == "SEPARATOR_TEMPERATUR")
			{
			    inFile >> Tsep; 
			}

			if (word == "SEPARATOR_PRESSURE")
			{
			    inFile >> Psep; 
			}

                        if (word == "WELLHEAD_LOCATION")
			{
			    inFile >> WH_Location; 
			}

			if (word == "PWF_Guess")
			{
			    inFile >> Pwf; 
			}

			if (word == "CHOKE_OPENING")
			{
			    inFile >> CHO; 
			}

			inFile >> word;
	    	}
	    	inFile.close();
	  }

  else cout << "Unable to open file"; 

	/*
	while (inFile >> shift)
	cout << shift << endl;
 	*/

	inFile.close();
