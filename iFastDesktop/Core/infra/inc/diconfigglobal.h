#ifndef DICONFIGGLOBAL_H
#define DICONFIGGLOBAL_H

#  pragma message( "including "__FILE__ )

#ifndef INCLUDED_MAP
#define INCLUDED_MAP
   #include <map>
#endif
#ifndef INCLUDED_STRING
#define INCLUDED_STRING
   #include <string>
#endif
#ifndef CONFIGURATION_HPP
   #include "configuration.hpp"
#endif

#ifndef DSTRING_HPP
   #include "dstring.hpp"
#endif

typedef std::map<DString, Configuration, std::less<DString> > manager_map;
typedef manager_map::value_type manager_type;
typedef manager_map::const_iterator manager_const_iterator;
typedef manager_map::iterator manager_iterator;

namespace Config
{
   enum Type
   {
      UNDEFINED_TYPE = -1,
      CONTAINER_TYPE,
      REGISTRY_TYPE,
      INI_TYPE,
      GROUP_TYPE,
      VIEW_TYPE            // Currently not implemented
   };
}

#endif //DICONFIGGLOBAL_H


//************************************************************************
//              Revision Control Entries
//************************************************************************
//
// Name:
//    %PM%
//    %PID%
//
// Description:
//    %PD%
//
// Design Parts:
//    %PIRP%
//
// Last Changed:
//    %PO%  -  %PRT%
//
// Changes:
//    %PLA%
//
//



