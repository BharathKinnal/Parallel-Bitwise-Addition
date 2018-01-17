// Program to simulate parallel bitwise addition using arrays

#include<bits/stdc++.h>
#include<stdint.h>
//#include<conio.h>
using namespace std;

// Specify size of number 
typedef uint16_t type;

// Naming all input and output variables for full adder
type A,B,C,S;

// Other parameters
int acc=0,tot=0,s,limit,i;



// To convert decimal to binary
void convert(int rep[],type x)
{
	for(i=0;i<s;i++)
	{
		rep[i]=(x>>(s-1-i))%2;
		//cout<<rep[i];
	}
	//cout<<endl;
}

// To convert binary to decimal
void convertBack(int rep[],type &x)
{
	x=0;
	for(i=0;i<s;i++)
	{
		x*=2;
		x+=rep[i];
	}
	//cout<<endl;
}



// To perform AND operation to find positions having all 1's
void And(int res[],int a[],int b[])
{
	for(i=0;i<s;i++)
	{
		res[i]=a[i] && b[i];
		//cout<<res[i];
	}
	//cout<<endl;
}

// To perform XNOR operation to find positions having only 1's or only 0's
void XNor(int res[],int a[],int b[])
{
	for(i=0;i<s;i++)
	{
		res[i]=!(a[i] ^ b[i]);
		//cout<<res[i];
	}
	res[i]=1;
	//cout<<'('<<res[i]<<')'<<endl;
}



// To check closest position from a bit havin only 1's or only 0's
int CheckPriority(int pos[],int same[],int j)
{
	if(same[j]==1)
		return j;
	return CheckPriority(pos,same,j+1);
}

// To run a priority encoder to find the closest position from a bit
// having only 1's or 0's, for each bit in the number
void PriorityEncoder(int res[],int pos[],int same[])
{
	//cout<<"Required positions = ";
	int test=0;
	for(int j=0;j<s;j++)
	{
		////cout<<test<<endl;
		res[j]=CheckPriority(pos,same,j);
		//cout<<res[j];
	}
	//cout<<endl;
}



// To find CARRY by calculating reqpos[]
void Carry(int res[],int same[],int only1[],int pos[],int reqpos[])
{
	PriorityEncoder(reqpos,pos,same);
	//cout<<"Carry = ";
	for(i=0;i<s;i++)
	{
		res[i]=only1[reqpos[i]];
		//cout<<res[i];
	}
	//cout<<endl;
}



// To test for accuracy of given algorithm for numbers I and J
type test(type I,type J)
{
	//int t=0;
	A=I;
	B=J;
	
	//Convert numbers A,B into arrays, for easy calculation
	int a[s],b[s];
	//cout<<"a = ";
	convert(a,A);
	//cout<<"b = ";
	convert(b,B);
	//cout<<endl;
	
	//To specify positions of each bit
	int pos[s*2],reqpos[s]={0};
	for(i=0;i<s*2;i++)
		pos[i]=i;

	
	//To find the positions where both bits are only 1's
	int d[s*2]={0};
	//cout<<"d = ";
	And(d,a,b);
	//cout<<endl;
	
	
	//To find the positions where both bits have the same value
	int f[s*2]={0};
	//cout<<"f = ";
	XNor(f,a,b);
	//cout<<endl;
	
	
	//To find CARRY by calculating reqpos[]
	int c[s+1]={0};
	Carry(c,f,d,pos,reqpos);
	//cout<<endl;
	
	
	//convertBack(c,C);
	////cout<<"Carry = "<<C<<endl;
	
	
	//To calculate SUM
	int sum[s];
	//cout<<"Sum (Binary) = ";
	for(i=0;i<s;i++)
	{
		sum[i]=a[i]^b[i]^c[i+1];	//1 bit in CARRY (c[]) acts as carry for next position 
		//cout<<sum[i];
	}
	//cout<<endl;
	
	
	//To find sum in decimal form
	convertBack(sum,S);
	//cout<<"Sum = "<<(int)S<<endl<<"Actual Sum = "<<A+B<<endl;
	
	
	//Calculating accuracy of results
	tot++;
	if(S==(A+B)%limit)
		acc++;
	//if(A==100)
		//cout<<(int)S<<endl;
}



main()
{
	//Size - s; Numbers - I,J; Largest number - limit 
	s=sizeof(type)*8;	
	int I=0x3c00,J=0x5500;
	limit=(1<<s);
	
	//Testing
	//if(GetAsyncKeyState()!=VK_RETURN)
	if(!(kbhit()))
	{
	for(I=0;I<=limit-1;I++){
		for(J=0;J<=limit-1;J++)
			test((type)I,(type)J);
		cout<<I<<endl;
	}
	}
		
	cout<<"No. of test cases = "<<(int)limit*limit<<endl;
	cout<<"Accuracy = "<<(double)acc/tot<<endl;
}
