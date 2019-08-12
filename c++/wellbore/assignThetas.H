double rise;
double run;
double hypotenuse;
double height;
double distance;
vector<float> sinThetas; 
vector<float> cosThetas; 
vector<float> Location; 
vector<float> verti; 
double L; 
L = 0;
Length = 0;
distance = horLoc[0];
Location.push_back(horLoc[0]);
height = vertLoc[0];
int j;

for(j = 0; j < vectorSize-1; j = j + 1 ){
	rise = (vertLoc[j]-vertLoc[j+1]);
        run = (horLoc[j] - horLoc[j+1]);
	hypotenuse = pow((pow(rise,2)+pow(run,2)),0.5);
	Length = Length + hypotenuse;
}

dL = Length/(N);


height = vertLoc[0];
distance = horLoc[0];

j = 0;
for(int i = 0; i < N; i = i + 1 ) {
	for(j = 0; j < vectorSize-1; j = j + 1) {
		if (distance >= horLoc[j] && distance <= horLoc[j+1]){
			rise = (vertLoc[j]-vertLoc[j+1]);
        		run = (horLoc[j] - horLoc[j+1]);
			hypotenuse = pow((pow(rise,2)+pow(run,2)),0.5);
			sinThetas.push_back(-rise/hypotenuse);
			cosThetas.push_back(-run/hypotenuse);		
			height = height + dL * sinThetas[i];
			verti.push_back(height);
			distance = distance + dL * cosThetas[i];
			Location.push_back(Location[i] + dL * cosThetas[i]);
			break;
		}
	}
}
/*Where is the wellhead? Find it---*/
	
WHL = 0;
for(int i = 0; i < N; i = i + 1 ) {
	if (Location[i] > WH_Location){
		WHL = i-1;
		break;
	}
}
	
	


	
