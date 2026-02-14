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
static constexpr auto number_of_floating_point_variables = 67;
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
 
#define nrn_init _nrn_init__SC_NMDA_NR2B
#define _nrn_initial _nrn_initial__SC_NMDA_NR2B
#define nrn_cur _nrn_cur__SC_NMDA_NR2B
#define _nrn_current _nrn_current__SC_NMDA_NR2B
#define nrn_jacob _nrn_jacob__SC_NMDA_NR2B
#define nrn_state _nrn_state__SC_NMDA_NR2B
#define _net_receive _net_receive__SC_NMDA_NR2B 
#define _f_rates _f_rates__SC_NMDA_NR2B 
#define kstates kstates__SC_NMDA_NR2B 
#define rates rates__SC_NMDA_NR2B 
 
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
#define gmax _ml->template fpfield<2>(_iml)
#define gmax_columnindex 2
#define Q10_diff _ml->template fpfield<3>(_iml)
#define Q10_diff_columnindex 3
#define Q10_channel _ml->template fpfield<4>(_iml)
#define Q10_channel_columnindex 4
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
#define tau_1 _ml->template fpfield<11>(_iml)
#define tau_1_columnindex 11
#define u0 _ml->template fpfield<12>(_iml)
#define u0_columnindex 12
#define Tmax _ml->template fpfield<13>(_iml)
#define Tmax_columnindex 13
#define Cdur _ml->template fpfield<14>(_iml)
#define Cdur_columnindex 14
#define Koff _ml->template fpfield<15>(_iml)
#define Koff_columnindex 15
#define Kon _ml->template fpfield<16>(_iml)
#define Kon_columnindex 16
#define aKoff _ml->template fpfield<17>(_iml)
#define aKoff_columnindex 17
#define Kdam _ml->template fpfield<18>(_iml)
#define Kdam_columnindex 18
#define Kda _ml->template fpfield<19>(_iml)
#define Kda_columnindex 19
#define Kdbm _ml->template fpfield<20>(_iml)
#define Kdbm_columnindex 20
#define Kdb _ml->template fpfield<21>(_iml)
#define Kdb_columnindex 21
#define Kf _ml->template fpfield<22>(_iml)
#define Kf_columnindex 22
#define Kfm _ml->template fpfield<23>(_iml)
#define Kfm_columnindex 23
#define Ks _ml->template fpfield<24>(_iml)
#define Ks_columnindex 24
#define Ksm _ml->template fpfield<25>(_iml)
#define Ksm_columnindex 25
#define Erev _ml->template fpfield<26>(_iml)
#define Erev_columnindex 26
#define v0_block _ml->template fpfield<27>(_iml)
#define v0_block_columnindex 27
#define k_block _ml->template fpfield<28>(_iml)
#define k_block_columnindex 28
#define nd _ml->template fpfield<29>(_iml)
#define nd_columnindex 29
#define diffuse _ml->template fpfield<30>(_iml)
#define diffuse_columnindex 30
#define lamd _ml->template fpfield<31>(_iml)
#define lamd_columnindex 31
#define i _ml->template fpfield<32>(_iml)
#define i_columnindex 32
#define ic _ml->template fpfield<33>(_iml)
#define ic_columnindex 33
#define g _ml->template fpfield<34>(_iml)
#define g_columnindex 34
#define a _ml->template fpfield<35>(_iml)
#define a_columnindex 35
#define b _ml->template fpfield<36>(_iml)
#define b_columnindex 36
#define T _ml->template fpfield<37>(_iml)
#define T_columnindex 37
#define Trelease _ml->template fpfield<38>(_iml)
#define Trelease_columnindex 38
#define PRE _ml->template data_array<39, 100>(_iml)
#define PRE_columnindex 39
#define MgBlock _ml->template fpfield<40>(_iml)
#define MgBlock_columnindex 40
#define CC0 _ml->template fpfield<41>(_iml)
#define CC0_columnindex 41
#define CC1 _ml->template fpfield<42>(_iml)
#define CC1_columnindex 42
#define CC2 _ml->template fpfield<43>(_iml)
#define CC2_columnindex 43
#define C1 _ml->template fpfield<44>(_iml)
#define C1_columnindex 44
#define C2 _ml->template fpfield<45>(_iml)
#define C2_columnindex 45
#define D1 _ml->template fpfield<46>(_iml)
#define D1_columnindex 46
#define D2 _ml->template fpfield<47>(_iml)
#define D2_columnindex 47
#define O _ml->template fpfield<48>(_iml)
#define O_columnindex 48
#define x _ml->template fpfield<49>(_iml)
#define x_columnindex 49
#define tspike _ml->template data_array<50, 100>(_iml)
#define tspike_columnindex 50
#define Mres _ml->template fpfield<51>(_iml)
#define Mres_columnindex 51
#define numpulses _ml->template fpfield<52>(_iml)
#define numpulses_columnindex 52
#define tzero _ml->template fpfield<53>(_iml)
#define tzero_columnindex 53
#define gbar_Q10 _ml->template fpfield<54>(_iml)
#define gbar_Q10_columnindex 54
#define Q10 _ml->template fpfield<55>(_iml)
#define Q10_columnindex 55
#define DCC0 _ml->template fpfield<56>(_iml)
#define DCC0_columnindex 56
#define DCC1 _ml->template fpfield<57>(_iml)
#define DCC1_columnindex 57
#define DCC2 _ml->template fpfield<58>(_iml)
#define DCC2_columnindex 58
#define DC1 _ml->template fpfield<59>(_iml)
#define DC1_columnindex 59
#define DC2 _ml->template fpfield<60>(_iml)
#define DC2_columnindex 60
#define DD1 _ml->template fpfield<61>(_iml)
#define DD1_columnindex 61
#define DD2 _ml->template fpfield<62>(_iml)
#define DD2_columnindex 62
#define DO _ml->template fpfield<63>(_iml)
#define DO_columnindex 63
#define v _ml->template fpfield<64>(_iml)
#define v_columnindex 64
#define _g _ml->template fpfield<65>(_iml)
#define _g_columnindex 65
#define _tsav _ml->template fpfield<66>(_iml)
#define _tsav_columnindex 66
#define _nd_area *_ml->dptr_field<0>(_iml)
 /* Thread safe. No static _ml, _iml or _ppvar. */
 static int hoc_nrnpointerindex =  -1;
 static _nrn_mechanism_std_vector<Datum> _extcall_thread;
 /* external NEURON variables */
 extern double celsius;
 /* declaration of user functions */
 static double _hoc_diffusione(void*);
 static double _hoc_imax(void*);
 static double _hoc_rates(void*);
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
 {"rates", _hoc_rates},
 {0, 0}
};
#define diffusione diffusione_SC_NMDA_NR2B
#define imax imax_SC_NMDA_NR2B
 extern double diffusione( _internalthreadargsproto_ );
 extern double imax( _internalthreadargsprotocomma_ double , double );
 /* declare global and static user variables */
 #define gind 0
 #define _gth 0
#define aKon aKon_SC_NMDA_NR2B
 double aKon = 9.06;
#define kB kB_SC_NMDA_NR2B
 double kB = 0.44;
#define usetable usetable_SC_NMDA_NR2B
 double usetable = 1;
 
static void _check_rates(_internalthreadargsproto_); 
static void _check_table_thread(_threadargsprotocomma_ int _type, _nrn_model_sorted_token const& _sorted_token) {
  if (gind != 0 && _thread != nullptr) { _globals = _thread[_gth].get<double*>(); } 
  _nrn_mechanism_cache_range _lmr{_sorted_token, *_nt, *_ml, _type};
  {
    auto* const _ml = &_lmr;
   _check_rates(_threadargs_);
   }
}
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 {"U", 0, 1},
 {"tau_facil", 0, 1e+09},
 {"tau_rec", 1e-09, 1e+09},
 {"tau_1", 1e-09, 1e+09},
 {"usetable_SC_NMDA_NR2B", 0, 1},
 {"u0", 0, 1},
 {0, 0, 0}
};
 static HocParmUnits _hoc_parm_units[] = {
 {"aKon_SC_NMDA_NR2B", "/ms/mM"},
 {"kB_SC_NMDA_NR2B", "mM"},
 {"gmax", "pS"},
 {"U", "1"},
 {"tau_rec", "ms"},
 {"tau_facil", "ms"},
 {"Rd", "um"},
 {"Diff", "um2/ms"},
 {"tau_1", "ms"},
 {"u0", "1"},
 {"Tmax", "mM"},
 {"Cdur", "ms"},
 {"Koff", "/ms"},
 {"Kon", "/ms/mM"},
 {"aKoff", "/ms"},
 {"Kdam", "/ms"},
 {"Kda", "/ms"},
 {"Kdbm", "/ms"},
 {"Kdb", "/ms"},
 {"Kf", "/ms"},
 {"Kfm", "/ms"},
 {"Ks", "/ms"},
 {"Ksm", "/ms"},
 {"Erev", "mV"},
 {"v0_block", "mV"},
 {"k_block", "mV"},
 {"lamd", "nm"},
 {"i", "nA"},
 {"ic", "nA"},
 {"g", "pS"},
 {"a", "/ms"},
 {"b", "/ms"},
 {"T", "mM"},
 {"Trelease", "mM"},
 {0, 0}
};
 static double C20 = 0;
 static double C10 = 0;
 static double CC20 = 0;
 static double CC10 = 0;
 static double CC00 = 0;
 static double D20 = 0;
 static double D10 = 0;
 static double O0 = 0;
 static double delta_t = 0.01;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 {"aKon_SC_NMDA_NR2B", &aKon_SC_NMDA_NR2B},
 {"kB_SC_NMDA_NR2B", &kB_SC_NMDA_NR2B},
 {"usetable_SC_NMDA_NR2B", &usetable_SC_NMDA_NR2B},
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
"SC_NMDA_NR2B",
 "syntype",
 "gmax_factor",
 "gmax",
 "Q10_diff",
 "Q10_channel",
 "U",
 "tau_rec",
 "tau_facil",
 "M",
 "Rd",
 "Diff",
 "tau_1",
 "u0",
 "Tmax",
 "Cdur",
 "Koff",
 "Kon",
 "aKoff",
 "Kdam",
 "Kda",
 "Kdbm",
 "Kdb",
 "Kf",
 "Kfm",
 "Ks",
 "Ksm",
 "Erev",
 "v0_block",
 "k_block",
 "nd",
 "diffuse",
 "lamd",
 0,
 "i",
 "ic",
 "g",
 "a",
 "b",
 "T",
 "Trelease",
 "PRE[100]",
 "MgBlock",
 0,
 "CC0",
 "CC1",
 "CC2",
 "C1",
 "C2",
 "D1",
 "D2",
 "O",
 0,
 0};
 
 /* Used by NrnProperty */
 static _nrn_mechanism_std_vector<double> _parm_default{
     0, /* syntype */
     1, /* gmax_factor */
     18800, /* gmax */
     1.5, /* Q10_diff */
     2.4, /* Q10_channel */
     0.42, /* U */
     8, /* tau_rec */
     5, /* tau_facil */
     21.515, /* M */
     1.03, /* Rd */
     0.223, /* Diff */
     1, /* tau_1 */
     0, /* u0 */
     1, /* Tmax */
     0.3, /* Cdur */
     0.115, /* Koff */
     4.53, /* Kon */
     0.23, /* aKoff */
     0.245, /* Kdam */
     1.659, /* Kda */
     0.00274, /* Kdbm */
     0.338, /* Kdb */
     8.553, /* Kf */
     0.528, /* Kfm */
     0.145, /* Ks */
     0.694, /* Ksm */
     -3.7, /* Erev */
     -20, /* v0_block */
     13, /* k_block */
     1, /* nd */
     1, /* diffuse */
     20, /* lamd */
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
    assert(_nrn_mechanism_get_num_vars(_prop) == 67);
 	/*initialize range parameters*/
 	syntype = _parm_default[0]; /* 0 */
 	gmax_factor = _parm_default[1]; /* 1 */
 	gmax = _parm_default[2]; /* 18800 */
 	Q10_diff = _parm_default[3]; /* 1.5 */
 	Q10_channel = _parm_default[4]; /* 2.4 */
 	U = _parm_default[5]; /* 0.42 */
 	tau_rec = _parm_default[6]; /* 8 */
 	tau_facil = _parm_default[7]; /* 5 */
 	M = _parm_default[8]; /* 21.515 */
 	Rd = _parm_default[9]; /* 1.03 */
 	Diff = _parm_default[10]; /* 0.223 */
 	tau_1 = _parm_default[11]; /* 1 */
 	u0 = _parm_default[12]; /* 0 */
 	Tmax = _parm_default[13]; /* 1 */
 	Cdur = _parm_default[14]; /* 0.3 */
 	Koff = _parm_default[15]; /* 0.115 */
 	Kon = _parm_default[16]; /* 4.53 */
 	aKoff = _parm_default[17]; /* 0.23 */
 	Kdam = _parm_default[18]; /* 0.245 */
 	Kda = _parm_default[19]; /* 1.659 */
 	Kdbm = _parm_default[20]; /* 0.00274 */
 	Kdb = _parm_default[21]; /* 0.338 */
 	Kf = _parm_default[22]; /* 8.553 */
 	Kfm = _parm_default[23]; /* 0.528 */
 	Ks = _parm_default[24]; /* 0.145 */
 	Ksm = _parm_default[25]; /* 0.694 */
 	Erev = _parm_default[26]; /* -3.7 */
 	v0_block = _parm_default[27]; /* -20 */
 	k_block = _parm_default[28]; /* 13 */
 	nd = _parm_default[29]; /* 1 */
 	diffuse = _parm_default[30]; /* 1 */
 	lamd = _parm_default[31]; /* 20 */
  }
 	 assert(_nrn_mechanism_get_num_vars(_prop) == 67);
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

 extern "C" void _SC_NMDA_NR2B_reg() {
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
     _nrn_thread_table_reg(_mechtype, _check_table_thread);
 #if NMODL_TEXT
  register_nmodl_text_and_filename(_mechtype);
#endif
   _nrn_mechanism_register_data_fields(_mechtype,
                                       _nrn_mechanism_field<double>{"syntype"} /* 0 */,
                                       _nrn_mechanism_field<double>{"gmax_factor"} /* 1 */,
                                       _nrn_mechanism_field<double>{"gmax"} /* 2 */,
                                       _nrn_mechanism_field<double>{"Q10_diff"} /* 3 */,
                                       _nrn_mechanism_field<double>{"Q10_channel"} /* 4 */,
                                       _nrn_mechanism_field<double>{"U"} /* 5 */,
                                       _nrn_mechanism_field<double>{"tau_rec"} /* 6 */,
                                       _nrn_mechanism_field<double>{"tau_facil"} /* 7 */,
                                       _nrn_mechanism_field<double>{"M"} /* 8 */,
                                       _nrn_mechanism_field<double>{"Rd"} /* 9 */,
                                       _nrn_mechanism_field<double>{"Diff"} /* 10 */,
                                       _nrn_mechanism_field<double>{"tau_1"} /* 11 */,
                                       _nrn_mechanism_field<double>{"u0"} /* 12 */,
                                       _nrn_mechanism_field<double>{"Tmax"} /* 13 */,
                                       _nrn_mechanism_field<double>{"Cdur"} /* 14 */,
                                       _nrn_mechanism_field<double>{"Koff"} /* 15 */,
                                       _nrn_mechanism_field<double>{"Kon"} /* 16 */,
                                       _nrn_mechanism_field<double>{"aKoff"} /* 17 */,
                                       _nrn_mechanism_field<double>{"Kdam"} /* 18 */,
                                       _nrn_mechanism_field<double>{"Kda"} /* 19 */,
                                       _nrn_mechanism_field<double>{"Kdbm"} /* 20 */,
                                       _nrn_mechanism_field<double>{"Kdb"} /* 21 */,
                                       _nrn_mechanism_field<double>{"Kf"} /* 22 */,
                                       _nrn_mechanism_field<double>{"Kfm"} /* 23 */,
                                       _nrn_mechanism_field<double>{"Ks"} /* 24 */,
                                       _nrn_mechanism_field<double>{"Ksm"} /* 25 */,
                                       _nrn_mechanism_field<double>{"Erev"} /* 26 */,
                                       _nrn_mechanism_field<double>{"v0_block"} /* 27 */,
                                       _nrn_mechanism_field<double>{"k_block"} /* 28 */,
                                       _nrn_mechanism_field<double>{"nd"} /* 29 */,
                                       _nrn_mechanism_field<double>{"diffuse"} /* 30 */,
                                       _nrn_mechanism_field<double>{"lamd"} /* 31 */,
                                       _nrn_mechanism_field<double>{"i"} /* 32 */,
                                       _nrn_mechanism_field<double>{"ic"} /* 33 */,
                                       _nrn_mechanism_field<double>{"g"} /* 34 */,
                                       _nrn_mechanism_field<double>{"a"} /* 35 */,
                                       _nrn_mechanism_field<double>{"b"} /* 36 */,
                                       _nrn_mechanism_field<double>{"T"} /* 37 */,
                                       _nrn_mechanism_field<double>{"Trelease"} /* 38 */,
                                       _nrn_mechanism_field<double>{"PRE", 100} /* 39 */,
                                       _nrn_mechanism_field<double>{"MgBlock"} /* 40 */,
                                       _nrn_mechanism_field<double>{"CC0"} /* 41 */,
                                       _nrn_mechanism_field<double>{"CC1"} /* 42 */,
                                       _nrn_mechanism_field<double>{"CC2"} /* 43 */,
                                       _nrn_mechanism_field<double>{"C1"} /* 44 */,
                                       _nrn_mechanism_field<double>{"C2"} /* 45 */,
                                       _nrn_mechanism_field<double>{"D1"} /* 46 */,
                                       _nrn_mechanism_field<double>{"D2"} /* 47 */,
                                       _nrn_mechanism_field<double>{"O"} /* 48 */,
                                       _nrn_mechanism_field<double>{"x"} /* 49 */,
                                       _nrn_mechanism_field<double>{"tspike", 100} /* 50 */,
                                       _nrn_mechanism_field<double>{"Mres"} /* 51 */,
                                       _nrn_mechanism_field<double>{"numpulses"} /* 52 */,
                                       _nrn_mechanism_field<double>{"tzero"} /* 53 */,
                                       _nrn_mechanism_field<double>{"gbar_Q10"} /* 54 */,
                                       _nrn_mechanism_field<double>{"Q10"} /* 55 */,
                                       _nrn_mechanism_field<double>{"DCC0"} /* 56 */,
                                       _nrn_mechanism_field<double>{"DCC1"} /* 57 */,
                                       _nrn_mechanism_field<double>{"DCC2"} /* 58 */,
                                       _nrn_mechanism_field<double>{"DC1"} /* 59 */,
                                       _nrn_mechanism_field<double>{"DC2"} /* 60 */,
                                       _nrn_mechanism_field<double>{"DD1"} /* 61 */,
                                       _nrn_mechanism_field<double>{"DD2"} /* 62 */,
                                       _nrn_mechanism_field<double>{"DO"} /* 63 */,
                                       _nrn_mechanism_field<double>{"v"} /* 64 */,
                                       _nrn_mechanism_field<double>{"_g"} /* 65 */,
                                       _nrn_mechanism_field<double>{"_tsav"} /* 66 */,
                                       _nrn_mechanism_field<double*>{"_nd_area", "area"} /* 0 */,
                                       _nrn_mechanism_field<Point_process*>{"_pntproc", "pntproc"} /* 1 */,
                                       _nrn_mechanism_field<void*>{"_tqitem", "netsend"} /* 2 */,
                                       _nrn_mechanism_field<int>{"_cvode_ieq", "cvodeieq"} /* 3 */);
  hoc_register_prop_size(_mechtype, 265, 4);
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
 	ivoc_help("help ?1 SC_NMDA_NR2B /home/mjy/project/bilinear_network/basket/mod_files/SC_NMDA_NR2B.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
 static double PI = 0x1.921fb54442d18p+1;
 static double *_t_MgBlock;
static int _reset;
static const char *modelname = "";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
static int _f_rates(_internalthreadargsprotocomma_ double);
static int rates(_internalthreadargsprotocomma_ double);
 
#define _MATELM1(_row,_col) *(_nrn_thread_getelm(static_cast<SparseObj*>(_so), _row + 1, _col + 1))
 
#define _RHS1(_arg) _rhs[_arg+1]
  
#define _linmat1  1
 static int _spth1 = 1;
 static int _cvspth1 = 0;
 
static int _ode_spec1(_internalthreadargsproto_);
/*static int _ode_matsol1(_internalthreadargsproto_);*/
 static void _n_rates(_internalthreadargsprotocomma_ double _lv);
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
 Trelease = diffusione ( _threadargs_ ) ;
   a = Kon * Trelease ;
   b = aKon * Trelease ;
   /* ~ CC0 <-> CC1 ( b * Q10 , Koff * Q10 )*/
 f_flux =  b * Q10 * CC0 ;
 b_flux =  Koff * Q10 * CC1 ;
 _RHS1( 5) -= (f_flux - b_flux);
 _RHS1( 4) += (f_flux - b_flux);
 
 _term =  b * Q10 ;
 _MATELM1( 5 ,5)  += _term;
 _MATELM1( 4 ,5)  -= _term;
 _term =  Koff * Q10 ;
 _MATELM1( 5 ,4)  -= _term;
 _MATELM1( 4 ,4)  += _term;
 /*REACTION*/
  /* ~ CC1 <-> CC2 ( a * Q10 , aKoff * Q10 )*/
 f_flux =  a * Q10 * CC1 ;
 b_flux =  aKoff * Q10 * CC2 ;
 _RHS1( 4) -= (f_flux - b_flux);
 _RHS1( 3) += (f_flux - b_flux);
 
 _term =  a * Q10 ;
 _MATELM1( 4 ,4)  += _term;
 _MATELM1( 3 ,4)  -= _term;
 _term =  aKoff * Q10 ;
 _MATELM1( 4 ,3)  -= _term;
 _MATELM1( 3 ,3)  += _term;
 /*REACTION*/
  /* ~ CC2 <-> D1 ( Kda * Q10 , Kdam * Q10 )*/
 f_flux =  Kda * Q10 * CC2 ;
 b_flux =  Kdam * Q10 * D1 ;
 _RHS1( 3) -= (f_flux - b_flux);
 _RHS1( 7) += (f_flux - b_flux);
 
 _term =  Kda * Q10 ;
 _MATELM1( 3 ,3)  += _term;
 _MATELM1( 7 ,3)  -= _term;
 _term =  Kdam * Q10 ;
 _MATELM1( 3 ,7)  -= _term;
 _MATELM1( 7 ,7)  += _term;
 /*REACTION*/
  /* ~ CC2 <-> D2 ( Kdb * Q10 , Kdbm * Q10 )*/
 f_flux =  Kdb * Q10 * CC2 ;
 b_flux =  Kdbm * Q10 * D2 ;
 _RHS1( 3) -= (f_flux - b_flux);
 _RHS1( 6) += (f_flux - b_flux);
 
 _term =  Kdb * Q10 ;
 _MATELM1( 3 ,3)  += _term;
 _MATELM1( 6 ,3)  -= _term;
 _term =  Kdbm * Q10 ;
 _MATELM1( 3 ,6)  -= _term;
 _MATELM1( 6 ,6)  += _term;
 /*REACTION*/
  /* ~ CC2 <-> C1 ( Kf * Q10 , Kfm * Q10 )*/
 f_flux =  Kf * Q10 * CC2 ;
 b_flux =  Kfm * Q10 * C1 ;
 _RHS1( 3) -= (f_flux - b_flux);
 _RHS1( 2) += (f_flux - b_flux);
 
 _term =  Kf * Q10 ;
 _MATELM1( 3 ,3)  += _term;
 _MATELM1( 2 ,3)  -= _term;
 _term =  Kfm * Q10 ;
 _MATELM1( 3 ,2)  -= _term;
 _MATELM1( 2 ,2)  += _term;
 /*REACTION*/
  /* ~ CC2 <-> C2 ( Ks * Q10 , Ksm * Q10 )*/
 f_flux =  Ks * Q10 * CC2 ;
 b_flux =  Ksm * Q10 * C2 ;
 _RHS1( 3) -= (f_flux - b_flux);
 _RHS1( 1) += (f_flux - b_flux);
 
 _term =  Ks * Q10 ;
 _MATELM1( 3 ,3)  += _term;
 _MATELM1( 1 ,3)  -= _term;
 _term =  Ksm * Q10 ;
 _MATELM1( 3 ,1)  -= _term;
 _MATELM1( 1 ,1)  += _term;
 /*REACTION*/
  /* ~ C1 <-> O ( Ks * Q10 , Ksm * Q10 )*/
 f_flux =  Ks * Q10 * C1 ;
 b_flux =  Ksm * Q10 * O ;
 _RHS1( 2) -= (f_flux - b_flux);
 
 _term =  Ks * Q10 ;
 _MATELM1( 2 ,2)  += _term;
 _term =  Ksm * Q10 ;
 _MATELM1( 2 ,0)  -= _term;
 /*REACTION*/
  /* ~ C2 <-> O ( Kf * Q10 , Kfm * Q10 )*/
 f_flux =  Kf * Q10 * C2 ;
 b_flux =  Kfm * Q10 * O ;
 _RHS1( 1) -= (f_flux - b_flux);
 
 _term =  Kf * Q10 ;
 _MATELM1( 1 ,1)  += _term;
 _term =  Kfm * Q10 ;
 _MATELM1( 1 ,0)  -= _term;
 /*REACTION*/
   /* CC0 + CC1 + CC2 + C1 + C2 + D1 + D2 + O = 1.0 */
 _RHS1(0) =  1.0;
 _MATELM1(0, 0) = 1;
 _RHS1(0) -= O ;
 _MATELM1(0, 6) = 1;
 _RHS1(0) -= D2 ;
 _MATELM1(0, 7) = 1;
 _RHS1(0) -= D1 ;
 _MATELM1(0, 1) = 1;
 _RHS1(0) -= C2 ;
 _MATELM1(0, 2) = 1;
 _RHS1(0) -= C1 ;
 _MATELM1(0, 3) = 1;
 _RHS1(0) -= CC2 ;
 _MATELM1(0, 4) = 1;
 _RHS1(0) -= CC1 ;
 _MATELM1(0, 5) = 1;
 _RHS1(0) -= CC0 ;
 /*CONSERVATION*/
   } return _reset;
 }
 static double _mfac_rates, _tmin_rates;
  static void _check_rates(_internalthreadargsproto_) {
  static int _maktable=1; int _i, _j, _ix = 0;
  double _xi, _tmax;
  static double _sav_v0_block;
  static double _sav_k_block;
  if (!usetable) {return;}
  if (_sav_v0_block != v0_block) { _maktable = 1;}
  if (_sav_k_block != k_block) { _maktable = 1;}
  if (_maktable) { double _x, _dx; _maktable=0;
   _tmin_rates =  - 120.0 ;
   _tmax =  30.0 ;
   _dx = (_tmax - _tmin_rates)/150.; _mfac_rates = 1./_dx;
   for (_i=0, _x=_tmin_rates; _i < 151; _x += _dx, _i++) {
    _f_rates(_threadargscomma_ _x);
    _t_MgBlock[_i] = MgBlock;
   }
   _sav_v0_block = v0_block;
   _sav_k_block = k_block;
  }
 }

 static int rates(_internalthreadargsprotocomma_ double _lv) { 
#if 0
_check_rates(_threadargs_);
#endif
 _n_rates(_threadargscomma_ _lv);
 return 0;
 }

 static void _n_rates(_internalthreadargsprotocomma_ double _lv){ int _i, _j;
 double _xi, _theta;
 if (!usetable) {
 _f_rates(_threadargscomma_ _lv); return; 
}
 _xi = _mfac_rates * (_lv - _tmin_rates);
 if (std::isnan(_xi)) {
  MgBlock = _xi;
  return;
 }
 if (_xi <= 0.) {
 MgBlock = _t_MgBlock[0];
 return; }
 if (_xi >= 150.) {
 MgBlock = _t_MgBlock[150];
 return; }
 _i = (int) _xi;
 _theta = _xi - (double)_i;
 MgBlock = _t_MgBlock[_i] + _theta*(_t_MgBlock[_i+1] - _t_MgBlock[_i]);
 }

 
static int  _f_rates ( _internalthreadargsprotocomma_ double _lv ) {
   MgBlock = 1.0 / ( 1.0 + exp ( - ( _lv - v0_block ) / k_block ) ) ;
    return 0; }
 
static double _hoc_rates(void* _vptr) {
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
 
#if 1
 _check_rates(_threadargs_);
#endif
 _r = 1.;
 rates ( _threadargscomma_ *getarg(1) );
 return(_r);
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
         _args[6] = _args[6] + U * ( 1.0 - _args[6] ) ;
         }
       else {
         _args[6] = U ;
         }
       _args[4] = _args[4] + x * _args[6] ;
       T = Tmax * _args[4] ;
       _lfi = fmod ( numpulses , 100.0 ) ;
       PRE [ ((int) _lfi ) ] = _args[4] ;
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
 {int _i; for(_i=0;_i<8;_i++) _ml->data(_iml, _dlist1[_i]) = 0.0;}
 Trelease = diffusione ( _threadargs_ ) ;
 a = Kon * Trelease ;
 b = aKon * Trelease ;
 /* ~ CC0 <-> CC1 ( b * Q10 , Koff * Q10 )*/
 f_flux =  b * Q10 * CC0 ;
 b_flux =  Koff * Q10 * CC1 ;
 DCC0 -= (f_flux - b_flux);
 DCC1 += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ CC1 <-> CC2 ( a * Q10 , aKoff * Q10 )*/
 f_flux =  a * Q10 * CC1 ;
 b_flux =  aKoff * Q10 * CC2 ;
 DCC1 -= (f_flux - b_flux);
 DCC2 += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ CC2 <-> D1 ( Kda * Q10 , Kdam * Q10 )*/
 f_flux =  Kda * Q10 * CC2 ;
 b_flux =  Kdam * Q10 * D1 ;
 DCC2 -= (f_flux - b_flux);
 DD1 += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ CC2 <-> D2 ( Kdb * Q10 , Kdbm * Q10 )*/
 f_flux =  Kdb * Q10 * CC2 ;
 b_flux =  Kdbm * Q10 * D2 ;
 DCC2 -= (f_flux - b_flux);
 DD2 += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ CC2 <-> C1 ( Kf * Q10 , Kfm * Q10 )*/
 f_flux =  Kf * Q10 * CC2 ;
 b_flux =  Kfm * Q10 * C1 ;
 DCC2 -= (f_flux - b_flux);
 DC1 += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ CC2 <-> C2 ( Ks * Q10 , Ksm * Q10 )*/
 f_flux =  Ks * Q10 * CC2 ;
 b_flux =  Ksm * Q10 * C2 ;
 DCC2 -= (f_flux - b_flux);
 DC2 += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ C1 <-> O ( Ks * Q10 , Ksm * Q10 )*/
 f_flux =  Ks * Q10 * C1 ;
 b_flux =  Ksm * Q10 * O ;
 DC1 -= (f_flux - b_flux);
 DO += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ C2 <-> O ( Kf * Q10 , Kfm * Q10 )*/
 f_flux =  Kf * Q10 * C2 ;
 b_flux =  Kfm * Q10 * O ;
 DC2 -= (f_flux - b_flux);
 DO += (f_flux - b_flux);
 
 /*REACTION*/
   /* CC0 + CC1 + CC2 + C1 + C2 + D1 + D2 + O = 1.0 */
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
 Trelease = diffusione ( _threadargs_ ) ;
 a = Kon * Trelease ;
 b = aKon * Trelease ;
 /* ~ CC0 <-> CC1 ( b * Q10 , Koff * Q10 )*/
 _term =  b * Q10 ;
 _MATELM1( 5 ,5)  += _term;
 _MATELM1( 4 ,5)  -= _term;
 _term =  Koff * Q10 ;
 _MATELM1( 5 ,4)  -= _term;
 _MATELM1( 4 ,4)  += _term;
 /*REACTION*/
  /* ~ CC1 <-> CC2 ( a * Q10 , aKoff * Q10 )*/
 _term =  a * Q10 ;
 _MATELM1( 4 ,4)  += _term;
 _MATELM1( 3 ,4)  -= _term;
 _term =  aKoff * Q10 ;
 _MATELM1( 4 ,3)  -= _term;
 _MATELM1( 3 ,3)  += _term;
 /*REACTION*/
  /* ~ CC2 <-> D1 ( Kda * Q10 , Kdam * Q10 )*/
 _term =  Kda * Q10 ;
 _MATELM1( 3 ,3)  += _term;
 _MATELM1( 7 ,3)  -= _term;
 _term =  Kdam * Q10 ;
 _MATELM1( 3 ,7)  -= _term;
 _MATELM1( 7 ,7)  += _term;
 /*REACTION*/
  /* ~ CC2 <-> D2 ( Kdb * Q10 , Kdbm * Q10 )*/
 _term =  Kdb * Q10 ;
 _MATELM1( 3 ,3)  += _term;
 _MATELM1( 6 ,3)  -= _term;
 _term =  Kdbm * Q10 ;
 _MATELM1( 3 ,6)  -= _term;
 _MATELM1( 6 ,6)  += _term;
 /*REACTION*/
  /* ~ CC2 <-> C1 ( Kf * Q10 , Kfm * Q10 )*/
 _term =  Kf * Q10 ;
 _MATELM1( 3 ,3)  += _term;
 _MATELM1( 2 ,3)  -= _term;
 _term =  Kfm * Q10 ;
 _MATELM1( 3 ,2)  -= _term;
 _MATELM1( 2 ,2)  += _term;
 /*REACTION*/
  /* ~ CC2 <-> C2 ( Ks * Q10 , Ksm * Q10 )*/
 _term =  Ks * Q10 ;
 _MATELM1( 3 ,3)  += _term;
 _MATELM1( 1 ,3)  -= _term;
 _term =  Ksm * Q10 ;
 _MATELM1( 3 ,1)  -= _term;
 _MATELM1( 1 ,1)  += _term;
 /*REACTION*/
  /* ~ C1 <-> O ( Ks * Q10 , Ksm * Q10 )*/
 _term =  Ks * Q10 ;
 _MATELM1( 2 ,2)  += _term;
 _MATELM1( 0 ,2)  -= _term;
 _term =  Ksm * Q10 ;
 _MATELM1( 2 ,0)  -= _term;
 _MATELM1( 0 ,0)  += _term;
 /*REACTION*/
  /* ~ C2 <-> O ( Kf * Q10 , Kfm * Q10 )*/
 _term =  Kf * Q10 ;
 _MATELM1( 1 ,1)  += _term;
 _MATELM1( 0 ,1)  -= _term;
 _term =  Kfm * Q10 ;
 _MATELM1( 1 ,0)  -= _term;
 _MATELM1( 0 ,0)  += _term;
 /*REACTION*/
   /* CC0 + CC1 + CC2 + C1 + C2 + D1 + D2 + O = 1.0 */
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
  C2 = C20;
  C1 = C10;
  CC2 = CC20;
  CC1 = CC10;
  CC0 = CC00;
  D2 = D20;
  D1 = D10;
  O = O0;
 {
   rates ( _threadargscomma_ v ) ;
   CC0 = 1.0 ;
   CC1 = 0.0 ;
   CC2 = 0.0 ;
   C1 = 0.0 ;
   C2 = 0.0 ;
   D1 = 0.0 ;
   D2 = 0.0 ;
   O = 0.0 ;
   T = 0.0 ;
   numpulses = 0.0 ;
   gbar_Q10 = pow( Q10_diff , ( ( celsius - 30.0 ) / 10.0 ) ) ;
   Q10 = pow( Q10_channel , ( ( celsius - 30.0 ) / 10.0 ) ) ;
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

#if 0
 _check_rates(_threadargs_);
#endif
 _tsav = -1e20;
   _v = _vec_v[_ni[_iml]];
 v = _v;
 initmodel(_threadargs_);
}
}

static double _nrn_current(_internalthreadargsprotocomma_ double _v) {
double _current=0.; v=_v;
{ {
   rates ( _threadargscomma_ v ) ;
   g = gmax * gbar_Q10 * O * gmax_factor ;
   i = ( 1e-6 ) * g * ( v - Erev ) * MgBlock ;
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
   _t_MgBlock = makevector(151*sizeof(double));
 _slist1[0] = {O_columnindex, 0};  _dlist1[0] = {DO_columnindex, 0};
 _slist1[1] = {C2_columnindex, 0};  _dlist1[1] = {DC2_columnindex, 0};
 _slist1[2] = {C1_columnindex, 0};  _dlist1[2] = {DC1_columnindex, 0};
 _slist1[3] = {CC2_columnindex, 0};  _dlist1[3] = {DCC2_columnindex, 0};
 _slist1[4] = {CC1_columnindex, 0};  _dlist1[4] = {DCC1_columnindex, 0};
 _slist1[5] = {CC0_columnindex, 0};  _dlist1[5] = {DCC0_columnindex, 0};
 _slist1[6] = {D2_columnindex, 0};  _dlist1[6] = {DD2_columnindex, 0};
 _slist1[7] = {D1_columnindex, 0};  _dlist1[7] = {DD1_columnindex, 0};
_first = 0;
}

#if NMODL_TEXT
static void register_nmodl_text_and_filename(int mech_type) {
    const char* nmodl_filename = "/home/mjy/project/bilinear_network/basket/mod_files/SC_NMDA_NR2B.mod";
    const char* nmodl_file_text = 
  "NEURON {\n"
  "	POINT_PROCESS  SC_NMDA_NR2B\n"
  "	NONSPECIFIC_CURRENT i\n"
  "	RANGE Q10_diff,Q10_channel\n"
  "	RANGE g , ic\n"
  "	RANGE Cdur,Erev,T,Tmax\n"
  "	RANGE Rd, gmax, a, b, Kon, akon, Koff, aKoff, Kda, Kdam, Kdb, Kdbm, Ks, Ksm, Kf, Kfm\n"
  "	RANGE tau_1, tau_rec, tau_facil, U, u0 \n"
  "	RANGE PRE\n"
  "	RANGE Used\n"
  "	RANGE MgBlock,v0_block,k_block\n"
  "	RANGE diffuse,Trelease,lamd, Diff, M, Rd, nd, syntype, gmax_factor\n"
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
  "	: Parametri Presinaptici\n"
  "	gmax		= 18800  	(pS)	: 7e3 : 4e4 :5000\n"
  "	Q10_diff	= 1.5 :1.4\n"
  "	Q10_channel	= 2.4 :2.2\n"
  "	U 		= 0.42 (1) 	< 0, 1 >\n"
  "	tau_rec 	= 8 (ms) 	< 1e-9, 1e9 > 	 \n"
  "	tau_facil 	= 5 (ms) 	< 0, 1e9 > 	\n"
  "\n"
  "	M	= 21.515	: numero di (kilo) molecole in una vescicola		\n"
  "	Rd	= 1.03 (um)\n"
  "	Diff	= 0.223 (um2/ms)\n"
  "	tau_1 	= 1 (ms) 	< 1e-9, 1e9 >\n"
  "\n"
  "	u0 		= 0 (1) < 0, 1 >\n"
  "	Tmax		= 1  	(mM)\n"
  "\n"
  "	: Postsinaptico, Westbrook scheme\n"
  "	\n"
  "	Cdur	= 0.3	(ms)\n"
  "	aKon =  9.06         (/ms/mM) \n"
  "        Koff =  0.115        (/ms)\n"
  "        Kon =   4.53         (/ms/mM) \n"
  "        aKoff = 0.23         (/ms)\n"
  "        Kdam =  0.245        (/ms)\n"
  "        Kda =  1.659        (/ms)\n"
  "        Kdbm =  0.00274      (/ms)\n"
  "        Kdb =  0.338        (/ms)\n"
  "        Kf =   8.553        (/ms)\n"
  "        Kfm =   0.528        (/ms)\n"
  "        Ks =   0.145        (/ms)\n"
  "        Ksm =   0.694        (/ms)\n"
  "	Erev	= -3.7  (mV)	: 0 (mV)\n"
  "	\n"
  "	v0_block = -20 (mV)	: -16 -8.69 (mV)	: -18.69 (mV) : -32.7 (mV)\n"
  "	k_block  = 13 (mV)\n"
  "	nd	 = 1\n"
  "	kB	 = 0.44	(mM)\n"
  "\n"
  "	: Diffusion			\n"
  "	diffuse	= 1\n"
  "	lamd	= 20 (nm)\n"
  "	celsius (degC)\n"
  "}\n"
  "\n"
  "\n"
  "ASSIGNED {\n"
  "	v		(mV)		: postsynaptic voltage\n"
  "	i 		(nA)		: current = g*(v - Erev)\n"
  "	ic 		(nA)		: current = g*(v - Erev)\n"
  "	g 		(pS)		: actual conductance\n"
  "\n"
  "	a		(/ms)    : binding\n"
  "	b		(/ms)\n"
  "	T		(mM)\n"
  "	x \n"
  "	\n"
  "	Trelease	(mM)\n"
  "	tspike[100]	(ms)	: will be initialized by the pointprocess\n"
  "	PRE[100]\n"
  "	Mres		(mM)	\n"
  "	\n"
  "	MgBlock\n"
  "	numpulses\n"
  "	tzero\n"
  "	gbar_Q10 (mho/cm2)\n"
  "	Q10 (1)\n"
  "}\n"
  "\n"
  "STATE {\n"
  "	: Channel states (all fractions)\n"
  "	CC0\n"
  "	CC1\n"
  "	CC2\n"
  "	C1\n"
  "	C2\n"
  "	D1\n"
  "	D2	\n"
  "	O	\n"
  "}\n"
  "\n"
  "INITIAL {\n"
  "	rates(v)\n"
  "	CC0 = 1\n"
  "	CC1 = 0\n"
  "	CC2 = 0\n"
  "	C1 = 0\n"
  "	C2 = 0\n"
  "	D1 = 0\n"
  "	D2 = 0\n"
  "	O  = 0\n"
  "	T  = 0\n"
  "	numpulses=0\n"
  "\n"
  "	gbar_Q10 = Q10_diff^((celsius-30)/10)\n"
  "	Q10 = Q10_channel^((celsius-30)/10)\n"
  "\n"
  "	Mres = 1e3 * (1e3 * 1e15 / 6.022e23 * M)     : (M) to (mM) so 1e3, 1um^3=1dm^3*1e-15 so 1e15\n"
  "	FROM i=1 TO 100 { PRE[i-1]=0 tspike[i-1]=0 } :PRE_2[500]=0}\n"
  "	tspike[0]=1e12	(ms)\n"
  "	if(tau_1>=tau_rec){ \n"
  "		printf(\"Warning: tau_1 (%g) should never be higher neither equal to tau_rec (%g)!\\n\",tau_1,tau_rec)\n"
  "		tau_rec=tau_1+1e-5\n"
  "		:printf(\"tau_rec has been set to %g\\n\",tau_rec) \n"
  "	} \n"
  "\n"
  "}\n"
  "	FUNCTION imax(a,b) {\n"
  "	    if (a>b) { imax=a }\n"
  "	    else { imax=b }\n"
  "	}\n"
  "	\n"
  "\n"
  "FUNCTION diffusione(){	 \n"
  "	LOCAL DifWave,i,cntc,fi,aaa\n"
  "	DifWave=0\n"
  "	cntc=imax(numpulses-100,0)\n"
  "	FROM i=cntc  TO numpulses{\n"
  "	    fi=fmod(i,100)\n"
  "		tzero=tspike[fi]\n"
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
  "BREAKPOINT {\n"
  "	rates(v)\n"
  "	SOLVE kstates METHOD sparse	\n"
  "	g = gmax * gbar_Q10 * O * gmax_factor\n"
  "	\n"
  "	: E' piu' logico spostare * MgBlock * PRE sul calcolo della corrente!\n"
  "	i = (1e-6) * g * (v - Erev) * MgBlock\n"
  "	ic = i\n"
  "    }\n"
  "\n"
  "KINETIC kstates {	\n"
  "	:if ( diffuse && (t>tspike[0]) ) { Trelease= T + diffusione() } else { Trelease=T }\n"
  "	Trelease = diffusione()\n"
  "	a = Kon * Trelease\n"
  "	b = aKon * Trelease\n"
  "	~ CC0 <-> CC1 (b*Q10,Koff*Q10) \n"
  "	~ CC1 <-> CC2 (a*Q10,aKoff*Q10) \n"
  "        ~ CC2 <-> D1 (Kda*Q10,Kdam*Q10)\n"
  "        ~ CC2 <-> D2 (Kdb*Q10,Kdbm*Q10) \n"
  "	~ CC2 <-> C1 (Kf*Q10,Kfm*Q10) \n"
  "	~ CC2 <-> C2 (Ks*Q10,Ksm*Q10)\n"
  "	~ C1 <-> O (Ks*Q10,Ksm*Q10) \n"
  "	~ C2 <-> O (Kf*Q10,Kfm*Q10) \n"
  "	\n"
  "	CONSERVE CC0+CC1+CC2+C1+C2+D1+D2+O = 1\n"
  "}\n"
  "\n"
  "PROCEDURE rates(v(mV)) {\n"
  "	: E' necessario includere DEPEND v0_block,k_block per aggiornare le tabelle!\n"
  "	TABLE MgBlock DEPEND v0_block,k_block FROM -120 TO 30 WITH 150\n"
  "	MgBlock = 1 / ( 1 + exp ( - ( v - v0_block ) / k_block ) )\n"
  "}\n"
  "\n"
  "\n"
  "NET_RECEIVE(weight, on, nspike, tzero (ms),y, z, u, tsyn (ms)) {LOCAL fi\n"
  "\n"
  ": *********** ATTENZIONE! ***********\n"
  ":\n"
  ": Qualora si vogliano utilizzare impulsi di glutammato saturanti e' \n"
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
  "			z = z*exp( - (t - tsyn) / (tau_rec) )	: RESCALED !\n"
  "			z = z + ( y*(exp(-(t - tsyn)/tau_1) - exp(-(t - tsyn)/(tau_rec)))/((tau_1/(tau_rec))-1) ) : RESCALED !\n"
  "			y = y*exp(-(t - tsyn)/tau_1)			\n"
  "			x = 1-y-z\n"
  "				\n"
  "			if (tau_facil > 0) { \n"
  "				u = u*exp(-(t - tsyn)/tau_facil)\n"
  "				u = u + U * ( 1 - u )							\n"
  "			} else { u = U }\n"
  "			\n"
  "			y = y + x * u\n"
  "			\n"
  "			T=Tmax*y\n"
  "			fi=fmod(numpulses,100)\n"
  "			PRE[fi]=y	: PRE[numpulses]=y\n"
  "			\n"
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
  "	if (flag == nspike) { \n"
  "			tzero = t\n"
  "			T = 0\n"
  "			on = 0\n"
  "	}\n"
  "}\n"
  "\n"
  ;
    hoc_reg_nmodl_filename(mech_type, nmodl_filename);
    hoc_reg_nmodl_text(mech_type, nmodl_file_text);
}
#endif
