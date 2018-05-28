#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int ROWS = 2, COMLUMNS = 4;

int numberOfMinterms = 0;
int DecimalMinterms[7];

struct KmapElement
{
	int state;
	int DecimalMinterm;
	int inclusion = 0;
	string binaryminterm;

};
struct Implicant
{
	vector <KmapElement> minterms;
	int Size;
};

KmapElement Kmap[ROWS][COMLUMNS];

vector <KmapElement> V1, V2, V3, V4, V5, V6, AllElemntsInImplicant;;
vector <Implicant> AllImplicants;

string FinalExpression="";





void GetInput();
void IntializeKMap(), IntializeBinaryMintermsKMap();
void PrintKMap();
void AlgorithmFindImplicants();
vector <KmapElement> GetVectorOfMaxSize(vector<KmapElement> V1, vector<KmapElement> V2, vector<KmapElement> V3, vector<KmapElement> V4, vector<KmapElement> V5);
void SortAllImplicantsBySizeInAscendingOrder();
void AssignInclusionTimesToImplicants();
void RemoveDuplicateImplicants();
void DecreaseInclusionOfMintermsInDeletedImplicant(int i);
void GetEssentialPrimeImplicants();
void GetFinalExpression();



int main()
{
	
	GetInput();
	IntializeKMap();
	IntializeBinaryMintermsKMap();
	PrintKMap();
	AlgorithmFindImplicants();
	SortAllImplicantsBySizeInAscendingOrder();
	AssignInclusionTimesToImplicants();
	RemoveDuplicateImplicants();
	GetEssentialPrimeImplicants();
	GetFinalExpression();
	cout << "F(A, B, C) = " << FinalExpression << endl;


	system("pause");


}


void GetInput()
{
	cout << "Enter number of minterms" << endl;
	cin >> numberOfMinterms;
	cout << "Enter minterms" << endl;
	int i = 0;
	int tempMinterm;
	do
	{
		do
		{
			cin >> tempMinterm;
			
		} while (tempMinterm > 7 || tempMinterm < 0);
			DecimalMinterms[i] = tempMinterm;
		i++;
	} while (i < numberOfMinterms);
	
	
}

void IntializeKMap()
{
	for (int i = 0; i < ROWS; i++)
		for (int j = 0; j < COMLUMNS; j++)
			Kmap[i][j].state = 0;


	Kmap[0][0].DecimalMinterm = 0;
	Kmap[0][1].DecimalMinterm = 1;
	Kmap[0][2].DecimalMinterm = 3;
	Kmap[0][3].DecimalMinterm = 2;
	Kmap[1][0].DecimalMinterm = 4;
	Kmap[1][1].DecimalMinterm = 5;
	Kmap[1][2].DecimalMinterm = 7;
	Kmap[1][3].DecimalMinterm = 6;


	for (int i = 0; i < numberOfMinterms; i++)
	{
		if (DecimalMinterms[i] == 0)
		{
			Kmap[0][0].state = 1;
			
		}
		else if (DecimalMinterms[i] == 1)
		{
			Kmap[0][1].state = 1;
			
		}
		else if (DecimalMinterms[i] == 3)
		{
			Kmap[0][2].state = 1;
			
		}
		else if (DecimalMinterms[i] == 2)
		{
			Kmap[0][3].state = 1;
			
		}
		else if (DecimalMinterms[i] == 4)
		{
			Kmap[1][0].state = 1;
			
		}
		else if (DecimalMinterms[i] == 5)
		{
			Kmap[1][1].state = 1;
		
		}
		else if (DecimalMinterms[i] == 7)
		{
			Kmap[1][2].state = 1;
			
		}
		else if (DecimalMinterms[i] == 6)
		{
			Kmap[1][3].state = 1;
			
		}

	}

}

void IntializeBinaryMintermsKMap()
{
	Kmap[0][0].binaryminterm = "000";
	Kmap[0][1].binaryminterm = "001";
	Kmap[0][2].binaryminterm = "011";
	Kmap[0][3].binaryminterm = "010";
	Kmap[1][0].binaryminterm = "100";
	Kmap[1][1].binaryminterm = "101";
	Kmap[1][2].binaryminterm = "111";
	Kmap[1][3].binaryminterm = "110";


}

void PrintKMap()
{
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cout << Kmap[i][j].state << "  ";
		}
		cout << endl;
	}
}


void AlgorithmFindImplicants()
{
	
	if (numberOfMinterms == 8)
	{
		FinalExpression = "1";
		
	}
	else if (numberOfMinterms == 0)
	{
		FinalExpression = "0";
	}
	else
	{



		for (int i = 0; i < ROWS; i++)
		{


			for (int j = 0; j < COMLUMNS; j++)
			{

				int implicantNum = 0;
				if (Kmap[i][j].state == 1)
				{



					V1.push_back(Kmap[i][j]);

					if (Kmap[i][(j + 1) % COMLUMNS].state == 1)
					{
						V2.push_back(Kmap[i][j]);
						V2.push_back(Kmap[i][(j + 1) % COMLUMNS]);


					}
					if (Kmap[(i + 1) % ROWS][j].state == 1)
					{
						V3.push_back(Kmap[i][j]);
						V3.push_back(Kmap[(i + 1) % ROWS][j]);




					}
					if (Kmap[i][(j + 1) % COMLUMNS].state == 1 && Kmap[(i + 1) % ROWS][j].state == 1 && Kmap[(i + 1) % ROWS][(j + 1) % COMLUMNS].state == 1)
					{
						V4.push_back(Kmap[i][j]);
						V4.push_back(Kmap[i][(j + 1) % COMLUMNS]);
						V4.push_back(Kmap[(i + 1) % ROWS][j]);
						V4.push_back(Kmap[(i + 1) % ROWS][(j + 1) % COMLUMNS]);




					}
					if (Kmap[i][(j + 1) % COMLUMNS].state == 1 && Kmap[i][(j + 2) % COMLUMNS].state == 1 && Kmap[i][(j + 3) % COMLUMNS].state == 1)
					{

						V5.push_back(Kmap[i][j]);
						V5.push_back(Kmap[i][(j + 1) % COMLUMNS]);
						V5.push_back(Kmap[i][(j + 2) % COMLUMNS]);
						V5.push_back(Kmap[i][(j + 3) % COMLUMNS]);


					}


					AllElemntsInImplicant = GetVectorOfMaxSize(V1, V2, V3, V4, V5);

					for (int m = 0; m < AllElemntsInImplicant.size(); m++)
					{

						if (AllElemntsInImplicant[m].DecimalMinterm == 0)
						{
							Kmap[0][0].inclusion = Kmap[0][0].inclusion + 1;

						}
						else if (AllElemntsInImplicant[m].DecimalMinterm == 1)
						{
							Kmap[0][1].inclusion = Kmap[0][1].inclusion + 1;
						}
						else if (AllElemntsInImplicant[m].DecimalMinterm == 2)
						{
							Kmap[0][3].inclusion = Kmap[0][3].inclusion + 1;
						}
						else if (AllElemntsInImplicant[m].DecimalMinterm == 3)
						{
							Kmap[0][2].inclusion = Kmap[0][2].inclusion + 1;
						}
						else if (AllElemntsInImplicant[m].DecimalMinterm == 4)
						{
							Kmap[1][0].inclusion = Kmap[1][0].inclusion + 1;
						}
						else if (AllElemntsInImplicant[m].DecimalMinterm == 5)
						{
							Kmap[1][1].inclusion = Kmap[1][1].inclusion + 1;
						}
						else if (AllElemntsInImplicant[m].DecimalMinterm == 6)
						{
							Kmap[1][3].inclusion = Kmap[1][3].inclusion + 1;
						}
						else if (AllElemntsInImplicant[m].DecimalMinterm == 7)
						{
							Kmap[1][2].inclusion = Kmap[1][2].inclusion + 1;
						}

					}

					Implicant A;
					for (int k = 0; k < AllElemntsInImplicant.size(); k++)
					{

						A.minterms.push_back(AllElemntsInImplicant[k]);

						cout << AllElemntsInImplicant[k].binaryminterm << " ";
					}
					cout << endl << "All elements in Implicant done." << endl;
					A.Size = AllElemntsInImplicant.size();
					AllImplicants.push_back(A);
					A.minterms.clear();
					A.Size = 0;

					implicantNum++;





				}
				V1.clear();
				V2.clear();
				V3.clear();
				V4.clear();
				V5.clear();

			}

		}
	}

		
	
	
}



vector <KmapElement> GetVectorOfMaxSize(vector<KmapElement> V1, vector<KmapElement> V2, vector<KmapElement> V3, vector<KmapElement> V4, vector<KmapElement> V5)
{
	int Sizes[5];
	Sizes[0] = V1.size();
	Sizes[1] = V2.size();
	Sizes[2] = V3.size();
	Sizes[3] = V4.size();
	Sizes[4] = V5.size();

	int max = -1;
	int vector_number;
	for (int i = 0; i < 5; i++)
	{
		
		if (Sizes[i] > max)
		{
			max = Sizes[i];
			vector_number = i+1;
		}

			
	}
	if (vector_number == 1)
		return V1;
	if (vector_number == 2)
		return V2;
	if (vector_number == 3)
		return V3;
	if (vector_number == 4)
		return V4;
	if (vector_number == 5)
		return V5;

	

}

void SortAllImplicantsBySizeInAscendingOrder()
{
	int i, j;
	for (i = 0; i < AllImplicants.size() - 1; i++)
	{
		for (j = 0; j < AllImplicants.size() - i - 1; j++)
			if (AllImplicants[j].Size > AllImplicants[j + 1].Size)
			{
				Implicant temp = AllImplicants[j];
				AllImplicants[j] = AllImplicants[j + 1];
				AllImplicants[j + 1] = temp;

			}
	}

	for (i = 0; i < AllImplicants.size(); i++)
	{
		cout << "After Sortion: " << i << "  ";
		for (j = 0; j < AllImplicants[i].minterms.size(); j++)
		{
			cout << AllImplicants[i].minterms[j].binaryminterm << "  ";
		}
		cout << endl;
	}
}



void AssignInclusionTimesToImplicants()
{
	for (int i = 0; i < AllImplicants.size(); i++)
	{
		for (int j = 0; j < AllImplicants[i].minterms.size(); j++)
		{
			if (AllImplicants[i].minterms[j].DecimalMinterm == 0)
			{
				AllImplicants[i].minterms[j].inclusion = Kmap[0][0].inclusion;
			}
			else if (AllImplicants[i].minterms[j].DecimalMinterm == 1)
			{
				AllImplicants[i].minterms[j].inclusion = Kmap[0][1].inclusion;
			}
			else if (AllImplicants[i].minterms[j].DecimalMinterm == 2)
			{
				AllImplicants[i].minterms[j].inclusion = Kmap[0][3].inclusion;
			}
			else if (AllImplicants[i].minterms[j].DecimalMinterm == 3)
			{
				AllImplicants[i].minterms[j].inclusion = Kmap[0][2].inclusion;
			}
			else if (AllImplicants[i].minterms[j].DecimalMinterm == 4)
			{
				AllImplicants[i].minterms[j].inclusion = Kmap[1][0].inclusion;
			}
			else if (AllImplicants[i].minterms[j].DecimalMinterm == 5)
			{
				AllImplicants[i].minterms[j].inclusion = Kmap[1][1].inclusion;
			}
			else if (AllImplicants[i].minterms[j].DecimalMinterm == 6)
			{
				AllImplicants[i].minterms[j].inclusion = Kmap[1][3].inclusion;
			}
			else if (AllImplicants[i].minterms[j].DecimalMinterm == 7)
			{
				AllImplicants[i].minterms[j].inclusion = Kmap[1][2].inclusion;
			}

		}
	}
}

void RemoveDuplicateImplicants()
{
	int isEqual = 0;
	for (int i = 0; i < AllImplicants.size(); i++)
	{
		for (int k = 1; k < AllImplicants.size() - 1; k++)
		{
			for (int j = 0; j < AllImplicants[i].minterms.size(); j++)
			{
				for (int N = 0; N < AllImplicants[k].minterms.size(); N++)
				{

					if (AllImplicants[i].minterms[j].binaryminterm == AllImplicants[k].minterms[N].binaryminterm)
					{

						isEqual++;
					}

				}

				if (isEqual == AllImplicants[i].minterms.size() && AllImplicants[i].Size == AllImplicants[k].Size)
				{
					DecreaseInclusionOfMintermsInDeletedImplicant(i);
					AllImplicants.erase(AllImplicants.begin() + i);


					//i--;

				}
				isEqual = 0;
			}

		}
	}
}

void DecreaseInclusionOfMintermsInDeletedImplicant(int i)
{
	int * DecimalMinterm = new int[AllImplicants[i].minterms.size()];
	for (int m = 0; m < AllImplicants[i].minterms.size(); m++)
	{
		DecimalMinterm[m] = AllImplicants[i].minterms[m].DecimalMinterm;
	}
	for (int k = 0; k < AllImplicants.size(); k++)
	{
		for (int L = 0; L < AllImplicants[k].minterms.size(); L++)
		{
			for (int S = 0; S < AllImplicants[i].minterms.size(); S++)
			{
				if (AllImplicants[k].minterms[L].binaryminterm == AllImplicants[i].minterms[S].binaryminterm)
				{

					AllImplicants[k].minterms[L].inclusion = AllImplicants[k].minterms[L].inclusion - 1;
				}
			}
		}
	}
}


void GetEssentialPrimeImplicants()
{
	cout << "After removing duplicate implicants " << endl;
	for (int i = 0; i < AllImplicants.size(); i++)
	{
		cout << "Implicant " << i << " with minterms ";
		for (int j = 0; j < AllImplicants[i].minterms.size(); j++)
		{
			cout << AllImplicants[i].minterms[j].binaryminterm << " ";
		}
		cout << endl;
	}

	int NumberOfMintermsIncludedinOtherImplicants = 0;

	for (int i = 0; i < AllImplicants.size(); i++)
	{

		NumberOfMintermsIncludedinOtherImplicants = 0;

		for (int j = 0; j < AllImplicants[i].minterms.size(); j++)
		{
			cout << "inclusion of minterm  " << j << " is = " << AllImplicants[i].minterms[j].inclusion << " in implicant  " << i << endl;
			if (AllImplicants[i].minterms[j].inclusion > 1)
			{
				NumberOfMintermsIncludedinOtherImplicants++;
			}

		}

		if (NumberOfMintermsIncludedinOtherImplicants == AllImplicants[i].Size)
		{
			DecreaseInclusionOfMintermsInDeletedImplicant(i);
			AllImplicants.erase(AllImplicants.begin() + i);
			--i;

			cout << "erase" << endl;
		}
	}






	cout << "After deletion" << endl;
	for (int i = 0; i < AllImplicants.size(); i++)
	{
		for (int j = 0; j < AllImplicants[i].minterms.size(); j++)
		{
			string minterm = AllImplicants[i].minterms[j].binaryminterm;
			cout << minterm << " ";
		}
		cout << i << endl;
	}
}

void GetFinalExpression()
{
	string *MintermsInPI;
	string PI = "";
	int NumOfMinterms;
	for (int i = 0; i < AllImplicants.size(); i++)
	{
		 NumOfMinterms = AllImplicants[i].minterms.size();
			MintermsInPI = new string[AllImplicants[i].minterms.size()];
			for (int j = 0; j < AllImplicants[i].minterms.size(); j++)
			{				


				MintermsInPI[j] = AllImplicants[i].minterms[j].binaryminterm;
				cout << MintermsInPI[j];
			}

			int NoChange = 0;
			
			for (int L = 0; L < 3; L++)
			{
				int m = 0;
					for (int k = 1; k < NumOfMinterms; k++)
					{
						cout << endl << "MintermsInPI[m][L] == MintermsInPI[k][L]" << MintermsInPI[m][L] << " "<<  MintermsInPI[k][L] << endl;
						if (MintermsInPI[m][L] == MintermsInPI[k][L])
						{
							NoChange++;
						}
					}
					
					cout << "No change " << NoChange<< endl;
				
					if (NoChange == NumOfMinterms - 1)
					{
						//cout <<endl<< "(MintermsInPI[0][L]   " << MintermsInPI[0][L] << endl;
							if (MintermsInPI[0][L] == '0')
							{
								
								PI += "(~";
								PI+= char(L + 65);
							    PI += ")";
							/*	cout << "Got into zero case" << endl;
								cout << endl << PI << endl;*/
							}
							else if (MintermsInPI[0][L] == '1')
							{
								PI += "(";
								PI += char(L + 65);
								PI += ")";
								/*cout << "Got into 1 case" << endl;
								cout << endl << PI << "1";*/
							}
					}
					NoChange = 0;
			}


			PI += " + ";
		
	}

	FinalExpression = PI;
	FinalExpression = FinalExpression.erase(FinalExpression.size() - 2);

}