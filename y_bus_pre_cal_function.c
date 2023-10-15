#include<stdio.h>
#include<stdlib.h>
#include"header.h"
#include<complex.h>
#include<math.h>

void y_bus_pre_calculation(struct bus_lf_data *bus_lf_dataset,struct xline_data *xline_dataset,struct xmer_data *xmer_dataset,struct shunt_data *shunt_dataset,struct gen_data *gen_dataset,int no_buses,int no_xlines,int no_xmers,int no_shunts,int no_gens,complex **y_bus_pre)
{
  for(int i=0; i<no_xlines; i++)  // for transmission line
    {
        y_bus_pre[xline_dataset[i].from_bus-1][xline_dataset[i].to_bus-1] = y_bus_pre[xline_dataset[i].from_bus-1][xline_dataset[i].to_bus-1] - (1/xline_dataset[i].impedance);
        y_bus_pre[xline_dataset[i].to_bus-1][xline_dataset[i].from_bus-1] = y_bus_pre[xline_dataset[i].to_bus-1][xline_dataset[i].from_bus-1] - (1/xline_dataset[i].impedance);
        y_bus_pre[xline_dataset[i].from_bus-1][xline_dataset[i].from_bus-1] = y_bus_pre[xline_dataset[i].from_bus-1][xline_dataset[i].from_bus-1] + (0+xline_dataset[i].susceptance*I) + (1/xline_dataset[i].impedance);
        y_bus_pre[xline_dataset[i].to_bus-1][xline_dataset[i].to_bus-1] = y_bus_pre[xline_dataset[i].to_bus-1][xline_dataset[i].to_bus-1] + (0+xline_dataset[i].susceptance*I) + (1/xline_dataset[i].impedance);

    }
     for(int i=0; i<no_xmers; i++) // for transformer
    {
         y_bus_pre[xmer_dataset[i].from_bus-1][xmer_dataset[i].to_bus-1] = y_bus_pre[xmer_dataset[i].from_bus-1][xmer_dataset[i].to_bus-1] - (1/(xmer_dataset[i].impedance*xmer_dataset[i].tap));
        y_bus_pre[xmer_dataset[i].to_bus-1][xmer_dataset[i].from_bus-1] = y_bus_pre[xmer_dataset[i].to_bus-1][xmer_dataset[i].from_bus-1] - (1/(xmer_dataset[i].impedance*xmer_dataset[i].tap));
        y_bus_pre[xmer_dataset[i].from_bus-1][xmer_dataset[i].from_bus-1] = y_bus_pre[xmer_dataset[i].from_bus-1][xmer_dataset[i].from_bus-1] + (1/((xmer_dataset[i].impedance)*(xmer_dataset[i].tap*xmer_dataset[i].tap)));
        y_bus_pre[xmer_dataset[i].to_bus-1][xmer_dataset[i].to_bus-1] = y_bus_pre[xmer_dataset[i].to_bus-1][xmer_dataset[i].to_bus-1] + (1/xmer_dataset[i].impedance);
    }
    for(int i=0; i<no_shunts; i++) // for shunt
    {
        y_bus_pre[shunt_dataset[i].at_bus-1][shunt_dataset[i].at_bus-1] = y_bus_pre[shunt_dataset[i].at_bus-1][shunt_dataset[i].at_bus-1] + (1/shunt_dataset[i].impedance);
    }
    for(int i=0; i<no_gens; i++) // for generator
    {
        y_bus_pre[gen_dataset[i].gen_bus_no-1][gen_dataset[i].gen_bus_no-1] = y_bus_pre[gen_dataset[i].gen_bus_no-1][gen_dataset[i].gen_bus_no-1] + (1/gen_dataset[i].gen_impedence);
    }

    for(int i=0; i<no_buses; i++) //for load
    {
        if(bus_lf_dataset[i].pload != 0)
        {
            complex power_conj_load;
            power_conj_load = bus_lf_dataset[i].pload + (-1*bus_lf_dataset[i].qload)*I;
            y_bus_pre[bus_lf_dataset[i].bus_no-1][bus_lf_dataset[i].bus_no-1] =  y_bus_pre[bus_lf_dataset[i].bus_no-1][bus_lf_dataset[i].bus_no-1]+(power_conj_load/(bus_lf_dataset[i].voltage_mag*bus_lf_dataset[i].voltage_mag));

        }
    }
}
