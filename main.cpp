#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>


using namespace std;

int main(int argc, char *argv[])
{

   	ifstream inputfile;
	ifstream inputfileconfig;
	ofstream outfile;
	int N,A,B,datasets=0;
	
   	inputfile.open(argv[1]);

	if(!inputfile){
	cout<<"Issue with opening the input file";
	return(-1);
	}

	outfile.open(argv[2]);

	if(!outfile){
	cout<<"Issue with opening the output file";
	return(-1);
	}

	
	inputfileconfig.open(argv[3]);

	if(!inputfileconfig){
	cout<<"Issue with opening the cost file";
	return(-1);
	}	

	int costfile[10001];

	int costindex;
	int costcontent;	

	if (inputfileconfig.is_open()) {
		while (!inputfileconfig.eof()) {	
			inputfileconfig>>costindex;
			inputfileconfig>>costcontent;

			//cout<<costindex<<" "<<costcontent<<endl;
			costfile[costindex]=costcontent;
			
		}
		inputfileconfig.close();
	}

	inputfile>>datasets;

	for(int m=0;m<datasets;m++){

		inputfile>>N;
		inputfile>>A;
		inputfile>>B;
		
		int cost=0;
		int val=0;		
		
		map<int,vector<int> > optimalmap ;
		map<int,vector<int> > optimalcost;
		map<int,vector<int> > optimalbestmap;
		map<int,int> costusemap;

		 
		for(int k=0;k<N;k++){

			int start_s=A*(k+1);		
			int end_s=start_s+B;
						
			for(int i=start_s;i<=end_s && i<=A*N;i++){//range taking
									
				if(start_s==A){// for k = 0 first iteration
				
					vector<int> values;
					values.push_back(i);	

					optimalmap.insert( pair<int,vector<int> >(i,values));
					costusemap.insert(pair<int,int>(i,costfile[i]));

				}//if start_s =A
				
				else{// for k >0 second iteration onwards

				   int mincostt=99999999;
  				   for (map<int,vector<int> >::iterator itst=optimalmap.begin(); itst!=optimalmap.end() && itst->first <= i; ++itst){
		
					int prev=itst->first;
					vector<int> startvec=optimalmap[prev];	
																			
					val = i-prev;
					
					startvec.push_back(val);

					int cost=0;
					cost = costusemap[prev] + costfile[val];
									
                    if(mincostt>cost){

                       mincostt=cost;
                       optimalbestmap.erase(i);
                       optimalbestmap.insert( pair<int,vector<int> >(i,startvec));
					   
						if(costusemap[i]==0 || costusemap[i] > mincostt){
                            costusemap.erase(i);
						}
                            costusemap.insert(pair<int,int>(i,mincostt));
                    }					

					} // inner for loop
																																	
				}//else
				
			}//start and end
			
			    if(start_s!=A){

			    for (map<int,vector<int> >::iterator itit=optimalmap.begin(); itit!=optimalmap.end(); ++itit){
				int f=itit->first;
				//cout<<f<<" ";
				optimalmap.erase(f);
			    }

			    optimalmap.insert(optimalbestmap.begin(), optimalbestmap.end());
			    optimalbestmap.clear();

			    }
			    
		}//k value
  				for (map<int,vector<int> >::iterator it=optimalmap.begin(); it!=optimalmap.end(); ++it){
					
					for( vector<int>::const_iterator itvec =it->second.begin(); itvec!=it->second.end();++itvec) {
											
    					 	cout<<*itvec<<" ";	
					}										
				}				
				cout<<endl;
				
				int finalcost=costusemap[N*A];
				
				if(m==(datasets-1)){
					outfile<<finalcost;
				}
				else{
					outfile<<finalcost<<endl;
				}
	
    	}//datasets 
	outfile.close();
	inputfile.close();

}//main