#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cmath>

#define rep(i, l, r) for(int i=l; i<=r; i++)
#define dow(i, l, r) for(int i=l; i>=r; i--)
#define clr(x, c) memset(x, c, sizeof(x))
#define travel(x) for(edge *p=fir[x]; p; p=p->n)
#define all(x) (x).begin,(x).end
#define pb push_back
#define fi first
#define se second
#define l(x) Left[x]
#define r(x) Right[x]
#define lowbit(x) (x&-x)

using namespace std;

typedef long long ll;
typedef pair<int,int> Pii;
typedef pair<ll,int> Pli;
typedef long double ld;
typedef unsigned long long ull;

#define maxn 3009

int id, content_num[maxn][11]; double rating[maxn][11], vol[maxn][11], score[maxn][11];
int Rank[maxn]; double new_rating[maxn], new_vol[maxn];
char name[maxn][20];


double erf_1(double x)
{
	double l=-1e10, r=1e10;
	rep(i, 1, 100)
		if (erf((l+r)/2)<=x) l=(l+r)/2; else r=(l+r)/2;
    return (l+r)/2;
}
double phi(double x) {return sqrt(2)*erf_1(2*x-1);}

struct node{double x; int y;} q[maxn];
bool cmp(node a, node b){return a.x>b.x;}

int main()
{	
	printf("Exam: "); char a0[20]="exam\\"; scanf("%s", a0+5);
	
	printf("OldRating: "); char a1[20]="rating\\"; scanf("%s", a1+7);
	
	printf("NewRating: "); char a2[20]="rating\\"; scanf("%s", a2+7);
	
	freopen(a1, "r", stdin);
	
	while (~scanf("%d", &id))
	{
		id-=30100; 
		scanf("%s", name[id]);
		rep(i, 1, 9) scanf("%lf%lf%d", &rating[id][i], &vol[id][i], &content_num[id][i]);
	}
	
	fclose(stdin); freopen(a0, "r", stdin);
	
	while (~scanf("%d%*s", &id))
	{
		id-=30100;
		rep(i, 1, 9) scanf("%lf", &score[id][i]);
	}
	
	rep(subject, 1, 9)
	{
		double ave_rating=0; int num=0;
		rep(i, 1, 2200) if (score[i][subject]>0)
			ave_rating+=rating[i][subject], q[++num]=(node){score[i][subject],i};
		sort(q+1, q+1+num, cmp);
		rep(i, 1, num) if (q[i].x!=q[i-1].x) Rank[q[i].y]=i; else Rank[q[i].y]=Rank[q[i-1].y];
		ave_rating/=num;
		double CF0=0, CF1=0;
		rep(i, 1, 2200) if (score[i][subject]>0) 
			CF0+=pow(vol[i][subject],2), CF1+=pow(rating[i][subject]-ave_rating,2);
		double CF=sqrt(CF0/num+CF1/(num-1));
		rep(i, 1, 2200) if (score[i][subject]>0) 
		{
			double Erank = 0.5; 
			rep(j, 1, 2200) if (score[j][subject]>0)
				Erank += 0.5*(erf((rating[j][subject]-rating[i][subject])/sqrt(2*pow(vol[i][subject],2)+2*pow(vol[j][subject],2)+1e-8))+1);
			double Epref = -phi((Erank-0.5)/num);
			double Apref = -phi((Rank[i]-0.5)/num);
			double PerfAs = rating[i][subject]+CF*(Apref-Epref);
			double Weight = 1/(1-(0.42/(content_num[i][subject]+1)+0.18))-1;
			if (rating[i][subject]>=2600) Weight *= 0.8; else if (rating[i][subject]>=2000) Weight *= 0.9;
			double Cap = 150+1500.0/(content_num[i][subject]+2);
			new_rating[i] = (rating[i][subject]+Weight*PerfAs)/(1+Weight);
			new_rating[i] = min(new_rating[i], rating[i][subject]+Cap);
			new_rating[i] = max(new_rating[i], rating[i][subject]-Cap);
			new_vol[i] = sqrt(pow(new_rating[i]-rating[i][subject],2)/Weight + pow(vol[i][subject],2)/(Weight+1));
		}
		rep(i, 1, 2200) if (score[i][subject]>0) 
			rating[i][subject]=new_rating[i], vol[i][subject]=new_vol[i], content_num[i][subject]++;
	}
	
	fclose(stdin);
	
	freopen(a2, "w", stdout);
	
	rep(i, 1, 2200) if (strlen(name[i]))
	{
		printf("%d %s", i+30100, name[i]);
		rep(j, 1, 9) printf(" %.4lf %.4lf %d", rating[i][j], vol[i][j], content_num[i][j]);
		puts("");
	}
	
	fclose(stdout);
	
	return 0;
}