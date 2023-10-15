#include<stdio.h>
#include<stdlib.h>
#include"header.h"
#include<math.h>
void data_storage(FILE  *fdata_read,struct bus_lf_data *bus_lf_dataset,struct xline_data *xline_dataset,struct xmer_data *xmer_dataset,struct shunt_data *shunt_dataset,struct gen_data *gen_dataset,int no_buses,int no_xlines,int no_xmers,int no_shunts,int no_gens)
{
    for(int i_loop=0; i_loop<no_buses; i_loop++)    // Storing the data from file into array of structures
    {
        fscanf(fdata_read,"%d",&bus_lf_dataset[i_loop].bus_no);
        fscanf(fdata_read,"%d",&bus_lf_dataset[i_loop].v_rated);
        fscanf(fdata_read,"%f",&bus_lf_dataset[i_loop].voltage_mag);
        fscanf(fdata_read,"%f",&bus_lf_dataset[i_loop].voltage_ang);
        bus_lf_dataset[i_loop].voltage = (bus_lf_dataset[i_loop].voltage_mag*cos(bus_lf_dataset[i_loop].voltage_ang*3.14/180))+(bus_lf_dataset[i_loop].voltage_mag*sin(bus_lf_dataset[i_loop].voltage_ang*3.14/180))*I;
        fscanf(fdata_read,"%f",&bus_lf_dataset[i_loop].pgen);
        fscanf(fdata_read,"%f",&bus_lf_dataset[i_loop].qgen);
        fscanf(fdata_read,"%f",&bus_lf_dataset[i_loop].pload);
        fscanf(fdata_read,"%f",&bus_lf_dataset[i_loop].qload);
    }
    for(int i_loop=0; i_loop<no_xlines; i_loop++)    // Storing the data from file into array of structures
    {
        float resistance1,reactance1;
        fscanf(fdata_read,"%d",&xline_dataset[i_loop].from_bus);
        fscanf(fdata_read,"%d",&xline_dataset[i_loop].to_bus);
        fscanf(fdata_read,"%f",&resistance1);
        fscanf(fdata_read,"%f",&reactance1);
        xline_dataset[i_loop].impedance=resistance1+reactance1*I;
        fscanf(fdata_read,"%f",&xline_dataset[i_loop].susceptance);
    }
    for(int i_loop=0; i_loop<no_xmers; i_loop++)    // Storing the data from file into array of structures
    {
        float resistance2,reactance2;
        fscanf(fdata_read,"%d",&xmer_dataset[i_loop].from_bus);
        fscanf(fdata_read,"%d",&xmer_dataset[i_loop].to_bus);
        fscanf(fdata_read,"%f",&resistance2);
        fscanf(fdata_read,"%f",&reactance2);
        xmer_dataset[i_loop].impedance=resistance2+reactance2*I;
        fscanf(fdata_read,"%f",&xmer_dataset[i_loop].tap);
        fscanf(fdata_read,"%f",&xmer_dataset[i_loop].tap_angle);
    }
    for(int i_loop=0; i_loop<no_shunts; i_loop++)    // Storing the data from file into array of structures
    {
        float resistance3,reactance3;
        fscanf(fdata_read,"%d",&shunt_dataset[i_loop].at_bus);
        fscanf(fdata_read,"%f",&resistance3);
        fscanf(fdata_read,"%f",&reactance3);
        shunt_dataset[i_loop].impedance=resistance3+reactance3*I;
    }
    for(int i_loop=0; i_loop<no_gens; i_loop++)    // Storing the data from file into array of structures
    {
        float resistance,reactance;
        fscanf(fdata_read,"%d",&gen_dataset[i_loop].gen_bus_no);
        fscanf(fdata_read,"%f",&gen_dataset[i_loop].inertia_const);
        fscanf(fdata_read,"%f",&gen_dataset[i_loop].d);
        fscanf(fdata_read,"%f",&gen_dataset[i_loop].ra);
        fscanf(fdata_read,"%f",&gen_dataset[i_loop].xd);
        fscanf(fdata_read,"%f",&gen_dataset[i_loop].xd_);
        fscanf(fdata_read,"%f",&gen_dataset[i_loop].xd__);
        fscanf(fdata_read,"%f",&gen_dataset[i_loop].xq);
        fscanf(fdata_read,"%f",&gen_dataset[i_loop].xq_);
        fscanf(fdata_read,"%f",&gen_dataset[i_loop].xq__);
        fscanf(fdata_read,"%f",&gen_dataset[i_loop].td0_);
        fscanf(fdata_read,"%f",&gen_dataset[i_loop].tq0_);
        fscanf(fdata_read,"%f",&gen_dataset[i_loop].td0__);
        fscanf(fdata_read,"%f",&gen_dataset[i_loop].tq0__);
        fscanf(fdata_read,"%f",&gen_dataset[i_loop].tc);
        fscanf(fdata_read,"%f",&gen_dataset[i_loop].ka);
        fscanf(fdata_read,"%f",&gen_dataset[i_loop].ta);
        fscanf(fdata_read,"%f",&gen_dataset[i_loop].efd_max);
        fscanf(fdata_read,"%f",&gen_dataset[i_loop].efd_min);
        resistance = gen_dataset[i_loop].ra;
        reactance = gen_dataset[i_loop].xd__;
        gen_dataset[i_loop].gen_impedence =resistance+reactance*I;
        //printf("%f+i(%f) ",creal(gen_dataset[i_loop].gen_impedence),cimag(gen_dataset[i_loop].gen_impedence));
    }

    fclose(fdata_read);
}


