// multiagents.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "..\node.h"
#include  "fstream"
#include "iostream"

using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::ofstream;

int _tmain(int argc, char* argv[])
{
	int nodecount=0;
	int round=0;
	Node **node;
	int **cost=NULL;
	int temp_relation[10];
	ifstream ip("graph.txt");
	
	
   //freopen(argv[1],"r",stdin);
   //freopen(argv[2],"w",stdout);
	   
	//printf("Enter the number of nodes \n");
	ip>>nodecount;
	//printf("Enter the number of constraints per node\n");
	ip>>round;

	node= new Node *[nodecount];
	int visited[10];
	for(int i=0;i<nodecount;i++){
				node[i]= new Node(i);
				node[i]->preference_index=0;
				visited[i]=0;
	}
int s=0;
int temp_cost=0;

// Taking input frm the user and putting into constraint cost map
	for(int i=0;i<nodecount;i++){

		//cost[i]=new int[nodecount];
		for(int j=s;j<nodecount;j++){
			if(i==j)
            {
				node[i]->UpdateCost(0,i);
				continue;
			}
			else 
				//printf("Enter the Constraint cost between node %d and %d\n",node[i]->GetNumber(),node[j]->GetNumber());
				ip>>temp_cost;
				node[i]->UpdateCost(temp_cost,j);
				node[j]->UpdateCost(temp_cost,i);
		}
		s+=1;
	}


// Print Unsorted List of each node
	for(int i=0;i<nodecount;i++){
		
			node[i]->PrintCost(nodecount);
			printf("\n");
			node[i]->PreferenceList(0,nodecount-1);
	}
// Print sorted list of each node
	printf("\nSorted\n");
	for(int i=0;i<nodecount;i++){
		
			node[i]->PrintCost(nodecount);
			printf("\n");
	}


// Algo to create a new graph

for(int j=0;j<round;j++){
		for(int i=0;i<nodecount;i++)
		{
			if(!visited[i]){

				int temp_pref=node[i]->GetPreference(node[i]->preference_index);
				if(node[temp_pref]->GetPreference(node[temp_pref]->preference_index)==i && node[i]->no_of_constraints<round){
						printf("Strong relation between %d and %d\n",temp_pref,i);
						node[i]->final_relation[node[i]->no_of_constraints]=temp_pref;
						node[temp_pref]->final_relation[node[temp_pref]->no_of_constraints]=i;
						node[i]->no_of_constraints++;
						node[temp_pref]->no_of_constraints++;
						visited[i]=1;
						visited[temp_pref]=1;
											
				}
				
				
			}
		 temp_relation[i]=-1;
			
		}// End of inner for loop
		for (int k=0;k<nodecount;k++){
			printf("Node[%d]\n",k);
			if(!visited[k] && node[k]->no_of_constraints<round){
					int temp_pref=node[k]->GetPreference(node[k]->preference_index);
							if(temp_relation[temp_pref]==-1){
								temp_relation[temp_pref]=k;
								visited[k]=1;
								//visited[temp_pref]=1;
								printf("Weak Relation between node[%d] and node[%d]\n",k,temp_pref);
															
						    }
					    	else{
						    	if(node[k]->GetCost(temp_pref)> node[temp_relation[temp_pref]]->GetCost(temp_pref)){
									printf("Deallocating node %d and replacing it with %d\n",node[k]->GetNumber(),node[temp_relation[temp_pref]]->GetNumber());

									visited[temp_relation[temp_pref]]=0;
									node[temp_relation[temp_pref]]->hop_count++;
									node[temp_relation[temp_pref]]->SwapPreference();
									visited[k]=1;
									int p=temp_relation[temp_pref];
									temp_relation[temp_pref]=k;
									k=p-1;
							    }
								else{
									printf("node[%d],Could not find a constraint in this round ,swapping preference\n",node[k]->GetNumber());
									node[k]->hop_count++;
									node[k]->SwapPreference();
									printf("Preference of node[%d] after swapping:\n",node[k]->GetNumber());
									node[k]->PrintCost(nodecount);
									k--;
									
									
								}
						    }//end of else
						}
						//end of constraint check loop
						/*else
						{
							node[k]->preference_index++;
						}*/
			
			
			}//end of weak relation for loop

			for(int l=0;l<nodecount;l++){
				visited[l]=0;
				node[l]->hop_count=0;
				if(temp_relation[l]!=-1){
					printf("node[%d] getting converted from weak to strong reln\n",node[l]->GetNumber());
					node[l]->no_of_constraints++;
					node[temp_relation[l]]->no_of_constraints++;
					node[l]->final_relation[node[l]->no_of_constraints]=temp_relation[l];
					node[temp_relation[l]]->final_relation[node[temp_relation[l]]->no_of_constraints]= l;
					if(l==temp_relation[temp_relation[l]])
									temp_relation[temp_relation[l]]=-1;

					temp_relation[l]=-1;
				}
			}//End of for loop
			for(int m=0;m<nodecount;m++)
				node[m]->preference_index=node[m]->no_of_constraints ;
	
								
			
}// End of all round loop
int **mat= new int*[10];
for(int i=0;i<nodecount;i++)
{
	mat[i] = node[i]->GetFinalRelation();	
}

for(int i=0;i<nodecount;i++)
	for(int j=0;j<nodecount;j++)	
		cout<<mat[i][j];

scanf("%d",&nodecount);
	return 0;
}

