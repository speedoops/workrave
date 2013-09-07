//
//

\#ifndef DBUS_${model.name}_HH
\#define DBUS_${model.name}_HH

\#include "dbus/DBusBindingGio.hh"

#for $interface in $model.interfaces

#if interface.condition != ''
\#if $interface.condition
#end if

#for imp in interface.imports
#for include in imp.includes
\#include "${include}"
#end for
#end for

#for imp in interface.imports
#for ns in imp.namespaces
using namespace $ns;
#end for
#end for
using namespace std;

class $interface.qname
{
public:
  virtual ~${interface.qname}() {}

  static $interface.qname *instance(const workrave::dbus::IDBus::Ptr dbus);

#for $m in interface.signals
  virtual void ${m.qname}(const string &path, #slurp
  #set comma = ''
  #for p in m.params
    #if p.hint == [] 
      $comma $interface.get_type(p.type).symbol() $p.name#slurp
    #else if 'ptr' in p.hint
      $comma $interface.get_type(p.type).symbol() *$p.name#slurp
    #else if 'ref' in p.hint
      $comma $interface.get_type(p.type).symbol() &$p.name#slurp
    #end if
  #set comma = ','
  #end for
  ) = 0;
#end for
};

#if interface.condition != ''
\#endif // $interface.condition
#end if

#end for

#endif // DBUS_${model.name}_HH
