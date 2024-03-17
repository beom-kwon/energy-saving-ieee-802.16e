#include <iostream>
using namespace std;

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
	cout<<"Initial Sleep Window Size : ";
	cin>>Ini_Sw;
	cout<<"\t    Max Sleep Window Size : ";
	cin>>Max_Sw;
	cout<<"\t    Listening Window Size : ";
	cin>>Lw;
	cout<<endl;
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
	cout<<"Sleep Window Size : ";
	cin>>Sw;
	cout<<"\t    Listening Window Size : ";
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
void ShowProgress(int*);

int main(void)
{
	Type1 Class0;

	Type2 Class1;
	Type2 Class2;
	Type2 Class3;
	Type2 Class4;
	Type2 Class5;
	Type2 Class6;
	Type2 Class7;

	cout<<"\n\t******** Simulation Start ********\n"<<endl;
	
	cout<<"\t[0] "; Class0.Input();
	cout<<"\t[1] "; Class1.Input();
	cout<<"\t[2] "; Class2.Input();
	cout<<"\t[3] "; Class3.Input();
	cout<<"\t[4] "; Class4.Input();
	cout<<"\t[5] "; Class5.Input();
	cout<<"\t[6] "; Class6.Input();
	cout<<"\t[7] "; Class7.Input();

	int Select_sw = 0, Select_lw = 0;

	// Find Minimum Sleep Window
	if((Class1.Sw<=Class2.Sw)&&(Class1.Sw<=Class3.Sw)&&(Class1.Sw<=Class4.Sw)&&(Class1.Sw<=Class5.Sw)&&(Class1.Sw<=Class6.Sw)&&(Class1.Sw<=Class7.Sw))
		Select_sw = Class1.Sw;
	else if((Class2.Sw<=Class1.Sw)&&(Class2.Sw<=Class3.Sw)&&(Class2.Sw<=Class4.Sw)&&(Class2.Sw<=Class5.Sw)&&(Class2.Sw<=Class6.Sw)&&(Class2.Sw<=Class7.Sw))
		Select_sw = Class2.Sw;
	else if((Class3.Sw<=Class1.Sw)&&(Class3.Sw<=Class2.Sw)&&(Class3.Sw<=Class4.Sw)&&(Class3.Sw<=Class5.Sw)&&(Class3.Sw<=Class6.Sw)&&(Class3.Sw<=Class7.Sw))
		Select_sw = Class3.Sw;
	else if((Class4.Sw<=Class1.Sw)&&(Class4.Sw<=Class2.Sw)&&(Class4.Sw<=Class3.Sw)&&(Class4.Sw<=Class5.Sw)&&(Class4.Sw<=Class6.Sw)&&(Class4.Sw<=Class7.Sw))
		Select_sw = Class4.Sw;	
	else if((Class5.Sw<=Class1.Sw)&&(Class5.Sw<=Class2.Sw)&&(Class5.Sw<=Class3.Sw)&&(Class5.Sw<=Class4.Sw)&&(Class5.Sw<=Class6.Sw)&&(Class5.Sw<=Class7.Sw))
		Select_sw = Class5.Sw;
	else if((Class6.Sw<=Class1.Sw)&&(Class6.Sw<=Class2.Sw)&&(Class6.Sw<=Class3.Sw)&&(Class6.Sw<=Class4.Sw)&&(Class6.Sw<=Class5.Sw)&&(Class6.Sw<=Class7.Sw))
		Select_sw = Class6.Sw;
	else Select_sw = Class7.Sw;

	// Find Maximum Listening Window
	if((Class1.Lw>=Class2.Lw)&&(Class1.Lw>=Class3.Lw)&&(Class1.Lw>=Class4.Lw)&&(Class1.Lw>=Class5.Lw)&&(Class1.Lw>=Class6.Lw)&&(Class1.Lw>=Class7.Lw))
		Select_lw = Class1.Lw;
	else if((Class2.Lw>=Class1.Lw)&&(Class2.Lw>=Class3.Lw)&&(Class2.Lw>=Class4.Lw)&&(Class2.Lw>=Class5.Lw)&&(Class2.Lw>=Class6.Lw)&&(Class2.Lw>=Class7.Lw))
		Select_lw = Class2.Lw;
	else if((Class3.Lw>=Class1.Lw)&&(Class3.Lw>=Class2.Lw)&&(Class3.Lw>=Class4.Lw)&&(Class3.Lw>=Class5.Lw)&&(Class3.Lw>=Class6.Lw)&&(Class3.Lw>=Class7.Lw))
		Select_lw = Class3.Lw;
	else if((Class4.Lw>=Class1.Lw)&&(Class4.Lw>=Class2.Lw)&&(Class3.Lw>=Class3.Lw)&&(Class3.Lw>=Class5.Lw)&&(Class3.Lw>=Class6.Lw)&&(Class3.Lw>=Class7.Lw))
		Select_lw = Class4.Lw;
	else if((Class5.Lw>=Class1.Lw)&&(Class5.Lw>=Class2.Lw)&&(Class3.Lw>=Class3.Lw)&&(Class3.Lw>=Class4.Lw)&&(Class3.Lw>=Class6.Lw)&&(Class3.Lw>=Class7.Lw))
		Select_lw = Class5.Lw;
	else if((Class6.Lw>=Class1.Lw)&&(Class6.Lw>=Class2.Lw)&&(Class3.Lw>=Class3.Lw)&&(Class3.Lw>=Class4.Lw)&&(Class3.Lw>=Class5.Lw)&&(Class3.Lw>=Class7.Lw))
		Select_lw = Class6.Lw;
	else Select_lw = Class7.Lw;

	cout<<"\t"<<"The Smallest Sleep Window Size : "<<Select_sw<<endl;
	cout<<"\t"<<"The Largest Listening Window Size : "<<Select_lw<<endl;
	cout<<endl;

	int arr[Arr_size]; // Array for the proposed method
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

	int* pArr = arr;

	ShowProgress(pArr);

	cout<<"\n\t******** Standard 802.16e - Power Saving Class ********\n"<<endl;

	Class0.Arragement();
	Class1.Arragement();
	Class2.Arragement();
	Class3.Arragement();
	Class4.Arragement();
	Class5.Arragement();
	Class6.Arragement();
	Class7.Arragement();

//	for(int i=0; i<Arr_size; i++){
//		cout<<Class0.arr[i]<<" ";
//	}
//	for(int i=0; i<Arr_size; i++){
//		cout<<Class1.arr[i]<<" ";
//	}
//	cout<<endl;
//	for(int i=0; i<Arr_size; i++){
//		cout<<Class2.arr[i]<<" ";
//	}
//	cout<<endl;
//	for(int i=0; i<Arr_size; i++){
//		cout<<Class3.arr[i]<<" ";
//	}
//	cout<<endl;

	int SumArr[Arr_size];    // Array for the Standard 802.16e
	int* pSumArr = SumArr;

	for(int i=0; i<Arr_size; i++)
	{
		if((Class0.arr[i]==1)||(Class1.arr[i]==1)||(Class2.arr[i]==1)||(Class3.arr[i]==1)||(Class4.arr[i]==1)||(Class5.arr[i]==1)||(Class6.arr[i]==1)||(Class7.arr[i]==1))
		{
			SumArr[i] = 1;
		}
		else if((Class0.arr[i]==0)&&(Class1.arr[i]==0)&&(Class2.arr[i]==0)&&(Class3.arr[i]==0)&&(Class4.arr[i]==0)&&(Class5.arr[i]==0)&&(Class6.arr[i]==0)&&(Class7.arr[i]==0))
		{
			SumArr[i] = 0;
		}
	}
//	for(int i=0; i<Arr_size; i++){
//		cout<<SumArr[i]<<" ";
//	}
	ShowProgress(pSumArr);
	
	cout<<"\n\t******** Implementation of the eMUI ********\n"<<endl;

	int eMUIArr[Arr_size];    // Array for the eMUI
	int* peMUIArr = eMUIArr;
	int StartFrame1 = 0;
	int StartFrame2 = 0;
	int StartFrame3 = 0;
	int StartFrame4 = 0;
	int StartFrame5 = 0;
	int StartFrame6 = 0;
	int StartFrame7 = 0;
	
	int maxSleep=0;

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
						for(int o=0; o<Class6.Sw; o++)
						{
							Class6.Shift(o);
							for(int p=0; p<Arr_size; p++)
							{
								if((Class1.arr[p]==1)||(Class2.arr[p]==1)||(Class3.arr[p]==1)||(Class4.arr[p]==1)||(Class5.arr[p]==1)||(Class6.arr[p]==1)||(Class7.arr[p]==1))
								{
									eMUIArr[p] = 1;
								}
								else if((Class1.arr[p]==0)&&(Class2.arr[p]==0)&&(Class3.arr[p]==0)&&(Class4.arr[p]==0)&&(Class5.arr[p]==0)&&(Class6.arr[p]==0)&&(Class7.arr[p]==0))
								{
									eMUIArr[p] = 0;
								}
								int Sleepcount = 0;
								int Listencount = 0;

								for(int b=0; b<Arr_size; b++)
								{
									if(eMUIArr[b]==0)
										Sleepcount++;
									else Listencount++;
								}
								if(maxSleep < Sleepcount)
								{
									StartFrame1 = i;
									StartFrame2 = j;
									StartFrame3 = k;
									StartFrame4 = l;
									StartFrame5 = n;
									StartFrame6 = o;
									StartFrame7 = p;
									maxSleep = Sleepcount;
								}
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
	Class4.Shift(StartFrame3);
	Class5.Shift(StartFrame3);
	Class6.Shift(StartFrame3);
	Class7.Shift(StartFrame3);

	for(int i=0; i<Arr_size; i++)
	{
		if((Class1.arr[i]==1)||(Class2.arr[i]==1)||(Class3.arr[i]==1)||(Class4.arr[i]==1)||(Class5.arr[i]==1)||(Class6.arr[i]==1)||(Class7.arr[i]==1))
		{
				eMUIArr[i] = 1;
		}
		else if((Class1.arr[i]==0)&&(Class2.arr[i]==0)&&(Class3.arr[i]==0)&&(Class4.arr[i]==0)&&(Class5.arr[i]==0)&&(Class6.arr[i]==0)&&(Class7.arr[i]==0))
		{
				eMUIArr[i] = 0;
		}
	}
	ShowProgress(peMUIArr);

	return 0;
}

// Sleep : 1 energy, Listen : 10 energy
void ShowProgress(int* pArr)
{
	int Swcount = 0;
	int Lwcount = 0;

	for(int i=0; i<Arr_size; i++){
		if(*(pArr+i)==0)
			Swcount++;
		else Lwcount++;
		/*
		if((i%4) == 0)
		{
			cout<<"\n\t["<<i<<"] # Sleep Window : "<<Swcount<<endl;
			cout<<"\t["<<i<<"] # Listening Window : "<<Lwcount<<endl;
			cout<<"\t["<<i<<"] Consumption Energy : "<<(1*Swcount+10*Lwcount)<<endl;
		}
		*/
	}
	cout<<"\n\tThe Number of Total Sleep Window : "<<Swcount<<endl;
	cout<<"\tThe Number of Total Listening Window : "<<Lwcount<<endl;	
	cout<<"\tThe Total Consumption Energy : "<<(1*Swcount+10*Lwcount)<<"\n"<<endl;
}