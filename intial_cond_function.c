#include<stdio.h>
#include<stdlib.h>
#include"header.h"
#include<complex.h>
#include<math.h>
#define PI 3.141592653589793238

void initial_condition(struct bus_lf_data *bus_lf_dataset,struct gen_data *gen_dataset,struct initial_cond_data *initial_cond_dataset,complex **y_bus_pre,int no_buses,int no_gens)
{
for(int i_loop=0;i_loop<no_buses;i_loop++)
    {
        for(int i_loop2=0;i_loop2<no_gens;i_loop2++)
        {
             if((bus_lf_dataset[i_loop].bus_no == gen_dataset[i_loop2].gen_bus_no))
             {
                 complex v_inv;
                 complex s_inv;
                 complex e_jdel;
                 v_inv = (bus_lf_dataset[i_loop].voltage_mag*cos(bus_lf_dataset[i_loop].voltage_ang*PI/180))-(bus_lf_dataset[i_loop].voltage_mag*sin(bus_lf_dataset[i_loop].voltage_ang*PI/180))*I;
                 initial_cond_dataset[i_loop2].Vt0 = conj(v_inv);
                 initial_cond_dataset[i_loop2].Vt0mag = cabs(initial_cond_dataset[i_loop2].Vt0);
                 s_inv = (bus_lf_dataset[i_loop].pgen)-(bus_lf_dataset[i_loop].qgen)*I;
                 initial_cond_dataset[i_loop2].i_gen = s_inv/v_inv;
                 initial_cond_dataset[i_loop2].e_gen = initial_cond_dataset[i_loop2].Vt0+(gen_dataset[i_loop2].ra+gen_dataset[i_loop2].xq*I)*initial_cond_dataset[i_loop2].i_gen;
                 initial_cond_dataset[i_loop2].del0 = carg(initial_cond_dataset[i_loop2].e_gen);
                 e_jdel = cos(initial_cond_dataset[i_loop2].del0)-sin(initial_cond_dataset[i_loop2].del0)*I;
                 initial_cond_dataset[i_loop2].e_gen_park = initial_cond_dataset[i_loop2].e_gen*e_jdel;
                 initial_cond_dataset[i_loop2].i_gen_park = initial_cond_dataset[i_loop2].i_gen*e_jdel;
                 initial_cond_dataset[i_loop2].iq0 = (cabs(initial_cond_dataset[i_loop2].i_gen_park)*cos(carg(initial_cond_dataset[i_loop2].i_gen_park)));
                 initial_cond_dataset[i_loop2].id0 = (cabs(initial_cond_dataset[i_loop2].i_gen_park)*sin(carg(initial_cond_dataset[i_loop2].i_gen_park)));
                 initial_cond_dataset[i_loop2].efd0 = cabs(initial_cond_dataset[i_loop2].e_gen)-((gen_dataset[i_loop2].xd-gen_dataset[i_loop2].xq)*initial_cond_dataset[i_loop2].id0);
                 if(initial_cond_dataset[i_loop2].efd0 >= gen_dataset[i_loop2].efd_max)
                 {
                     initial_cond_dataset[i_loop2].efd0 = gen_dataset[i_loop2].efd_max;
                 }
                 if(initial_cond_dataset[i_loop2].efd0 <= gen_dataset[i_loop2].efd_min)
                 {
                     initial_cond_dataset[i_loop2].efd0 = gen_dataset[i_loop2].efd_min;
                 }
                 initial_cond_dataset[i_loop2].v_ref = ((initial_cond_dataset[i_loop2].efd0)/gen_dataset[i_loop2].ka)+bus_lf_dataset[i_loop].voltage_mag;
                 initial_cond_dataset[i_loop2].eq_0 = (gen_dataset[i_loop2].xd-gen_dataset[i_loop2].xd_)*initial_cond_dataset[i_loop2].id0+initial_cond_dataset[i_loop2].efd0;
                 initial_cond_dataset[i_loop2].ed_0 = (-1)*(gen_dataset[i_loop2].xq-gen_dataset[i_loop2].xq_)*initial_cond_dataset[i_loop2].iq0;
                 initial_cond_dataset[i_loop2].eq__0 = initial_cond_dataset[i_loop2].eq_0 + ((gen_dataset[i_loop2].xd_-gen_dataset[i_loop2].xd__)*initial_cond_dataset[i_loop2].id0);
                 initial_cond_dataset[i_loop2].ed__0 = initial_cond_dataset[i_loop2].ed_0 - ((gen_dataset[i_loop2].xq_-gen_dataset[i_loop2].xq__)*initial_cond_dataset[i_loop2].iq0);
                 initial_cond_dataset[i_loop2].tm0 = (initial_cond_dataset[i_loop2].eq__0*initial_cond_dataset[i_loop2].iq0)+(initial_cond_dataset[i_loop2].ed__0*initial_cond_dataset[i_loop2].id0)+((gen_dataset[i_loop2].xd__-gen_dataset[i_loop2].xq__)*initial_cond_dataset[i_loop2].id0*initial_cond_dataset[i_loop2].iq0);
                 initial_cond_dataset[i_loop2].te0 = initial_cond_dataset[i_loop2].tm0;
                 initial_cond_dataset[i_loop2].sm0 = 0;
                 initial_cond_dataset[i_loop2].edc0 = ((gen_dataset[i_loop2].xd__-gen_dataset[i_loop2].xq__)*initial_cond_dataset[i_loop2].iq0);


        }
        }

        }

}
