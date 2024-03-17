// The Number of Class is 3
// Type 1 : 1
// Type 2 : 2

#include <iostream>
#include <time.h>
using namespace std;

#define No_Simulation 1
#define Arr_size 360 
#define Gap 10

class Type1{
public:
	int Ini_Sw;
	int Max_Sw;
	int Lw;
	int arr[Arr_size];
	int swcnt;
	int lwcnt;

	void Input(void);
	void Arragement(void);
};
class Type2{
public:
	int Sw;
	int Lw;
	int arr[Arr_size];
	int swcnt;
	int lwcnt;

	void Input(void);
	void Arragement(void);
	void Shift(int);
};
void Type1::Input()
{	
	Ini_Sw = 1;
	Max_Sw = 64;
	Lw = 1;
	//cout<<"Initial Sleep Window Size : "<<Ini_Sw;
	//cout<<"\t    Max Sleep Window Size : "<<Max_Sw;
	//cout<<"\t    Listening Window Size : "<<Lw;
	//cout<<endl;
}
void Type1::Arragement()
{
	swcnt = Ini_Sw;
	lwcnt = Lw;

	// 0 : sleep, 1 : listen
	for(int i=0; i<Arr_size; i++){	
		if((swcnt == 0) && (lwcnt == 0))
		{
			if(Ini_Sw < Max_Sw)
			{
				Ini_Sw *= 2;
				if(Ini_Sw > Max_Sw)
				{
					Ini_Sw = Max_Sw;
				}
				swcnt = Ini_Sw;
			}
			else if(Ini_Sw == Max_Sw)
			{
				swcnt = Max_Sw;
			}
			lwcnt = Lw;
		}
		if(swcnt != 0){
			arr[i] = 0;
			swcnt--;
		}
		else if(lwcnt != 0){
			arr[i] = 1;
			lwcnt--;
		}
	}
}
void Type2::Input()
{
	cout<<"\tSleep Window Size : ";
	cin>>Sw;
	cout<<"\tListening Window Size : ";
	cin>>Lw;
	cout<<endl;
} 
void Type2::Arragement()
{
	swcnt = Sw;
	lwcnt = Lw;

	// 0 : sleep, 1 : listen
	for(int i=0; i<Arr_size; i++){	
		if((swcnt == 0) && (lwcnt == 0)){
			swcnt = Sw;
			lwcnt = Lw;
		}
		if(swcnt != 0){
			arr[i] = 0;
			swcnt--;
		}
		else if(lwcnt != 0){
			arr[i] = 1;
			lwcnt--;
		}
	}
}
void Type2::Shift(int startFrame)
{
	swcnt = Sw;
	lwcnt = Lw;

	if(startFrame != 0)
	{
		for(int i=0; i<startFrame; i++)
		{
			arr[i] = 1;
		}
	}
	// 0 : sleep, 1 : listen
	for(int i = startFrame; i<Arr_size; i++){	
		if((swcnt == 0) && (lwcnt == 0)){
			swcnt = Sw;
			lwcnt = Lw;
		}
		if(swcnt != 0){
			arr[i] = 0;
			swcnt--;
		}
		else if(lwcnt != 0){
			arr[i] = 1;
			lwcnt--;
		}
	}
}
int ShowProgress(int*);

int main(void)
{
	srand((unsigned)time(NULL));
	Type1 Class0;
	Type2 Class1;
	Type2 Class2;

	cout<< "\n\t The Number of Class is 3 (Type 1 : 1, Type 2 : 2) \n"<<endl;
	
	int IdeaArr[Arr_size];    // Array for the proposed method
	int* pArr = IdeaArr;
	double Idea_E_Avg = 0;
	double Idea_S_Avg = 0;
	double Idea_L_Avg = 0;
	int Idea_Sum_S_window = 0;
	
	int SumArr[Arr_size];    // Array for the Standard 802.16e
	int* pSumArr = SumArr;
	double Stand_E_Avg = 0;
	double Stand_S_Avg = 0;
	double Stand_L_Avg = 0;
	int Stand_Sum_S_window = 0;

	int eMUIArr[Arr_size];    // Array for the eMUI
	int* peMUIArr = eMUIArr;
	double eMUI_E_Avg = 0;
	double eMUI_S_Avg = 0;
	double eMUI_L_Avg = 0;
	int eMUI_Sum_S_window = 0;
	int maxSleep = 0;
	int StartFrame1 = 0;
	int StartFrame2 = 0;
	
	for(int i=0; i<No_Simulation; i++)
	{
		Class0.Input();
		Class1.Input();
		Class2.Input();

		int Select_sw = 0, Select_lw = 0;
		if((Class1.Sw <= Class2.Sw))
			Select_sw = Class1.Sw;
		else
			Select_sw = Class2.Sw;

		if((Class1.Lw >= Class2.Lw))
			Select_lw = Class1.Lw;
		else
			Select_lw = Class2.Lw;

		int arr[Arr_size];      // Array for the proposed method
		int scnt = Select_sw;
		int lcnt = Select_lw;
	
		// 0 : sleep, 1 : listen
		for(int i=0; i<Arr_size; i++){	
			if((scnt == 0) && (lcnt == 0)){
				scnt = Select_sw;
				lcnt = Select_lw;
			}
			if(scnt != 0){
				arr[i] = 0;
				scnt--;
			}
			else if(lcnt != 0){
				arr[i] = 1;
				lcnt--;
			}
		}
		for(int i=0; i<Arr_size; i++)
		{
			IdeaArr[i] = arr[i];
		}
		Idea_Sum_S_window += ShowProgress(pArr); 

		//Class0.Arragement();
		Class1.Arragement();
		Class2.Arragement();

		// eMUI
		for(int i=0; i<Class1.Sw; i++)
		{
			Class1.Shift(i);
			for(int j=0; j<Class2.Sw; j++)
			{
				Class2.Shift(j);
				for(int k=0; k<Arr_size; k++)
				{
					if((Class1.arr[k]==1)||(Class2.arr[k]==1))
					{
						eMUIArr[k] = 1;
					}
					else if((Class1.arr[k]==0)||(Class2.arr[k]==0))
					{
						eMUIArr[k] = 0;
					}
					int Sleepcount = 0;
					int Listencount = 0;
				
					for(int b=0; b<Arr_size; b++)
					{
						if(eMUIArr[b]==0)
							Sleepcount ++;
						else Listencount ++;
					}	
					if(maxSleep < Sleepcount)
					{
						StartFrame1 = i;
						StartFrame2 = j;
						maxSleep = Sleepcount;
					}
				}
			}
		}
		Class1.Shift(StartFrame1);
		Class2.Shift(StartFrame2);

		for(int i=0; i<Arr_size; i++)
		{
			if((Class1.arr[i]==1)||(Class2.arr[i]==1))
			{
				eMUIArr[i] = 1;
			}
			else if((Class1.arr[i]==0)&&(Class2.arr[i]==0))
			{
				eMUIArr[i] = 0;
			}
		}
		eMUI_Sum_S_window += ShowProgress(peMUIArr);

		// Standar 802.16e
		Class0.Arragement();
		Class1.Arragement();
		Class2.Arragement();

		for(int i=0; i<Arr_size; i++)
		{
			if((Class0.arr[i]==1)||(Class1.arr[i]==1)||(Class2.arr[i]==1))
			{
				SumArr[i] = 1;
			}
			else if((Class0.arr[i]==0)&&(Class1.arr[i]==0)&&(Class2.arr[i]==0))
			{
				SumArr[i] = 0;
			}
		}
		Stand_Sum_S_window += ShowProgress(pSumArr);
	}

	cout<<"\n\t******** Implementation of the Proposed Method ********\n"<<endl;
	Idea_S_Avg = Idea_Sum_S_window;
	Idea_L_Avg = (double)(Arr_size*No_Simulation) - Idea_S_Avg;
	Idea_E_Avg = ((1.0*Idea_S_Avg)+(10.0*Idea_L_Avg))/(double)No_Simulation;
	// (start) Find the Number of Frames in Unavailability Interval
	int Idea_Sw = 0;
	int Idea_Lw = 0;

	for(int i=0; i<Arr_size; i++)
	{
		if(IdeaArr[i]==0)
			Idea_Sw++;
		else Idea_Lw++;
		
		if((i%Gap) == 0)
		{
			cout<<"\n\t["<<i<<"] # Sleep Window : "<<Idea_Sw;
		}
	}
	cout<<endl;
	// (end)
	cout << "\tIdea Sleep Avg = " << Idea_S_Avg << endl;
	cout << "\tIdea Listenning Avg = " << Idea_L_Avg << endl;
	cout << "\tIdea Energy Avg = " << Idea_E_Avg << endl;

	cout<<"\n\t******** Standard 802.16e - Power Saving Class ********\n"<<endl;		
	Stand_S_Avg = Stand_Sum_S_window;
	Stand_L_Avg = (double)(Arr_size*No_Simulation) - Stand_S_Avg;
	Stand_E_Avg = ((1.0*Stand_S_Avg)+(10.0*Stand_L_Avg))/(double)No_Simulation;
	// (start) Find the Number of Frames in Unavailability Interval
	int std_Sw = 0;
	int std_Lw = 0;

	for(int i=0; i<Arr_size; i++)
	{
		if(SumArr[i]==0)
			std_Sw++;
		else std_Lw++;
		
		if((i%Gap) == 0)
		{
			cout<<"\n\t["<<i<<"] # Sleep Window : "<<std_Sw;
		}
	}
	cout<<endl;
	// (end)
	cout << "\tStandard Sleep Avg = " << Stand_S_Avg << endl;
	cout << "\tStandard Listenning Avg = " << Stand_L_Avg << endl;
	cout << "\tStandard Energy Avg = " << Stand_E_Avg << endl;
	
	cout<<"\n\t******** Implementation of the eMUI ********\n"<<endl;	
	eMUI_S_Avg = eMUI_Sum_S_window;
	eMUI_L_Avg = (double)(Arr_size*No_Simulation) - eMUI_S_Avg;
	eMUI_E_Avg = ((1.0*eMUI_S_Avg)+(10.0*eMUI_L_Avg))/(double)No_Simulation;
	// (start) Find the Number of Frames in Unavailability Interval
	int eMUI_Sw = 0;
	int eMUI_Lw = 0;

	for(int i=0; i<Arr_size; i++)
	{
		if(eMUIArr[i]==0)
			eMUI_Sw++;
		else eMUI_Lw++;
		
		if((i%Gap) == 0)
		{
			cout<<"\n\t["<<i<<"] # Sleep Window : "<<eMUI_Sw;
		}
	}
	cout<<endl;
	// (end)
	cout << "\teMUI Sleep Avg = " << eMUI_S_Avg << endl;
	cout << "\teMUI Listenning Avg = " << eMUI_L_Avg << endl;
	cout << "\teMUI Energy Avg = " << eMUI_E_Avg << endl;
	cout << endl;
	
	return 0;
}

// Sleep : 1 energy, Listen : 10 energy
int ShowProgress(int* pArr)
{
	int Swcount = 0;
	int Lwcount = 0;

	for(int i=0; i<Arr_size; i++){
		if(*(pArr+i)==0)
			Swcount++;
		else Lwcount++;
	}
	return Swcount;
}