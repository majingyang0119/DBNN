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
static constexpr auto number_of_datum_variables = 3;
static constexpr auto number_of_floating_point_variables = 18;
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
 
#define nrn_init _nrn_init__Kv3_3
#define _nrn_initial _nrn_initial__Kv3_3
#define nrn_cur _nrn_cur__Kv3_3
#define _nrn_current _nrn_current__Kv3_3
#define nrn_jacob _nrn_jacob__Kv3_3
#define nrn_state _nrn_state__Kv3_3
#define _net_receive _net_receive__Kv3_3 
#define rateConst rateConst__Kv3_3 
#define state state__Kv3_3 
 
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
#define gateCurrent _ml->template fpfield<0>(_iml)
#define gateCurrent_columnindex 0
#define gbar _ml->template fpfield<1>(_iml)
#define gbar_columnindex 1
#define gunit _ml->template fpfield<2>(_iml)
#define gunit_columnindex 2
#define ik _ml->template fpfield<3>(_iml)
#define ik_columnindex 3
#define igate _ml->template fpfield<4>(_iml)
#define igate_columnindex 4
#define i _ml->template fpfield<5>(_iml)
#define i_columnindex 5
#define g _ml->template fpfield<6>(_iml)
#define g_columnindex 6
#define nc _ml->template fpfield<7>(_iml)
#define nc_columnindex 7
#define ninf _ml->template fpfield<8>(_iml)
#define ninf_columnindex 8
#define taun _ml->template fpfield<9>(_iml)
#define taun_columnindex 9
#define n _ml->template fpfield<10>(_iml)
#define n_columnindex 10
#define ek _ml->template fpfield<11>(_iml)
#define ek_columnindex 11
#define qt _ml->template fpfield<12>(_iml)
#define qt_columnindex 12
#define alpha _ml->template fpfield<13>(_iml)
#define alpha_columnindex 13
#define beta _ml->template fpfield<14>(_iml)
#define beta_columnindex 14
#define Dn _ml->template fpfield<15>(_iml)
#define Dn_columnindex 15
#define v _ml->template fpfield<16>(_iml)
#define v_columnindex 16
#define _g _ml->template fpfield<17>(_iml)
#define _g_columnindex 17
#define _ion_ek *(_ml->dptr_field<0>(_iml))
#define _p_ion_ek static_cast<neuron::container::data_handle<double>>(_ppvar[0])
#define _ion_ik *(_ml->dptr_field<1>(_iml))
#define _p_ion_ik static_cast<neuron::container::data_handle<double>>(_ppvar[1])
#define _ion_dikdv *(_ml->dptr_field<2>(_iml))
 /* Thread safe. No static _ml, _iml or _ppvar. */
 static int hoc_nrnpointerindex =  -1;
 static _nrn_mechanism_std_vector<Datum> _extcall_thread;
 static Prop* _extcall_prop;
 /* _prop_id kind of shadows _extcall_prop to allow validity checking. */
 static _nrn_non_owning_id_without_container _prop_id{};
 /* external NEURON variables */
 extern double celsius;
 /* declaration of user functions */
 static void _hoc_alphaFkt(void);
 static void _hoc_betaFkt(void);
 static void _hoc_ngateFlip(void);
 static void _hoc_rateConst(void);
 static int _mechtype;
extern void _nrn_cacheloop_reg(int, int);
extern void hoc_register_limits(int, HocParmLimits*);
extern void hoc_register_units(int, HocParmUnits*);
extern void nrn_promote(Prop*, int, int);
 
#define NMODL_TEXT 1
#if NMODL_TEXT
static void register_nmodl_text_and_filename(int mechtype);
#endif
 static void _hoc_setdata();
 /* connect user functions to hoc names */
 static VoidFunc hoc_intfunc[] = {
 {"setdata_Kv3_3", _hoc_setdata},
 {"alphaFkt_Kv3_3", _hoc_alphaFkt},
 {"betaFkt_Kv3_3", _hoc_betaFkt},
 {"ngateFlip_Kv3_3", _hoc_ngateFlip},
 {"rateConst_Kv3_3", _hoc_rateConst},
 {0, 0}
};
 
/* Direct Python call wrappers to density mechanism functions.*/
 static double _npy_alphaFkt(Prop*);
 static double _npy_betaFkt(Prop*);
 static double _npy_ngateFlip(Prop*);
 static double _npy_rateConst(Prop*);
 
static NPyDirectMechFunc npy_direct_func_proc[] = {
 {"alphaFkt", _npy_alphaFkt},
 {"betaFkt", _npy_betaFkt},
 {"ngateFlip", _npy_ngateFlip},
 {"rateConst", _npy_rateConst},
 {0, 0}
};
#define alphaFkt alphaFkt_Kv3_3
#define betaFkt betaFkt_Kv3_3
#define ngateFlip ngateFlip_Kv3_3
 extern double alphaFkt( _internalthreadargsprotocomma_ double );
 extern double betaFkt( _internalthreadargsprotocomma_ double );
 extern double ngateFlip( _internalthreadargsproto_ );
 /* declare global and static user variables */
 #define gind 0
 #define _gth 0
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 {"gbar_Kv3_3", 0, 1e+09},
 {0, 0, 0}
};
 static HocParmUnits _hoc_parm_units[] = {
 {"gateCurrent_Kv3_3", "1"},
 {"gbar_Kv3_3", "S/cm2"},
 {"gunit_Kv3_3", "pS"},
 {"ik_Kv3_3", "mA/cm2"},
 {"igate_Kv3_3", "mA/cm2"},
 {"i_Kv3_3", "mA/cm2"},
 {"g_Kv3_3", "S/cm2"},
 {"nc_Kv3_3", "1/cm2"},
 {"ninf_Kv3_3", "1"},
 {"taun_Kv3_3", "ms"},
 {0, 0}
};
 static double delta_t = 0.01;
 static double n0 = 0;
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
 _extcall_prop = _prop;
 _prop_id = _nrn_get_prop_id(_prop);
 }
 static void _hoc_setdata() {
 Prop *_prop, *hoc_getdata_range(int);
 _prop = hoc_getdata_range(_mechtype);
   _setdata(_prop);
 hoc_retpushx(1.);
}
 static void nrn_alloc(Prop*);
static void nrn_init(_nrn_model_sorted_token const&, NrnThread*, Memb_list*, int);
static void nrn_state(_nrn_model_sorted_token const&, NrnThread*, Memb_list*, int);
 static void nrn_cur(_nrn_model_sorted_token const&, NrnThread*, Memb_list*, int);
static void nrn_jacob(_nrn_model_sorted_token const&, NrnThread*, Memb_list*, int);
 
static int _ode_count(int);
static void _ode_map(Prop*, int, neuron::container::data_handle<double>*, neuron::container::data_handle<double>*, double*, int);
static void _ode_spec(_nrn_model_sorted_token const&, NrnThread*, Memb_list*, int);
static void _ode_matsol(_nrn_model_sorted_token const&, NrnThread*, Memb_list*, int);
 
#define _cvode_ieq _ppvar[3].literal_value<int>()
 static void _ode_matsol_instance1(_internalthreadargsproto_);
 /* connect range variables in _p that hoc is supposed to know about */
 static const char *_mechanism[] = {
 "7.7.0",
"Kv3_3",
 "gateCurrent_Kv3_3",
 "gbar_Kv3_3",
 "gunit_Kv3_3",
 0,
 "ik_Kv3_3",
 "igate_Kv3_3",
 "i_Kv3_3",
 "g_Kv3_3",
 "nc_Kv3_3",
 "ninf_Kv3_3",
 "taun_Kv3_3",
 0,
 "n_Kv3_3",
 0,
 0};
 static Symbol* _k_sym;
 
 /* Used by NrnProperty */
 static _nrn_mechanism_std_vector<double> _parm_default{
     0, /* gateCurrent */
     0.005, /* gbar */
     16, /* gunit */
 }; 
 
 
extern Prop* need_memb(Symbol*);
static void nrn_alloc(Prop* _prop) {
  Prop *prop_ion{};
  Datum *_ppvar{};
   _ppvar = nrn_prop_datum_alloc(_mechtype, 4, _prop);
    _nrn_mechanism_access_dparam(_prop) = _ppvar;
     _nrn_mechanism_cache_instance _ml_real{_prop};
    auto* const _ml = &_ml_real;
    size_t const _iml{};
    assert(_nrn_mechanism_get_num_vars(_prop) == 18);
 	/*initialize range parameters*/
 	gateCurrent = _parm_default[0]; /* 0 */
 	gbar = _parm_default[1]; /* 0.005 */
 	gunit = _parm_default[2]; /* 16 */
 	 assert(_nrn_mechanism_get_num_vars(_prop) == 18);
 	_nrn_mechanism_access_dparam(_prop) = _ppvar;
 	/*connect ionic variables to this model*/
 prop_ion = need_memb(_k_sym);
 nrn_promote(prop_ion, 0, 1);
 	_ppvar[0] = _nrn_mechanism_get_param_handle(prop_ion, 0); /* ek */
 	_ppvar[1] = _nrn_mechanism_get_param_handle(prop_ion, 3); /* ik */
 	_ppvar[2] = _nrn_mechanism_get_param_handle(prop_ion, 4); /* _ion_dikdv */
 
}
 static void _initlists();
  /* some states have an absolute tolerance */
 static Symbol** _atollist;
 static HocStateTolerance _hoc_state_tol[] = {
 {0, 0}
};
 extern Symbol* hoc_lookup(const char*);
extern void _nrn_thread_reg(int, int, void(*)(Datum*));
void _nrn_thread_table_reg(int, nrn_thread_table_check_t);
extern void hoc_register_tolerance(int, HocStateTolerance*, Symbol***);
extern void _cvode_abstol( Symbol**, double*, int);

 extern "C" void _Kv33_reg() {
	int _vectorized = 1;
  _initlists();
 	ion_reg("k", -10000.);
 	_k_sym = hoc_lookup("k_ion");
 	register_mech(_mechanism, nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init, hoc_nrnpointerindex, 1);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
 hoc_register_parm_default(_mechtype, &_parm_default);
         hoc_register_npy_direct(_mechtype, npy_direct_func_proc);
     _nrn_setdata_reg(_mechtype, _setdata);
 #if NMODL_TEXT
  register_nmodl_text_and_filename(_mechtype);
#endif
   _nrn_mechanism_register_data_fields(_mechtype,
                                       _nrn_mechanism_field<double>{"gateCurrent"} /* 0 */,
                                       _nrn_mechanism_field<double>{"gbar"} /* 1 */,
                                       _nrn_mechanism_field<double>{"gunit"} /* 2 */,
                                       _nrn_mechanism_field<double>{"ik"} /* 3 */,
                                       _nrn_mechanism_field<double>{"igate"} /* 4 */,
                                       _nrn_mechanism_field<double>{"i"} /* 5 */,
                                       _nrn_mechanism_field<double>{"g"} /* 6 */,
                                       _nrn_mechanism_field<double>{"nc"} /* 7 */,
                                       _nrn_mechanism_field<double>{"ninf"} /* 8 */,
                                       _nrn_mechanism_field<double>{"taun"} /* 9 */,
                                       _nrn_mechanism_field<double>{"n"} /* 10 */,
                                       _nrn_mechanism_field<double>{"ek"} /* 11 */,
                                       _nrn_mechanism_field<double>{"qt"} /* 12 */,
                                       _nrn_mechanism_field<double>{"alpha"} /* 13 */,
                                       _nrn_mechanism_field<double>{"beta"} /* 14 */,
                                       _nrn_mechanism_field<double>{"Dn"} /* 15 */,
                                       _nrn_mechanism_field<double>{"v"} /* 16 */,
                                       _nrn_mechanism_field<double>{"_g"} /* 17 */,
                                       _nrn_mechanism_field<double*>{"_ion_ek", "k_ion"} /* 0 */,
                                       _nrn_mechanism_field<double*>{"_ion_ik", "k_ion"} /* 1 */,
                                       _nrn_mechanism_field<double*>{"_ion_dikdv", "k_ion"} /* 2 */,
                                       _nrn_mechanism_field<int>{"_cvode_ieq", "cvodeieq"} /* 3 */);
  hoc_register_prop_size(_mechtype, 18, 4);
  hoc_register_dparam_semantics(_mechtype, 0, "k_ion");
  hoc_register_dparam_semantics(_mechtype, 1, "k_ion");
  hoc_register_dparam_semantics(_mechtype, 2, "k_ion");
  hoc_register_dparam_semantics(_mechtype, 3, "cvodeieq");
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 
    hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 Kv3_3 /home/mjy/project/bilinear_network/purkinje/mod_files/Kv33.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
 static double e0 = 1.60217646e-19;
 static double q10 = 2.7;
 static double ca = 0.22;
 static double cva = 16;
 static double cka = -26.5;
 static double cb = 0.22;
 static double cvb = 16;
 static double ckb = 26.5;
 static double zn = 1.9196;
static int _reset;
static const char *modelname = "Voltage-gated potassium channel from Kv3 subunits";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
static int rateConst(_internalthreadargsprotocomma_ double);
 
static int _ode_spec1(_internalthreadargsproto_);
/*static int _ode_matsol1(_internalthreadargsproto_);*/
 static neuron::container::field_index _slist1[1], _dlist1[1];
 static int state(_internalthreadargsproto_);
 
/*CVODE*/
 static int _ode_spec1 (_internalthreadargsproto_) {int _reset = 0; {
   rateConst ( _threadargscomma_ v ) ;
   Dn = alpha * ( 1.0 - n ) - beta * n ;
   }
 return _reset;
}
 static int _ode_matsol1 (_internalthreadargsproto_) {
 rateConst ( _threadargscomma_ v ) ;
 Dn = Dn  / (1. - dt*( ( alpha )*( ( ( - 1.0 ) ) ) - ( beta )*( 1.0 ) )) ;
  return 0;
}
 /*END CVODE*/
 static int state (_internalthreadargsproto_) { {
   rateConst ( _threadargscomma_ v ) ;
    n = n + (1. - exp(dt*(( alpha )*( ( ( - 1.0 ) ) ) - ( beta )*( 1.0 ))))*(- ( ( alpha )*( ( 1.0 ) ) ) / ( ( alpha )*( ( ( - 1.0 ) ) ) - ( beta )*( 1.0 ) ) - n) ;
   }
  return 0;
}
 
static int  rateConst ( _internalthreadargsprotocomma_ double _lv ) {
   alpha = qt * alphaFkt ( _threadargscomma_ _lv ) ;
   beta = qt * betaFkt ( _threadargscomma_ _lv ) ;
   ninf = alpha / ( alpha + beta ) ;
   taun = 1.0 / ( alpha + beta ) ;
    return 0; }
 
static void _hoc_rateConst(void) {
  double _r;
 Datum* _ppvar; Datum* _thread; NrnThread* _nt;
 
  if(!_prop_id) {
    hoc_execerror("No data for rateConst_Kv3_3. Requires prior call to setdata_Kv3_3 and that the specified mechanism instance still be in existence.", NULL);
  }
  Prop* _local_prop = _extcall_prop;
  _nrn_mechanism_cache_instance _ml_real{_local_prop};
auto* const _ml = &_ml_real;
size_t const _iml{};
_ppvar = _local_prop ? _nrn_mechanism_access_dparam(_local_prop) : nullptr;
_thread = _extcall_thread.data();
double* _globals = nullptr;
if (gind != 0 && _thread != nullptr) { _globals = _thread[_gth].get<double*>(); }
_nt = nrn_threads;
 _r = 1.;
 rateConst ( _threadargscomma_ *getarg(1) );
 hoc_retpushx(_r);
}
 
static double _npy_rateConst(Prop* _prop) {
    double _r{0.0};
 Datum* _ppvar; Datum* _thread; NrnThread* _nt;
 _nrn_mechanism_cache_instance _ml_real{_prop};
auto* const _ml = &_ml_real;
size_t const _iml{};
_ppvar = _nrn_mechanism_access_dparam(_prop);
_thread = _extcall_thread.data();
double* _globals = nullptr;
if (gind != 0 && _thread != nullptr) { _globals = _thread[_gth].get<double*>(); }
_nt = nrn_threads;
 _r = 1.;
 rateConst ( _threadargscomma_ *getarg(1) );
 return(_r);
}
 
double alphaFkt ( _internalthreadargsprotocomma_ double _lv ) {
   double _lalphaFkt;
 _lalphaFkt = ca * exp ( - ( _lv + cva ) / cka ) ;
   
return _lalphaFkt;
 }
 
static void _hoc_alphaFkt(void) {
  double _r;
 Datum* _ppvar; Datum* _thread; NrnThread* _nt;
 
  Prop* _local_prop = _prop_id ? _extcall_prop : nullptr;
  _nrn_mechanism_cache_instance _ml_real{_local_prop};
auto* const _ml = &_ml_real;
size_t const _iml{};
_ppvar = _local_prop ? _nrn_mechanism_access_dparam(_local_prop) : nullptr;
_thread = _extcall_thread.data();
double* _globals = nullptr;
if (gind != 0 && _thread != nullptr) { _globals = _thread[_gth].get<double*>(); }
_nt = nrn_threads;
 _r =  alphaFkt ( _threadargscomma_ *getarg(1) );
 hoc_retpushx(_r);
}
 
static double _npy_alphaFkt(Prop* _prop) {
    double _r{0.0};
 Datum* _ppvar; Datum* _thread; NrnThread* _nt;
 _nrn_mechanism_cache_instance _ml_real{_prop};
auto* const _ml = &_ml_real;
size_t const _iml{};
_ppvar = _nrn_mechanism_access_dparam(_prop);
_thread = _extcall_thread.data();
double* _globals = nullptr;
if (gind != 0 && _thread != nullptr) { _globals = _thread[_gth].get<double*>(); }
_nt = nrn_threads;
 _r =  alphaFkt ( _threadargscomma_ *getarg(1) );
 return(_r);
}
 
double betaFkt ( _internalthreadargsprotocomma_ double _lv ) {
   double _lbetaFkt;
 _lbetaFkt = cb * exp ( - ( _lv + cvb ) / ckb ) ;
   
return _lbetaFkt;
 }
 
static void _hoc_betaFkt(void) {
  double _r;
 Datum* _ppvar; Datum* _thread; NrnThread* _nt;
 
  Prop* _local_prop = _prop_id ? _extcall_prop : nullptr;
  _nrn_mechanism_cache_instance _ml_real{_local_prop};
auto* const _ml = &_ml_real;
size_t const _iml{};
_ppvar = _local_prop ? _nrn_mechanism_access_dparam(_local_prop) : nullptr;
_thread = _extcall_thread.data();
double* _globals = nullptr;
if (gind != 0 && _thread != nullptr) { _globals = _thread[_gth].get<double*>(); }
_nt = nrn_threads;
 _r =  betaFkt ( _threadargscomma_ *getarg(1) );
 hoc_retpushx(_r);
}
 
static double _npy_betaFkt(Prop* _prop) {
    double _r{0.0};
 Datum* _ppvar; Datum* _thread; NrnThread* _nt;
 _nrn_mechanism_cache_instance _ml_real{_prop};
auto* const _ml = &_ml_real;
size_t const _iml{};
_ppvar = _nrn_mechanism_access_dparam(_prop);
_thread = _extcall_thread.data();
double* _globals = nullptr;
if (gind != 0 && _thread != nullptr) { _globals = _thread[_gth].get<double*>(); }
_nt = nrn_threads;
 _r =  betaFkt ( _threadargscomma_ *getarg(1) );
 return(_r);
}
 
double ngateFlip ( _internalthreadargsproto_ ) {
   double _lngateFlip;
 _lngateFlip = ( ninf - n ) / taun ;
   
return _lngateFlip;
 }
 
static void _hoc_ngateFlip(void) {
  double _r;
 Datum* _ppvar; Datum* _thread; NrnThread* _nt;
 
  if(!_prop_id) {
    hoc_execerror("No data for ngateFlip_Kv3_3. Requires prior call to setdata_Kv3_3 and that the specified mechanism instance still be in existence.", NULL);
  }
  Prop* _local_prop = _extcall_prop;
  _nrn_mechanism_cache_instance _ml_real{_local_prop};
auto* const _ml = &_ml_real;
size_t const _iml{};
_ppvar = _local_prop ? _nrn_mechanism_access_dparam(_local_prop) : nullptr;
_thread = _extcall_thread.data();
double* _globals = nullptr;
if (gind != 0 && _thread != nullptr) { _globals = _thread[_gth].get<double*>(); }
_nt = nrn_threads;
 _r =  ngateFlip ( _threadargs_ );
 hoc_retpushx(_r);
}
 
static double _npy_ngateFlip(Prop* _prop) {
    double _r{0.0};
 Datum* _ppvar; Datum* _thread; NrnThread* _nt;
 _nrn_mechanism_cache_instance _ml_real{_prop};
auto* const _ml = &_ml_real;
size_t const _iml{};
_ppvar = _nrn_mechanism_access_dparam(_prop);
_thread = _extcall_thread.data();
double* _globals = nullptr;
if (gind != 0 && _thread != nullptr) { _globals = _thread[_gth].get<double*>(); }
_nt = nrn_threads;
 _r =  ngateFlip ( _threadargs_ );
 return(_r);
}
 
static int _ode_count(int _type){ return 1;}
 
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
  ek = _ion_ek;
     _ode_spec1 (_threadargs_);
  }}
 
static void _ode_map(Prop* _prop, int _ieq, neuron::container::data_handle<double>* _pv, neuron::container::data_handle<double>* _pvdot, double* _atol, int _type) { 
  Datum* _ppvar;
  _ppvar = _nrn_mechanism_access_dparam(_prop);
  _cvode_ieq = _ieq;
  for (int _i=0; _i < 1; ++_i) {
    _pv[_i] = _nrn_mechanism_get_param_handle(_prop, _slist1[_i]);
    _pvdot[_i] = _nrn_mechanism_get_param_handle(_prop, _dlist1[_i]);
    _cvode_abstol(_atollist, _atol, _i);
  }
 }
 
static void _ode_matsol_instance1(_internalthreadargsproto_) {
 _ode_matsol1 (_threadargs_);
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
  ek = _ion_ek;
 _ode_matsol_instance1(_threadargs_);
 }}

static void initmodel(_internalthreadargsproto_) {
  int _i; double _save;{
  n = n0;
 {
   nc = ( 1e12 ) * gbar / gunit ;
   qt = pow( q10 , ( ( celsius - 22.0 ) / 10.0 ) ) ;
   rateConst ( _threadargscomma_ v ) ;
   n = ninf ;
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
   _v = _vec_v[_ni[_iml]];
 v = _v;
  ek = _ion_ek;
 initmodel(_threadargs_);
 }
}

static double _nrn_current(_internalthreadargsprotocomma_ double _v) {
double _current=0.; v=_v;
{ {
   g = gbar * pow( n , 4.0 ) ;
   ik = g * ( v - ek ) ;
   igate = nc * ( 1e6 ) * e0 * 4.0 * zn * ngateFlip ( _threadargs_ ) ;
   if ( gateCurrent  != 0.0 ) {
     i = igate ;
     }
   }
 _current += ik;
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
  ek = _ion_ek;
 auto const _g_local = _nrn_current(_threadargscomma_ _v + .001);
 	{ double _dik;
  _dik = ik;
 _rhs = _nrn_current(_threadargscomma_ _v);
  _ion_dikdv += (_dik - ik)/.001 ;
 	}
 _g = (_g_local - _rhs)/.001;
  _ion_ik += ik ;
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
  ek = _ion_ek;
 {   state(_threadargs_);
  } }}

}

static void terminal(){}

static void _initlists(){
 int _i; static int _first = 1;
  if (!_first) return;
 _slist1[0] = {n_columnindex, 0};  _dlist1[0] = {Dn_columnindex, 0};
_first = 0;
}

#if NMODL_TEXT
static void register_nmodl_text_and_filename(int mech_type) {
    const char* nmodl_filename = "/home/mjy/project/bilinear_network/purkinje/mod_files/Kv33.mod";
    const char* nmodl_file_text = 
  "TITLE Voltage-gated potassium channel from Kv3 subunits\n"
  "\n"
  "COMMENT\n"
  "Voltage-gated potassium channel with high threshold and fast activation/deactivation kinetics\n"
  "\n"
  "KINETIC SCHEME: Hodgkin-Huxley (n^4)\n"
  "n'= alpha * (1-n) - betha * n\n"
  "g(v) = gbar * n^4 * ( v-ek )\n"
  "\n"
  "The rate constants of activation (alpha) and deactivation (beta) were approximated by:\n"
  "\n"
  "alpha(v) = ca * exp(-(v+cva)/cka)\n"
  "beta(v) = cb * exp(-(v+cvb)/ckb)\n"
  "\n"
  "Parameters can, cvan, ckan, cbn, cvbn, ckbn are given in the CONSTANT block.\n"
  "Values derive from least-square fits to experimental data of G/Gmax(v) and taun(v) in Martina et al. J Neurophys. 97 (563-671, 2007.\n"
  "Model includes a calculation of Kv gating current\n"
  "\n"
  "Reference: Akemann et al., Biophys. J. (2009) 96: 3959-3976\n"
  "\n"
  "Laboratory for Neuronal Circuit Dynamics\n"
  "RIKEN Brain Science Institute, Wako City, Japan\n"
  "http://www.neurodynamics.brain.riken.jp\n"
  "\n"
  "Date of Implementation: April 2007\n"
  "Contact: akemann@brain.riken.jp\n"
  "\n"
  "Suffix from Kv3 to Kv3_3\n"
  "\n"
  "ENDCOMMENT\n"
  "\n"
  "\n"
  "NEURON {\n"
  "    THREADSAFE\n"
  "	SUFFIX Kv3_3\n"
  "	USEION k READ ek WRITE ik\n"
  "	NONSPECIFIC_CURRENT i\n"
  "	RANGE gbar, g, ik, i, igate, nc\n"
  "	RANGE ninf, taun\n"
  "	RANGE gateCurrent, gunit\n"
  "}\n"
  "\n"
  "UNITS {\n"
  "	(mV) = (millivolt)\n"
  "	(mA) = (milliamp)\n"
  "	(nA) = (nanoamp)\n"
  "	(pA) = (picoamp)\n"
  "	(S)  = (siemens)\n"
  "	(mS) = (millisiemens)\n"
  "	(nS) = (nanosiemens)\n"
  "	(pS) = (picosiemens)\n"
  "	(um) = (micron)\n"
  "	(molar) = (1/liter)\n"
  "	(mM) = (millimolar)		\n"
  "}\n"
  "\n"
  "CONSTANT {\n"
  "	e0 = 1.60217646e-19 (coulombs)\n"
  "	q10 = 2.7\n"
  "\n"
  "	ca = 0.22 (1/ms)\n"
  "	cva = 16 (mV)\n"
  "	cka = -26.5 (mV)\n"
  "	cb = 0.22 (1/ms)\n"
  "	cvb = 16 (mV)\n"
  "	ckb = 26.5 (mV)\n"
  "	\n"
  "	zn = 1.9196 (1)		: valence of n-gate\n"
  "}\n"
  "\n"
  "PARAMETER {\n"
  "	gateCurrent = 0 (1)	: gating currents ON = 1 OFF = 0\n"
  "	\n"
  "	gbar = 0.005 (S/cm2)   <0,1e9>\n"
  "	gunit = 16 (pS)		: unitary conductance \n"
  "}\n"
  "\n"
  "ASSIGNED {\n"
  "	celsius (degC)\n"
  "	v (mV)\n"
  "	\n"
  "	ik (mA/cm2)\n"
  "	igate (mA/cm2)\n"
  "	i (mA/cm2)\n"
  " \n"
  "	ek (mV)\n"
  "	g (S/cm2)\n"
  "	nc (1/cm2)\n"
  "	qt (1)\n"
  "\n"
  "	ninf (1)\n"
  "	taun (ms)\n"
  "	alpha (1/ms)\n"
  "	beta (1/ms)\n"
  "}\n"
  "\n"
  "STATE { n }\n"
  "\n"
  "INITIAL {\n"
  "	nc = (1e12) * gbar / gunit\n"
  "	qt = q10^((celsius-22 (degC))/10 (degC))\n"
  "	rateConst(v)\n"
  "	n = ninf\n"
  "}\n"
  "\n"
  "BREAKPOINT {\n"
  "	SOLVE state METHOD cnexp\n"
  "      g = gbar * n^4 \n"
  "	ik = g * (v - ek)\n"
  "	igate = nc * (1e6) * e0 * 4 * zn * ngateFlip()\n"
  "\n"
  "	if (gateCurrent != 0) { \n"
  "		i = igate\n"
  "	}\n"
  "}\n"
  "\n"
  "DERIVATIVE state {\n"
  "	rateConst(v)\n"
  "	n' = alpha * (1-n) - beta * n\n"
  "}\n"
  "\n"
  "PROCEDURE rateConst(v (mV)) {\n"
  "	alpha = qt * alphaFkt(v)\n"
  "	beta = qt * betaFkt(v)\n"
  "	ninf = alpha / (alpha + beta) \n"
  "	taun = 1 / (alpha + beta)\n"
  "}\n"
  "\n"
  "FUNCTION alphaFkt(v (mV)) (1/ms) {\n"
  "	alphaFkt = ca * exp(-(v+cva)/cka) \n"
  "}\n"
  "\n"
  "FUNCTION betaFkt(v (mV)) (1/ms) {\n"
  "	betaFkt = cb * exp(-(v+cvb)/ckb)\n"
  "}\n"
  "\n"
  "FUNCTION ngateFlip() (1/ms) {\n"
  "	ngateFlip = (ninf-n)/taun \n"
  "}\n"
  "\n"
  "\n"
  ;
    hoc_reg_nmodl_filename(mech_type, nmodl_filename);
    hoc_reg_nmodl_text(mech_type, nmodl_file_text);
}
#endif
