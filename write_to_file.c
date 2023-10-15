#include<stdio.h>
#include<stdlib.h>
#include"header.h"
#include<complex.h>
#include<math.h>
void y_bus_to_file(complex **y_bus_pre, int no_buses)
{
    FILE *fptr_write;
    fptr_write=fopen("y_bus_pre.txt","w");
    if(fptr_write==NULL)
    {
        printf("\nError opening file");
        exit(1);
    }

    fprintf(fptr_write,"the prefault Y-bus is: \n");

    for(int iloop_1=0; iloop_1<no_buses; iloop_1++)
    {
        for(int iloop_2=0; iloop_2<no_buses; iloop_2++)
        {

            fprintf(fptr_write,"%lf%+lfi\t ",creal(y_bus_pre[iloop_1][iloop_2]),cimag(y_bus_pre[iloop_1][iloop_2]));
        }

        fprintf(fptr_write,"\n\n");
    }
    fclose(fptr_write);
}

void initial_to_file(struct initial_cond_data *initial_cond_dataset, int no_gens)
{
    FILE *fptr_write2;
    fptr_write2=fopen("initial_conditions.txt","w");
    if(fptr_write2==NULL)
    {
        printf("\nError opening file");
        exit(1);
    }

    fprintf(fptr_write2,"the initial conditions are: \n");
    fprintf(fptr_write2,"gen no\tdel0\t     Id0\t Iq0\t   Efd0\t Eq'0\t    Ed'0\t Eq''0\t Ed''0\t Smo\t    Te0\t Tmo\t     Edc\t       Vref\t     Vtmag\n ");
    for(int iloop_3=0; iloop_3<no_gens; iloop_3++)
    {
        fprintf(fptr_write2,"%d\t\t",iloop_3+1);
        fprintf(fptr_write2,"%lf\t",initial_cond_dataset[iloop_3].del0);
        fprintf(fptr_write2,"   %lf\t",initial_cond_dataset[iloop_3].id0);
        fprintf(fptr_write2,"%lf\t   ",initial_cond_dataset[iloop_3].iq0);
        fprintf(fptr_write2,"%lf\t ",initial_cond_dataset[iloop_3].efd0);
        fprintf(fptr_write2,"%lf\t  ",initial_cond_dataset[iloop_3].eq_0);
        fprintf(fptr_write2," %lf\t",initial_cond_dataset[iloop_3].ed_0);
        fprintf(fptr_write2," %lf\t      ",initial_cond_dataset[iloop_3].eq__0);
        fprintf(fptr_write2," %lf\t",initial_cond_dataset[iloop_3].ed__0);
        fprintf(fptr_write2,"%lf\t ",initial_cond_dataset[iloop_3].sm0);
        fprintf(fptr_write2," %lf\t",initial_cond_dataset[iloop_3].te0);
        fprintf(fptr_write2," %lf\t   ",initial_cond_dataset[iloop_3].tm0);
        fprintf(fptr_write2," %lf\t      ",initial_cond_dataset[iloop_3].edc0);
        fprintf(fptr_write2," %lf\t",initial_cond_dataset[iloop_3].v_ref);
        fprintf(fptr_write2,"    %lf\t",initial_cond_dataset[iloop_3].Vt0mag);

        fprintf(fptr_write2,"\n\n ");

    }
fclose(fptr_write2);
    }
