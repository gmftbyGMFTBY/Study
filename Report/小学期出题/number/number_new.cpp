#include<stdio.h>
#include<string.h>
#define maxn 20
int n,num[maxn],a[maxn],b[maxn],ans[maxn],flag;
int check(int k)
{
	int i,j;
	for(i=1;i<=k;i++)if(num[a[i]]>b[i])return 0;
	int sum=0;
	for(i=1;i<=k;i++)
	{
		int mark=0;
		for(j=1;j<i;j++)
			if(a[j]==a[i])
			{
				if(b[i]!=b[j])return 0;
				mark=1;
			}
		if(!mark)
		{
			sum+=b[i];
			if(sum>n)return 0;
		}
	}
	return 1;
}
void dfs(int k)
{
	int i;
	if(k==n+1)
	{
		//for(i=1;i<=n;i++)printf("%d ",b[i]);
		//printf("\n");
		for(i=1;i<=n;i++)
			if(num[a[i]]!=b[i])return;
		if(flag)
		{
			for(i=1;i<=n;i++)
				if(b[i]>ans[i])return;
		}
		flag=1;
		for(i=1;i<=n;i++)ans[i]=b[i];
		return ;
	}
	if(a[k]>n)
	{
		b[k]=0;
		num[0]++;
		dfs(k+1);
		num[0]--;
		return ;
	}
	for(i=0;i<=n;i++)
	{
		b[k]=i;
		num[i]++;
		if(check(k))dfs(k+1);
		num[i]--;
	}
}
int main()
{
	while(~scanf("%d",&n))
	{
		int i;
		for(i=1;i<=n;i++)scanf("%d",&a[i]);
		memset(num,0,sizeof(num));
		flag=0;
		dfs(1);
		if(flag)
			for(i=1;i<=n;i++)printf("%d%c",ans[i],i==n?'\n':' ');
		else printf("do not exist\n");
	}
	return 0;
}
