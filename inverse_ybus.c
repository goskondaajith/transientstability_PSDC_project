#include<stdio.h>
#include<conio.h>
#include<math.h>
#include<complex.h>
#include<stdlib.h>
#include"header.h"
#define PI 3.141592653589793238
void inv_ybus(complex **Ybus1, complex **Ybus_inv, int n_bus)
{

     complex determinant(complex **Ybus1,int k)
 {

	double s = 1;
	complex det=0+0*I;
	complex *temp_ybus[k];

    for(int iloop=0; iloop<k; iloop++)
    {
        temp_ybus[iloop]=(complex *)calloc(k,sizeof(complex));

    }

	int i, j, m, n, c;

	if (k == 1)
        {

		return (Ybus1[0][0]);

	}
	else
        {

		det = 0+0*I;

		for (c = 0; c < k; c++)
            {

			m = 0;

			n = 0;

			for (i = 0; i < k; i++)
                {

				for (j = 0; j < k; j++)
                    {

					temp_ybus[i][j] = 0;

					if (i != 0 && j != c)
                        {

						temp_ybus[m][n] = Ybus1[i][j];

						if (n < (k - 2))

						       n++;
						       else
						       {

							n = 0;

							m++;

						}

					}

				}

			}

			det = det + s * (Ybus1[0][c] * determinant(temp_ybus, k - 1));

			s = -1 * s;

		}

	}

	return (det);

}

void trans(complex **Ybus1, complex **cofact_ybus, int r)
{

	int i, j;

   complex *temp_ybus[r];

    for(int iloop=0; iloop<r; iloop++)
    {
        temp_ybus[iloop]=(complex *)calloc(r,sizeof(complex));

    }

	complex *inv_ybus[r];

    for(int iloop=0; iloop<r; iloop++)
    {
        inv_ybus[iloop]=(complex *)calloc(r,sizeof(complex));

    }


	for (i = 0; i < r; i++) {

		for (j = 0; j < r; j++) {

			temp_ybus[i][j] = cofact_ybus[j][i];

		}

	}

	complex d = determinant(Ybus1,r);

	inv_ybus[i][j] = 0;

	for (i = 0; i < r; i++) {

		for (j = 0; j < r; j++) {

			inv_ybus[i][j] = temp_ybus[i][j] / d;

		}

	}


	for (i = 0; i < r; i++) {

		for (j = 0; j < r; j++) {

			Ybus_inv[i][j]=inv_ybus[i][j];

		}

		printf("\n");

	}

}

void cofactors(complex **Ybus1,int f)
{
	complex *temp_ybus[f];

    for(int iloop=0; iloop<f; iloop++)
    {
        temp_ybus[iloop]=(complex *)calloc(f,sizeof(complex));

    }

	complex *cofact_ybus[f];

    for(int iloop=0; iloop<f; iloop++)
    {
        cofact_ybus[iloop]=(complex *)calloc(f,sizeof(complex));

    }



	int p, q, m, n, i, j;

	for (q = 0; q < f; q++) {

		for (p = 0; p < f; p++) {

			m = 0;

			n = 0;

			for (i = 0; i < f; i++) {

				for (j = 0; j < f; j++) {

					temp_ybus[i][j] = 0;

					if (i != q && j != p) {

						temp_ybus[m][n] = Ybus1[i][j];

						if (n < (f - 2))

						       n++; else {

							n = 0;

							m++;

						}

					}

				}

			}

			cofact_ybus[q][p] = pow(-1, q + p) * determinant(temp_ybus, f - 1);

		}

	}

	trans(Ybus1, cofact_ybus, f);

}


cofactors(Ybus1,n_bus);

}
