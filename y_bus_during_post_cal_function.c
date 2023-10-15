#include<stdio.h>
#include<stdlib.h>
#include"header.h"
#include<complex.h>
#include<math.h>
/*void y_bus_during_post_calculation(struct bus_lf_data *bus_lf_dataset,struct xline_data *xline_dataset,struct xmer_data *xmer_dataset,struct shunt_data *shunt_dataset,struct gen_data *gen_dataset,complex **y_bus_during,complex **y_bus_post,struct simulation_input sim_input,int no_xlines,int no_buses)
{
    int i=0;
switch(sim_input.dist_type)
    {
    case 0:
        printf("No disturbance on system");
        sim_input.fault_instant = sim_input.sim_time;
        sim_input.fault_duration = 0;
        break;
    case 1:
        printf("\nEnter the generator number:  ");
        scanf("%d",&sim_input.disturbed_gen);
        printf("\nEnter the percentage change in the input power to mentioned generator: ");
        scanf("%lf",&sim_input.deltm);
        printf("\nEnter the instant of the disturbance");
        scanf("%lf",&sim_input.fault_instant);
        printf("\nEnter the fault duration in cycles: ");
        scanf("%lf",&sim_input.fault_duration);
        break;
    case 2:
        printf("\nEnter the generator number:  ");
        scanf("%d",&sim_input.disturbed_gen);
        printf("\nenter the percentage change in the reference voltage to mentioned generator: ");
        scanf("%lf",&sim_input.delvref);
        printf("\nEnter the instant of the disturbance");
        scanf("%lf",&sim_input.fault_instant);
        printf("\nEnter the fault duration in cycles: ");
        scanf("%lf",&sim_input.fault_duration);
        break;
    case 3:
        printf("\nEnter the bus number:  ");
        scanf("%d",&sim_input.fault_bus_no);
        printf("\nEnter the instant of the disturbance");
        scanf("%lf",&sim_input.fault_instant);
        printf("\nenter the fault duration in cycles: ");
        scanf("%lf",&sim_input.fault_duration);
        printf("Enter the fault resistance (real part of zfault): ");
        scanf("%lf",sim_input.fault_resistance);
        printf("Enter the fault reactance (imaginary part of zfault): ");
        scanf("%lf",sim_input.fault_reactance);
        sim_input.fault_impedence = sim_input.fault_resistance + sim_input.fault_reactance*I;
        y_bus_during[sim_input.fault_bus_no-1][sim_input.fault_bus_no-1] = y_bus_during[sim_input.fault_bus_no-1][sim_input.fault_bus_no-1] + (1/sim_input.fault_impedence);
        y_bus_post[sim_input.fault_bus_no-1][sim_input.fault_bus_no-1] = y_bus_post[sim_input.fault_bus_no-1][sim_input.fault_bus_no-1] + (1/sim_input.fault_impedence);
        break;
    case 4:
        printf("\nEnter the from bus number:  ");
        scanf("%d",&sim_input.fault_from_bus);
        printf("\nEnter the to bus number:  ");
        sim_input.fault_instant = sim_input.sim_time;
        sim_input.fault_duration = 0;
        scanf("%d",&sim_input.fault_to_bus);
        for(int i_loop=0; i_loop<no_xlines; i_loop++)    // Storing the data from file into array of structures
        {
            if((xline_dataset[i_loop].from_bus == sim_input.fault_from_bus) && (xline_dataset[i_loop].to_bus == sim_input.fault_to_bus))
            {
                i = i_loop;
            }
        }
         y_bus_during[sim_input.fault_from_bus-1][sim_input.fault_to_bus-1] = y_bus_during[sim_input.fault_from_bus-1][xline_dataset[i].to_bus-1] + (1/xline_dataset[i].impedance);
        y_bus_during[sim_input.fault_to_bus-1][sim_input.fault_from_bus-1] = y_bus_during[sim_input.fault_to_bus-1][sim_input.fault_from_bus-1] + (1/xline_dataset[i].impedance);
        y_bus_during[sim_input.fault_from_bus-1][sim_input.fault_from_bus-1] = y_bus_during[sim_input.fault_from_bus-1][sim_input.fault_from_bus-1] - (0+xline_dataset[i].susceptance*I) - (1/xline_dataset[i].impedance);
        y_bus_during[sim_input.fault_to_bus-1][sim_input.fault_to_bus-1] = y_bus_during[sim_input.fault_to_bus-1][sim_input.fault_to_bus-1] - (0+xline_dataset[i].susceptance*I) - (1/xline_dataset[i].impedance);
         y_bus_post[sim_input.fault_from_bus-1][sim_input.fault_to_bus-1] = y_bus_post[sim_input.fault_from_bus-1][sim_input.fault_to_bus-1] + (1/xline_dataset[i].impedance);
        y_bus_post[sim_input.fault_to_bus-1][sim_input.fault_from_bus-1] = y_bus_post[sim_input.fault_to_bus-1][sim_input.fault_from_bus-1] + (1/xline_dataset[i].impedance);
        y_bus_post[sim_input.fault_from_bus-1][sim_input.fault_from_bus-1] = y_bus_post[sim_input.fault_from_bus-1][sim_input.fault_from_bus-1] - (0+xline_dataset[i].susceptance*I) - (1/xline_dataset[i].impedance);
        y_bus_post[sim_input.fault_to_bus-1][sim_input.fault_to_bus-1] = y_bus_post[sim_input.fault_to_bus-1][sim_input.fault_to_bus-1] - (0+xline_dataset[i].susceptance*I) - (1/xline_dataset[i].impedance);
        break;
    case 5:
        printf("\nEnter the from bus number:  ");
        scanf("%d",&sim_input.fault_from_bus);
        printf("\nEnter the to bus number:  ");
        printf("\nEnter the instant of the disturbance");
        scanf("%lf",&sim_input.fault_instant);
        scanf("%d",&sim_input.fault_to_bus);
        printf("\nenter the fault duration in sec: ");
        scanf("%lf",&sim_input.fault_duration);
        printf("\nenter the percentage distance from the from bus: ");
        scanf("%lf",&sim_input.fault_distance);
        printf("Enter the fault resistance (real part of zfault): ");
        scanf("%lf",sim_input.fault_resistance);
        printf("Enter the fault reactance (imaginary part of zfault): ");
        scanf("%lf",sim_input.fault_reactance);
        sim_input.fault_impedence = sim_input.fault_resistance + sim_input.fault_reactance*I;
        printf("\nDo you want to trip the line? (1 for yes and 0 for no):  ");
        scanf("%d",&sim_input.line_trip);
        for(int i_loop=0; i_loop<no_xlines; i_loop++)    // Storing the data from file into array of structures
        {
            if((xline_dataset[i_loop].from_bus == sim_input.fault_from_bus) && (xline_dataset[i_loop].to_bus == sim_input.fault_to_bus))
            {
                i = i_loop;
            }
        }
        complex z1,z2,z3;
        z1 = sim_input.fault_distance*(xline_dataset[i].impedance);
        z2 = (100-sim_input.fault_distance)*(xline_dataset[i].impedance);
        z3 = sim_input.fault_impedence;

        y_bus_during[sim_input.fault_from_bus-1][sim_input.fault_to_bus-1] = y_bus_during[sim_input.fault_from_bus-1][sim_input.fault_to_bus-1] + (1/xline_dataset[i].impedance);
        y_bus_during[sim_input.fault_to_bus-1][sim_input.fault_from_bus-1] = y_bus_during[sim_input.fault_to_bus-1][sim_input.fault_from_bus-1] + (1/xline_dataset[i].impedance);
        y_bus_during[sim_input.fault_from_bus-1][sim_input.fault_from_bus-1] = y_bus_during[sim_input.fault_from_bus-1][sim_input.fault_from_bus-1] - (0+xline_dataset[i].susceptance*I) - (1/xline_dataset[i].impedance);
        y_bus_during[sim_input.fault_to_bus-1][sim_input.fault_to_bus-1] = y_bus_during[sim_input.fault_to_bus-1][sim_input.fault_to_bus-1] - (0+xline_dataset[i].susceptance*I) - (1/xline_dataset[i].impedance);
        if(sim_input.line_trip == 1)
        {
        y_bus_post[sim_input.fault_from_bus-1][sim_input.fault_to_bus-1] = y_bus_post[sim_input.fault_from_bus-1][sim_input.fault_to_bus-1] + (1/xline_dataset[i].impedance);
        y_bus_post[sim_input.fault_to_bus-1][sim_input.fault_from_bus-1] = y_bus_post[sim_input.fault_to_bus-1][sim_input.fault_from_bus-1] + (1/xline_dataset[i].impedance);
        y_bus_post[sim_input.fault_from_bus-1][sim_input.fault_from_bus-1] = y_bus_post[sim_input.fault_from_bus-1][sim_input.fault_from_bus-1] - (0+xline_dataset[i].susceptance*I) - (1/xline_dataset[i].impedance);
        y_bus_post[sim_input.fault_to_bus-1][sim_input.fault_to_bus-1] = y_bus_post[sim_input.fault_to_bus-1][sim_input.fault_to_bus-1] -     (0+xline_dataset[i].susceptance*I) - (1/xline_dataset[i].impedance);
        }
        y_bus_during[sim_input.fault_from_bus-1][sim_input.fault_from_bus-1] = y_bus_during[sim_input.fault_from_bus-1][sim_input.fault_from_bus-1] + (1/(z1+z3+(z1*z3/z2)));
        y_bus_during[sim_input.fault_to_bus-1][sim_input.fault_to_bus-1] = y_bus_during[sim_input.fault_to_bus-1][sim_input.fault_to_bus-1] + (1/(z2+z3+(z2*z3/z1)));
        y_bus_during[sim_input.fault_from_bus-1][sim_input.fault_to_bus-1] = y_bus_during[sim_input.fault_from_bus-1][sim_input.fault_to_bus-1] - (1/(z1+z2+(z1*z2/z3)));
        y_bus_during[sim_input.fault_to_bus-1][sim_input.fault_from_bus-1] = y_bus_during[sim_input.fault_to_bus-1][sim_input.fault_from_bus-1] - (1/(z1+z2+(z1*z2/z3)));
        y_bus_during[sim_input.fault_from_bus-1][sim_input.fault_from_bus-1] = y_bus_during[sim_input.fault_from_bus-1][sim_input.fault_from_bus-1] + (1/(z1+z2+(z1*z2/z3)));
        y_bus_during[sim_input.fault_to_bus-1][sim_input.fault_to_bus-1] = y_bus_during[sim_input.fault_to_bus-1][sim_input.fault_to_bus-1] + (1/(z1+z2+(z1*z2/z3)));
        break;
    default:
        break;
    }
    /*printf("The during Y-bus is: \n");
    for(int i=0; i<no_buses; i++)
    {
        for(int j=0; j<no_buses; j++)
        {
           // printf("hello");
            printf("%lf%+lfi ",creal(y_bus_during[i][j]),cimag(y_bus_during[i][j]));
        }
        printf("\n \n");
    }
    printf("The post Y-bus is: \n");
    for(int i=0; i<no_buses; i++)
    {
        for(int j=0; j<no_buses; j++)
        {
           // printf("hello");
            printf("%lf%+lfi ",creal(y_bus_post[i][j]),cimag(y_bus_post[i][j]));
        }
        printf("\n \n");
    }*/


//}
