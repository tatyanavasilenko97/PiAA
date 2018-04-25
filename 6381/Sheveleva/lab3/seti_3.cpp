#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>
using namespace std;

struct Way 
{
	int elem;
	int matrix;
};

int main () 
{
	int graf_real[26][26]={0},
		graf_residual[26][26]={0},
		max_flow_amount, size;
	int s = 0, w, curr, flag, saw;
	int min, res=0;
	char istok, stok, f_el, s_el;
	int hesh[26];
	int s_max=0, max=0;
	Way way[50];
		 
	cin >> size;
    cin >> istok >> stok;
	while (s < size)
	{
		cin >> f_el >> s_el >> max_flow_amount;
		graf_real[f_el-istok][s_el-istok] = max_flow_amount;
		s++;
	}
	
	while(1)
	{
		memset(hesh, 0, sizeof(hesh));
		memset(way, 0, sizeof(way));
		way[0].elem = 0; way[0].matrix = 0; w = 1;
		curr = 0;
		saw = -1;
		while(curr != stok - istok)
		{
			s_max=0, max=0;
			flag = 0;
			for(int i = 0; i<26;i++)
				if((graf_residual[curr][i] != 0)&&(hesh[i] != 1)&&(i != saw))
					{
						way[w].elem = i; way[w].matrix = 1; w++;
						flag = 1;
						hesh[curr] = 1;
						curr = i;
						saw = -1;
					}
			if (flag == 0)
			{
				for(int i = 0; i<26;i++)
					if((graf_real[curr][i] != 0) && (hesh[i] != 1) && (i != saw))
						if(max < graf_real[curr][i])
							{
								max = graf_real[curr][i]; 
								s_max = i;
							}
				if(max != 0)
					{
						way[w].elem = s_max; way[w].matrix = 0; w++;
						flag = 1;
						hesh[curr] = 1;
						curr = s_max;
						saw = -1;
					}
			}
			if((flag == 0)&&(curr!=0)) 
			{
				saw=curr;
				way[w-1].elem = 0; way[w-1].matrix = 0; w--;
				curr = way[w-1].elem;
				continue;
			}
			if((flag == 0)&&((curr==0)||(curr==stok - istok))) {break;}
		}
		
		if(flag == 0) break;
		min = graf_real[way[0].elem][way[1].elem];
		
		for (int j = 0; j < w - 1; j++)
		{
			if(way[j+1].matrix == 0)
				{
					if(min > graf_real[way[j].elem][way[j + 1].elem])
					min = graf_real[way[j].elem][way[j + 1].elem]; 
				}
			else
				{
					if(min > graf_residual[way[j].elem][way[j + 1].elem])
					min = graf_residual[way[j].elem][way[j + 1].elem];
				}
		}
		
		res += min;
		
		for (int j = 0; j < w - 1; j++)
		{
			if(way[j+1].matrix == 0)
			{
				graf_real[way[j].elem][way[j + 1].elem] -= min;
				graf_residual[way[j + 1].elem][way[j].elem] += min;
			}
			else
			{
				graf_residual[way[j].elem][way[j + 1].elem] -= min;
				graf_real[way[j + 1].elem][way[j].elem] += min;
			}
		}
	}
	cout<<res<<endl;
	for(int i=0;i<26;i++)
		for(int j=0;j<26;j++)
			if(graf_real[i][j]!=0 || graf_residual[j][i]!=0) 
				cout<<(char)(i+(int)istok)<<' '<<(char)(j+(int)istok)<<' '<<graf_residual[j][i]<<endl;
	return 0;
}
