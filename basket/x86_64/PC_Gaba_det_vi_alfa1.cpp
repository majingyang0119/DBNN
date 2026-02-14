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
static constexpr auto number_of_floating_point_variables = 72;
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
 
#define nrn_init _nrn_init__PC_gaba_alpha1
#define _nrn_initial _nrn_initial__PC_gaba_alpha1
#define nrn_cur _nrn_cur__PC_gaba_alpha1
#define _nrn_current _nrn_current__PC_gaba_alpha1
#define nrn_jacob _nrn_jacob__PC_gaba_alpha1
#define nrn_state _nrn_state__PC_gaba_alpha1
#define _net_receive _net_receive__PC_gaba_alpha1 
#define kstates kstates__PC_gaba_alpha1 
 
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
#define gmaxA1 _ml->template fpfield<2>(_iml)
#define gmaxA1_columnindex 2
#define Q10_diff _ml->template fpfield<3>(_iml)
#define Q10_diff_columnindex 3
#define Q10_channel _ml->template fpfield<4>(_iml)
#define Q10_channel_columnindex 4
#define Cdur _ml->template fpfield<5>(_iml)
#define Cdur_columnindex 5
#define kon _ml->template fpfield<6>(_iml)
#define kon_columnindex 6
#define koff _ml->template fpfield<7>(_iml)
#define koff_columnindex 7
#define d3 _ml->template fpfield<8>(_iml)
#define d3_columnindex 8
#define r3 _ml->template fpfield<9>(_iml)
#define r3_columnindex 9
#define d1d2 _ml->template fpfield<10>(_iml)
#define d1d2_columnindex 10
#define r1r2 _ml->template fpfield<11>(_iml)
#define r1r2_columnindex 11
#define a1 _ml->template fpfield<12>(_iml)
#define a1_columnindex 12
#define b1 _ml->template fpfield<13>(_iml)
#define b1_columnindex 13
#define a2 _ml->template fpfield<14>(_iml)
#define a2_columnindex 14
#define b2 _ml->template fpfield<15>(_iml)
#define b2_columnindex 15
#define r1 _ml->template fpfield<16>(_iml)
#define r1_columnindex 16
#define r2 _ml->template fpfield<17>(_iml)
#define r2_columnindex 17
#define d1 _ml->template fpfield<18>(_iml)
#define d1_columnindex 18
#define d2 _ml->template fpfield<19>(_iml)
#define d2_columnindex 19
#define Erev _ml->template fpfield<20>(_iml)
#define Erev_columnindex 20
#define tau_1 _ml->template fpfield<21>(_iml)
#define tau_1_columnindex 21
#define tau_rec _ml->template fpfield<22>(_iml)
#define tau_rec_columnindex 22
#define tau_facil _ml->template fpfield<23>(_iml)
#define tau_facil_columnindex 23
#define U _ml->template fpfield<24>(_iml)
#define U_columnindex 24
#define Tmax _ml->template fpfield<25>(_iml)
#define Tmax_columnindex 25
#define onSET _ml->template fpfield<26>(_iml)
#define onSET_columnindex 26
#define M _ml->template fpfield<27>(_iml)
#define M_columnindex 27
#define Rd _ml->template fpfield<28>(_iml)
#define Rd_columnindex 28
#define Diff _ml->template fpfield<29>(_iml)
#define Diff_columnindex 29
#define lamd _ml->template fpfield<30>(_iml)
#define lamd_columnindex 30
#define diff_flag _ml->template fpfield<31>(_iml)
#define diff_flag_columnindex 31
#define nd _ml->template fpfield<32>(_iml)
#define nd_columnindex 32
#define i _ml->template fpfield<33>(_iml)
#define i_columnindex 33
#define ic _ml->template fpfield<34>(_iml)
#define ic_columnindex 34
#define g _ml->template fpfield<35>(_iml)
#define g_columnindex 35
#define gA1 _ml->template fpfield<36>(_iml)
#define gA1_columnindex 36
#define Open _ml->template fpfield<37>(_iml)
#define Open_columnindex 37
#define diffus _ml->template fpfield<38>(_iml)
#define diffus_columnindex 38
#define T _ml->template fpfield<39>(_iml)
#define T_columnindex 39
#define Trelease _ml->template fpfield<40>(_iml)
#define Trelease_columnindex 40
#define xout _ml->template fpfield<41>(_iml)
#define xout_columnindex 41
#define yout _ml->template fpfield<42>(_iml)
#define yout_columnindex 42
#define zout _ml->template fpfield<43>(_iml)
#define zout_columnindex 43
#define uout _ml->template fpfield<44>(_iml)
#define uout_columnindex 44
#define C _ml->template fpfield<45>(_iml)
#define C_columnindex 45
#define CA1 _ml->template fpfield<46>(_iml)
#define CA1_columnindex 46
#define CA2 _ml->template fpfield<47>(_iml)
#define CA2_columnindex 47
#define DA1 _ml->template fpfield<48>(_iml)
#define DA1_columnindex 48
#define DA2 _ml->template fpfield<49>(_iml)
#define DA2_columnindex 49
#define DA2f _ml->template fpfield<50>(_iml)
#define DA2f_columnindex 50
#define OA1 _ml->template fpfield<51>(_iml)
#define OA1_columnindex 51
#define OA2 _ml->template fpfield<52>(_iml)
#define OA2_columnindex 52
#define Mres _ml->template fpfield<53>(_iml)
#define Mres_columnindex 53
#define tpre _ml->template fpfield<54>(_iml)
#define tpre_columnindex 54
#define tspike _ml->template data_array<55, 100>(_iml)
#define tspike_columnindex 55
#define PRE _ml->template data_array<56, 100>(_iml)
#define PRE_columnindex 56
#define numpulses _ml->template fpfield<57>(_iml)
#define numpulses_columnindex 57
#define tzero _ml->template fpfield<58>(_iml)
#define tzero_columnindex 58
#define gbar_Q10 _ml->template fpfield<59>(_iml)
#define gbar_Q10_columnindex 59
#define Q10 _ml->template fpfield<60>(_iml)
#define Q10_columnindex 60
#define DC _ml->template fpfield<61>(_iml)
#define DC_columnindex 61
#define DCA1 _ml->template fpfield<62>(_iml)
#define DCA1_columnindex 62
#define DCA2 _ml->template fpfield<63>(_iml)
#define DCA2_columnindex 63
#define DDA1 _ml->template fpfield<64>(_iml)
#define DDA1_columnindex 64
#define DDA2 _ml->template fpfield<65>(_iml)
#define DDA2_columnindex 65
#define DDA2f _ml->template fpfield<66>(_iml)
#define DDA2f_columnindex 66
#define DOA1 _ml->template fpfield<67>(_iml)
#define DOA1_columnindex 67
#define DOA2 _ml->template fpfield<68>(_iml)
#define DOA2_columnindex 68
#define v _ml->template fpfield<69>(_iml)
#define v_columnindex 69
#define _g _ml->template fpfield<70>(_iml)
#define _g_columnindex 70
#define _tsav _ml->template fpfield<71>(_iml)
#define _tsav_columnindex 71
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
#define diffusione diffusione_PC_gaba_alpha1
#define imax imax_PC_gaba_alpha1
 extern double diffusione( _internalthreadargsproto_ );
 extern double imax( _internalthreadargsprotocomma_ double , double );
 /* declare global and static user variables */
 #define gind 0
 #define _gth 0
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 {"U", 0, 1},
 {"tau_facil", 0, 1e+09},
 {"tau_rec", 1e-09, 1e+09},
 {"tau_1", 1e-09, 1e+09},
 {0, 0, 0}
};
 static HocParmUnits _hoc_parm_units[] = {
 {"gmaxA1", "pS"},
 {"Cdur", "ms"},
 {"kon", "/ms/mM"},
 {"koff", "/ms"},
 {"d3", "/ms"},
 {"r3", "/ms"},
 {"d1d2", "/ms/mM"},
 {"r1r2", "/ms"},
 {"a1", "/ms"},
 {"b1", "/ms"},
 {"a2", "/ms"},
 {"b2", "/ms"},
 {"r1", "/ms"},
 {"r2", "/ms"},
 {"d1", "/ms"},
 {"d2", "/ms"},
 {"Erev", "mV"},
 {"tau_1", "ms"},
 {"tau_rec", "ms"},
 {"tau_facil", "ms"},
 {"Tmax", "mM"},
 {"Rd", "um"},
 {"Diff", "um2/ms"},
 {"lamd", "nm"},
 {"i", "nA"},
 {"ic", "nA"},
 {"g", "pS"},
 {"gA1", "nA"},
 {"T", "mM"},
 {"Trelease", "mM"},
 {0, 0}
};
 static double CA20 = 0;
 static double CA10 = 0;
 static double C0 = 0;
 static double DA2f0 = 0;
 static double DA20 = 0;
 static double DA10 = 0;
 static double OA20 = 0;
 static double OA10 = 0;
 static double delta_t = 0.01;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
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
"PC_gaba_alpha1",
 "syntype",
 "gmax_factor",
 "gmaxA1",
 "Q10_diff",
 "Q10_channel",
 "Cdur",
 "kon",
 "koff",
 "d3",
 "r3",
 "d1d2",
 "r1r2",
 "a1",
 "b1",
 "a2",
 "b2",
 "r1",
 "r2",
 "d1",
 "d2",
 "Erev",
 "tau_1",
 "tau_rec",
 "tau_facil",
 "U",
 "Tmax",
 "onSET",
 "M",
 "Rd",
 "Diff",
 "lamd",
 "diff_flag",
 "nd",
 0,
 "i",
 "ic",
 "g",
 "gA1",
 "Open",
 "diffus",
 "T",
 "Trelease",
 "xout",
 "yout",
 "zout",
 "uout",
 0,
 "C",
 "CA1",
 "CA2",
 "DA1",
 "DA2",
 "DA2f",
 "OA1",
 "OA2",
 0,
 0};
 
 /* Used by NrnProperty */
 static _nrn_mechanism_std_vector<double> _parm_default{
     0, /* syntype */
     1, /* gmax_factor */
     918.807, /* gmaxA1 */
     1.5, /* Q10_diff */
     2.4, /* Q10_channel */
     0.3, /* Cdur */
     20, /* kon */
     2, /* koff */
     15, /* d3 */
     0.15, /* r3 */
     15, /* d1d2 */
     0.007, /* r1r2 */
     0.06, /* a1 */
     0.03, /* b1 */
     0.4, /* a2 */
     10, /* b2 */
     0.0007, /* r1 */
     0.006, /* r2 */
     0.00033, /* d1 */
     1.2, /* d2 */
     -60, /* Erev */
     0.1, /* tau_1 */
     36.169, /* tau_rec */
     58.517, /* tau_facil */
     0.35, /* U */
     1, /* Tmax */
     1, /* onSET */
     7.506, /* M */
     0.978, /* Rd */
     0.223, /* Diff */
     20, /* lamd */
     1, /* diff_flag */
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
    assert(_nrn_mechanism_get_num_vars(_prop) == 72);
 	/*initialize range parameters*/
 	syntype = _parm_default[0]; /* 0 */
 	gmax_factor = _parm_default[1]; /* 1 */
 	gmaxA1 = _parm_default[2]; /* 918.807 */
 	Q10_diff = _parm_default[3]; /* 1.5 */
 	Q10_channel = _parm_default[4]; /* 2.4 */
 	Cdur = _parm_default[5]; /* 0.3 */
 	kon = _parm_default[6]; /* 20 */
 	koff = _parm_default[7]; /* 2 */
 	d3 = _parm_default[8]; /* 15 */
 	r3 = _parm_default[9]; /* 0.15 */
 	d1d2 = _parm_default[10]; /* 15 */
 	r1r2 = _parm_default[11]; /* 0.007 */
 	a1 = _parm_default[12]; /* 0.06 */
 	b1 = _parm_default[13]; /* 0.03 */
 	a2 = _parm_default[14]; /* 0.4 */
 	b2 = _parm_default[15]; /* 10 */
 	r1 = _parm_default[16]; /* 0.0007 */
 	r2 = _parm_default[17]; /* 0.006 */
 	d1 = _parm_default[18]; /* 0.00033 */
 	d2 = _parm_default[19]; /* 1.2 */
 	Erev = _parm_default[20]; /* -60 */
 	tau_1 = _parm_default[21]; /* 0.1 */
 	tau_rec = _parm_default[22]; /* 36.169 */
 	tau_facil = _parm_default[23]; /* 58.517 */
 	U = _parm_default[24]; /* 0.35 */
 	Tmax = _parm_default[25]; /* 1 */
 	onSET = _parm_default[26]; /* 1 */
 	M = _parm_default[27]; /* 7.506 */
 	Rd = _parm_default[28]; /* 0.978 */
 	Diff = _parm_default[29]; /* 0.223 */
 	lamd = _parm_default[30]; /* 20 */
 	diff_flag = _parm_default[31]; /* 1 */
 	nd = _parm_default[32]; /* 1 */
  }
 	 assert(_nrn_mechanism_get_num_vars(_prop) == 72);
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

 extern "C" void _PC_Gaba_det_vi_alfa1_reg() {
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
                                       _nrn_mechanism_field<double>{"gmaxA1"} /* 2 */,
                                       _nrn_mechanism_field<double>{"Q10_diff"} /* 3 */,
                                       _nrn_mechanism_field<double>{"Q10_channel"} /* 4 */,
                                       _nrn_mechanism_field<double>{"Cdur"} /* 5 */,
                                       _nrn_mechanism_field<double>{"kon"} /* 6 */,
                                       _nrn_mechanism_field<double>{"koff"} /* 7 */,
                                       _nrn_mechanism_field<double>{"d3"} /* 8 */,
                                       _nrn_mechanism_field<double>{"r3"} /* 9 */,
                                       _nrn_mechanism_field<double>{"d1d2"} /* 10 */,
                                       _nrn_mechanism_field<double>{"r1r2"} /* 11 */,
                                       _nrn_mechanism_field<double>{"a1"} /* 12 */,
                                       _nrn_mechanism_field<double>{"b1"} /* 13 */,
                                       _nrn_mechanism_field<double>{"a2"} /* 14 */,
                                       _nrn_mechanism_field<double>{"b2"} /* 15 */,
                                       _nrn_mechanism_field<double>{"r1"} /* 16 */,
                                       _nrn_mechanism_field<double>{"r2"} /* 17 */,
                                       _nrn_mechanism_field<double>{"d1"} /* 18 */,
                                       _nrn_mechanism_field<double>{"d2"} /* 19 */,
                                       _nrn_mechanism_field<double>{"Erev"} /* 20 */,
                                       _nrn_mechanism_field<double>{"tau_1"} /* 21 */,
                                       _nrn_mechanism_field<double>{"tau_rec"} /* 22 */,
                                       _nrn_mechanism_field<double>{"tau_facil"} /* 23 */,
                                       _nrn_mechanism_field<double>{"U"} /* 24 */,
                                       _nrn_mechanism_field<double>{"Tmax"} /* 25 */,
                                       _nrn_mechanism_field<double>{"onSET"} /* 26 */,
                                       _nrn_mechanism_field<double>{"M"} /* 27 */,
                                       _nrn_mechanism_field<double>{"Rd"} /* 28 */,
                                       _nrn_mechanism_field<double>{"Diff"} /* 29 */,
                                       _nrn_mechanism_field<double>{"lamd"} /* 30 */,
                                       _nrn_mechanism_field<double>{"diff_flag"} /* 31 */,
                                       _nrn_mechanism_field<double>{"nd"} /* 32 */,
                                       _nrn_mechanism_field<double>{"i"} /* 33 */,
                                       _nrn_mechanism_field<double>{"ic"} /* 34 */,
                                       _nrn_mechanism_field<double>{"g"} /* 35 */,
                                       _nrn_mechanism_field<double>{"gA1"} /* 36 */,
                                       _nrn_mechanism_field<double>{"Open"} /* 37 */,
                                       _nrn_mechanism_field<double>{"diffus"} /* 38 */,
                                       _nrn_mechanism_field<double>{"T"} /* 39 */,
                                       _nrn_mechanism_field<double>{"Trelease"} /* 40 */,
                                       _nrn_mechanism_field<double>{"xout"} /* 41 */,
                                       _nrn_mechanism_field<double>{"yout"} /* 42 */,
                                       _nrn_mechanism_field<double>{"zout"} /* 43 */,
                                       _nrn_mechanism_field<double>{"uout"} /* 44 */,
                                       _nrn_mechanism_field<double>{"C"} /* 45 */,
                                       _nrn_mechanism_field<double>{"CA1"} /* 46 */,
                                       _nrn_mechanism_field<double>{"CA2"} /* 47 */,
                                       _nrn_mechanism_field<double>{"DA1"} /* 48 */,
                                       _nrn_mechanism_field<double>{"DA2"} /* 49 */,
                                       _nrn_mechanism_field<double>{"DA2f"} /* 50 */,
                                       _nrn_mechanism_field<double>{"OA1"} /* 51 */,
                                       _nrn_mechanism_field<double>{"OA2"} /* 52 */,
                                       _nrn_mechanism_field<double>{"Mres"} /* 53 */,
                                       _nrn_mechanism_field<double>{"tpre"} /* 54 */,
                                       _nrn_mechanism_field<double>{"tspike", 100} /* 55 */,
                                       _nrn_mechanism_field<double>{"PRE", 100} /* 56 */,
                                       _nrn_mechanism_field<double>{"numpulses"} /* 57 */,
                                       _nrn_mechanism_field<double>{"tzero"} /* 58 */,
                                       _nrn_mechanism_field<double>{"gbar_Q10"} /* 59 */,
                                       _nrn_mechanism_field<double>{"Q10"} /* 60 */,
                                       _nrn_mechanism_field<double>{"DC"} /* 61 */,
                                       _nrn_mechanism_field<double>{"DCA1"} /* 62 */,
                                       _nrn_mechanism_field<double>{"DCA2"} /* 63 */,
                                       _nrn_mechanism_field<double>{"DDA1"} /* 64 */,
                                       _nrn_mechanism_field<double>{"DDA2"} /* 65 */,
                                       _nrn_mechanism_field<double>{"DDA2f"} /* 66 */,
                                       _nrn_mechanism_field<double>{"DOA1"} /* 67 */,
                                       _nrn_mechanism_field<double>{"DOA2"} /* 68 */,
                                       _nrn_mechanism_field<double>{"v"} /* 69 */,
                                       _nrn_mechanism_field<double>{"_g"} /* 70 */,
                                       _nrn_mechanism_field<double>{"_tsav"} /* 71 */,
                                       _nrn_mechanism_field<double*>{"_nd_area", "area"} /* 0 */,
                                       _nrn_mechanism_field<Point_process*>{"_pntproc", "pntproc"} /* 1 */,
                                       _nrn_mechanism_field<void*>{"_tqitem", "netsend"} /* 2 */,
                                       _nrn_mechanism_field<int>{"_cvode_ieq", "cvodeieq"} /* 3 */);
  hoc_register_prop_size(_mechtype, 270, 4);
  hoc_register_dparam_semantics(_mechtype, 0, "area");
  hoc_register_dparam_semantics(_mechtype, 1, "pntproc");
  hoc_register_dparam_semantics(_mechtype, 2, "netsend");
  hoc_register_dparam_semantics(_mechtype, 3, "cvodeieq");
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 pnt_receive[_mechtype] = _net_receive;
 pnt_receive_init[_mechtype] = _net_init;
 pnt_receive_size[_mechtype] = 9;
 
    hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 PC_gaba_alpha1 /home/mjy/project/bilinear_network/basket/mod_files/PC_Gaba_det_vi_alfa1.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
 static double PI = 0x1.921fb54442d18p+1;
static int _reset;
static const char *modelname = "Gaba mod file only for fitting purpose ";

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
 static neuron::container::field_index _slist1[8], _dlist1[8]; static double *_temp1;
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
 double _lDifWave , _li , _lcntc , _lfi , _laaa ;
 _lDifWave = 0.0 ;
   _lcntc = imax ( _threadargscomma_ numpulses - 100.0 , 0.0 ) ;
   {int  _li ;for ( _li = ((int) _lcntc ) ; _li <= ((int) numpulses ) ; _li ++ ) {
     _lfi = fmod ( ((double) _li ) , 100.0 ) ;
     tzero = tspike [ ((int) _lfi ) ] ;
     if ( t > tzero ) {
       _laaa = ( - Rd * Rd / ( 4.0 * Diff * ( t - tzero ) ) ) ;
       if ( fabs ( _laaa ) < 699.0 ) {
         _lDifWave = _lDifWave + PRE [ ((int) _lfi ) ] * Mres * exp ( _laaa ) / ( ( 4.0 * PI * Diff * ( 1e-3 ) * lamd ) * ( t - tzero ) ) ;
         }
       else {
         if ( _laaa > 0.0 ) {
           _lDifWave = _lDifWave + PRE [ ((int) _lfi ) ] * Mres * exp ( 699.0 ) / ( ( 4.0 * PI * Diff * ( 1e-3 ) * lamd ) * ( t - tzero ) ) ;
           }
         else {
           _lDifWave = _lDifWave + PRE [ ((int) _lfi ) ] * Mres * exp ( - 699.0 ) / ( ( 4.0 * PI * Diff * ( 1e-3 ) * lamd ) * ( t - tzero ) ) ;
           }
         }
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
for(_i=1;_i<8;_i++){
  	_RHS1(_i) = -_dt1*(_ml->data(_iml, _slist1[_i]) - _ml->data(_iml, _dlist1[_i]));
	_MATELM1(_i, _i) = _dt1;
      
} }
 diffus = diffusione ( _threadargs_ ) ;
   Trelease = T ;
   /* ~ C <-> CA1 ( 2.0 * kon * Trelease * Q10 , koff * Q10 )*/
 f_flux =  2.0 * kon * Trelease * Q10 * C ;
 b_flux =  koff * Q10 * CA1 ;
 _RHS1( 3) -= (f_flux - b_flux);
 _RHS1( 2) += (f_flux - b_flux);
 
 _term =  2.0 * kon * Trelease * Q10 ;
 _MATELM1( 3 ,3)  += _term;
 _MATELM1( 2 ,3)  -= _term;
 _term =  koff * Q10 ;
 _MATELM1( 3 ,2)  -= _term;
 _MATELM1( 2 ,2)  += _term;
 /*REACTION*/
  /* ~ CA1 <-> CA2 ( kon * Trelease * Q10 , 2.0 * koff * Q10 )*/
 f_flux =  kon * Trelease * Q10 * CA1 ;
 b_flux =  2.0 * koff * Q10 * CA2 ;
 _RHS1( 2) -= (f_flux - b_flux);
 _RHS1( 1) += (f_flux - b_flux);
 
 _term =  kon * Trelease * Q10 ;
 _MATELM1( 2 ,2)  += _term;
 _MATELM1( 1 ,2)  -= _term;
 _term =  2.0 * koff * Q10 ;
 _MATELM1( 2 ,1)  -= _term;
 _MATELM1( 1 ,1)  += _term;
 /*REACTION*/
  /* ~ CA2 <-> DA2f ( d3 * Q10 , r3 * Q10 )*/
 f_flux =  d3 * Q10 * CA2 ;
 b_flux =  r3 * Q10 * DA2f ;
 _RHS1( 1) -= (f_flux - b_flux);
 _RHS1( 4) += (f_flux - b_flux);
 
 _term =  d3 * Q10 ;
 _MATELM1( 1 ,1)  += _term;
 _MATELM1( 4 ,1)  -= _term;
 _term =  r3 * Q10 ;
 _MATELM1( 1 ,4)  -= _term;
 _MATELM1( 4 ,4)  += _term;
 /*REACTION*/
  /* ~ DA1 <-> DA2 ( d1d2 * Trelease * Q10 , r1r2 * Q10 )*/
 f_flux =  d1d2 * Trelease * Q10 * DA1 ;
 b_flux =  r1r2 * Q10 * DA2 ;
 _RHS1( 6) -= (f_flux - b_flux);
 _RHS1( 5) += (f_flux - b_flux);
 
 _term =  d1d2 * Trelease * Q10 ;
 _MATELM1( 6 ,6)  += _term;
 _MATELM1( 5 ,6)  -= _term;
 _term =  r1r2 * Q10 ;
 _MATELM1( 6 ,5)  -= _term;
 _MATELM1( 5 ,5)  += _term;
 /*REACTION*/
  /* ~ OA1 <-> CA1 ( a1 * Q10 , b1 * Q10 )*/
 f_flux =  a1 * Q10 * OA1 ;
 b_flux =  b1 * Q10 * CA1 ;
 _RHS1( 7) -= (f_flux - b_flux);
 _RHS1( 2) += (f_flux - b_flux);
 
 _term =  a1 * Q10 ;
 _MATELM1( 7 ,7)  += _term;
 _MATELM1( 2 ,7)  -= _term;
 _term =  b1 * Q10 ;
 _MATELM1( 7 ,2)  -= _term;
 _MATELM1( 2 ,2)  += _term;
 /*REACTION*/
  /* ~ OA2 <-> CA2 ( a2 * Q10 , b2 * Q10 )*/
 f_flux =  a2 * Q10 * OA2 ;
 b_flux =  b2 * Q10 * CA2 ;
 _RHS1( 1) += (f_flux - b_flux);
 
 _term =  a2 * Q10 ;
 _MATELM1( 1 ,0)  -= _term;
 _term =  b2 * Q10 ;
 _MATELM1( 1 ,1)  += _term;
 /*REACTION*/
  /* ~ DA1 <-> CA1 ( r1 * Q10 , d1 * Q10 )*/
 f_flux =  r1 * Q10 * DA1 ;
 b_flux =  d1 * Q10 * CA1 ;
 _RHS1( 6) -= (f_flux - b_flux);
 _RHS1( 2) += (f_flux - b_flux);
 
 _term =  r1 * Q10 ;
 _MATELM1( 6 ,6)  += _term;
 _MATELM1( 2 ,6)  -= _term;
 _term =  d1 * Q10 ;
 _MATELM1( 6 ,2)  -= _term;
 _MATELM1( 2 ,2)  += _term;
 /*REACTION*/
  /* ~ DA2 <-> CA2 ( r2 * Q10 , d2 * Q10 )*/
 f_flux =  r2 * Q10 * DA2 ;
 b_flux =  d2 * Q10 * CA2 ;
 _RHS1( 5) -= (f_flux - b_flux);
 _RHS1( 1) += (f_flux - b_flux);
 
 _term =  r2 * Q10 ;
 _MATELM1( 5 ,5)  += _term;
 _MATELM1( 1 ,5)  -= _term;
 _term =  d2 * Q10 ;
 _MATELM1( 5 ,1)  -= _term;
 _MATELM1( 1 ,1)  += _term;
 /*REACTION*/
   /* C + CA1 + CA2 + DA1 + DA2 + DA2f + OA1 + OA2 = 1.0 */
 _RHS1(0) =  1.0;
 _MATELM1(0, 0) = 1;
 _RHS1(0) -= OA2 ;
 _MATELM1(0, 7) = 1;
 _RHS1(0) -= OA1 ;
 _MATELM1(0, 4) = 1;
 _RHS1(0) -= DA2f ;
 _MATELM1(0, 5) = 1;
 _RHS1(0) -= DA2 ;
 _MATELM1(0, 6) = 1;
 _RHS1(0) -= DA1 ;
 _MATELM1(0, 1) = 1;
 _RHS1(0) -= CA2 ;
 _MATELM1(0, 2) = 1;
 _RHS1(0) -= CA1 ;
 _MATELM1(0, 3) = 1;
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
 if ( onSET ) {
     _args[1] = 0.0 ;
     onSET = 0.0 ;
     }
   if ( _lflag  == 0.0 ) {
     _args[2] = _args[2] + 1.0 ;
     if (  ! _args[1] ) {
       _args[3] = t ;
       tpre = t ;
       _args[1] = 1.0 ;
       _args[6] = _args[6] * exp ( - ( t - _args[8] ) / tau_rec ) ;
       _args[6] = _args[6] + ( _args[5] * ( exp ( - ( t - _args[8] ) / tau_1 ) - exp ( - ( t - _args[8] ) / tau_rec ) ) / ( ( tau_1 / tau_rec ) - 1.0 ) ) ;
       _args[5] = _args[5] * exp ( - ( t - _args[8] ) / tau_1 ) ;
       _args[4] = 1.0 - _args[5] - _args[6] ;
       if ( tau_facil > 0.0 ) {
         _args[7] = _args[7] * exp ( - ( t - _args[8] ) / tau_facil ) ;
         _args[7] = _args[7] + U * ( 1.0 - _args[7] ) ;
         }
       else {
         _args[7] = U ;
         }
       _args[5] = _args[5] + _args[4] * _args[7] ;
       T = Tmax * _args[5] ;
       _lfi = fmod ( numpulses , 100.0 ) ;
       PRE [ ((int) _lfi ) ] = _args[5] ;
       tspike [ ((int) _lfi ) ] = t ;
       numpulses = numpulses + 1.0 ;
       _args[8] = t ;
       }
     net_send ( _tqitem, _args, _pnt, t +  Cdur , _args[2] ) ;
     }
   if ( _lflag  == _args[2] ) {
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
   _args[6] = 0.0 ;
   _args[7] = 0.0 ;
   xout = _args[4] ;
   yout = _args[5] ;
   zout = _args[6] ;
   uout = _args[7] ;
   _args[8] = t ;
   _args[2] = 1.0 ;
   }
 
/*CVODE ode begin*/
 static int _ode_spec1(_internalthreadargsproto_) {
  int _reset=0;
  {
 double b_flux, f_flux, _term; int _i;
 {int _i; for(_i=0;_i<8;_i++) _ml->data(_iml, _dlist1[_i]) = 0.0;}
 diffus = diffusione ( _threadargs_ ) ;
 Trelease = T ;
 /* ~ C <-> CA1 ( 2.0 * kon * Trelease * Q10 , koff * Q10 )*/
 f_flux =  2.0 * kon * Trelease * Q10 * C ;
 b_flux =  koff * Q10 * CA1 ;
 DC -= (f_flux - b_flux);
 DCA1 += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ CA1 <-> CA2 ( kon * Trelease * Q10 , 2.0 * koff * Q10 )*/
 f_flux =  kon * Trelease * Q10 * CA1 ;
 b_flux =  2.0 * koff * Q10 * CA2 ;
 DCA1 -= (f_flux - b_flux);
 DCA2 += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ CA2 <-> DA2f ( d3 * Q10 , r3 * Q10 )*/
 f_flux =  d3 * Q10 * CA2 ;
 b_flux =  r3 * Q10 * DA2f ;
 DCA2 -= (f_flux - b_flux);
 DDA2f += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ DA1 <-> DA2 ( d1d2 * Trelease * Q10 , r1r2 * Q10 )*/
 f_flux =  d1d2 * Trelease * Q10 * DA1 ;
 b_flux =  r1r2 * Q10 * DA2 ;
 DDA1 -= (f_flux - b_flux);
 DDA2 += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ OA1 <-> CA1 ( a1 * Q10 , b1 * Q10 )*/
 f_flux =  a1 * Q10 * OA1 ;
 b_flux =  b1 * Q10 * CA1 ;
 DOA1 -= (f_flux - b_flux);
 DCA1 += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ OA2 <-> CA2 ( a2 * Q10 , b2 * Q10 )*/
 f_flux =  a2 * Q10 * OA2 ;
 b_flux =  b2 * Q10 * CA2 ;
 DOA2 -= (f_flux - b_flux);
 DCA2 += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ DA1 <-> CA1 ( r1 * Q10 , d1 * Q10 )*/
 f_flux =  r1 * Q10 * DA1 ;
 b_flux =  d1 * Q10 * CA1 ;
 DDA1 -= (f_flux - b_flux);
 DCA1 += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ DA2 <-> CA2 ( r2 * Q10 , d2 * Q10 )*/
 f_flux =  r2 * Q10 * DA2 ;
 b_flux =  d2 * Q10 * CA2 ;
 DDA2 -= (f_flux - b_flux);
 DCA2 += (f_flux - b_flux);
 
 /*REACTION*/
   /* C + CA1 + CA2 + DA1 + DA2 + DA2f + OA1 + OA2 = 1.0 */
 /*CONSERVATION*/
   } return _reset;
 }
 
/*CVODE matsol*/
 static int _ode_matsol1(void* _so, double* _rhs, _internalthreadargsproto_) {int _reset=0;{
 double b_flux, f_flux, _term; int _i;
   b_flux = f_flux = 0.;
 {int _i; double _dt1 = 1.0/dt;
for(_i=0;_i<8;_i++){
  	_RHS1(_i) = _dt1*(_ml->data(_iml, _dlist1[_i]));
	_MATELM1(_i, _i) = _dt1;
      
} }
 diffus = diffusione ( _threadargs_ ) ;
 Trelease = T ;
 /* ~ C <-> CA1 ( 2.0 * kon * Trelease * Q10 , koff * Q10 )*/
 _term =  2.0 * kon * Trelease * Q10 ;
 _MATELM1( 3 ,3)  += _term;
 _MATELM1( 2 ,3)  -= _term;
 _term =  koff * Q10 ;
 _MATELM1( 3 ,2)  -= _term;
 _MATELM1( 2 ,2)  += _term;
 /*REACTION*/
  /* ~ CA1 <-> CA2 ( kon * Trelease * Q10 , 2.0 * koff * Q10 )*/
 _term =  kon * Trelease * Q10 ;
 _MATELM1( 2 ,2)  += _term;
 _MATELM1( 1 ,2)  -= _term;
 _term =  2.0 * koff * Q10 ;
 _MATELM1( 2 ,1)  -= _term;
 _MATELM1( 1 ,1)  += _term;
 /*REACTION*/
  /* ~ CA2 <-> DA2f ( d3 * Q10 , r3 * Q10 )*/
 _term =  d3 * Q10 ;
 _MATELM1( 1 ,1)  += _term;
 _MATELM1( 4 ,1)  -= _term;
 _term =  r3 * Q10 ;
 _MATELM1( 1 ,4)  -= _term;
 _MATELM1( 4 ,4)  += _term;
 /*REACTION*/
  /* ~ DA1 <-> DA2 ( d1d2 * Trelease * Q10 , r1r2 * Q10 )*/
 _term =  d1d2 * Trelease * Q10 ;
 _MATELM1( 6 ,6)  += _term;
 _MATELM1( 5 ,6)  -= _term;
 _term =  r1r2 * Q10 ;
 _MATELM1( 6 ,5)  -= _term;
 _MATELM1( 5 ,5)  += _term;
 /*REACTION*/
  /* ~ OA1 <-> CA1 ( a1 * Q10 , b1 * Q10 )*/
 _term =  a1 * Q10 ;
 _MATELM1( 7 ,7)  += _term;
 _MATELM1( 2 ,7)  -= _term;
 _term =  b1 * Q10 ;
 _MATELM1( 7 ,2)  -= _term;
 _MATELM1( 2 ,2)  += _term;
 /*REACTION*/
  /* ~ OA2 <-> CA2 ( a2 * Q10 , b2 * Q10 )*/
 _term =  a2 * Q10 ;
 _MATELM1( 0 ,0)  += _term;
 _MATELM1( 1 ,0)  -= _term;
 _term =  b2 * Q10 ;
 _MATELM1( 0 ,1)  -= _term;
 _MATELM1( 1 ,1)  += _term;
 /*REACTION*/
  /* ~ DA1 <-> CA1 ( r1 * Q10 , d1 * Q10 )*/
 _term =  r1 * Q10 ;
 _MATELM1( 6 ,6)  += _term;
 _MATELM1( 2 ,6)  -= _term;
 _term =  d1 * Q10 ;
 _MATELM1( 6 ,2)  -= _term;
 _MATELM1( 2 ,2)  += _term;
 /*REACTION*/
  /* ~ DA2 <-> CA2 ( r2 * Q10 , d2 * Q10 )*/
 _term =  r2 * Q10 ;
 _MATELM1( 5 ,5)  += _term;
 _MATELM1( 1 ,5)  -= _term;
 _term =  d2 * Q10 ;
 _MATELM1( 5 ,1)  -= _term;
 _MATELM1( 1 ,1)  += _term;
 /*REACTION*/
   /* C + CA1 + CA2 + DA1 + DA2 + DA2f + OA1 + OA2 = 1.0 */
 /*CONSERVATION*/
   } return _reset;
 }
 
/*CVODE end*/
 
static int _ode_count(int _type){ return 8;}
 
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
  for (int _i=0; _i < 8; ++_i) {
    _pv[_i] = _nrn_mechanism_get_param_handle(_prop, _slist1[_i]);
    _pvdot[_i] = _nrn_mechanism_get_param_handle(_prop, _dlist1[_i]);
    _cvode_abstol(_atollist, _atol, _i);
  }
 }
 
static void _ode_matsol_instance1(_internalthreadargsproto_) {
 _cvode_sparse_thread(&(_thread[_cvspth1].literal_value<void*>()), 8, _dlist1, neuron::scopmath::row_view{_ml, _iml}, _ode_matsol1, _threadargs_);
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
  CA2 = CA20;
  CA1 = CA10;
  C = C0;
  DA2f = DA2f0;
  DA2 = DA20;
  DA1 = DA10;
  OA2 = OA20;
  OA1 = OA10;
 {
   C = 1.0 ;
   CA1 = 0.0 ;
   CA2 = 0.0 ;
   DA1 = 0.0 ;
   DA2 = 0.0 ;
   DA2f = 0.0 ;
   OA1 = 0.0 ;
   OA2 = 0.0 ;
   Open = 0.0 ;
   T = 0.0 ;
   gbar_Q10 = pow( Q10_diff , ( ( celsius - 30.0 ) / 10.0 ) ) ;
   Q10 = pow( Q10_channel , ( ( celsius - 30.0 ) / 10.0 ) ) ;
   numpulses = 0.0 ;
   Mres = 1e3 * ( 1e3 * 1e15 / 6.022e23 * M ) ;
   {int  _li ;for ( _li = 1 ; _li <= 100 ; _li ++ ) {
     PRE [ _li - 1 ] = 0.0 ;
     tspike [ _li - 1 ] = 0.0 ;
     } }
   tspike [ 0 ] = 1e12 ;
   if ( tau_1 >= tau_rec ) {
     printf ( "Warning: tau_1 (%g) should never be higher neither equal to tau_rec (%g)!\n" , tau_1 , tau_rec ) ;
     tau_rec = tau_1 + 1e-5 ;
     }
   onSET = 1.0 ;
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
   Open = OA1 + OA2 ;
   gA1 = gmaxA1 * gbar_Q10 * Open ;
   g = gA1 * gmax_factor ;
   i = ( 1e-6 ) * g * ( v - Erev ) ;
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
 {  sparse_thread(&(_thread[_spth1].literal_value<void*>()), 8, _slist1, _dlist1, neuron::scopmath::row_view{_ml, _iml}, &t, dt, kstates, _linmat1, _threadargs_);
     if (secondorder) {
    int _i;
    for (_i = 0; _i < 8; ++_i) {
      _ml->data(_iml, _slist1[_i]) += dt*_ml->data(_iml, _dlist1[_i]);
    }}
 }}}
 dt = _dtsav;
}

static void terminal(){}

static void _initlists(){
 int _i; static int _first = 1;
  if (!_first) return;
 _slist1[0] = {OA2_columnindex, 0};  _dlist1[0] = {DOA2_columnindex, 0};
 _slist1[1] = {CA2_columnindex, 0};  _dlist1[1] = {DCA2_columnindex, 0};
 _slist1[2] = {CA1_columnindex, 0};  _dlist1[2] = {DCA1_columnindex, 0};
 _slist1[3] = {C_columnindex, 0};  _dlist1[3] = {DC_columnindex, 0};
 _slist1[4] = {DA2f_columnindex, 0};  _dlist1[4] = {DDA2f_columnindex, 0};
 _slist1[5] = {DA2_columnindex, 0};  _dlist1[5] = {DDA2_columnindex, 0};
 _slist1[6] = {DA1_columnindex, 0};  _dlist1[6] = {DDA1_columnindex, 0};
 _slist1[7] = {OA1_columnindex, 0};  _dlist1[7] = {DOA1_columnindex, 0};
_first = 0;
}

#if NMODL_TEXT
static void register_nmodl_text_and_filename(int mech_type) {
    const char* nmodl_filename = "/home/mjy/project/bilinear_network/basket/mod_files/PC_Gaba_det_vi_alfa1.mod";
    const char* nmodl_file_text = 
  "TITLE Gaba mod file only for fitting purpose \n"
  "\n"
  "COMMENT\n"
  "Thierry Nieus, unpublished results, please keep reserved.\n"
  "Variables with suffix \"_s\" are meant for single IPSC fit, with suffix \"_2\" for CGP experimental condition\n"
  "	Does not work with variable dt!\n"
  "ENDCOMMENT\n"
  "\n"
  "\n"
  "\n"
  "NEURON {\n"
  "	POINT_PROCESS PC_gaba_alpha1\n"
  "	 \n"
  "	NONSPECIFIC_CURRENT i\n"
  "	RANGE Q10_diff,Q10_channel\n"
  "	RANGE g, ic ,Cdur ,Tmax, Erev\n"
  "	RANGE Open\n"
  "\n"
  "	RANGE kon,koff,d3,r3,d1d2,r1r2,a1,b1,a2,b2,r1,r2,d1,d2\n"
  "\n"
  "	RANGE gmaxA1,onSET	\n"
  "	RANGE gA1\n"
  "\n"
  "	RANGE xout,yout,zout,uout	\n"
  "	\n"
  "	RANGE tau_1,tau_rec,tau_facil,U,T,U_2 \n"
  "	RANGE diff_flag,diff_flag2,M,Rd,Diff,lamd\n"
  "	RANGE nd,diffus ,Trelease, gmax_factor, syntype \n"
  "	RANGE C, CA1, CA2, DA1, DA2, DA2f, OA1, OA2	\n"
  "}\n"
  "\n"
  "UNITS {\n"
  "	(nA) 	= (nanoamp)\n"
  "	(mV) 	= (millivolt)\n"
  "	(umho)  = (micromho)\n"
  "	(mM) 	= (milli/liter)\n"
  "	(pS) 	= (picosiemens)\n"
  "	PI   	= (pi)(1)\n"
  "    }\n"
  "    \n"
  "    \n"
  "    \n"
  "    PARAMETER {\n"
  "	syntype\n"
  "	gmax_factor = 1\n"
  "	: Parametri Postsinaptici\n"
  "	gmaxA1	= 918.807	(pS)	\n"
  "	Q10_diff	= 1.5\n"
  "	Q10_channel	= 2.4\n"
  "	Cdur	= 0.3		(ms)	\n"
  "\n"
  "	: A1 kinetic rates EC50=(around) 20 uM, U=0.35\n"
  "	kon	= 20		(/ms/mM)	: 20\n"
  "	koff	= 2		(/ms) 		 \n"
  "	d3	= 15		(/ms) 	: 15	 \n"
  "	r3	= 0.15		(/ms) 	: 0.15, use 3.75 for slices in the PR model\n"
  "	d1d2	= 15		(/ms/mM) : 15	\n"
  "	r1r2	= 0.007		(/ms)	: 0.007\n"
  "	a1	= 0.06		(/ms)	: 0.06\n"
  "	b1	= 0.03		(/ms)\n"
  "	a2	= 0.4		(/ms)	: 0.4\n"
  "	b2	= 10		(/ms)	\n"
  "	r1	= 7e-4		(/ms)\n"
  "	r2	= 6e-3		(/ms)	: 6e-3\n"
  "	d1	= 3.3e-4	(/ms)\n"
  "	d2	= 1.2		(/ms)	: 1.2\n"
  "	\n"
  "	Erev	= -60		(mV)\n"
  "\n"
  "	: Parametri Presinaptici\n"
  "	tau_1 	= 0.1 		(ms) 	< 1e-9, 1e9 >\n"
  "	tau_rec = 36.169 	(ms) 	< 1e-9, 1e9 > 	:43.4\n"
  "	tau_facil = 58.517	(ms) 	< 0, 1e9 >	: 6.22 \n"
  "	U 	= 0.35			< 0, 1 >\n"
  "	 \n"
  "	\n"
  "	Tmax	= 1  		(mM)	\n"
  "	onSET	= 1\n"
  "	 \n"
  "		\n"
  "	: Diffusion parameters\n"
  "	: Diffusion: M=21.500, R=1.033, D=0.223, lamd=0.02 as in excitatory synapses	\n"
  "\n"
  "	M	= 7.506	: numero di (kilo) molecole in una vescicola	(52.76)	\n"
  "	Rd	= 0.978 (um)	:4.79	:4.96	: 4.96 (first fit!)\n"
  "	Diff	= 0.223 (um2/ms)\n"
  "\n"
  "	lamd	= 20 		(nm)\n"
  "	diff_flag	= 1			: flag diffusion on/off\n"
  "	 \n"
  "	nd		= 1			: kernel exponent of diffusion\n"
  "\n"
  "	 \n"
  "	celsius (degC)\n"
  "}\n"
  "\n"
  "\n"
  "ASSIGNED {\n"
  "	v		(mV)		: postsynaptic voltage\n"
  "	i 		(nA)		: current = g*(v - Erev)\n"
  "	ic 		(nA)		: current = g*(v - Erev)\n"
  "	g 		(pS)		: conductance\n"
  "	gA1		(nA)\n"
  "	\n"
  "	Open\n"
  "	diffus	\n"
  " \n"
  "	T		(mM)	\n"
  "	 \n"
  "	Trelease	(mM)\n"
  "	 	\n"
  "	Mres		(mM)	\n"
  "	tpre		(ms)\n"
  "\n"
  "	xout\n"
  "	yout\n"
  "	zout\n"
  "	uout\n"
  "	\n"
  "	tspike[100]	(ms)	: will be initialized by the pointprocess\n"
  "	PRE[100]\n"
  "	:PRE_2[500]\n"
  "	numpulses\n"
  "	tzero\n"
  "	gbar_Q10 (mho/cm2)\n"
  "	Q10 (1)\n"
  "}\n"
  "\n"
  "STATE {	\n"
  "	: CTRL - A1\n"
  "	C\n"
  "	CA1\n"
  "	CA2\n"
  "	DA1\n"
  "	DA2\n"
  "	DA2f\n"
  "	OA1\n"
  "	OA2	\n"
  " \n"
  "}\n"
  "\n"
  "INITIAL {\n"
  "	: CTRL - A1\n"
  "	C=1\n"
  "	CA1=0\n"
  "	CA2=0\n"
  "	DA1=0\n"
  "	DA2=0\n"
  "	DA2f=0\n"
  "	OA1=0  	\n"
  "	OA2=0\n"
  "\n"
  " \n"
  "	Open=0\n"
  "	  \n"
  "	T=0 		(mM)\n"
  "	\n"
  "	gbar_Q10 = Q10_diff^((celsius-30)/10)\n"
  "	Q10 = Q10_channel^((celsius-30)/10)\n"
  " \n"
  "	numpulses=0\n"
  "	Mres=1e3* (1e3 * 1e15 / 6.022e23 * M)     : (M) to (mM) so 1e3, 1um^3=1dm^3*1e-15 so 1e15\n"
  "	FROM i=1 TO 100 { PRE[i-1]=0 tspike[i-1]=0 } :PRE_2[500]=0}\n"
  "	tspike[0]=1e12	(ms)\n"
  "	if(tau_1>=tau_rec){ \n"
  "		printf(\"Warning: tau_1 (%g) should never be higher neither equal to tau_rec (%g)!\\n\",tau_1,tau_rec)\n"
  "		tau_rec=tau_1+1e-5\n"
  "		:printf(\"tau_rec has been set to %g\\n\",tau_rec) \n"
  "	} \n"
  "	onSET	= 1\n"
  "	 \n"
  "}\n"
  "	FUNCTION imax(a,b) {\n"
  "	    if (a>b) { imax=a }\n"
  "	    else { imax=b }\n"
  "	}\n"
  "	\n"
  "FUNCTION diffusione(){	 \n"
  "	LOCAL DifWave,i,cntc,fi,aaa\n"
  "	DifWave=0\n"
  "	cntc=imax(numpulses-100,0)\n"
  "	FROM i=cntc  TO numpulses{\n"
  "	    fi=fmod(i,100)\n"
  "	    tzero=tspike[fi]\n"
  "		if(t>tzero){\n"
  "		    aaa = (-Rd*Rd/(4*Diff*(t-tzero)))\n"
  "		    if(fabs(aaa)<699){\n"
  "			DifWave=DifWave+PRE[fi]*Mres*exp(aaa)/((4*PI*Diff*(1e-3)*lamd)*(t-tzero)) : ^nd nd =1\n"
  "		    }else{\n"
  "			if(aaa>0){\n"
  "			    DifWave=DifWave+PRE[fi]*Mres*exp(699)/((4*PI*Diff*(1e-3)*lamd)*(t-tzero)) : ^nd nd =1\n"
  "			}else{\n"
  "			    DifWave=DifWave+PRE[fi]*Mres*exp(-699)/((4*PI*Diff*(1e-3)*lamd)*(t-tzero)) : ^nd nd =1\n"
  "			}\n"
  "		    }\n"
  "		}\n"
  "	}	\n"
  "	diffusione=DifWave\n"
  "}\n"
  "\n"
  "\n"
  "\n"
  "BREAKPOINT {\n"
  "	SOLVE kstates METHOD sparse\n"
  "	\n"
  "	Open=OA1+OA2\n"
  "	\n"
  "	gA1 = gmaxA1 * gbar_Q10 * Open\n"
  "	\n"
  "	g = gA1 * gmax_factor\n"
  "	\n"
  "	i = (1e-6) * g * ( v - Erev )\n"
  "	ic = i\n"
  "}\n"
  "\n"
  "KINETIC kstates {\n"
  "\n"
  "	: ************\n"
  "	: *** CTRL ***	\n"
  "	: ************\n"
  "	\n"
  "\n"
  "	diffus=diffusione() 	\n"
  "	Trelease = T :+ diffus\n"
  "	\n"
  "	:	***	ALFA 1 *** \n"
  "	\n"
  "	: second row\n"
  "	~	C  	<-> 	CA1	(2*kon*Trelease*Q10,koff*Q10)\n"
  "	~	CA1 	<-> 	CA2	(kon*Trelease*Q10,2*koff*Q10)\n"
  "	~	CA2	<->	DA2f	(d3*Q10,r3*Q10)\n"
  "	: third row\n"
  "	~ 	DA1  	<-> 	DA2	(d1d2*Trelease*Q10,r1r2*Q10)\n"
  "	: first <=> second row\n"
  "	~ 	OA1  	<-> 	CA1	(a1*Q10,b1*Q10)\n"
  "	~ 	OA2  	<-> 	CA2	(a2*Q10,b2*Q10)\n"
  "	: third <=> second row\n"
  "	~	DA1	<->	CA1	(r1*Q10,d1*Q10)\n"
  "	~	DA2	<->	CA2	(r2*Q10,d2*Q10)	\n"
  "	CONSERVE C+CA1+CA2+DA1+DA2+DA2f+OA1+OA2=1\n"
  "	\n"
  "}\n"
  "\n"
  "\n"
  "NET_RECEIVE(weight,on, nspike,tzero (ms),x,y,z,u, tsyn (ms)) {LOCAL fi\n"
  "	INITIAL {\n"
  "		x = 0\n"
  "		y = 0\n"
  "		z = 0\n"
  "		u = 0 \n"
  "		 		\n"
  "		xout=x\n"
  "		yout=y\n"
  "		zout=z\n"
  "		uout=u\n"
  "		tsyn = t\n"
  "		nspike = 1\n"
  "	}\n"
  "\n"
  "	if(onSET){\n"
  "		on=0 \n"
  "		onSET=0\n"
  "		 \n"
  "	}\n"
  "	\n"
  "	if (flag == 0) { \n"
  "		: Qui faccio rientrare la modulazione presinaptica\n"
  "		nspike = nspike + 1\n"
  "		:printf(\"T = %g (mM)\\n\",Trelease)\n"
  "		if (!on) {\n"
  "			tzero = t	\n"
  "			tpre=t	: activates diffusion\n"
  "			on = 1		\n"
  "					\n"
  "			z = z*exp(-(t - tsyn)/tau_rec)		\n"
  "			z = z + ( y*(exp(-(t - tsyn)/tau_1) - exp(-(t - tsyn)/tau_rec)) / ((tau_1/tau_rec)-1) )\n"
  "			y = y*exp(-(t - tsyn)/tau_1)			\n"
  "			x = 1-y-z			\n"
  "			if (tau_facil > 0) { \n"
  "				u = u*exp(-(t - tsyn)/tau_facil)\n"
  "				u = u + U * ( 1 - u )							\n"
  "			} else { u = U }\n"
  "			y = y + x * u\n"
  "			T=Tmax*y\n"
  "			:printf(\"T = %g (mM)\\n\",T)\n"
  "\n"
  "			 \n"
  "				\n"
  "			fi=fmod(numpulses,100)\n"
  "			PRE[fi]=y	: PRE[numpulses]=y\n"
  "			 \n"
  "			tspike[fi] = t\n"
  "			numpulses=numpulses+1\n"
  "\n"
  "			 \n"
  "\n"
  "			tsyn = t			\n"
  "		}\n"
  "		net_send(Cdur, nspike)\n"
  "		 \n"
  "	}\n"
  "\n"
  "	if (flag == nspike) { \n"
  "		T = 0\n"
  "		 \n"
  "		on = 0\n"
  "	}\n"
  "}\n"
  ;
    hoc_reg_nmodl_filename(mech_type, nmodl_filename);
    hoc_reg_nmodl_text(mech_type, nmodl_file_text);
}
#endif
