
// Owaineur version 1.1.0

// Source code

// Released into the public domain under CC0

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int akt,rnd,i,j,k,l,tm,s_m_n;
double aa[12],bb[12],cc[12],wg[3][144],hna[12],hnb[12],bs[3][12],lr;
double m_wg[3][3][144],m_bs[3][3][12];
double na,nb;
char sym;

void nf() {
	double ta = 0;
	int twg = 0;
	for (j = 0; j < 12; j++) {
		bb[j] = 0;
		hna[j] = 0;
		hnb[j] = 0;
	}
	for (j = 0; j < 12; j++) {
		ta = 0;
		for (k = 0; k < 12; k++) {
			ta += aa[k] * wg[0][twg];
			twg++;
		}
		hna[j] = tanh(ta + bs[0][j]);
	}
	twg = 0,ta = 0;
	for (j = 0; j < 12; j++) {
		ta = 0;
		for (k = 0; k < 12; k++) {
			ta += hna[k] * wg[1][twg];
			twg++;
		}
		hnb[j] =  tanh(ta + bs[1][j]);
	}
	twg = 0,ta = 0;
	for (j = 0; j < 12; j++) {
		ta = 0;
		for (k = 0; k < 12; k++) {
			ta += hnb[k] * wg[2][twg];
			twg++;
		}
		bb[j] =  tanh(ta + bs[2][j]);
	}
}

void nm() {
	double er,era,erb[12],sm = 0,ps,psa,o_wg[3][144];
	int twga = 0,twgb = 0,twgc = 0;
	for (j = 0; j < 3; j++) {
		for (k = 0; k < 144; k++) {
			o_wg[j][k] = wg[j][k];
		}
	}
	for (j = 0; j < 12; j++) {
		ps = 1 - (bb[j] * bb[j]);
		er = (cc[j] - bb[j]) * ps;
		for (k = 0; k < 12; k++) {
			wg[2][twga] += lr * er * hnb[k];
			wg[2][twga] += na + ((double)rand() / RAND_MAX) * (nb - na);
			twga++;
		}
		bs[2][j] += lr * er;
	}
	for (j = 0; j < 12; j++) {
		sm = 0;
		ps = 1 - (hnb[j] * hnb[j]);
		twga = twgc;
		for (k = 0; k < 12; k++) {
			psa = 1 - (bb[k] * bb[k]);
			er = (cc[k] - bb[k]) * psa;
			sm += er * o_wg[2][twga];
			twga+=12;
		}
		era = sm * ps;
		for (k = 0; k < 12; k++) {
			wg[1][twgb] += lr * era * hna[k];
			wg[1][twgb] += na + ((double)rand() / RAND_MAX) * (nb - na);
			twgb++;
		}
		bs[1][j] += lr * era;
		erb[j] = era;
		twgc++;
	}
	twgc = 0;
	twgb = 0;
	for (j = 0; j < 12; j++) {
		sm = 0;
		ps = 1 - (hna[j] * hna[j]);
		twga = twgc;
		for (k = 0; k < 12; k++) {
			sm += erb[k] * o_wg[1][twga];
			twga+=12;
		}
		era = sm * ps;
		for (k = 0; k < 12; k++) {
			wg[0][twgb] += lr * era * aa[k];
			wg[0][twgb] += na + ((double)rand() / RAND_MAX) * (nb - na);
			twgb++;
		}
		bs[0][j] += lr * era;
		twgc++;
	}
}

void s_m() {
	s_m_n = 0;
	printf("\nSlot:");
	scanf("%d",&s_m_n);
	s_m_n -= 1;
	if (s_m_n < 0) s_m_n = 0;
	if (s_m_n > 2) s_m_n = 2;
}

int main()
{
	printf("\nPUBLIC DOMAIN SOFTWARE");
	printf("\nOwaineur");
	printf("\nVersion 1.1.0\n");
	srand(time(NULL));
	int num;
	printf("\nR/S?");
	scanf(" %c",&sym);
	if (sym == 'r') {
		for (i = 0; i < 3; i++) {
			for (j = 0; j < 12; j++) {
				na = 0 - 0.5,nb = 0.5;
				bs[i][j] = na + ((double)rand() / RAND_MAX) * (nb - na);
			}
			for (j = 0; j < 144; j++) {
				na = 0 - 0.5,nb = 0.5;
				wg[i][j] = na + ((double)rand() / RAND_MAX) * (nb - na);
			}
		}
	}
	if (sym == 's') {
		num = 1;
		for (i = 0; i < 3; i++) {
			for (j = 0; j < 12; j++) {
				printf("\nBias %d:",num);
				scanf("%lf",&bs[i][j]);
				num++;
			}
		}
		num = 1;
		for (i = 0; i < 3; i++) {
			for (j = 0; j < 144; j++) {
				printf("\nWG %d:",num);
				scanf("%lf",&wg[i][j]);
				num++;
			}
		}
	}
	for (k = 0; k < 3; k++) {
		for (i = 0; i < 3; i++) {
			for (j = 0; j < 12; j++) {
				m_bs[k][i][j] = 0;
			}
			for (j = 0; j < 144; j++) {
				m_wg[k][i][j] = 0;
			}
		}
	}
	akt = 1;
	na = 0 - 0.000001,nb = 0.000001;
	do
	{
		for (i = 0; i < 12; i++) {
			printf("\nI %d:",i+1);
			scanf("%lf",&aa[i]);
		}
		for (i = 0; i < 12; i++) {
			printf("\nT %d:",i+1);
			scanf("%lf",&cc[i]);
		}
		printf("\nTime:");
		scanf("%d",&tm);
		printf("\nLR:");
		scanf("%lf",&lr);
		for (i = 0; i < tm; i++) {
			nf();
			nm();
		}
		nf();
		for (i = 0; i < 12; i++)
			printf("\nO %d: %lf",i+1,bb[i]);
		printf("\n ");
		scanf(" %c",&sym);
		if (sym == 'i') {
			num = 1;
			for (i = 0; i < 3; i++) {
				for (j = 0; j < 144; j++) {
					printf("\nWG %d: %lf",num,wg[i][j]);
					num++;
				}
			}
			num = 1;
			for (i = 0; i < 3; i++) {
				for (j = 0; j < 12; j++) {
					printf("\nBias %d: %lf",num,bs[i][j]);
					num++;
				}
			}
		}
		if (sym == 'm') {
			s_m();
			for (i = 0; i < 3; i++) {
				for (j = 0; j < 12; j++) {
					bs[i][j] = m_bs[s_m_n][i][j];
				}
			}
			for (i = 0; i < 3; i++) {
				for (j = 0; j < 144; j++) {
					wg[i][j] = m_wg[s_m_n][i][j];
				}
			}
			printf("\nOK");
		}
		if (sym == 's') {
			s_m();
			for (i = 0; i < 3; i++) {
				for (j = 0; j < 12; j++) {
					m_bs[s_m_n][i][j] = bs[i][j];
				}
			}
			for (i = 0; i < 3; i++) {
				for (j = 0; j < 144; j++) {
					m_wg[s_m_n][i][j] = wg[i][j];
				}
			}
			printf("\nOK");
		}
		if (sym == 'x') akt = 0;
	}
	while (akt == 1);
	printf("\nOk");
	return 0;
}
