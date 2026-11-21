
// Owaineur version 1.4.0

// Source code

// Released into the public domain under CC0

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int akt,rnd,i,j,k,l,tm,s_m_n;
double aa[16],bb[16],cc[16],wga[2][384],wgb[2][576],hna[24],hnb[24],hnc[24],bsa[3][24],bsb[16],lr,rndns;
double m_wga[8][2][384],m_wgb[8][2][576],m_bsa[8][3][24],m_bsb[8][16];
double na,nb;
char sym;

void nf() {
	double ta = 0;
	int twg = 0;
	for (j = 0; j < 16; j++) bb[j] = 0;
	for (j = 0; j < 24; j++) {
		hna[j] = 0;
		hnb[j] = 0;
		hnc[j] = 0;
	}
	for (j = 0; j < 24; j++) {
		ta = 0;
		for (k = 0; k < 16; k++) {
			ta += aa[k] * wga[0][twg];
			twg++;
		}
		hna[j] = tanh(ta + bsa[0][j]);
	}
	twg = 0;
	for (j = 0; j < 24; j++) {
		ta = 0;
		for (k = 0; k < 24; k++) {
			ta += hna[k] * wgb[0][twg];
			twg++;
		}
		hnb[j] =  tanh(ta + bsa[1][j]);
	}
	twg = 0;
	for (j = 0; j < 24; j++) {
		ta = 0;
		for (k = 0; k < 24; k++) {
			ta += hnb[k] * wgb[1][twg];
			twg++;
		}
		hnc[j] =  tanh(ta + bsa[2][j]);
	}
	twg = 0;
	for (j = 0; j < 16; j++) {
		ta = 0;
		for (k = 0; k < 24; k++) {
			ta += hnc[k] * wga[1][twg];
			twg++;
		}
		bb[j] =  tanh(ta + bsb[j]);
	}
}

void nm() {
	double er,era[16],erb[24],erc[24],sm = 0,ps,o_wga[2][384],o_wgb[2][576];
	int twga = 0,twgb = 0,twgc = 0;
	for (j = 0; j < 2; j++) {
		for (k = 0; k < 384; k++) {
			o_wga[j][k] = wga[j][k];
		}
		for (k = 0; k < 576; k++) {
			o_wgb[j][k] = wgb[j][k];
		}
	}
	for (j = 0; j < 16; j++) {
		ps = 1 - (bb[j] * bb[j]);
		er = (cc[j] - bb[j]) * ps;
		for (k = 0; k < 24; k++) {
			wga[1][twga] += lr * er * hnc[k];
			if (rndns > 0) wga[1][twga] += na + ((double)rand() / RAND_MAX) * (nb - na);
			twga++;
		}
		bsb[j] += lr * er;
		era[j] = er;
	}
	for (j = 0; j < 24; j++) {
		sm = 0;
		ps = 1 - (hnc[j] * hnc[j]);
		twga = twgc;
		for (k = 0; k < 16; k++) {
			sm += era[k] * o_wga[1][twga];
			twga+=24;
		}
		er = sm * ps;
		for (k = 0; k < 24; k++) {
			wgb[1][twgb] += lr * er * hnb[k];
			if (rndns > 0) wgb[1][twgb] += na + ((double)rand() / RAND_MAX) * (nb - na);
			twgb++;
		}
		bsa[2][j] += lr * er;
		erb[j] = er;
		twgc++;
	}
	twgc = 0;
	twgb = 0;
	for (j = 0; j < 24; j++) {
		sm = 0;
		ps = 1 - (hnb[j] * hnb[j]);
		twga = twgc;
		for (k = 0; k < 24; k++) {
			sm += erb[k] * o_wgb[1][twga];
			twga+=24;
		}
		er = sm * ps;
		for (k = 0; k < 24; k++) {
			wgb[0][twgb] += lr * er * hna[k];
			if (rndns > 0) wgb[0][twgb] += na + ((double)rand() / RAND_MAX) * (nb - na);
			twgb++;
		}
		bsa[1][j] += lr * er;
		erc[j] = er;
		twgc++;
	}
	twgc = 0;
	twgb = 0;
	for (j = 0; j < 24; j++) {
		sm = 0;
		ps = 1 - (hna[j] * hna[j]);
		twga = twgc;
		for (k = 0; k < 24; k++) {
			sm += erc[k] * o_wgb[0][twga];
			twga+=24;
		}
		er = sm * ps;
		for (k = 0; k < 16; k++) {
			wga[0][twgb] += lr * er * aa[k];
			if (rndns > 0) wga[0][twgb] += na + ((double)rand() / RAND_MAX) * (nb - na);
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
	if (s_m_n > 7) s_m_n = 7;
}

int main()
{
	printf("\nPUBLIC DOMAIN SOFTWARE");
	printf("\nOwaineur");
	printf("\nVersion 1.4.0\n");
	srand(time(NULL));
	int num;
	printf("\nR/S?");
	scanf(" %c",&sym);
	if (sym == 'r') {
		for (i = 0; i < 3; i++) {
			for (j = 0; j < 24; j++) {
				na = 0 - 0.5,nb = 0.5;
				bsa[i][j] = na + ((double)rand() / RAND_MAX) * (nb - na);
			}
		}
		for (i = 0; i < 2; i++) {
			for (j = 0; j < 384; j++) {
				na = 0 - 0.5,nb = 0.5;
				wga[i][j] = na + ((double)rand() / RAND_MAX) * (nb - na);
			}
			for (j = 0; j < 576; j++) {
				na = 0 - 0.5,nb = 0.5;
				wgb[i][j] = na + ((double)rand() / RAND_MAX) * (nb - na);
			}
		}
		for (j = 0; j < 16; j++) {
			na = 0 - 0.5,nb = 0.5;
			bsb[j] = na + ((double)rand() / RAND_MAX) * (nb - na);
		}
	}
	if (sym == 's') {
		num = 1;
		for (i = 0; i < 3; i++) {
			for (j = 0; j < 24; j++) {
				printf("\nBias %d:",num);
				scanf("%lf",&bsa[i][j]);
				num++;
			}
		}
		for (j = 0; j < 16; j++) {
			printf("\nBias %d:",num);
			scanf("%lf",&bsb[j]);
			num++;
		}
		num = 1;
		for (j = 0; j < 384; j++) {
			printf("\nWG %d:",num);
			scanf("%lf",&wga[0][j]);
			num++;
		}
		for (i = 0; i < 2; i++) {
			for (j = 0; j < 576; j++) {
				printf("\nWG %d:",num);
				scanf("%lf",&wgb[i][j]);
				num++;
			}
		}
		for (j = 0; j < 384; j++) {
			printf("\nWG %d:",num);
			scanf("%lf",&wga[1][j]);
			num++;
		}
	}
	for (k = 0; k < 8; k++) {
		for (i = 0; i < 3; i++) {
			for (j = 0; j < 24; j++) {
				m_bsa[k][i][j] = 0;
			}
		}
		for (i = 0; i < 2; i++) {
			for (j = 0; j < 384; j++) {
				m_wga[k][i][j] = 0;
			}
			for (j = 0; j < 576; j++) {
				m_wgb[k][i][j] = 0;
			}
		}
		for (j = 0; j < 16; j++) {
			m_bsb[k][j] = 0;
		}
	}
	rndns = 0;
	akt = 1;
	do
	{
		for (i = 0; i < 16; i++) {
			printf("\nI %d:",i+1);
			scanf("%lf",&aa[i]);
		}
		for (i = 0; i < 16; i++) {
			printf("\nT %d:",i+1);
			scanf("%lf",&cc[i]);
		}
		printf("\nTime:");
		scanf("%d",&tm);
		printf("\nLR:");
		scanf("%lf",&lr);
		printf("\nRN:");
		scanf("%lf",&rndns);
		na = 0 - rndns,nb = rndns;
		for (i = 0; i < tm; i++) {
			nf();
			nm();
		}
		nf();
		for (i = 0; i < 16; i++)
			printf("\nO %d: %lf",i+1,bb[i]);
		printf("\n ");
		scanf(" %c",&sym);
		if (sym == 'i') {
			num = 1;
			for (j = 0; j < 384; j++) {
				printf("\nWG %d: %lf",num,wga[0][j]);
				num++;
			}
			for (i = 0; i < 2; i++) {
				for (j = 0; j < 576; j++) {
					printf("\nWG %d: %lf",num,wgb[i][j]);
					num++;
				}
			}
			for (j = 0; j < 384; j++) {
				printf("\nWG %d: %lf",num,wga[1][j]);
				num++;
			}
			num = 1;
			for (i = 0; i < 3; i++) {
				for (j = 0; j < 24; j++) {
					printf("\nBias %d: %lf",num,bsa[i][j]);
					num++;
				}
			}
			for (j = 0; j < 16; j++) {
				printf("\nBias %d: %lf",num,bsb[j]);
				num++;
			}
		}
		if (sym == 'm') {
			s_m();
			for (i = 0; i < 3; i++) {
				for (j = 0; j < 24; j++) {
					bsa[i][j] = m_bsa[s_m_n][i][j];
				}
			}
			for (j = 0; j < 16; j++) {
				bsb[j] = m_bsb[s_m_n][j];
			}
			for (i = 0; i < 2; i++) {
				for (j = 0; j < 384; j++) {
					wga[i][j] = m_wga[s_m_n][i][j];
				}
				for (j = 0; j < 576; j++) {
					wgb[i][j] = m_wgb[s_m_n][i][j];
				}
			}
			printf("\nOK");
		}
		if (sym == 's') {
			s_m();
			for (i = 0; i < 3; i++) {
				for (j = 0; j < 24; j++) {
					m_bsa[s_m_n][i][j] = bsa[i][j];
				}
			}
			for (j = 0; j < 16; j++) {
				m_bsb[s_m_n][j] = bsb[j];
			}
			for (i = 0; i < 2; i++) {
				for (j = 0; j < 384; j++) {
					m_wga[s_m_n][i][j] = wga[i][j];
				}
				for (j = 0; j < 576; j++) {
					m_wgb[s_m_n][i][j] = wgb[i][j];
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
