#include<stdio.h>
#include<stdlib.h>
#include"header.h"
#include<complex.h>
#include<math.h>

void main()
{
    int no_buses,no_xlines,no_xmers,no_shunts,no_loads,no_gens;
    FILE *fdata_read;
    if((fdata_read=fopen("PAI9B.txt","r"))== NULL)
    {
        printf("\nError opening file");
        exit(1);
    }

    // initializing bus data,generator data,transformer data,shunt data

    fscanf(fdata_read,"%d %d %d %d %d %d",&no_buses,&no_xlines,&no_xmers,&no_shunts,&no_loads,&no_gens);
    struct bus_lf_data *bus_lf_dataset;
    bus_lf_dataset = (struct bus_lf_data*)malloc(no_buses*sizeof(struct bus_lf_data));
    struct xline_data *xline_dataset;
    xline_dataset = (struct xline_data*)malloc(no_xlines*sizeof(struct xline_data));
    struct xmer_data *xmer_dataset;
    xmer_dataset = (struct xmer_data*)malloc(no_xmers*sizeof(struct xmer_data));
    struct shunt_data *shunt_dataset;
    shunt_dataset = (struct shunt_data*)malloc(no_shunts*sizeof(struct shunt_data));
    struct gen_data *gen_dataset;
    gen_dataset = (struct gen_data*)malloc(no_gens*sizeof(struct gen_data));

    //initializing simulation inputs and saving values from file

    struct simulation_input sim_input;
    data_storage(fdata_read,bus_lf_dataset,xline_dataset,xmer_dataset,shunt_dataset,gen_dataset,no_buses,no_xlines,no_xmers,no_shunts,no_gens,sim_input);

    double mva;
    fscanf(fdata_read,"%lf",&mva);
    fscanf(fdata_read,"%lf",&sim_input.base_frequency);
    fscanf(fdata_read,"%lf",&sim_input.sim_time);
    fscanf(fdata_read,"%lf",&sim_input.step_time);

    //initializing Y bus pre

    complex **y_bus_pre;
     y_bus_pre = (complex**)malloc(no_buses*sizeof(complex *));
    for(int i = 0;i<no_buses;i++)
    {
    y_bus_pre[i] = (complex*)malloc(no_buses*sizeof(complex));
    }

    // initially storing zero in all elements of Y bus

    for(int i_loop1=0; i_loop1<no_buses; i_loop1++)
    {
        for(int i_loop2=0; i_loop2<no_buses; i_loop2++)
            y_bus_pre[i_loop1][i_loop2]=0;
    }

    //calling function to calculate pre fault Y bus

   y_bus_pre_calculation(bus_lf_dataset,xline_dataset,xmer_dataset,shunt_dataset,gen_dataset,no_buses,no_xlines,no_xmers,no_shunts,no_gens,y_bus_pre);

  //y bus during initialization

    complex **y_bus_during;
     y_bus_during = (complex**)malloc(no_buses*sizeof(complex *));
    for(int i = 0;i<no_buses;i++)
    {
    y_bus_during[i] = (complex*)malloc(no_buses*sizeof(complex));
    }
    for(int i_loop1=0; i_loop1<no_buses; i_loop1++)
    {
        for(int i_loop2=0; i_loop2<no_buses; i_loop2++)
            y_bus_during[i_loop1][i_loop2]=y_bus_pre[i_loop1][i_loop2];
    }

    // y bus post initialization

    complex **y_bus_post;
     y_bus_post = (complex**)malloc(no_buses*sizeof(complex *));
    for(int i = 0;i<no_buses;i++)
    {
    y_bus_post[i] = (complex*)malloc(no_buses*sizeof(complex));
    }
    for(int i_loop1=0; i_loop1<no_buses; i_loop1++)
    {
        for(int i_loop2=0; i_loop2<no_buses; i_loop2++)
            y_bus_post[i_loop1][i_loop2]=y_bus_pre[i_loop1][i_loop2];
    }
    y_bus_to_file(y_bus_pre,no_buses);


// initial conditions


    struct initial_cond_data *initial_cond_dataset;
    initial_cond_dataset = (struct initial_cond_data*)malloc(no_gens*sizeof(struct initial_cond_data));


    initial_condition(bus_lf_dataset,gen_dataset,initial_cond_dataset,y_bus_pre,no_buses,no_gens);
    initial_to_file(initial_cond_dataset,no_gens);

    //initiating state variables

    struct state_variables *state_variables_data;
    state_variables_data = (struct state_variables*)malloc(no_gens*sizeof(struct state_variables));




    // Taking inputs from the user for the type of fault

    printf("Select any one from the below(integers from 0 to 5): \n");
    printf("0. No disturbance \n");
    printf("1. Change in input power of generator \n");
    printf("2. Change in reference voltage of generator \n");
    printf("3. 3-ph fault at bus \n");
    printf("4. line trip \n");
    printf("5. 3-ph fault at line \n");
    scanf("%d",&sim_input.dist_type);

switch(sim_input.dist_type)
    {
    case 0: // NO disturbance
        printf("No disturbance on system");
        sim_input.fault_instant = sim_input.sim_time;
        sim_input.fault_duration = 0;
        break;
    case 1: // Change in torque of selected generator
        printf("\nEnter the generator number:  ");
        scanf("%d",&sim_input.disturbed_gen);
        printf("\nEnter the percentage change in the input power to mentioned generator: ");
        scanf("%lf",&sim_input.deltm);
        printf("\nEnter the instant of the disturbance (in secs): ");
        scanf("%lf",&sim_input.fault_instant);
        printf("\nEnter the fault duration in cycles: ");
        scanf("%lf",&sim_input.fault_duration);
        break;
    case 2:  // Change in reference voltage
        printf("\nEnter the generator number:  ");
        scanf("%d",&sim_input.disturbed_gen);
        printf("\nenter the percentage change in the reference voltage to mentioned generator: ");
        scanf("%lf",&sim_input.delvref);
        printf("\nEnter the instant of the disturbance (in secs): ");
        scanf("%lf",&sim_input.fault_instant);
        printf("\nEnter the fault duration in cycles: ");
        scanf("%lf",&sim_input.fault_duration);
        break;
    case 3:  // 3 phase fault at bus
        printf("\nEnter the bus number:  ");
        scanf("%d",&sim_input.fault_bus_no);
        printf("\nEnter the instant of the disturbance(in secs) :  ");
        scanf("%lf",&sim_input.fault_instant);
        printf("\nenter the fault duration in cycles: ");
        scanf("%lf",&sim_input.fault_duration);
        printf("Enter the fault resistance (real part of zfault): ");
        scanf("%lf",&sim_input.fault_resistance);
        printf("Enter the fault reactance (imaginary part of zfault): ");
        scanf("%lf",&sim_input.fault_reactance);
        sim_input.fault_impedence = sim_input.fault_resistance + sim_input.fault_reactance*I;
        y_bus_during[sim_input.fault_bus_no-1][sim_input.fault_bus_no-1] = y_bus_during[sim_input.fault_bus_no-1][sim_input.fault_bus_no-1] + (1/sim_input.fault_impedence);
        break;
    case 4:  // line trip
        printf("\nEnter the from bus number:  ");
        scanf("%d",&sim_input.fault_from_bus);
        printf("\nEnter the to bus number:  ");
        scanf("%d",&sim_input.fault_to_bus);
        printf("\nEnter the instant of the disturbance (in secs):  ");
        scanf("%lf",&sim_input.fault_instant);
        sim_input.fault_duration = (sim_input.sim_time-sim_input.fault_instant);

        for(int i_loop=0; i_loop<no_xlines; i_loop++)
        {
            if((xline_dataset[i_loop].from_bus == sim_input.fault_from_bus) && (xline_dataset[i_loop].to_bus == sim_input.fault_to_bus))
            {
                y_bus_during[sim_input.fault_from_bus-1][sim_input.fault_to_bus-1] = 0+0*I;
                y_bus_during[sim_input.fault_to_bus-1][sim_input.fault_from_bus-1] = 0+0*I;
                y_bus_during[sim_input.fault_from_bus-1][sim_input.fault_from_bus-1] = y_bus_during[sim_input.fault_from_bus-1][sim_input.fault_from_bus-1] - (0+xline_dataset[i_loop].susceptance*I) - (1/xline_dataset[i_loop].impedance);
                y_bus_during[sim_input.fault_to_bus-1][sim_input.fault_to_bus-1] = y_bus_during[sim_input.fault_to_bus-1][sim_input.fault_to_bus-1] - (0+xline_dataset[i_loop].susceptance*I) - (1/xline_dataset[i_loop].impedance);
                y_bus_post[sim_input.fault_from_bus-1][sim_input.fault_to_bus-1] = 0+0*I;
                y_bus_post[sim_input.fault_to_bus-1][sim_input.fault_from_bus-1] = 0+0*I;
                y_bus_post[sim_input.fault_from_bus-1][sim_input.fault_from_bus-1] = y_bus_post[sim_input.fault_from_bus-1][sim_input.fault_from_bus-1] - (0+xline_dataset[i_loop].susceptance*I) - (1/xline_dataset[i_loop].impedance);
                y_bus_post[sim_input.fault_to_bus-1][sim_input.fault_to_bus-1] = y_bus_post[sim_input.fault_to_bus-1][sim_input.fault_to_bus-1] - (0+xline_dataset[i_loop].susceptance*I) - (1/xline_dataset[i_loop].impedance);
            }

        }
        for(int i_loop=0; i_loop<no_xmers; i_loop++)
        {
            if((xmer_dataset[i_loop].from_bus == sim_input.fault_from_bus) && (xmer_dataset[i_loop].to_bus == sim_input.fault_to_bus))
            {
                y_bus_during[sim_input.fault_from_bus-1][sim_input.fault_to_bus-1] = 0+0*I;
                y_bus_during[sim_input.fault_to_bus-1][sim_input.fault_from_bus-1] = 0+0*I;
                y_bus_during[sim_input.fault_from_bus-1][sim_input.fault_from_bus-1] = y_bus_during[sim_input.fault_from_bus-1][sim_input.fault_from_bus-1] - (1/((xmer_dataset[i_loop].impedance)*(xmer_dataset[i_loop].tap*xmer_dataset[i_loop].tap)));
                y_bus_during[sim_input.fault_to_bus-1][sim_input.fault_to_bus-1] = y_bus_during[sim_input.fault_to_bus-1][sim_input.fault_to_bus-1] -(1/xmer_dataset[i_loop].impedance);
                y_bus_post[sim_input.fault_from_bus-1][sim_input.fault_to_bus-1] = 0+0*I;
                y_bus_post[sim_input.fault_to_bus-1][sim_input.fault_from_bus-1] = 0+0*I;
                y_bus_post[sim_input.fault_from_bus-1][sim_input.fault_from_bus-1] = y_bus_post[sim_input.fault_from_bus-1][sim_input.fault_from_bus-1] -(1/((xmer_dataset[i_loop].impedance)*(xmer_dataset[i_loop].tap*xmer_dataset[i_loop].tap)));
                y_bus_post[sim_input.fault_to_bus-1][sim_input.fault_to_bus-1] = y_bus_post[sim_input.fault_to_bus-1][sim_input.fault_to_bus-1] -(1/xmer_dataset[i_loop].impedance);
            }

        }

        break;
    case 5:  // 3 phase fault at line
        printf("\nEnter the from bus number:  ");
        scanf("%d",&sim_input.fault_from_bus);
        printf("\nEnter the to bus number:  ");
        scanf("%d",&sim_input.fault_to_bus);
        printf("\nEnter the instant of the disturbance(in secs): ");
        scanf("%lf",&sim_input.fault_instant);
        printf("\nenter the fault duration: ");
        scanf("%lf",&sim_input.fault_duration);
        printf("\nenter the percentage distance from the from bus: ");
        scanf("%lf",&sim_input.fault_distance);
        printf("Enter the fault resistance (real part of zfault): ");
        scanf("%lf",&sim_input.fault_resistance);
        printf("Enter the fault reactance (imaginary part of zfault): ");
        scanf("%lf",&sim_input.fault_reactance);
        sim_input.fault_impedence = sim_input.fault_resistance + sim_input.fault_reactance*I;
        printf("\nDo you want to trip the line? (1 for yes and 0 for no):  ");
        scanf("%d",&sim_input.line_trip);
        for(int i_loop=0; i_loop<no_xlines; i_loop++)
        {
            if((xline_dataset[i_loop].from_bus == sim_input.fault_from_bus) && (xline_dataset[i_loop].to_bus == sim_input.fault_to_bus))
            {
                complex z1,z2,z3;
                complex z12,z23,z13;
                z1 = sim_input.fault_distance/100*(xline_dataset[i_loop].impedance);
                z2 = (100-sim_input.fault_distance)/100*(xline_dataset[i_loop].impedance);
                z3 = sim_input.fault_impedence;
                z12 = z1+z2+(z1*z2/z3);
                z13 = z1+z3+(z1*z3/z2);
                z23 = z2+z3+(z2*z3/z1);

                y_bus_during[sim_input.fault_from_bus-1][sim_input.fault_to_bus-1] = 0+0*I;
                y_bus_during[sim_input.fault_to_bus-1][sim_input.fault_from_bus-1] = 0+0*I;
                y_bus_during[sim_input.fault_from_bus-1][sim_input.fault_from_bus-1] = y_bus_during[sim_input.fault_from_bus-1][sim_input.fault_from_bus-1] - (0+xline_dataset[i_loop].susceptance*I) - (1/xline_dataset[i_loop].impedance);
                y_bus_during[sim_input.fault_to_bus-1][sim_input.fault_to_bus-1] = y_bus_during[sim_input.fault_to_bus-1][sim_input.fault_to_bus-1] - (0+xline_dataset[i_loop].susceptance*I) - (1/xline_dataset[i_loop].impedance);
                if(sim_input.line_trip == 1)
                    {
                        y_bus_post[sim_input.fault_from_bus-1][sim_input.fault_to_bus-1] = 0+0*I;
                        y_bus_post[sim_input.fault_to_bus-1][sim_input.fault_from_bus-1] = 0+0*I;
                        y_bus_post[sim_input.fault_from_bus-1][sim_input.fault_from_bus-1] = y_bus_post[sim_input.fault_from_bus-1][sim_input.fault_from_bus-1] - (0+xline_dataset[i_loop].susceptance*I) - (1/xline_dataset[i_loop].impedance);
                        y_bus_post[sim_input.fault_to_bus-1][sim_input.fault_to_bus-1] = y_bus_post[sim_input.fault_to_bus-1][sim_input.fault_to_bus-1] -(0+xline_dataset[i_loop].susceptance*I) - (1/xline_dataset[i_loop].impedance);
                    }
                y_bus_during[sim_input.fault_from_bus-1][sim_input.fault_from_bus-1] = y_bus_during[sim_input.fault_from_bus-1][sim_input.fault_from_bus-1] + (1/z12)+(1/z13);
                y_bus_during[sim_input.fault_to_bus-1][sim_input.fault_to_bus-1] = y_bus_during[sim_input.fault_to_bus-1][sim_input.fault_to_bus-1] + (1/z12)+(1/z23) ;
                y_bus_during[sim_input.fault_from_bus-1][sim_input.fault_to_bus-1] = y_bus_during[sim_input.fault_from_bus-1][sim_input.fault_to_bus-1] - (1/z12) ;
                y_bus_during[sim_input.fault_to_bus-1][sim_input.fault_from_bus-1] = y_bus_during[sim_input.fault_to_bus-1][sim_input.fault_from_bus-1] - (1/z12);
            }
        }
        for(int i_loop=0; i_loop<no_xmers; i_loop++)
        {
            if((xmer_dataset[i_loop].from_bus == sim_input.fault_from_bus) && (xmer_dataset[i_loop].to_bus == sim_input.fault_to_bus))
            {

                // converting star to delta and modifying Y bus
                complex z1,z2,z3;
                complex z12,z23,z13;
                z1 = sim_input.fault_distance/100*(xmer_dataset[i_loop].impedance);
                z2 = (100-sim_input.fault_distance)/100*(xmer_dataset[i_loop].impedance);
                z3 = sim_input.fault_impedence;
                z12 = z1+z2+(z1*z2/z3);
                z13 = z1+z3+(z1*z3/z2);
                z23 = z2+z3+(z2*z3/z1);

                y_bus_during[sim_input.fault_from_bus-1][sim_input.fault_to_bus-1] = 0+0*I;
                y_bus_during[sim_input.fault_to_bus-1][sim_input.fault_from_bus-1] = 0+0*I;
                y_bus_during[sim_input.fault_from_bus-1][sim_input.fault_from_bus-1] = y_bus_during[sim_input.fault_from_bus-1][sim_input.fault_from_bus-1] - (1/((xmer_dataset[i_loop].impedance)*(xmer_dataset[i_loop].tap*xmer_dataset[i_loop].tap)));
                y_bus_during[sim_input.fault_to_bus-1][sim_input.fault_to_bus-1] = y_bus_during[sim_input.fault_to_bus-1][sim_input.fault_to_bus-1] - (1/xmer_dataset[i_loop].impedance);
                if(sim_input.line_trip == 1) //
                    {
                        y_bus_post[sim_input.fault_from_bus-1][sim_input.fault_to_bus-1] = 0+0*I;
                        y_bus_post[sim_input.fault_to_bus-1][sim_input.fault_from_bus-1] = 0+0*I;
                        y_bus_post[sim_input.fault_from_bus-1][sim_input.fault_from_bus-1] = y_bus_post[sim_input.fault_from_bus-1][sim_input.fault_from_bus-1]  - (1/((xmer_dataset[i_loop].impedance)*(xmer_dataset[i_loop].tap*xmer_dataset[i_loop].tap)));
                        y_bus_post[sim_input.fault_to_bus-1][sim_input.fault_to_bus-1] = y_bus_post[sim_input.fault_to_bus-1][sim_input.fault_to_bus-1] - (1/xmer_dataset[i_loop].impedance);
                    }
                y_bus_during[sim_input.fault_from_bus-1][sim_input.fault_from_bus-1] = y_bus_during[sim_input.fault_from_bus-1][sim_input.fault_from_bus-1] + (1/z12)+(1/z13);
                y_bus_during[sim_input.fault_to_bus-1][sim_input.fault_to_bus-1] = y_bus_during[sim_input.fault_to_bus-1][sim_input.fault_to_bus-1] + (1/z12)+(1/z23) ;
                y_bus_during[sim_input.fault_from_bus-1][sim_input.fault_to_bus-1] = y_bus_during[sim_input.fault_from_bus-1][sim_input.fault_to_bus-1] - (1/z12) ;
                y_bus_during[sim_input.fault_to_bus-1][sim_input.fault_from_bus-1] = y_bus_during[sim_input.fault_to_bus-1][sim_input.fault_from_bus-1] - (1/z12);
            }
        }
        break;
    default:
        break;
    }

    // Creating Zbus pre( Y-bus pre inverse) and calculating it using the inverse function

    complex **y_bus_pre_inv;
     y_bus_pre_inv = (complex**)malloc(no_buses*sizeof(complex *));
    for(int i = 0;i<no_buses;i++)
    {
    y_bus_pre_inv[i] = (complex*)malloc(no_buses*sizeof(complex));
    }
    for(int i_loop1=0; i_loop1<no_buses; i_loop1++)
    {
        for(int i_loop2=0; i_loop2<no_buses; i_loop2++)
            y_bus_pre_inv[i_loop1][i_loop2]=0;
    }
    // calling inverse function
    inv_ybus(y_bus_pre,y_bus_pre_inv,no_buses);

    // Creating Zbus during( Y-bus during inverse) and calculating it using the inverse function

    complex **y_bus_during_inv;
     y_bus_during_inv = (complex**)malloc(no_buses*sizeof(complex *));
    for(int i = 0;i<no_buses;i++)
    {
    y_bus_during_inv[i] = (complex*)malloc(no_buses*sizeof(complex));
    }
    for(int i_loop1=0; i_loop1<no_buses; i_loop1++)
    {
        for(int i_loop2=0; i_loop2<no_buses; i_loop2++)
            y_bus_during_inv[i_loop1][i_loop2]=y_bus_pre[i_loop1][i_loop2];
    }
    // calling inverse function
    inv_ybus(y_bus_during,y_bus_during_inv,no_buses);




     // Creating Zbus post( Y-bus post inverse) and calculating it using the inverse function
    complex **y_bus_post_inv;
     y_bus_post_inv = (complex**)malloc(no_buses*sizeof(complex *));
    for(int i = 0;i<no_buses;i++)
    {
    y_bus_post_inv[i] = (complex*)malloc(no_buses*sizeof(complex));
    }
    for(int i_loop1=0; i_loop1<no_buses; i_loop1++)
    {
        for(int i_loop2=0; i_loop2<no_buses; i_loop2++)
            y_bus_post_inv[i_loop1][i_loop2]=y_bus_pre[i_loop1][i_loop2];
    }
    // calling inverse function
    inv_ybus(y_bus_post,y_bus_post_inv,no_buses);


    // initializing the state variables using initial condition data
     for(int i_loop=0;i_loop<no_gens;i_loop++)
    {
        state_variables_data[i_loop].efd_old=initial_cond_dataset[i_loop].efd0;
        state_variables_data[i_loop].ed_old=initial_cond_dataset[i_loop].ed_0;
        state_variables_data[i_loop].ed__old=initial_cond_dataset[i_loop].ed__0;
        state_variables_data[i_loop].eq_old=initial_cond_dataset[i_loop].eq_0;
        state_variables_data[i_loop].eq__old=initial_cond_dataset[i_loop].eq__0;
        state_variables_data[i_loop].id=cimag(initial_cond_dataset[i_loop].i_gen_park);
        state_variables_data[i_loop].iq=creal(initial_cond_dataset[i_loop].i_gen_park);
        state_variables_data[i_loop].sm_old=initial_cond_dataset[i_loop].sm0;
        state_variables_data[i_loop].v_ref=initial_cond_dataset[i_loop].v_ref;
        state_variables_data[i_loop].tm=initial_cond_dataset[i_loop].tm0;
        state_variables_data[i_loop].te=initial_cond_dataset[i_loop].te0;
        state_variables_data[i_loop].edc__old=initial_cond_dataset[i_loop].edc0;
        state_variables_data[i_loop].del_old=initial_cond_dataset[i_loop].del0;
        state_variables_data[i_loop].VQ=bus_lf_dataset[i_loop].voltage_mag*cos(bus_lf_dataset[i_loop].voltage_ang*3.14/180);
        state_variables_data[i_loop].VD=bus_lf_dataset[i_loop].voltage_mag*sin(bus_lf_dataset[i_loop].voltage_ang*3.14/180);
        state_variables_data[i_loop].Vt = initial_cond_dataset[i_loop].Vt0;
        state_variables_data[i_loop].Vtmag = initial_cond_dataset[i_loop].Vt0mag;
        state_variables_data[i_loop].Ig = 0+0*I;

        state_variables_data[i_loop].efd_new=state_variables_data[i_loop].efd_old;
        state_variables_data[i_loop].ed_new=state_variables_data[i_loop].ed_old;
        state_variables_data[i_loop].ed__new=state_variables_data[i_loop].ed__old;
        state_variables_data[i_loop].eq_new=state_variables_data[i_loop].eq_old;
        state_variables_data[i_loop].eq__new=state_variables_data[i_loop].eq__old;
        state_variables_data[i_loop].sm_new=state_variables_data[i_loop].sm_old;
        state_variables_data[i_loop].edc__new=state_variables_data[i_loop].edc__old;
        state_variables_data[i_loop].del_new=state_variables_data[i_loop].del_old;
    }
     FILE *fptr2;
    if((fptr2=fopen("output.txt","w"))==NULL)
    {
        printf("\n Error in opening the file");
        exit(1);
    }

    for(int i=1; i<=no_gens; i++)
    {
    fprintf(fptr2,"\tGno\ttime \tdel \tSm \tEfd \tEdc \tEd_ \tEd__ \tEq_ \tEq__ \tid \tiq \tVref \tTe \tVQ \tVD \tIQ \tID \tVt");
    }
    fprintf(fptr2,"\n");
    time_sim_func(initial_cond_dataset,state_variables_data,gen_dataset,y_bus_pre_inv,y_bus_during_inv,y_bus_post_inv,no_gens,no_buses,sim_input,fptr2);
     fclose(fptr2);
}
