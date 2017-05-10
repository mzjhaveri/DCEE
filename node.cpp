
#include "stdafx.h"

class Node{

private: 
	int number;
	int constraint_cost[10][2];


public:
	int final_relation[10];
	int hop_count;
	int no_of_constraints;	
	int preference_index;
	 Node(int no){
		 int j;
		 number = no;
		 for(int i=0;i<10;i++){
			 final_relation[i]=-1;
			for (j=0;j<2;j++)
				constraint_cost[i][j]=0;
			}
		 hop_count=0;
		 no_of_constraints=0;
		 preference_index=0;

	 }

	void Maintain_Queue(){}
	void UpdateCost(int cost,int rel_node){

		constraint_cost[rel_node][0]=rel_node;
		constraint_cost[rel_node][1]=cost;

	}
	int GetNumber(){
		return this->number;
	}
	void PrintCost(int nodecount){
		for(int i=0;i<nodecount;i++){
				printf("[%d]%d  ",constraint_cost[i][0],constraint_cost[i][1]);

		}
	}
	int GetCost(int ref_node){
		return constraint_cost[ref_node][1];
	}

	int GetPreference(int i)
	{
		return constraint_cost[i][0];
	}
	void SwapPreference(){
		int temp,temp1;
		temp=constraint_cost[preference_index][0];
		temp1=constraint_cost[preference_index][1];
		constraint_cost[preference_index][0]=constraint_cost[preference_index+hop_count][0];
		constraint_cost[preference_index][1]=constraint_cost[preference_index+hop_count][1];
		constraint_cost[preference_index][0]=temp;
		constraint_cost[preference_index][1]=temp1;
	}

	int* GetFinalRelation(){
		int* mat=new int [10];
		for (int i=0;i<no_of_constraints;i++){
			if(final_relation[i]!=-1)
			{
				printf("%d and %d are connected\n",number,final_relation[i]);
				mat[final_relation[i]]=constraint_cost[final_relation[i]][1];
			}
		}
		return mat;

	}

	void PreferenceList(int left,int right){

		int i = left, j = right;

      int tmp,temp_index;
	  
      int pivot = constraint_cost[(left + right) / 2][1];
	 
       /* partition */

      while (i <= j) {

            while (constraint_cost[i][1] > pivot)

                  i++;

            while (constraint_cost[j][1] < pivot)

                  j--;

            if (i <= j) {

                  tmp = constraint_cost[i][1];
				  temp_index=constraint_cost[i][0];
                  constraint_cost[i][1]=constraint_cost[j][1];
				  constraint_cost[i][0]=constraint_cost[j][0];

                  constraint_cost[j][1] = tmp;
				  constraint_cost[j][0]= temp_index;

                  i++;

                  j--;

            }

	  }
 

      /* recursion */

      if (left < j)

           PreferenceList(left, j);

      if (i < right)

            PreferenceList(i, right);
	}
		

};



