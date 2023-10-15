#include<stdio.h>
#include<stdlib.h>
#include"header.h"
#include<complex.h>
#include<math.h>
void time_sim_func(struct initial_cond_data *initial_cond_dataset,struct state_variables *state_variables_data,struct gen_data *gen_dataset, complex **y_bus_pre_inv,complex **y_bus_during_inv,complex **y_bus_post_inv,int no_gens, int no_buses, struct simulation_input sim_input,FILE *fptr2)
{

   for( double time_current = 0; time_current<sim_input.sim_time;time_current = time_current+sim_input.step_time)
    {

        if(time_current< sim_input.fault_instant)
        {
            network_eqns(y_bus_pre_inv,state_variables_data,gen_dataset,no_gens,no_buses);
            rk4(state_variables_data,gen_dataset,no_gens, sim_input);

        }
        else if(sim_input.fault_instant<=time_current && time_current<(sim_input.fault_instant+(sim_input.fault_duration/sim_input.base_frequency)))
        {

            if(sim_input.dist_type == 1)
            {
                for(int i =0;i<no_gens;i++)
                {
                    if((sim_input.disturbed_gen) == gen_dataset[i].gen_bus_no)
                    {
                        state_variables_data[i].tm = ((100+sim_input.deltm)/100)*initial_cond_dataset[i].tm0;
                    }
                }
            }
            else if(sim_input.dist_type == 2)
            {
                for(int i =0;i<no_gens;i++)
                {
                    if((sim_input.disturbed_gen) == gen_dataset[i].gen_bus_no)
                    {
                        state_variables_data[i].v_ref = ((100+sim_input.delvref)/100)*initial_cond_dataset[i].v_ref;
                    }
                }

            }
            network_eqns(y_bus_during_inv,state_variables_data,gen_dataset,no_gens,no_buses);
            rk4(state_variables_data,gen_dataset,no_gens, sim_input);
        }
        else if(time_current>(sim_input.fault_instant+(sim_input.fault_duration/sim_input.base_frequency)) && time_current<sim_input.sim_time)
        {
             if(sim_input.dist_type == 1)
            {
                for(int i =0;i<no_gens;i++)
                {
                    if((sim_input.disturbed_gen) == gen_dataset[i].gen_bus_no)
                    {
                        state_variables_data[i].tm = initial_cond_dataset[i].tm0;
                    }
                }
            }
            else if(sim_input.dist_type == 2)
            {
                for(int i =0;i<no_gens;i++)
                {
                    if((sim_input.disturbed_gen) == gen_dataset[i].gen_bus_no)
                    {
                        state_variables_data[i].v_ref = initial_cond_dataset[i].v_ref;
                    }
                }

            }
            network_eqns(y_bus_post_inv,state_variables_data,gen_dataset,no_gens,no_buses);
            rk4(state_variables_data,gen_dataset,no_gens, sim_input);
        }

        for(int i=0;i<3;i++)
        {
            fprintf(fptr2,"\t%d \t%lf \t%lf \t%lf \t%lf \t%lf \t%lf \t%lf \t%lf \t%lf \t%lf \t%lf \t%lf \t%lf \t%lf \t%lf \t%lf \t%lf \t%lf",gen_dataset[i].gen_bus_no,time_current+0.001,state_variables_data[i].del_new,state_variables_data[i].sm_new,state_variables_data[i].efd_new,state_variables_data[i].edc__new,state_variables_data[i].ed_new,state_variables_data[i].ed__new,state_variables_data[i].eq_new,state_variables_data[i].eq__new,state_variables_data[i].iq,state_variables_data[i].id,state_variables_data[i].v_ref,state_variables_data[i].tm,state_variables_data[i].VQ,state_variables_data[i].VD,state_variables_data[i].IQ,state_variables_data[i].ID,state_variables_data[i].Vtmag);
        }
        fprintf(fptr2,"\n");
        for(int i_loop = 0; i_loop < no_gens; i_loop++)
        {
        state_variables_data[i_loop].efd_old=state_variables_data[i_loop].efd_new;
        state_variables_data[i_loop].ed_old=state_variables_data[i_loop].ed_new;
        state_variables_data[i_loop].ed__old=state_variables_data[i_loop].ed__new;
        state_variables_data[i_loop].eq_old=state_variables_data[i_loop].eq_new;
        state_variables_data[i_loop].eq__old=state_variables_data[i_loop].eq__new;
        state_variables_data[i_loop].del_old=state_variables_data[i_loop].del_new;
        state_variables_data[i_loop].sm_old=state_variables_data[i_loop].sm_new;
        state_variables_data[i_loop].edc__old=state_variables_data[i_loop].edc__new;
        state_variables_data[i_loop].te=(state_variables_data[i_loop].ed__old*state_variables_data[i_loop].id)+(state_variables_data[i_loop].eq__old*state_variables_data[i_loop].iq)+(state_variables_data[i_loop].id*state_variables_data[i_loop].iq*(gen_dataset[i_loop].xd__-gen_dataset[i_loop].xq__));


        }

    }

}
