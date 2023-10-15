#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED
#include<complex.h>
#include<math.h>
struct bus_lf_data
{
    int bus_no;
    double v_rated;
    double voltage_mag;
    double voltage_ang;
    complex voltage;
    double pgen;
    double qgen;
    double pload;
    double qload;
};
struct xline_data
{
    int from_bus,to_bus;
    complex impedance;
    double susceptance;
};
struct xmer_data
{
    int from_bus,to_bus;
    complex impedance;
    double tap;
    double tap_angle;
};
struct shunt_data
{
    int at_bus;
    complex impedance;
};
struct gen_data
{
    int gen_bus_no;
    double inertia_const;
    double d;
    double ra;
    double xd;
    double xd_;
    double xd__;
    double xq;
    double xq_;
    double xq__;
    double td0_;
    double tq0_;
    double td0__;
    double tq0__;
    double tc;
    double ka;
    double ta;
    double efd_max;
    double efd_min;
    complex gen_impedence;
};
struct initial_cond_data
{
    complex e_gen;
    complex i_gen;
    complex e_gen_park;
    complex i_gen_park;
    double del0;
    double v_ref;
    double efd0;
    double ed_0;
    double ed__0;
    double eq_0;
    double eq__0;
    double tm0;
    double id0;
    double iq0;
    double te0;
    double sm0;
    double edc0;
    complex Vt0;
    double Vt0mag;

};
struct state_variables
{
    double del_old;
    double del_new;
    double v_ref;
    double efd_old;
    double efd_new;
    double ed_old;
    double ed_new;
    double ed__old;
    double ed__new;
    double eq_old;
    double eq_new;
    double eq__old;
    double eq__new;
    double tm;
    double id;
    double iq;
    double ID;
    double IQ;
    double te;
    double sm_old;
    double sm_new;
    double edc__old;
    double edc__new;
    double vd;
    double vq;
    double VD;
    double VQ;
    double vtmag;
    double Vtmag;
    complex Vt;
    complex vt;
    complex Ig;

};
struct simulation_input
{
    int dist_type;
    double fault_instant;
    double fault_duration;
    int disturbed_gen;
    int fault_bus_no;
    int fault_from_bus;
    int fault_to_bus;
    double fault_distance;
    double delvref;
    double deltm;
    double base_frequency;
    double sim_time, step_time;
    double fault_resistance;
    double fault_reactance;
    complex fault_impedence;
    int line_trip;
};


void data_storage(FILE *fdata_read,struct bus_lf_data *bus_lf_dataset,struct xline_data *xline_dataset,struct xmer_data *xmer_dataset,struct shunt_data *shunt_dataset,struct gen_data *gen_dataset,int no_buses,int no_xlines,int no_xmers,int no_shunts,int no_gens,struct simulation_input sim_input);
void y_bus_pre_calculation(struct bus_lf_data *bus_lf_dataset,struct xline_data *xline_dataset,struct xmer_data *xmer_dataset,struct shunt_data *shunt_dataset,struct gen_data *gen_dataset,int no_buses,int no_xlines,int no_xmers,int no_shunts,int no_gens,complex **y_bus_pre);
void initial_condition(struct bus_lf_data *bus_lf_dataset,struct gen_data *gen_dataset,struct initial_cond_data *initial_cond_dataset,complex **y_bus_pre,int no_buses,int no_gens);
void y_bus_to_file(complex **y_bus_pre, int no_buses);
void initial_to_file(struct initial_cond_data *initial_cond_dataset, int no_gens);
void rk4(struct state_variables *state_variables_data,struct gen_data *gen_dataset,int no_gens,struct simulation_input sim_input);
void time_sim_func(struct initial_cond_data *initial_cond_dataset,struct state_variables *state_variables_data,struct gen_data *gen_dataset, complex **y_bus_pre_inv,complex **y_bus_during_inv,complex **y_bus_post_inv,int no_gens, int no_buses, struct simulation_input sim_input,FILE *fptr2);
void network_eqns(complex **y_bus, struct state_variables *state_variables_data,struct gen_data *gen_dataset,int no_gens, int no_buses);

#endif // FUNCTIONS_H_INCLUDED
