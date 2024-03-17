// The Number of Class is 6
// Type 1 : 1
// Type 2 : 5

#include <iostream>
#include <time.h>
using namespace std;

#define No_Simulation 2000
#define Arr_size 36 

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
	Sw = (rand()%9)+2;
	Lw = (rand()%(Sw-1))+1;
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
double Delay(int*, int);

int main(void)
{
	srand((unsigned)time(NULL));
	Type1 Class0;
	Type2 Class1;
	Type2 Class2;
	Type2 Class3;
	Type2 Class4;
	Type2 Class5;
	
	cout<< "\n\t The Number of Class is 6 (Type 1 : 1, Type 2 : 5) "<<endl;
	cout<<"\n\t******** Implementation of the Proposed Method ********\n"<<endl;
	
	int IdeaArr[Arr_size];    // Array for the proposed method
	int* pArr = IdeaArr;
	double Idea_E_Avg = 0;
	double Idea_S_Avg = 0;
	double Idea_L_Avg = 0;
	int Idea_Sum_S_window = 0;
	double Idea_delay_sum = 0;
	double Idea_delay_avg = 0;

	int SumArr[Arr_size];    // Array for the Standard 802.16e
	int* pSumArr = SumArr;
	double Stand_E_Avg = 0;
	double Stand_S_Avg = 0;
	double Stand_L_Avg = 0;
	int Stand_Sum_S_window = 0;
	double Stand_delay_sum = 0;
	double Stand_delay_avg = 0;

	int eMUIArr[Arr_size];    // Array for the eMUI
	int* peMUIArr = eMUIArr;
	double eMUI_E_Avg = 0;
	double eMUI_S_Avg = 0;
	double eMUI_L_Avg = 0;
	int eMUI_Sum_S_window = 0;
	int maxSleep = 0;
	int StartFrame1 = 0;
	int StartFrame2 = 0;
	int StartFrame3 = 0;
	int StartFrame4 = 0;
	int StartFrame5 = 0;
	double eMUI_delay_sum = 0;
	double eMUI_delay_avg = 0;
	
	for(int i=0; i<No_Simulation; i++)
	{
		int random = rand();

		Class0.Input();
		Class1.Input();
		Class2.Input();
		Class3.Input();
		Class4.Input();
		Class5.Input();

		int Select_sw = 0, Select_lw = 0;
		if((Class1.Sw<=Class2.Sw)&&(Class1.Sw<=Class3.Sw)&&(Class1.Sw<=Class4.Sw)&&(Class1.Sw<=Class5.Sw))
			Select_sw = Class1.Sw;
		else if((Class2.Sw<=Class1.Sw)&&(Class2.Sw<=Class3.Sw)&&(Class2.Sw<=Class4.Sw)&&(Class2.Sw<=Class5.Sw))
			Select_sw = Class2.Sw;
		else if((Class3.Sw<=Class1.Sw)&&(Class3.Sw<=Class2.Sw)&&(Class3.Sw<=Class4.Sw)&&(Class3.Sw<=Class5.Sw))
			Select_sw = Class3.Sw;
		else if((Class4.Sw<=Class1.Sw)&&(Class4.Sw<=Class2.Sw)&&(Class4.Sw<=Class3.Sw)&&(Class4.Sw<=Class5.Sw))
			Select_sw = Class4.Sw;
		else
			Select_sw = Class5.Sw;

		if((Class1.Lw>=Class2.Lw)&&(Class1.Lw>=Class3.Lw)&&(Class1.Lw>=Class4.Lw)&&(Class1.Lw>=Class5.Lw))
			Select_lw = Class1.Lw;
		else if((Class2.Lw>=Class1.Lw)&&(Class2.Lw>=Class3.Lw)&&(Class2.Lw>=Class4.Lw)&&(Class2.Lw>=Class5.Lw))
			Select_lw = Class2.Lw;
		else if((Class3.Lw>=Class1.Lw)&&(Class3.Lw>=Class2.Lw)&&(Class3.Lw>=Class4.Lw)&&(Class3.Lw>=Class5.Lw))
			Select_lw = Class3.Lw;
		else if((Class4.Lw>=Class1.Lw)&&(Class4.Lw>=Class2.Lw)&&(Class4.Lw>=Class3.Lw)&&(Class4.Lw>=Class5.Lw))
			Select_lw = Class4.Lw;
		else
			Select_lw = Class5.Lw;

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
		Idea_delay_sum += Delay(pArr, random);

		//Class0.Arragement();
		Class1.Arragement();
		Class2.Arragement();
		Class3.Arragement();
		Class4.Arragement();
		Class5.Arragement();

		// eMUI
		for(int i=0; i<Class1.Sw; i++)
		{
			Class1.Shift(i);
			for(int j=0; j<Class2.Sw; j++)
			{
				Class2.Shift(j);
				for(int k=0; k<Class3.Sw; k++)
				{
					Class3.Shift(k);
					for(int l=0; l<Class4.Sw; l++)
					{
						Class4.Shift(l);
						for(int n=0; n<Class5.Sw; n++)
						{
							Class5.Shift(n);
							for(int o=0; o<Arr_size; o++)
							{
								if((Class1.arr[o]==1)||(Class2.arr[o]==1)||(Class3.arr[o]==1)||(Class4.arr[o]==1)||(Class5.arr[o]==1))
								{
									eMUIArr[o] = 1;
								}
								else if((Class1.arr[o]==0)||(Class2.arr[o]==0)||(Class3.arr[o]==0)||(Class4.arr[o]==0)||(Class5.arr[o]==0))
								{
									eMUIArr[o] = 0;
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
									StartFrame3 = k;
									StartFrame4 = l;
									StartFrame5 = n;
									maxSleep = Sleepcount;
								}
							}
						}
					}
				}
			}
		}
		Class1.Shift(StartFrame1);
		Class2.Shift(StartFrame2);
		Class3.Shift(StartFrame3);
		Class4.Shift(StartFrame4);
		Class5.Shift(StartFrame5);

		for(int i=0; i<Arr_size; i++)
		{
			if((Class1.arr[i]==1)||(Class2.arr[i]==1)||(Class3.arr[i]==1)||(Class4.arr[i]==1)||(Class5.arr[i]==1))
			{
				eMUIArr[i] = 1;
			}
			else if((Class1.arr[i]==0)&&(Class2.arr[i]==0)&&(Class3.arr[i]==0)&&(Class4.arr[i]==0)&&(Class5.arr[i]==0))
			{
				eMUIArr[i] = 0;
			}
		}
		eMUI_Sum_S_window += ShowProgress(peMUIArr);
		eMUI_delay_sum += Delay(peMUIArr, random);

		// Standar 802.16e
		Class0.Arragement();
		Class1.Arragement();
		Class2.Arragement();
		Class3.Arragement();
		Class4.Arragement();
		Class5.Arragement();

		for(int i=0; i<Arr_size; i++)
		{
			if((Class0.arr[i]==1)||(Class1.arr[i]==1)||(Class2.arr[i]==1)||(Class3.arr[i]==1)||(Class4.arr[i]==1)||(Class5.arr[i]==1))
			{
				SumArr[i] = 1;
			}
			else if((Class0.arr[i]==0)&&(Class1.arr[i]==0)&&(Class2.arr[i]==0)&&(Class3.arr[i]==0)&&(Class4.arr[i]==0)&&(Class5.arr[i]==0))
			{
				SumArr[i] = 0;
			}
		}
		Stand_Sum_S_window += ShowProgress(pSumArr);
		Stand_delay_sum += Delay(pSumArr, random);
	}
	//cout.setf(fixed);
	//cout.setf(precisitions);

	Idea_S_Avg = Idea_Sum_S_window;
	Idea_L_Avg = (double)(Arr_size*No_Simulation) - Idea_S_Avg;
	Idea_E_Avg = ((1.0*Idea_S_Avg)+(10.0*Idea_L_Avg))/(double)No_Simulation;
	Idea_delay_avg = Idea_delay_sum/(double)No_Simulation;

	cout << "\tIdea Sleep Avg = " << Idea_S_Avg << endl;
	cout << "\tIdea Listenning Avg = " << Idea_L_Avg << endl;
	cout << "\tIdea Energy Avg = " << Idea_E_Avg << endl;
	cout << "\tIdea Delay Avg = " << Idea_delay_avg << endl;

	cout<<"\n\t******** Standard 802.16e - Power Saving Class ********\n"<<endl;		
	Stand_S_Avg = Stand_Sum_S_window;
	Stand_L_Avg = (double)(Arr_size*No_Simulation) - Stand_S_Avg;
	Stand_E_Avg = ((1.0*Stand_S_Avg)+(10.0*Stand_L_Avg))/(double)No_Simulation;
	Stand_delay_avg = Stand_delay_sum/(double)No_Simulation;

	cout << "\tStandard Sleep Avg = " << Stand_S_Avg << endl;
	cout << "\tStandard Listenning Avg = " << Stand_L_Avg << endl;
	cout << "\tStandard Energy Avg = " << Stand_E_Avg << endl;
	cout << "\tStandard Delay Avg = " << Stand_delay_avg << endl;

	cout<<"\n\t******** Implementation of the eMUI ********\n"<<endl;	
	eMUI_S_Avg = eMUI_Sum_S_window;
	eMUI_L_Avg = (double)(Arr_size*No_Simulation) - eMUI_S_Avg;
	eMUI_E_Avg = ((1.0*eMUI_S_Avg)+(10.0*eMUI_L_Avg))/(double)No_Simulation;
	eMUI_delay_avg = eMUI_delay_sum/(double)No_Simulation;

	cout << "\teMUI Sleep Avg = " << eMUI_S_Avg << endl;
	cout << "\teMUI Listenning Avg = " << eMUI_L_Avg << endl;
	cout << "\teMUI Energy Avg = " << eMUI_E_Avg << endl;
	cout << "\teMUI Delay Avg = " << eMUI_delay_avg << endl;
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
double Delay(int* tempArr, int random)
{
	int temp=0;
	int sum=0;
	int swpart=0;
	int swnum=0;
	bool swon=0;

	// 0 : sleep, 1 : listen
	for(int i=0; i<Arr_size; i++)
	{
		if(*(tempArr+i)==0)
		{
			swnum++;
			swon=1;
		}
		else if((*(tempArr+i)==1) && (swon==1))
		{
			swpart++;
			temp = (random%swnum)+1;
			sum += temp;
			swnum = 0;
			swon = 0;
		}
		if((swon==1) && (i == (Arr_size-1)))
			swpart++;
	}
	if(swpart==0)
		return 0.0;
	else
		return ((double)sum/(double)swpart);
}