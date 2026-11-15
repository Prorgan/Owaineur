
// Owaineur version 1.2.0

// Source code

// Released into the public domain under CC0

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int akt,rnd,i,j,k,l,tm,s_m_n;
double aa[12],bb[12],cc[12],wga[2][192],wgb[256],hna[16],hnb[16],bsa[2][16],bsb[12],lr;
double m_wga[3][2][192],m_wgb[3][256],m_bsa[3][2][16],m_bsb[3][12];
double na,nb;
char sym;

void nf() {
	double ta = 0;
	int twg = 0;
	for (j = 0; j < 12; j++) bb[j] = 0;
	for (j = 0; j < 16; j++) {
		hna[j] = 0;
		hnb[j] = 0;
	}
	for (j = 0; j < 16; j++) {
		ta = 0;
		for (k = 0; k < 12; k++) {
			ta += aa[k] * wga[0][twg];
			twg++;
		}
		hna[j] = tanh(ta + bsa[0][j]);
	}
	twg = 0;
	for (j = 0; j < 16; j++) {
		ta = 0;
		for (k = 0; k < 16; k++) {
			ta += hna[k] * wgb[twg];
			twg++;
		}
		hnb[j] =  tanh(ta + bsa[1][j]);
	}
	twg = 0;
	for (j = 0; j < 12; j++) {
		ta = 0;
		for (k = 0; k < 16; k++) {
			ta += hnb[k] * wga[1][twg];
			twg++;
		}
		bb[j] =  tanh(ta + bsb[j]);
	}
}

void nm() {
	double er,era[12],erb[16],sm = 0,ps,o_wga[2][192],o_wgb[256];
	int twga = 0,twgb = 0,twgc = 0;
	for (j = 0; j < 2; j++) {
		for (k = 0; k < 192; k++) {
			o_wga[j][k] = wga[j][k];
		}
	}
	for (k = 0; k < 256; k++) {
		o_wgb[k] = wgb[k];
	}
	for (j = 0; j < 12; j++) {
		ps = 1 - (bb[j] * bb[j]);
		er = (cc[j] - bb[j]) * ps;
		for (k = 0; k < 16; k++) {
			wga[1][twga] += lr * er * hnb[k];
			wga[1][twga] += na + ((double)rand() / RAND_MAX) * (nb - na);
			twga++;
		}
		bsb[j] += lr * er;
		era[j] = er;
	}
	for (j = 0; j < 16; j++) {
		sm = 0;
		ps = 1 - (hnb[j] * hnb[j]);
		twga = twgc;
		for (k = 0; k < 12; k++) {
			sm += era[k] * o_wga[1][twga];
			twga+=16;
		}
		er = sm * ps;
		for (k = 0; k < 16; k++) {
			wgb[twgb] += lr * er * hna[k];
			wgb[twgb] += na + ((double)rand() / RAND_MAX) * (nb - na);
			twgb++;
		}
		bsa[1][j] += lr * er;
		erb[j] = er;
		twgc++;
	}
	twgc = 0;
	twgb = 0;
	for (j = 0; j < 16; j++) {
		sm = 0;
		ps = 1 - (hna[j] * hna[j]);
		twga = twgc;
		for (k = 0; k < 16; k++) {
			sm += erb[k] * o_wgb[twga];
			twga+=16;
		}
		er = sm * ps;
		for (k = 0; k < 12; k++) {
			wga[0][twgb] += lr * er * aa[k];
			wga[0][twgb] += na + ((double)rand() / RAND_MAX) * (nb - na);
			twgb++;
		}
		bsa[0][j] += lr * er;
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
	printf("\nVersion 1.2.0\n");
	srand(time(NULL));
	int num;
	printf("\nR/S?");
	scanf(" %c",&sym);
	if (sym == 'r') {
		for (i = 0; i < 2; i++) {
			for (j = 0; j < 16; j++) {
				na = 0 - 0.5,nb = 0.5;
				bsa[i][j] = na + ((double)rand() / RAND_MAX) * (nb - na);
			}
			for (j = 0; j < 192; j++) {
				na = 0 - 0.5,nb = 0.5;
				wga[i][j] = na + ((double)rand() / RAND_MAX) * (nb - na);
			}
		}
		for (j = 0; j < 12; j++) {
			na = 0 - 0.5,nb = 0.5;
			bsb[j] = na + ((double)rand() / RAND_MAX) * (nb - na);
		}
		for (j = 0; j < 256; j++) {
			na = 0 - 0.5,nb = 0.5;
			wgb[j] = na + ((double)rand() / RAND_MAX) * (nb - na);
		}
	}
	if (sym == 's') {
		num = 1;
		for (i = 0; i < 2; i++) {
			for (j = 0; j < 16; j++) {
				printf("\nBias %d:",num);
				scanf("%lf",&bsa[i][j]);
				num++;
			}
		}
		for (j = 0; j < 12; j++) {
			printf("\nBias %d:",num);
			scanf("%lf",&bsb[j]);
			num++;
		}
		num = 1;
		for (j = 0; j < 192; j++) {
			printf("\nWG %d:",num);
			scanf("%lf",&wga[0][j]);
			num++;
		}
		for (j = 0; j < 256; j++) {
			printf("\nWG %d:",num);
			scanf("%lf",&wgb[j]);
			num++;
		}
		for (j = 0; j < 192; j++) {
			printf("\nWG %d:",num);
			scanf("%lf",&wga[1][j]);
			num++;
		}
	}
	for (k = 0; k < 3; k++) {
		for (i = 0; i < 2; i++) {
			for (j = 0; j < 16; j++) {
				m_bsa[k][i][j] = 0;
			}
			for (j = 0; j < 192; j++) {
				m_wga[k][i][j] = 0;
			}
		}
		for (j = 0; j < 12; j++) {
			m_bsb[k][j] = 0;
		}
		for (j = 0; j < 256; j++) {
			m_wgb[k][j] = 0;
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
			for (j = 0; j < 192; j++) {
				printf("\nWG %d: %lf",num,wga[0][j]);
				num++;
			}
			for (j = 0; j < 256; j++) {
				printf("\nWG %d: %lf",num,wgb[j]);
				num++;
			}
			for (j = 0; j < 192; j++) {
				printf("\nWG %d: %lf",num,wga[1][j]);
				num++;
			}
			num = 1;
			for (i = 0; i < 2; i++) {
				for (j = 0; j < 16; j++) {
					printf("\nBias %d: %lf",num,bsa[i][j]);
					num++;
				}
			}
			for (j = 0; j < 12; j++) {
				printf("\nBias %d: %lf",num,bsb[j]);
				num++;
			}
		}
		if (sym == 'm') {
			s_m();
			for (i = 0; i < 2; i++) {
				for (j = 0; j < 16; j++) {
					bsa[i][j] = m_bsa[s_m_n][i][j];
				}
			}
			for (j = 0; j < 12; j++) {
				bsb[j] = m_bsb[s_m_n][j];
			}
			for (i = 0; i < 2; i++) {
				for (j = 0; j < 192; j++) {
					wga[i][j] = m_wga[s_m_n][i][j];
				}
			}
			for (j = 0; j < 256; j++) {
				wgb[j] = m_wgb[s_m_n][j];
			}
			printf("\nOK");
		}
		if (sym == 's') {
			s_m();
			for (i = 0; i < 2; i++) {
				for (j = 0; j < 16; j++) {
					m_bsa[s_m_n][i][j] = bsa[i][j];
				}
			}
			for (j = 0; j < 12; j++) {
				m_bsb[s_m_n][j] = bsb[j];
			}
			for (i = 0; i < 2; i++) {
				for (j = 0; j < 192; j++) {
					m_wga[s_m_n][i][j] = wga[i][j];
				}
			}
			for (j = 0; j < 256; j++) {
				m_wgb[s_m_n][j] = wgb[j];
			}
			printf("\nOK");
		}
		if (sym == 'x') akt = 0;
	}
	while (akt == 1);
	printf("\nOk");
	return 0;
}
