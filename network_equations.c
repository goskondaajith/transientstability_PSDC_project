#include<stdio.h>
#include<stdlib.h>
#include"header.h"
#include<complex.h>
#include<math.h>
void network_eqns(complex **y_bus_inver, struct state_variables *state_variables_data,struct gen_data *gen_dataset,int no_gens, int no_buses)
{

    for(int i=0; i<no_gens;i++)
    {
        state_variables_data[i].Ig =((state_variables_data[i].eq__old+(state_variables_data[i].ed__old+state_variables_data[i].edc__old)*I)/(gen_dataset[i].ra+gen_dataset[i].xd__*I))*cexp(I*state_variables_data[i].del_old);
        state_variables_data[i].IQ = creal(state_variables_data[i].Ig);
        state_variables_data[i].ID = cimag(state_variables_data[i].Ig);
        state_variables_data[i].Vt = 0+0*I;
        state_variables_data[i].vt = 0+0*I;
    }
    for(int i=0; i<no_gens;i++)
    {
        for(int j=0;j<no_gens;j++)
        {
            state_variables_data[i].Vt = state_variables_data[i].Vt + (y_bus_inver[i][j]*state_variables_data[j].Ig);
        }
        state_variables_data[i].VQ = creal(state_variables_data[i].Vt);
        state_variables_data[i].VD = cimag(state_variables_data[i].Vt);
        state_variables_data[i].vt = (state_variables_data[i].Vt)/cexp(I*state_variables_data[i].del_old);
        state_variables_data[i].vq = creal(state_variables_data[i].vt);
        state_variables_data[i].vd = cimag(state_variables_data[i].vt);
        state_variables_data[i].Vtmag = cabs(state_variables_data[i].Vt);
        state_variables_data[i].vtmag = cabs(state_variables_data[i].vt);
        state_variables_data[i].iq = (((state_variables_data[i].eq__old-state_variables_data[i].vq)*gen_dataset[i].ra)+((state_variables_data[i].edc__old+state_variables_data[i].ed__old-state_variables_data[i].vd)*gen_dataset[i].xd__))/((gen_dataset[i].ra*gen_dataset[i].ra)+(gen_dataset[i].xd__*gen_dataset[i].xd__));
        state_variables_data[i].id = (((state_variables_data[i].edc__old+state_variables_data[i].ed__old-state_variables_data[i].vd)*gen_dataset[i].ra)-((state_variables_data[i].eq__old-state_variables_data[i].vq)*gen_dataset[i].xd__))/((gen_dataset[i].ra*gen_dataset[i].ra)+(gen_dataset[i].xd__*gen_dataset[i].xd__));

    }
}
