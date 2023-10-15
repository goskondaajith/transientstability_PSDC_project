#include<stdio.h>
#include<stdlib.h>
#include"header.h"
#include<complex.h>
#include<math.h>
void rk4(struct state_variables *state_variables_data,struct gen_data *gen_dataset,int no_gens, struct simulation_input sim_input)
{
    printf("hello");
    double base_frequency;
    base_frequency = sim_input.base_frequency;


    // eq double dash


    double deq__(double eq__,int i_loop)
        {
            double deq__dt=0;
            deq__dt=((( gen_dataset[i_loop].xd_-gen_dataset[i_loop].xd__)*state_variables_data[i_loop].id)+state_variables_data[i_loop].eq_old-eq__)/gen_dataset[i_loop].td0__;
            return deq__dt;
        }

    for(int i_loop=0;i_loop<no_gens;i_loop++)
    {
        double k1=0,k2=0,k3=0,k4=0;
        k1 = sim_input.step_time*deq__(state_variables_data[i_loop].eq__old,i_loop);
        k2 = sim_input.step_time*deq__(state_variables_data[i_loop].eq__old + 0.5*k1,i_loop);
        k3 = sim_input.step_time*deq__(state_variables_data[i_loop].eq__old + 0.5*k2,i_loop);
        k4 = sim_input.step_time*deq__(state_variables_data[i_loop].eq__old + k3,i_loop);

        state_variables_data[i_loop].eq__new= state_variables_data[i_loop].eq__old + (1.0/6.0)*(k1 + 2*k2 + 2*k3 + k4);

    // ed double dash


    double ded__(double ed__,int i_loop)
        {
            double ded__dt=0;
            ded__dt= ((( gen_dataset[i_loop].xq__-gen_dataset[i_loop].xq_)*state_variables_data[i_loop].iq)+state_variables_data[i_loop].ed_old-ed__)/gen_dataset[i_loop].tq0__;
            return ded__dt;
        }

    for(int i_loop=0;i_loop<no_gens;i_loop++)
    {
        double k1=0,k2=0,k3=0,k4=0;
        k1 = sim_input.step_time*ded__(state_variables_data[i_loop].ed__old,i_loop);
        k2 = sim_input.step_time*ded__(state_variables_data[i_loop].ed__old + 0.5*k1,i_loop);
        k3 = sim_input.step_time*ded__(state_variables_data[i_loop].ed__old + 0.5*k2,i_loop);
        k4 = sim_input.step_time*ded__(state_variables_data[i_loop].ed__old + k3,i_loop);

        state_variables_data[i_loop].ed__new= state_variables_data[i_loop].ed__old + (1.0/6.0)*(k1 + 2*k2 + 2*k3 + k4);


    }

    // eq dash


    double deq_(double eq_,int i_loop)
        {
            double deq_dt=0;
            deq_dt= ((( gen_dataset[i_loop].xd-gen_dataset[i_loop].xd_)*state_variables_data[i_loop].id)+state_variables_data[i_loop].efd_old-eq_)/gen_dataset[i_loop].td0_;
            return deq_dt;
        }

    for(int i_loop=0;i_loop<no_gens;i_loop++)
    {
        double k1=0,k2=0,k3=0,k4=0;
        k1 = sim_input.step_time*deq_(state_variables_data[i_loop].eq_old,i_loop);
        k2 = sim_input.step_time*deq_(state_variables_data[i_loop].eq_old + 0.5*k1,i_loop);
        k3 = sim_input.step_time*deq_(state_variables_data[i_loop].eq_old + 0.5*k2,i_loop);
        k4 = sim_input.step_time*deq_(state_variables_data[i_loop].eq_old + k3,i_loop);

        state_variables_data[i_loop].eq_new= state_variables_data[i_loop].eq_old + (1.0/6.0)*(k1 + 2*k2 + 2*k3 + k4);



    }

    // ed dash


    double ded_(double ed_,int i_loop)
        {
            double ded_dt=0;
            ded_dt= ((( gen_dataset[i_loop].xq_-gen_dataset[i_loop].xq)*state_variables_data[i_loop].iq)-ed_)/gen_dataset[i_loop].tq0_;
            return ded_dt;
        }

    for(int i_loop=0;i_loop<no_gens;i_loop++)
    {
        double k1=0,k2=0,k3=0,k4=0;
        k1 = sim_input.step_time*ded_(state_variables_data[i_loop].ed_old,i_loop);
        k2 = sim_input.step_time*ded_(state_variables_data[i_loop].ed_old + 0.5*k1,i_loop);
        k3 = sim_input.step_time*ded_(state_variables_data[i_loop].ed_old + 0.5*k2,i_loop);
        k4 = sim_input.step_time*ded_(state_variables_data[i_loop].ed_old + k3,i_loop);

        state_variables_data[i_loop].ed_new= state_variables_data[i_loop].ed_old + (1.0/6.0)*(k1 + 2*k2 + 2*k3 + k4);

    }


    //delta

    double ddelta(double delta,int i_loop, double base_frequency)
        {
            double ddeltadt=0;
            ddeltadt=(state_variables_data[i_loop].sm_old-0)*(2*3.141593*base_frequency);
            return ddeltadt;
        }

    for(int i_loop=0;i_loop<no_gens;i_loop++)
    {
        double k1=0,k2=0,k3=0,k4=0;
        k1 = sim_input.step_time*ddelta(state_variables_data[i_loop].del_old,i_loop,base_frequency);
        k2 = sim_input.step_time*ddelta(state_variables_data[i_loop].del_old + 0.5*k1,i_loop, base_frequency);
        k3 = sim_input.step_time*ddelta(state_variables_data[i_loop].del_old + 0.5*k2,i_loop, base_frequency);
        k4 = sim_input.step_time*ddelta(state_variables_data[i_loop].del_old + k3,i_loop,base_frequency);

        // Update next value of y
        state_variables_data[i_loop].del_new= state_variables_data[i_loop].del_old + (1.0/6.0)*(k1 + 2*k2 + 2*k3 + k4);

    }

    // Sm

    double dsm(double smfu,int i_loop)
        {
            double dsmdt=0;
            dsmdt = (((-smfu)*gen_dataset[i_loop].d)+state_variables_data[i_loop].tm-state_variables_data[i_loop].te)/(2*gen_dataset[i_loop].inertia_const);
            return dsmdt;
        }

    for(int i_loop=0;i_loop<no_gens;i_loop++)
    {
        double k1=0,k2=0,k3=0,k4=0;

        k1 = sim_input.step_time*dsm(state_variables_data[i_loop].sm_old,i_loop);
        k2 = sim_input.step_time*dsm(state_variables_data[i_loop].sm_old + 0.5*k1,i_loop);
        k3 = sim_input.step_time*dsm(state_variables_data[i_loop].sm_old + 0.5*k2,i_loop);
        k4 = sim_input.step_time*dsm(state_variables_data[i_loop].sm_old + k3,i_loop);


        state_variables_data[i_loop].sm_new= state_variables_data[i_loop].sm_old + (1.0/6.0)*(k1 + 2*k2 + 2*k3 + k4);

    }

    // efd

    double defd(double efd,int i_loop)
        {
            double defddt=0;
            defddt = (((state_variables_data[i_loop].v_ref-state_variables_data[i_loop].Vtmag)*gen_dataset[i_loop].ka)-efd)/gen_dataset[i_loop].ta;
            return defddt;
        }

    for(int i_loop=0;i_loop<no_gens;i_loop++)
    {
        double k1=0,k2=0,k3=0,k4=0;
        k1 = sim_input.step_time*defd(state_variables_data[i_loop].efd_old,i_loop);
        k2 = sim_input.step_time*defd(state_variables_data[i_loop].efd_old + 0.5*k1,i_loop);
        k3 = sim_input.step_time*defd(state_variables_data[i_loop].efd_old + 0.5*k2,i_loop);
        k4 = sim_input.step_time*defd(state_variables_data[i_loop].efd_old + k3,i_loop);

        state_variables_data[i_loop].efd_new= state_variables_data[i_loop].efd_old + (1.0/6.0)*(k1 + 2*k2 + 2*k3 + k4);

    }


    // edc

    double dedc(double edc,int i_loop)
        {
            double dedcdt=0;
            dedcdt =((-edc-((gen_dataset[i_loop].xq__-gen_dataset[i_loop].xd__)*state_variables_data[i_loop].iq))/gen_dataset[i_loop].tc);
            return dedcdt;
        }

    for(int i_loop=0;i_loop<no_gens;i_loop++)
    {
        double k1=0,k2=0,k3=0,k4=0;
        k1 = sim_input.step_time*dedc(state_variables_data[i_loop].edc__old,i_loop);
        k2 = sim_input.step_time*dedc(state_variables_data[i_loop].edc__old + 0.5*k1,i_loop);
        k3 = sim_input.step_time*dedc(state_variables_data[i_loop].edc__old + 0.5*k2,i_loop);
        k4 = sim_input.step_time*dedc(state_variables_data[i_loop].edc__old + k3,i_loop);


        state_variables_data[i_loop].edc__new= state_variables_data[i_loop].edc__old + (1.0/6.0)*(k1 + 2*k2 + 2*k3 + k4);

    }

}
}
