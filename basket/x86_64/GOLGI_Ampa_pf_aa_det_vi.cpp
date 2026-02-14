/* Created by Language version: 7.7.0 */
/* VECTORIZED */
#define NRN_VECTORIZED 1
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mech_api.h"
#undef PI
#define nil 0
#define _pval pval
// clang-format off
#include "md1redef.h"
#include "section_fwd.hpp"
#include "nrniv_mf.h"
#include "md2redef.h"
#include "nrnconf.h"
// clang-format on
#include "neuron/cache/mechanism_range.hpp"
static constexpr auto number_of_datum_variables = 2;
static constexpr auto number_of_floating_point_variables = 53;
namespace {
template <typename T>
using _nrn_mechanism_std_vector = std::vector<T>;
using _nrn_model_sorted_token = neuron::model_sorted_token;
using _nrn_mechanism_cache_range = neuron::cache::MechanismRange<number_of_floating_point_variables, number_of_datum_variables>;
using _nrn_mechanism_cache_instance = neuron::cache::MechanismInstance<number_of_floating_point_variables, number_of_datum_variables>;
using _nrn_non_owning_id_without_container = neuron::container::non_owning_identifier_without_container;
template <typename T>
using _nrn_mechanism_field = neuron::mechanism::field<T>;
template <typename... Args>
void _nrn_mechanism_register_data_fields(Args&&... args) {
  neuron::mechanism::register_data_fields(std::forward<Args>(args)...);
}
}
 
#if !NRNGPU
#undef exp
#define exp hoc_Exp
#if NRN_ENABLE_ARCH_INDEP_EXP_POW
#undef pow
#define pow hoc_pow
#endif
#endif
 
#define nrn_init _nrn_init__Golgi_PF_syn
#define _nrn_initial _nrn_initial__Golgi_PF_syn
#define nrn_cur _nrn_cur__Golgi_PF_syn
#define _nrn_current _nrn_current__Golgi_PF_syn
#define nrn_jacob _nrn_jacob__Golgi_PF_syn
#define nrn_state _nrn_state__Golgi_PF_syn
#define _net_receive _net_receive__Golgi_PF_syn 
#define kstates kstates__Golgi_PF_syn 
 
#define _threadargscomma_ _ml, _iml, _ppvar, _thread, _globals, _nt,
#define _threadargsprotocomma_ Memb_list* _ml, size_t _iml, Datum* _ppvar, Datum* _thread, double* _globals, NrnThread* _nt,
#define _internalthreadargsprotocomma_ _nrn_mechanism_cache_range* _ml, size_t _iml, Datum* _ppvar, Datum* _thread, double* _globals, NrnThread* _nt,
#define _threadargs_ _ml, _iml, _ppvar, _thread, _globals, _nt
#define _threadargsproto_ Memb_list* _ml, size_t _iml, Datum* _ppvar, Datum* _thread, double* _globals, NrnThread* _nt
#define _internalthreadargsproto_ _nrn_mechanism_cache_range* _ml, size_t _iml, Datum* _ppvar, Datum* _thread, double* _globals, NrnThread* _nt
 	/*SUPPRESS 761*/
	/*SUPPRESS 762*/
	/*SUPPRESS 763*/
	/*SUPPRESS 765*/
	 extern double *hoc_getarg(int);
 
#define t _nt->_t
#define dt _nt->_dt
#define syntype _ml->template fpfield<0>(_iml)
#define syntype_columnindex 0
#define gmax_factor _ml->template fpfield<1>(_iml)
#define gmax_factor_columnindex 1
#define Q10_diff _ml->template fpfield<2>(_iml)
#define Q10_diff_columnindex 2
#define Q10_channel _ml->template fpfield<3>(_iml)
#define Q10_channel_columnindex 3
#define gmax _ml->template fpfield<4>(_iml)
#define gmax_columnindex 4
#define U _ml->template fpfield<5>(_iml)
#define U_columnindex 5
#define tau_rec _ml->template fpfield<6>(_iml)
#define tau_rec_columnindex 6
#define tau_facil _ml->template fpfield<7>(_iml)
#define tau_facil_columnindex 7
#define M _ml->template fpfield<8>(_iml)
#define M_columnindex 8
#define Rd _ml->template fpfield<9>(_iml)
#define Rd_columnindex 9
#define Diff _ml->template fpfield<10>(_iml)
#define Diff_columnindex 10
#define Cdur _ml->template fpfield<11>(_iml)
#define Cdur_columnindex 11
#define r1FIX _ml->template fpfield<12>(_iml)
#define r1FIX_columnindex 12
#define r2 _ml->template fpfield<13>(_iml)
#define r2_columnindex 13
#define r3 _ml->template fpfield<14>(_iml)
#define r3_columnindex 14
#define r4 _ml->template fpfield<15>(_iml)
#define r4_columnindex 15
#define r5 _ml->template fpfield<16>(_iml)
#define r5_columnindex 16
#define r6FIX _ml->template fpfield<17>(_iml)
#define r6FIX_columnindex 17
#define Erev _ml->template fpfield<18>(_iml)
#define Erev_columnindex 18
#define kB _ml->template fpfield<19>(_iml)
#define kB_columnindex 19
#define tau_1 _ml->template fpfield<20>(_iml)
#define tau_1_columnindex 20
#define Tmax _ml->template fpfield<21>(_iml)
#define Tmax_columnindex 21
#define diffuse _ml->template fpfield<22>(_iml)
#define diffuse_columnindex 22
#define lamd _ml->template fpfield<23>(_iml)
#define lamd_columnindex 23
#define nd _ml->template fpfield<24>(_iml)
#define nd_columnindex 24
#define i _ml->template fpfield<25>(_iml)
#define i_columnindex 25
#define ic _ml->template fpfield<26>(_iml)
#define ic_columnindex 26
#define g _ml->template fpfield<27>(_iml)
#define g_columnindex 27
#define r1 _ml->template fpfield<28>(_iml)
#define r1_columnindex 28
#define r6 _ml->template fpfield<29>(_iml)
#define r6_columnindex 29
#define T _ml->template fpfield<30>(_iml)
#define T_columnindex 30
#define Trelease _ml->template fpfield<31>(_iml)
#define Trelease_columnindex 31
#define tspike _ml->template data_array<32, 800>(_iml)
#define tspike_columnindex 32
#define x _ml->template fpfield<33>(_iml)
#define x_columnindex 33
#define y_read _ml->template fpfield<34>(_iml)
#define y_read_columnindex 34
#define z_read _ml->template fpfield<35>(_iml)
#define z_read_columnindex 35
#define u_read _ml->template fpfield<36>(_iml)
#define u_read_columnindex 36
#define PRE _ml->template data_array<37, 800>(_iml)
#define PRE_columnindex 37
#define C _ml->template fpfield<38>(_iml)
#define C_columnindex 38
#define O _ml->template fpfield<39>(_iml)
#define O_columnindex 39
#define D _ml->template fpfield<40>(_iml)
#define D_columnindex 40
#define tsyn _ml->template fpfield<41>(_iml)
#define tsyn_columnindex 41
#define Mres _ml->template fpfield<42>(_iml)
#define Mres_columnindex 42
#define numpulses _ml->template fpfield<43>(_iml)
#define numpulses_columnindex 43
#define tzero _ml->template fpfield<44>(_iml)
#define tzero_columnindex 44
#define gbar_Q10 _ml->template fpfield<45>(_iml)
#define gbar_Q10_columnindex 45
#define Q10 _ml->template fpfield<46>(_iml)
#define Q10_columnindex 46
#define DC _ml->template fpfield<47>(_iml)
#define DC_columnindex 47
#define DO _ml->template fpfield<48>(_iml)
#define DO_columnindex 48
#define DD _ml->template fpfield<49>(_iml)
#define DD_columnindex 49
#define v _ml->template fpfield<50>(_iml)
#define v_columnindex 50
#define _g _ml->template fpfield<51>(_iml)
#define _g_columnindex 51
#define _tsav _ml->template fpfield<52>(_iml)
#define _tsav_columnindex 52
#define _nd_area *_ml->dptr_field<0>(_iml)
 /* Thread safe. No static _ml, _iml or _ppvar. */
 static int hoc_nrnpointerindex =  -1;
 static _nrn_mechanism_std_vector<Datum> _extcall_thread;
 /* external NEURON variables */
 extern double celsius;
 /* declaration of user functions */
 static double _hoc_diffusione(void*);
 static double _hoc_imax(void*);
 static int _mechtype;
extern void _nrn_cacheloop_reg(int, int);
extern void hoc_register_limits(int, HocParmLimits*);
extern void hoc_register_units(int, HocParmUnits*);
extern void nrn_promote(Prop*, int, int);
 
#define NMODL_TEXT 1
#if NMODL_TEXT
static void register_nmodl_text_and_filename(int mechtype);
#endif
 extern Prop* nrn_point_prop_;
 static int _pointtype;
 static void* _hoc_create_pnt(Object* _ho) { void* create_point_process(int, Object*);
 return create_point_process(_pointtype, _ho);
}
 static void _hoc_destroy_pnt(void*);
 static double _hoc_loc_pnt(void* _vptr) {double loc_point_process(int, void*);
 return loc_point_process(_pointtype, _vptr);
}
 static double _hoc_has_loc(void* _vptr) {double has_loc_point(void*);
 return has_loc_point(_vptr);
}
 static double _hoc_get_loc_pnt(void* _vptr) {
 double get_loc_point_process(void*); return (get_loc_point_process(_vptr));
}
 static void _hoc_setdata(void*);
 /* connect user functions to hoc names */
 static VoidFunc hoc_intfunc[] = {
 {0, 0}
};
 static Member_func _member_func[] = {
 {"loc", _hoc_loc_pnt},
 {"has_loc", _hoc_has_loc},
 {"get_loc", _hoc_get_loc_pnt},
 {"diffusione", _hoc_diffusione},
 {"imax", _hoc_imax},
 {0, 0}
};
#define diffusione diffusione_Golgi_PF_syn
#define imax imax_Golgi_PF_syn
 extern double diffusione( _internalthreadargsproto_ );
 extern double imax( _internalthreadargsprotocomma_ double , double );
 /* declare global and static user variables */
 #define gind 0
 #define _gth 0
#define u0 u0_Golgi_PF_syn
 double u0 = 0;
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 {"U", 0, 1},
 {"tau_facil", 0, 1e+09},
 {"tau_rec", 1e-09, 1e+09},
 {"tau_1", 1e-09, 1e+09},
 {"u0_Golgi_PF_syn", 0, 1},
 {0, 0, 0}
};
 static HocParmUnits _hoc_parm_units[] = {
 {"u0_Golgi_PF_syn", "1"},
 {"gmax", "pS"},
 {"U", "1"},
 {"tau_rec", "ms"},
 {"tau_facil", "ms"},
 {"Rd", "um"},
 {"Diff", "um2/ms"},
 {"Cdur", "ms"},
 {"r2", "/ms"},
 {"r3", "/ms"},
 {"r4", "/ms"},
 {"Erev", "mV"},
 {"kB", "mM"},
 {"tau_1", "ms"},
 {"Tmax", "mM"},
 {"lamd", "nm"},
 {"i", "nA"},
 {"ic", "nA"},
 {"g", "pS"},
 {"r1", "/ms"},
 {"r6", "/ms"},
 {"T", "mM"},
 {"Trelease", "mM"},
 {"tspike", "ms"},
 {0, 0}
};
 static double C0 = 0;
 static double D0 = 0;
 static double O0 = 0;
 static double delta_t = 0.01;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 {"u0_Golgi_PF_syn", &u0_Golgi_PF_syn},
 {0, 0}
};
 static DoubVec hoc_vdoub[] = {
 {0, 0, 0}
};
 static double _sav_indep;
 extern void _nrn_setdata_reg(int, void(*)(Prop*));
 static void _setdata(Prop* _prop) {
 }
 static void _hoc_setdata(void* _vptr) { Prop* _prop;
 _prop = ((Point_process*)_vptr)->_prop;
   _setdata(_prop);
 }
 static void nrn_alloc(Prop*);
static void nrn_init(_nrn_model_sorted_token const&, NrnThread*, Memb_list*, int);
static void nrn_state(_nrn_model_sorted_token const&, NrnThread*, Memb_list*, int);
 static void nrn_cur(_nrn_model_sorted_token const&, NrnThread*, Memb_list*, int);
static void nrn_jacob(_nrn_model_sorted_token const&, NrnThread*, Memb_list*, int);
 static void _hoc_destroy_pnt(void* _vptr) {
   destroy_point_process(_vptr);
}
 
static int _ode_count(int);
static void _ode_map(Prop*, int, neuron::container::data_handle<double>*, neuron::container::data_handle<double>*, double*, int);
static void _ode_spec(_nrn_model_sorted_token const&, NrnThread*, Memb_list*, int);
static void _ode_matsol(_nrn_model_sorted_token const&, NrnThread*, Memb_list*, int);
 
#define _cvode_ieq _ppvar[3].literal_value<int>()
 static void _ode_matsol_instance1(_internalthreadargsproto_);
 /* connect range variables in _p that hoc is supposed to know about */
 static const char *_mechanism[] = {
 "7.7.0",
"Golgi_PF_syn",
 "syntype",
 "gmax_factor",
 "Q10_diff",
 "Q10_channel",
 "gmax",
 "U",
 "tau_rec",
 "tau_facil",
 "M",
 "Rd",
 "Diff",
 "Cdur",
 "r1FIX",
 "r2",
 "r3",
 "r4",
 "r5",
 "r6FIX",
 "Erev",
 "kB",
 "tau_1",
 "Tmax",
 "diffuse",
 "lamd",
 "nd",
 0,
 "i",
 "ic",
 "g",
 "r1",
 "r6",
 "T",
 "Trelease",
 "tspike[800]",
 "x",
 "y_read",
 "z_read",
 "u_read",
 "PRE[800]",
 0,
 "C",
 "O",
 "D",
 0,
 0};
 
 /* Used by NrnProperty */
 static _nrn_mechanism_std_vector<double> _parm_default{
     0, /* syntype */
     1, /* gmax_factor */
     1.1, /* Q10_diff */
     2.4, /* Q10_channel */
     1200, /* gmax */
     0.4, /* U */
     35.1, /* tau_rec */
     54, /* tau_facil */
     21.515, /* M */
     1.03, /* Rd */
     0.223, /* Diff */
     0.3, /* Cdur */
     5.4, /* r1FIX */
     0.82, /* r2 */
     0, /* r3 */
     0, /* r4 */
     0.013, /* r5 */
     1.12, /* r6FIX */
     0, /* Erev */
     0.44, /* kB */
     6, /* tau_1 */
     1, /* Tmax */
     0, /* diffuse */
     20, /* lamd */
     1, /* nd */
 }; 
 
 
extern Prop* need_memb(Symbol*);
static void nrn_alloc(Prop* _prop) {
  Prop *prop_ion{};
  Datum *_ppvar{};
  if (nrn_point_prop_) {
    _nrn_mechanism_access_alloc_seq(_prop) = _nrn_mechanism_access_alloc_seq(nrn_point_prop_);
    _ppvar = _nrn_mechanism_access_dparam(nrn_point_prop_);
  } else {
   _ppvar = nrn_prop_datum_alloc(_mechtype, 4, _prop);
    _nrn_mechanism_access_dparam(_prop) = _ppvar;
     _nrn_mechanism_cache_instance _ml_real{_prop};
    auto* const _ml = &_ml_real;
    size_t const _iml{};
    assert(_nrn_mechanism_get_num_vars(_prop) == 53);
 	/*initialize range parameters*/
 	syntype = _parm_default[0]; /* 0 */
 	gmax_factor = _parm_default[1]; /* 1 */
 	Q10_diff = _parm_default[2]; /* 1.1 */
 	Q10_channel = _parm_default[3]; /* 2.4 */
 	gmax = _parm_default[4]; /* 1200 */
 	U = _parm_default[5]; /* 0.4 */
 	tau_rec = _parm_default[6]; /* 35.1 */
 	tau_facil = _parm_default[7]; /* 54 */
 	M = _parm_default[8]; /* 21.515 */
 	Rd = _parm_default[9]; /* 1.03 */
 	Diff = _parm_default[10]; /* 0.223 */
 	Cdur = _parm_default[11]; /* 0.3 */
 	r1FIX = _parm_default[12]; /* 5.4 */
 	r2 = _parm_default[13]; /* 0.82 */
 	r3 = _parm_default[14]; /* 0 */
 	r4 = _parm_default[15]; /* 0 */
 	r5 = _parm_default[16]; /* 0.013 */
 	r6FIX = _parm_default[17]; /* 1.12 */
 	Erev = _parm_default[18]; /* 0 */
 	kB = _parm_default[19]; /* 0.44 */
 	tau_1 = _parm_default[20]; /* 6 */
 	Tmax = _parm_default[21]; /* 1 */
 	diffuse = _parm_default[22]; /* 0 */
 	lamd = _parm_default[23]; /* 20 */
 	nd = _parm_default[24]; /* 1 */
  }
 	 assert(_nrn_mechanism_get_num_vars(_prop) == 53);
 	_nrn_mechanism_access_dparam(_prop) = _ppvar;
 	/*connect ionic variables to this model*/
 
}
 static void _initlists();
  /* some states have an absolute tolerance */
 static Symbol** _atollist;
 static HocStateTolerance _hoc_state_tol[] = {
 {0, 0}
};
 
#define _tqitem &(_ppvar[2])
 static void _net_receive(Point_process*, double*, double);
 static void _net_init(Point_process*, double*, double);
 static void _thread_cleanup(Datum*);
 extern Symbol* hoc_lookup(const char*);
extern void _nrn_thread_reg(int, int, void(*)(Datum*));
void _nrn_thread_table_reg(int, nrn_thread_table_check_t);
extern void hoc_register_tolerance(int, HocStateTolerance*, Symbol***);
extern void _cvode_abstol( Symbol**, double*, int);

 extern "C" void _GOLGI_Ampa_pf_aa_det_vi_reg() {
	int _vectorized = 1;
  _initlists();
 	_pointtype = point_register_mech(_mechanism,
	 nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init,
	 hoc_nrnpointerindex, 3,
	 _hoc_create_pnt, _hoc_destroy_pnt, _member_func);
  _extcall_thread.resize(2);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
 hoc_register_parm_default(_mechtype, &_parm_default);
     _nrn_setdata_reg(_mechtype, _setdata);
     _nrn_thread_reg(_mechtype, 0, _thread_cleanup);
 #if NMODL_TEXT
  register_nmodl_text_and_filename(_mechtype);
#endif
   _nrn_mechanism_register_data_fields(_mechtype,
                                       _nrn_mechanism_field<double>{"syntype"} /* 0 */,
                                       _nrn_mechanism_field<double>{"gmax_factor"} /* 1 */,
                                       _nrn_mechanism_field<double>{"Q10_diff"} /* 2 */,
                                       _nrn_mechanism_field<double>{"Q10_channel"} /* 3 */,
                                       _nrn_mechanism_field<double>{"gmax"} /* 4 */,
                                       _nrn_mechanism_field<double>{"U"} /* 5 */,
                                       _nrn_mechanism_field<double>{"tau_rec"} /* 6 */,
                                       _nrn_mechanism_field<double>{"tau_facil"} /* 7 */,
                                       _nrn_mechanism_field<double>{"M"} /* 8 */,
                                       _nrn_mechanism_field<double>{"Rd"} /* 9 */,
                                       _nrn_mechanism_field<double>{"Diff"} /* 10 */,
                                       _nrn_mechanism_field<double>{"Cdur"} /* 11 */,
                                       _nrn_mechanism_field<double>{"r1FIX"} /* 12 */,
                                       _nrn_mechanism_field<double>{"r2"} /* 13 */,
                                       _nrn_mechanism_field<double>{"r3"} /* 14 */,
                                       _nrn_mechanism_field<double>{"r4"} /* 15 */,
                                       _nrn_mechanism_field<double>{"r5"} /* 16 */,
                                       _nrn_mechanism_field<double>{"r6FIX"} /* 17 */,
                                       _nrn_mechanism_field<double>{"Erev"} /* 18 */,
                                       _nrn_mechanism_field<double>{"kB"} /* 19 */,
                                       _nrn_mechanism_field<double>{"tau_1"} /* 20 */,
                                       _nrn_mechanism_field<double>{"Tmax"} /* 21 */,
                                       _nrn_mechanism_field<double>{"diffuse"} /* 22 */,
                                       _nrn_mechanism_field<double>{"lamd"} /* 23 */,
                                       _nrn_mechanism_field<double>{"nd"} /* 24 */,
                                       _nrn_mechanism_field<double>{"i"} /* 25 */,
                                       _nrn_mechanism_field<double>{"ic"} /* 26 */,
                                       _nrn_mechanism_field<double>{"g"} /* 27 */,
                                       _nrn_mechanism_field<double>{"r1"} /* 28 */,
                                       _nrn_mechanism_field<double>{"r6"} /* 29 */,
                                       _nrn_mechanism_field<double>{"T"} /* 30 */,
                                       _nrn_mechanism_field<double>{"Trelease"} /* 31 */,
                                       _nrn_mechanism_field<double>{"tspike", 800} /* 32 */,
                                       _nrn_mechanism_field<double>{"x"} /* 33 */,
                                       _nrn_mechanism_field<double>{"y_read"} /* 34 */,
                                       _nrn_mechanism_field<double>{"z_read"} /* 35 */,
                                       _nrn_mechanism_field<double>{"u_read"} /* 36 */,
                                       _nrn_mechanism_field<double>{"PRE", 800} /* 37 */,
                                       _nrn_mechanism_field<double>{"C"} /* 38 */,
                                       _nrn_mechanism_field<double>{"O"} /* 39 */,
                                       _nrn_mechanism_field<double>{"D"} /* 40 */,
                                       _nrn_mechanism_field<double>{"tsyn"} /* 41 */,
                                       _nrn_mechanism_field<double>{"Mres"} /* 42 */,
                                       _nrn_mechanism_field<double>{"numpulses"} /* 43 */,
                                       _nrn_mechanism_field<double>{"tzero"} /* 44 */,
                                       _nrn_mechanism_field<double>{"gbar_Q10"} /* 45 */,
                                       _nrn_mechanism_field<double>{"Q10"} /* 46 */,
                                       _nrn_mechanism_field<double>{"DC"} /* 47 */,
                                       _nrn_mechanism_field<double>{"DO"} /* 48 */,
                                       _nrn_mechanism_field<double>{"DD"} /* 49 */,
                                       _nrn_mechanism_field<double>{"v"} /* 50 */,
                                       _nrn_mechanism_field<double>{"_g"} /* 51 */,
                                       _nrn_mechanism_field<double>{"_tsav"} /* 52 */,
                                       _nrn_mechanism_field<double*>{"_nd_area", "area"} /* 0 */,
                                       _nrn_mechanism_field<Point_process*>{"_pntproc", "pntproc"} /* 1 */,
                                       _nrn_mechanism_field<void*>{"_tqitem", "netsend"} /* 2 */,
                                       _nrn_mechanism_field<int>{"_cvode_ieq", "cvodeieq"} /* 3 */);
  hoc_register_prop_size(_mechtype, 1651, 4);
  hoc_register_dparam_semantics(_mechtype, 0, "area");
  hoc_register_dparam_semantics(_mechtype, 1, "pntproc");
  hoc_register_dparam_semantics(_mechtype, 2, "netsend");
  hoc_register_dparam_semantics(_mechtype, 3, "cvodeieq");
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 pnt_receive[_mechtype] = _net_receive;
 pnt_receive_init[_mechtype] = _net_init;
 pnt_receive_size[_mechtype] = 8;
 
    hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 Golgi_PF_syn /home/mjy/project/bilinear_network/basket/mod_files/GOLGI_Ampa_pf_aa_det_vi.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
 static double PI = 0x1.921fb54442d18p+1;
static int _reset;
static const char *modelname = "";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
 
#define _MATELM1(_row,_col) *(_nrn_thread_getelm(static_cast<SparseObj*>(_so), _row + 1, _col + 1))
 
#define _RHS1(_arg) _rhs[_arg+1]
  
#define _linmat1  1
 static int _spth1 = 1;
 static int _cvspth1 = 0;
 
static int _ode_spec1(_internalthreadargsproto_);
/*static int _ode_matsol1(_internalthreadargsproto_);*/
 static neuron::container::field_index _slist1[3], _dlist1[3]; static double *_temp1;
 static int kstates (void* _so, double* _rhs, _internalthreadargsproto_);
 
double imax ( _internalthreadargsprotocomma_ double _la , double _lb ) {
   double _limax;
 if ( _la > _lb ) {
     _limax = _la ;
     }
   else {
     _limax = _lb ;
     }
   
return _limax;
 }
 
static double _hoc_imax(void* _vptr) {
 double _r;
 Datum* _ppvar; Datum* _thread; NrnThread* _nt;
   auto* const _pnt = static_cast<Point_process*>(_vptr);
  auto* const _p = _pnt->_prop;
  if (!_p) {
    hoc_execerror("POINT_PROCESS data instance not valid", NULL);
  }
   _nrn_mechanism_cache_instance _ml_real{_p};
  auto* const _ml = &_ml_real;
  size_t const _iml{};
  _ppvar = _nrn_mechanism_access_dparam(_p);
  _thread = _extcall_thread.data();
  double* _globals = nullptr;
  if (gind != 0 && _thread != nullptr) { _globals = _thread[_gth].get<double*>(); }
  _nt = static_cast<NrnThread*>(_pnt->_vnt);
 _r =  imax ( _threadargscomma_ *getarg(1) , *getarg(2) );
 return(_r);
}
 
double diffusione ( _internalthreadargsproto_ ) {
   double _ldiffusione;
 double _lDifWave , _li , _lcntc , _lfi ;
 _lDifWave = 0.0 ;
   _lcntc = imax ( _threadargscomma_ numpulses - 5.0 , 0.0 ) ;
   {int  _li ;for ( _li = ((int) _lcntc ) ; _li <= ((int) numpulses ) ; _li ++ ) {
     _lfi = fmod ( ((double) _li ) , 800.0 ) ;
     tzero = tspike [ ((int) _lfi ) ] ;
     if ( t > tzero ) {
       _lDifWave = _lDifWave + PRE [ ((int) _lfi ) ] * Mres * exp ( - Rd * Rd / ( 4.0 * Diff * ( t - tzero ) ) ) / pow( ( ( 4.0 * PI * Diff * ( 1e-3 ) * lamd ) * ( t - tzero ) ) , nd ) ;
       }
     } }
   _ldiffusione = _lDifWave ;
   
return _ldiffusione;
 }
 
static double _hoc_diffusione(void* _vptr) {
 double _r;
 Datum* _ppvar; Datum* _thread; NrnThread* _nt;
   auto* const _pnt = static_cast<Point_process*>(_vptr);
  auto* const _p = _pnt->_prop;
  if (!_p) {
    hoc_execerror("POINT_PROCESS data instance not valid", NULL);
  }
   _nrn_mechanism_cache_instance _ml_real{_p};
  auto* const _ml = &_ml_real;
  size_t const _iml{};
  _ppvar = _nrn_mechanism_access_dparam(_p);
  _thread = _extcall_thread.data();
  double* _globals = nullptr;
  if (gind != 0 && _thread != nullptr) { _globals = _thread[_gth].get<double*>(); }
  _nt = static_cast<NrnThread*>(_pnt->_vnt);
 _r =  diffusione ( _threadargs_ );
 return(_r);
}
 
static int kstates (void* _so, double* _rhs, _internalthreadargsproto_)
 {int _reset=0;
 {
   double b_flux, f_flux, _term; int _i;
 {int _i; double _dt1 = 1.0/dt;
for(_i=1;_i<3;_i++){
  	_RHS1(_i) = -_dt1*(_ml->data(_iml, _slist1[_i]) - _ml->data(_iml, _dlist1[_i]));
	_MATELM1(_i, _i) = _dt1;
      
} }
 r1 = r1FIX * pow( Trelease , 2.0 ) / pow( ( Trelease + kB ) , 2.0 ) ;
   r6 = r6FIX * pow( Trelease , 2.0 ) / pow( ( Trelease + kB ) , 2.0 ) ;
   /* ~ C <-> O ( r1 * Q10 , r2 * Q10 )*/
 f_flux =  r1 * Q10 * C ;
 b_flux =  r2 * Q10 * O ;
 _RHS1( 1) -= (f_flux - b_flux);
 _RHS1( 2) += (f_flux - b_flux);
 
 _term =  r1 * Q10 ;
 _MATELM1( 1 ,1)  += _term;
 _MATELM1( 2 ,1)  -= _term;
 _term =  r2 * Q10 ;
 _MATELM1( 1 ,2)  -= _term;
 _MATELM1( 2 ,2)  += _term;
 /*REACTION*/
  /* ~ D <-> C ( r5 * Q10 , r6 * Q10 )*/
 f_flux =  r5 * Q10 * D ;
 b_flux =  r6 * Q10 * C ;
 _RHS1( 1) += (f_flux - b_flux);
 
 _term =  r5 * Q10 ;
 _MATELM1( 1 ,0)  -= _term;
 _term =  r6 * Q10 ;
 _MATELM1( 1 ,1)  += _term;
 /*REACTION*/
   /* C + O + D = 1.0 */
 _RHS1(0) =  1.0;
 _MATELM1(0, 0) = 1;
 _RHS1(0) -= D ;
 _MATELM1(0, 2) = 1;
 _RHS1(0) -= O ;
 _MATELM1(0, 1) = 1;
 _RHS1(0) -= C ;
 /*CONSERVATION*/
   } return _reset;
 }
 
static void _net_receive (Point_process* _pnt, double* _args, double _lflag) 
{  Prop* _p; Datum* _ppvar; Datum* _thread; NrnThread* _nt;
   _nrn_mechanism_cache_instance _ml_real{_pnt->_prop};
  auto* const _ml = &_ml_real;
  size_t const _iml{};
   _thread = nullptr; double* _globals = nullptr; _nt = (NrnThread*)_pnt->_vnt;   _ppvar = _nrn_mechanism_access_dparam(_pnt->_prop);
  if (_tsav > t){ hoc_execerror(hoc_object_name(_pnt->ob), ":Event arrived out of order. Must call ParallelContext.set_maxstep AFTER assigning minimum NetCon.delay");}
 _tsav = t;   if (_lflag == 1. ) {*(_tqitem) = nullptr;}
 {
   double _lfi ;
 if ( _lflag  == 0.0 ) {
     _args[2] = _args[2] + 1.0 ;
     if (  ! _args[1] ) {
       _args[3] = t ;
       _args[1] = 1.0 ;
       _args[5] = _args[5] * exp ( - ( t - _args[7] ) / ( tau_rec ) ) ;
       _args[5] = _args[5] + ( _args[4] * ( exp ( - ( t - _args[7] ) / tau_1 ) - exp ( - ( t - _args[7] ) / ( tau_rec ) ) ) / ( ( tau_1 / ( tau_rec ) ) - 1.0 ) ) ;
       _args[4] = _args[4] * exp ( - ( t - _args[7] ) / tau_1 ) ;
       x = 1.0 - _args[4] - _args[5] ;
       if ( tau_facil > 0.0 ) {
         _args[6] = _args[6] * exp ( - ( t - _args[7] ) / tau_facil ) ;
         _args[6] = _args[6] + U * ( 1.0 + 30.0 * _args[6] ) * ( exp ( - 5.0 * _args[6] ) - exp ( - 5.0 ) ) ;
         }
       else {
         _args[6] = U ;
         }
       _args[4] = _args[4] + x * _args[6] ;
       T = Tmax * _args[4] ;
       _lfi = fmod ( numpulses , 800.0 ) ;
       PRE [ ((int) _lfi ) ] = _args[4] ;
       y_read = _args[4] ;
       z_read = _args[5] ;
       u_read = _args[6] ;
       tspike [ ((int) _lfi ) ] = t ;
       numpulses = numpulses + 1.0 ;
       _args[7] = t ;
       }
     net_send ( _tqitem, _args, _pnt, t +  Cdur , _args[2] ) ;
     }
   if ( _lflag  == _args[2] ) {
     _args[3] = t ;
     T = 0.0 ;
     _args[1] = 0.0 ;
     }
   } }
 
static void _net_init(Point_process* _pnt, double* _args, double _lflag) {
     _nrn_mechanism_cache_instance _ml_real{_pnt->_prop};
  auto* const _ml = &_ml_real;
  size_t const _iml{};
  Datum* _ppvar = _nrn_mechanism_access_dparam(_pnt->_prop);
  Datum* _thread = nullptr;
  double* _globals = nullptr;
  NrnThread* _nt = (NrnThread*)_pnt->_vnt;
 _args[4] = 0.0 ;
   _args[5] = 0.0 ;
   _args[6] = u0 ;
   _args[7] = t ;
   _args[2] = 1.0 ;
   }
 
/*CVODE ode begin*/
 static int _ode_spec1(_internalthreadargsproto_) {
  int _reset=0;
  {
 double b_flux, f_flux, _term; int _i;
 {int _i; for(_i=0;_i<3;_i++) _ml->data(_iml, _dlist1[_i]) = 0.0;}
 r1 = r1FIX * pow( Trelease , 2.0 ) / pow( ( Trelease + kB ) , 2.0 ) ;
 r6 = r6FIX * pow( Trelease , 2.0 ) / pow( ( Trelease + kB ) , 2.0 ) ;
 /* ~ C <-> O ( r1 * Q10 , r2 * Q10 )*/
 f_flux =  r1 * Q10 * C ;
 b_flux =  r2 * Q10 * O ;
 DC -= (f_flux - b_flux);
 DO += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ D <-> C ( r5 * Q10 , r6 * Q10 )*/
 f_flux =  r5 * Q10 * D ;
 b_flux =  r6 * Q10 * C ;
 DD -= (f_flux - b_flux);
 DC += (f_flux - b_flux);
 
 /*REACTION*/
   /* C + O + D = 1.0 */
 /*CONSERVATION*/
   } return _reset;
 }
 
/*CVODE matsol*/
 static int _ode_matsol1(void* _so, double* _rhs, _internalthreadargsproto_) {int _reset=0;{
 double b_flux, f_flux, _term; int _i;
   b_flux = f_flux = 0.;
 {int _i; double _dt1 = 1.0/dt;
for(_i=0;_i<3;_i++){
  	_RHS1(_i) = _dt1*(_ml->data(_iml, _dlist1[_i]));
	_MATELM1(_i, _i) = _dt1;
      
} }
 r1 = r1FIX * pow( Trelease , 2.0 ) / pow( ( Trelease + kB ) , 2.0 ) ;
 r6 = r6FIX * pow( Trelease , 2.0 ) / pow( ( Trelease + kB ) , 2.0 ) ;
 /* ~ C <-> O ( r1 * Q10 , r2 * Q10 )*/
 _term =  r1 * Q10 ;
 _MATELM1( 1 ,1)  += _term;
 _MATELM1( 2 ,1)  -= _term;
 _term =  r2 * Q10 ;
 _MATELM1( 1 ,2)  -= _term;
 _MATELM1( 2 ,2)  += _term;
 /*REACTION*/
  /* ~ D <-> C ( r5 * Q10 , r6 * Q10 )*/
 _term =  r5 * Q10 ;
 _MATELM1( 0 ,0)  += _term;
 _MATELM1( 1 ,0)  -= _term;
 _term =  r6 * Q10 ;
 _MATELM1( 0 ,1)  -= _term;
 _MATELM1( 1 ,1)  += _term;
 /*REACTION*/
   /* C + O + D = 1.0 */
 /*CONSERVATION*/
   } return _reset;
 }
 
/*CVODE end*/
 
static int _ode_count(int _type){ return 3;}
 
static void _ode_spec(_nrn_model_sorted_token const& _sorted_token, NrnThread* _nt, Memb_list* _ml_arg, int _type) {
   Datum* _ppvar;
   size_t _iml;   _nrn_mechanism_cache_range* _ml;   Node* _nd{};
  double _v{};
  int _cntml;
  _nrn_mechanism_cache_range _lmr{_sorted_token, *_nt, *_ml_arg, _type};
  _ml = &_lmr;
  _cntml = _ml_arg->_nodecount;
  Datum *_thread{_ml_arg->_thread};
  double* _globals = nullptr;
  if (gind != 0 && _thread != nullptr) { _globals = _thread[_gth].get<double*>(); }
  for (_iml = 0; _iml < _cntml; ++_iml) {
    _ppvar = _ml_arg->_pdata[_iml];
    _nd = _ml_arg->_nodelist[_iml];
    v = NODEV(_nd);
     _ode_spec1 (_threadargs_);
 }}
 
static void _ode_map(Prop* _prop, int _ieq, neuron::container::data_handle<double>* _pv, neuron::container::data_handle<double>* _pvdot, double* _atol, int _type) { 
  Datum* _ppvar;
  _ppvar = _nrn_mechanism_access_dparam(_prop);
  _cvode_ieq = _ieq;
  for (int _i=0; _i < 3; ++_i) {
    _pv[_i] = _nrn_mechanism_get_param_handle(_prop, _slist1[_i]);
    _pvdot[_i] = _nrn_mechanism_get_param_handle(_prop, _dlist1[_i]);
    _cvode_abstol(_atollist, _atol, _i);
  }
 }
 
static void _ode_matsol_instance1(_internalthreadargsproto_) {
 _cvode_sparse_thread(&(_thread[_cvspth1].literal_value<void*>()), 3, _dlist1, neuron::scopmath::row_view{_ml, _iml}, _ode_matsol1, _threadargs_);
 }
 
static void _ode_matsol(_nrn_model_sorted_token const& _sorted_token, NrnThread* _nt, Memb_list* _ml_arg, int _type) {
   Datum* _ppvar;
   size_t _iml;   _nrn_mechanism_cache_range* _ml;   Node* _nd{};
  double _v{};
  int _cntml;
  _nrn_mechanism_cache_range _lmr{_sorted_token, *_nt, *_ml_arg, _type};
  _ml = &_lmr;
  _cntml = _ml_arg->_nodecount;
  Datum *_thread{_ml_arg->_thread};
  double* _globals = nullptr;
  if (gind != 0 && _thread != nullptr) { _globals = _thread[_gth].get<double*>(); }
  for (_iml = 0; _iml < _cntml; ++_iml) {
    _ppvar = _ml_arg->_pdata[_iml];
    _nd = _ml_arg->_nodelist[_iml];
    v = NODEV(_nd);
 _ode_matsol_instance1(_threadargs_);
 }}
 
static void _thread_cleanup(Datum* _thread) {
   _nrn_destroy_sparseobj_thread(static_cast<SparseObj*>(_thread[_cvspth1].get<void*>()));
   _nrn_destroy_sparseobj_thread(static_cast<SparseObj*>(_thread[_spth1].get<void*>()));
 }

static void initmodel(_internalthreadargsproto_) {
  int _i; double _save;{
  C = C0;
  D = D0;
  O = O0;
 {
   C = 1.0 ;
   O = 0.0 ;
   D = 0.0 ;
   T = 0.0 ;
   numpulses = 0.0 ;
   Trelease = 0.0 ;
   tspike [ 0 ] = 1e12 ;
   gbar_Q10 = pow( Q10_diff , ( ( celsius - 30.0 ) / 10.0 ) ) ;
   Q10 = pow( Q10_channel , ( ( celsius - 30.0 ) / 10.0 ) ) ;
   Mres = 1e3 * ( 1e3 * 1e15 / 6.022e23 * M ) ;
   numpulses = 0.0 ;
   {int  _li ;for ( _li = 1 ; _li <= 800 ; _li ++ ) {
     PRE [ _li - 1 ] = 0.0 ;
     tspike [ _li - 1 ] = 0.0 ;
     } }
   tspike [ 0 ] = 1e12 ;
   if ( tau_1 >= tau_rec ) {
     printf ( "Warning: tau_1 (%g) should never be higher neither equal to tau_rec (%g)!\n" , tau_1 , tau_rec ) ;
     tau_rec = tau_1 + 1e-5 ;
     }
   }
 
}
}

static void nrn_init(_nrn_model_sorted_token const& _sorted_token, NrnThread* _nt, Memb_list* _ml_arg, int _type){
_nrn_mechanism_cache_range _lmr{_sorted_token, *_nt, *_ml_arg, _type};
auto* const _vec_v = _nt->node_voltage_storage();
auto* const _ml = &_lmr;
Datum* _ppvar; Datum* _thread;
Node *_nd; double _v; int* _ni; int _iml, _cntml;
_ni = _ml_arg->_nodeindices;
_cntml = _ml_arg->_nodecount;
_thread = _ml_arg->_thread;
double* _globals = nullptr;
if (gind != 0 && _thread != nullptr) { _globals = _thread[_gth].get<double*>(); }
for (_iml = 0; _iml < _cntml; ++_iml) {
 _ppvar = _ml_arg->_pdata[_iml];
 _tsav = -1e20;
   _v = _vec_v[_ni[_iml]];
 v = _v;
 initmodel(_threadargs_);
}
}

static double _nrn_current(_internalthreadargsprotocomma_ double _v) {
double _current=0.; v=_v;
{ {
   if ( diffuse  && ( t > tspike [ 0 ] ) ) {
     Trelease = T + diffusione ( _threadargs_ ) ;
     }
   else {
     Trelease = T ;
     }
   g = gmax * gbar_Q10 * O ;
   i = ( 1e-6 ) * g * ( v - Erev ) * gmax_factor ;
   ic = i ;
   }
 _current += i;

} return _current;
}

static void nrn_cur(_nrn_model_sorted_token const& _sorted_token, NrnThread* _nt, Memb_list* _ml_arg, int _type) {
_nrn_mechanism_cache_range _lmr{_sorted_token, *_nt, *_ml_arg, _type};
auto const _vec_rhs = _nt->node_rhs_storage();
auto const _vec_sav_rhs = _nt->node_sav_rhs_storage();
auto const _vec_v = _nt->node_voltage_storage();
auto* const _ml = &_lmr;
Datum* _ppvar; Datum* _thread;
Node *_nd; int* _ni; double _rhs, _v; int _iml, _cntml;
_ni = _ml_arg->_nodeindices;
_cntml = _ml_arg->_nodecount;
_thread = _ml_arg->_thread;
double* _globals = nullptr;
if (gind != 0 && _thread != nullptr) { _globals = _thread[_gth].get<double*>(); }
for (_iml = 0; _iml < _cntml; ++_iml) {
 _ppvar = _ml_arg->_pdata[_iml];
   _v = _vec_v[_ni[_iml]];
 auto const _g_local = _nrn_current(_threadargscomma_ _v + .001);
 	{ _rhs = _nrn_current(_threadargscomma_ _v);
 	}
 _g = (_g_local - _rhs)/.001;
 _g *=  1.e2/(_nd_area);
 _rhs *= 1.e2/(_nd_area);
	 _vec_rhs[_ni[_iml]] -= _rhs;
 
}
 
}

static void nrn_jacob(_nrn_model_sorted_token const& _sorted_token, NrnThread* _nt, Memb_list* _ml_arg, int _type) {
_nrn_mechanism_cache_range _lmr{_sorted_token, *_nt, *_ml_arg, _type};
auto const _vec_d = _nt->node_d_storage();
auto const _vec_sav_d = _nt->node_sav_d_storage();
auto* const _ml = &_lmr;
Datum* _ppvar; Datum* _thread;
Node *_nd; int* _ni; int _iml, _cntml;
_ni = _ml_arg->_nodeindices;
_cntml = _ml_arg->_nodecount;
_thread = _ml_arg->_thread;
double* _globals = nullptr;
if (gind != 0 && _thread != nullptr) { _globals = _thread[_gth].get<double*>(); }
for (_iml = 0; _iml < _cntml; ++_iml) {
  _vec_d[_ni[_iml]] += _g;
 
}
 
}

static void nrn_state(_nrn_model_sorted_token const& _sorted_token, NrnThread* _nt, Memb_list* _ml_arg, int _type) {
_nrn_mechanism_cache_range _lmr{_sorted_token, *_nt, *_ml_arg, _type};
auto* const _vec_v = _nt->node_voltage_storage();
auto* const _ml = &_lmr;
Datum* _ppvar; Datum* _thread;
Node *_nd; double _v = 0.0; int* _ni;
double _dtsav = dt;
if (secondorder) { dt *= 0.5; }
_ni = _ml_arg->_nodeindices;
size_t _cntml = _ml_arg->_nodecount;
_thread = _ml_arg->_thread;
double* _globals = nullptr;
if (gind != 0 && _thread != nullptr) { _globals = _thread[_gth].get<double*>(); }
for (size_t _iml = 0; _iml < _cntml; ++_iml) {
 _ppvar = _ml_arg->_pdata[_iml];
 _nd = _ml_arg->_nodelist[_iml];
   _v = _vec_v[_ni[_iml]];
 v=_v;
{
 {  sparse_thread(&(_thread[_spth1].literal_value<void*>()), 3, _slist1, _dlist1, neuron::scopmath::row_view{_ml, _iml}, &t, dt, kstates, _linmat1, _threadargs_);
     if (secondorder) {
    int _i;
    for (_i = 0; _i < 3; ++_i) {
      _ml->data(_iml, _slist1[_i]) += dt*_ml->data(_iml, _dlist1[_i]);
    }}
 }}}
 dt = _dtsav;
}

static void terminal(){}

static void _initlists(){
 int _i; static int _first = 1;
  if (!_first) return;
 _slist1[0] = {D_columnindex, 0};  _dlist1[0] = {DD_columnindex, 0};
 _slist1[1] = {C_columnindex, 0};  _dlist1[1] = {DC_columnindex, 0};
 _slist1[2] = {O_columnindex, 0};  _dlist1[2] = {DO_columnindex, 0};
_first = 0;
}

#if NMODL_TEXT
static void register_nmodl_text_and_filename(int mech_type) {
    const char* nmodl_filename = "/home/mjy/project/bilinear_network/basket/mod_files/GOLGI_Ampa_pf_aa_det_vi.mod";
    const char* nmodl_file_text = 
  "TITLE \n"
  "\n"
  "COMMENT\n"
  "ENDCOMMENT\n"
  "\n"
  "NEURON {\n"
  "	POINT_PROCESS Golgi_PF_syn\n"
  "	NONSPECIFIC_CURRENT i\n"
  "	RANGE Q10_diff,Q10_channel\n"
  "	RANGE R, g, ic\n"
  "	RANGE Cdur, Erev \n"
  "	RANGE r1FIX, r2, r3,r4,r5,gmax,r1,r6,r6FIX,kB\n"
  "	RANGE tau_1, tau_rec, tau_facil, U	 \n"
  "	RANGE PRE,T,Tmax,x\n"
  "	RANGE y_read,z_read,u_read\n"
  "	RANGE C,O,D\n"
  "		\n"
  "	RANGE diffuse,Trelease,lamd\n"
  "	RANGE M,Diff,Rd\n"
  "	\n"
  "	RANGE tspike\n"
  "	RANGE nd, syntype, gmax_factor\n"
  "}\n"
  "\n"
  "UNITS {\n"
  "	(nA) = (nanoamp)	\n"
  "	(mV) = (millivolt)\n"
  "	(umho) = (micromho)\n"
  "	(mM) = (milli/liter)\n"
  "	(pS) = (picosiemens)\n"
  "	(nS) = (nanosiemens)\n"
  "	(um) = (micrometer)\n"
  "	PI	= (pi)		(1)\n"
  "    }\n"
  "    \n"
  "    PARAMETER {\n"
  "	syntype\n"
  "	gmax_factor = 1\n"
  "	Q10_diff	= 1.1\n"
  "	Q10_channel	= 2.4\n"
  "	: Parametri Postsinaptici\n"
  "	gmax		= 1200   (pS)	\n"
  "\n"
  "	U 			= 0.4 (1) 	< 0, 1 >\n"
  "	tau_rec 	= 35.1 (ms) 	< 1e-9, 1e9 > 	 \n"
  "	tau_facil 	= 54 (ms) 	< 0, 1e9 > 	\n"
  "\n"
  "	M			= 21.515	: numero di (kilo) molecole in una vescicola		\n"
  "	Rd			= 1.03 (um)\n"
  "	Diff		= 0.223 (um2/ms)\n"
  "		 \n"
  "	Cdur		= 0.3	(ms)		 \n"
  "	r1FIX		= 5.4 : 1.66	(/ms/mM) \n"
  "	r2			= 0.82	(/ms)			 \n"
  "	r3			= 0		(/ms)		 \n"
  "	r4			= 0		(/ms)		 \n"
  "	r5			= 0.013 : 0.013	(/ms)			 \n"
  "	r6FIX		= 1.12 : 0.237	(/ms/mM)		 \n"
  "	Erev		= 0	(mV)\n"
  "	kB			= 0.44	(mM)\n"
  "\n"
  "	: Parametri Presinaptici\n"
  "	tau_1 		= 6 (ms) 	< 1e-9, 1e9 >\n"
  "	 \n"
  "\n"
  "	\n"
  "	u0 			= 0 (1) 	< 0, 1 >	: se u0=0 al primo colpo y=U\n"
  "	Tmax		= 1  (mM)	\n"
  "	\n"
  "	: Diffusion			\n"
  "	diffuse		= 0\n"
  "	\n"
  "	lamd		= 20 (nm)\n"
  "	nd			= 1\n"
  "	celsius (degC)\n"
  "}\n"
  "\n"
  "\n"
  "ASSIGNED {\n"
  "	v		(mV)		: postsynaptic voltage\n"
  "	i 		(nA)		: current = g*(v - Erev)\n"
  "	ic 		(nA)		: current = g*(v - Erev)\n"
  "	g 		(pS)		: conductance\n"
  "	r1		(/ms)\n"
  "	r6		(/ms)\n"
  "	T		(mM)\n"
  "\n"
  "	Trelease	(mM)\n"
  "	tspike[800]	(ms)\n"
  "	x \n"
  "	y_read\n"
  "	z_read\n"
  "	u_read\n"
  "	tsyn		(ms)\n"
  "	PRE[800]\n"
  "	\n"
  "	Mres		(mM)	\n"
  "	numpulses\n"
  "	tzero\n"
  "	gbar_Q10 (mho/cm2)\n"
  "	Q10 (1)\n"
  "}\n"
  "\n"
  "STATE {	\n"
  "	C\n"
  "	O\n"
  "	D\n"
  "}\n"
  "\n"
  "INITIAL {\n"
  "	C=1\n"
  "	O=0\n"
  "	D=0\n"
  "	T=0 (mM)\n"
  "	numpulses=0\n"
  "	Trelease=0 (mM)\n"
  "	tspike[0]=1e12	(ms)\n"
  "	 \n"
  "	gbar_Q10 = Q10_diff^((celsius-30)/10)\n"
  "	Q10 = Q10_channel^((celsius-30)/10)\n"
  "\n"
  "	: fattore di conversione che comprende molecole -> mM\n"
  "	: n molecole/(Na*V) -> M/(6.022e23*1dm^3)\n"
  "\n"
  "	Mres = 1e3 * ( 1e3 * 1e15 / 6.022e23 * M ) : (M) to (mM) so 1e3, 1um^3=1dm^3*1e-15 so 1e15	\n"
  "	numpulses=0\n"
  "\n"
  "	FROM i=1 TO 800 { PRE[i-1]=0 tspike[i-1]=0 }  \n"
  "	tspike[0]=1e12	(ms)\n"
  "	if(tau_1>=tau_rec){ \n"
  "		printf(\"Warning: tau_1 (%g) should never be higher neither equal to tau_rec (%g)!\\n\",tau_1,tau_rec)\n"
  "		tau_rec=tau_1+1e-5\n"
  "	    } \n"
  "	}\n"
  "		\n"
  "	FUNCTION imax(a,b) {\n"
  "	    if (a>b) { imax=a }\n"
  "	    else { imax=b }\n"
  "	}\n"
  "	\n"
  "FUNCTION diffusione(){	 \n"
  "	LOCAL DifWave,i,cntc,fi\n"
  "	DifWave=0\n"
  "	cntc=imax(numpulses-5,0)\n"
  "	FROM i=cntc  TO numpulses{\n"
  "	    :printf (\"%g %g  \",numpulses,fmod(numpulses,10))\n"
  "	    fi=fmod(i,800)\n"
  "	    :printf (\"%g %g %g __ \",i,numpulses,fi)\n"
  "	    tzero=tspike[fi]\n"
  "		if(t>tzero){\n"
  "			DifWave=DifWave+PRE[fi]*Mres*exp(-Rd*Rd/(4*Diff*(t-tzero)))/((4*PI*Diff*(1e-3)*lamd)*(t-tzero))^nd\n"
  "		    }\n"
  "		}	\n"
  "		:printf(\"\\n\\n\")\n"
  "	diffusione=DifWave\n"
  "}\n"
  "\n"
  "BREAKPOINT {\n"
  "\n"
  "	if ( diffuse && (t>tspike[0]) ) { Trelease= T + diffusione() } else { Trelease=T }\n"
  "\n"
  "	SOLVE kstates METHOD sparse\n"
  "	g = gmax * gbar_Q10 * O\n"
  "	i = (1e-6) * g * (v - Erev) * gmax_factor\n"
  "	ic = i\n"
  "}\n"
  "\n"
  "KINETIC kstates {\n"
  "	r1 = r1FIX * Trelease^2 / (Trelease + kB)^2\n"
  "	r6 = r6FIX * Trelease^2 / (Trelease + kB)^2\n"
  "	~ C  <-> O	(r1*Q10,r2*Q10)\n"
  "	:~ O  <-> D	(r3*Q10,r4*Q10) \n"
  "	~ D  <-> C	(r5*Q10,r6*Q10)\n"
  "	CONSERVE C+O+D = 1\n"
  "}\n"
  "\n"
  "\n"
  "NET_RECEIVE(weight, on, nspike, tzero (ms),y, z, u, tsyn (ms)) {LOCAL fi\n"
  "\n"
  ": *********** ATTENZIONE! ***********\n"
  ":\n"
  ": Qualora si vogliano utilizzare impulsi di glutammato saturanti e'\n"
  ": necessario che il pulse sia piu' corto dell'intera simulazione\n"
  ": altrimenti la variabile on non torna al suo valore di default.\n"
  "\n"
  "INITIAL {\n"
  "	y = 0\n"
  "	z = 0\n"
  "	u = u0\n"
  "	tsyn = t\n"
  "	nspike = 1\n"
  "}\n"
  "   if (flag == 0) { \n"
  "		: Qui faccio rientrare la modulazione presinaptica\n"
  "		nspike = nspike + 1\n"
  "		if (!on) {\n"
  "			tzero = t\n"
  "			on = 1				\n"
  "			z = z*exp( - (t - tsyn) / (tau_rec) )	 \n"
  "			z = z + ( y*(exp(-(t - tsyn)/tau_1) - exp(-(t - tsyn)/(tau_rec)))/((tau_1/(tau_rec))-1) )  \n"
  "			y = y*exp(-(t - tsyn)/tau_1)			\n"
  "			x = 1-y-z\n"
  "				\n"
  "			if (tau_facil > 0) { \n"
  "				u = u*exp(-(t - tsyn)/tau_facil)\n"
  "				u = u + U * (1+30*u) * (exp(-5*u)- exp(-5))\n"
  "			} else { u = U }\n"
  "			\n"
  "			y = y + x * u\n"
  "			\n"
  "			T=Tmax*y\n"
  "			fi=fmod(numpulses,800)\n"
  "			PRE[fi]=y	: PRE[numpulses]=y\n"
  "			y_read = y\n"
  "			z_read = z\n"
  "			u_read = u\n"
  "			:PRE=1	: Istruzione non necessaria ma se ommesso allora le copie dell'oggetto successive alla prima non funzionano!\n"
  "			:}\n"
  "			: all'inizio numpulses=0 !			\n"
  "			\n"
  "			tspike[fi] = t\n"
  "			numpulses=numpulses+1\n"
  "			tsyn = t\n"
  "			\n"
  "		}\n"
  "		net_send(Cdur, nspike)	 \n"
  "    }\n"
  "    if (flag == nspike) { \n"
  "		tzero = t\n"
  "		T = 0\n"
  "		on = 0\n"
  "    }\n"
  "}\n"
  "\n"
  ;
    hoc_reg_nmodl_filename(mech_type, nmodl_filename);
    hoc_reg_nmodl_text(mech_type, nmodl_file_text);
}
#endif
