//
//  StateCountryList.hpp
//
//  This header file was automatically generated!
//  **** DO NOT MODIFY THIS FILE!!! ****
//
//  Generation timestamp
//     Date:
//     Time:
//

#ifndef STATECOUNTRYLIST_HPP
#define STATECOUNTRYLIST_HPP

#ifndef  COMMONPORT_H
   #include "CommonPort.h"
#endif

#ifndef  LISTBASE_HPP
   #include "ListBase.hpp"
#endif

#ifndef  CONDITIONMANAGER_HPP
   #include "ConditionManager.hpp"
#endif

#ifndef SINGLETONREGISTER_HPP
   #include "singletonregister.hpp"
#endif

//use namespace std for the Standard C++ library
using namespace std;

//forward declares
// Forward declaration of implementation class
class StateCountryListImpl;

//defines for identifying subclasses using substitution at compile time
#undef  $ParentClass$
#define $ParentClass$    ListBase

#undef  $ThisClass$
#define $ThisClass$      StateCountryList

#undef  $ThisClassImpl$
#define $ThisClassImpl$  StateCountryListImpl

#undef  $ParentClassStr$
#define $ParentClassStr$    I_("ListBase")

#undef  $ThisClassStr$
#define $ThisClassStr$      I_("StateCountryList")

#undef  $ThisClassImplStr$
#define $ThisClassImplStr$  I_("StateCountryListImpl")


// Import/Export resolution
#undef DITABUSCORE_LINKAGE
#ifdef DITABUSCORE_DLL
   #define DITABUSCORE_LINKAGE CLASS_EXPORT
#else
   #define DITABUSCORE_LINKAGE CLASS_IMPORT
#endif

class DITABUSCORE_LINKAGE StateCountryList : public ListBase
{
   public:
      static StateCountryList* getInstance();
      static void killInstance();
      
      bool isStateCountryAPOFPO( const DString &strStateCountryCode ) const;
      bool isStateCountryDomestic( const DString &strStateCountryCode ) const;
      bool isStateCountryUSTerritory( const DString &strStateCountryCode ) const;

      bool isZipCodeValidForState( const DString &strStateCountryCode, const DString &strZipCode ) const;
      bool isStateCountryValid( const DString &strValue, DString & strStateCountryCode ) const;
      SEVERITY getStateAbbreviation( const DString &strStateCountryCode, DString & strStateAbbreviation );
      SEVERITY getStateName( const DString &strValue, DString & strStateName );
      DString getStateCountryCodeByAbbreviation( const DString& strStateCountryAbbreviation ) const;
      DString getStateCountryCodeByName( const DString& strStateCountryName ) const;
      int getSrfrtMaxTrmAge( const DString& strStateCountry, const DString& strRegFmt, const DString& strRegFmtSmb );
      int getMinAge( const DString& strStateCountry );
      bool isUgmaAllowedInState( const DString& strStateCountryCode ) const;
      bool isUtmaAllowedInState( const DString& strStateCountryCode ) const;
      const DString getForeignTaxRate( const DString &strStateCountryCode, bool fFormatReturnValue = true );
      int getListItemIndex( const DString& strStateCountryCode, const DString& strPostalCode = I_("") ) const;

   private:
      StateCountryList();
      SEVERITY init( void );
      virtual ~StateCountryList();

   private:
      static StateCountryList* _pInstance;

      // StateCountryList is a static interface
      //   which means the implementation is a static
      //   The implementation is read-only after construction
      //    So a semaphore around the creation of the interface also protects the implementation
      static MutexSemaphore _createSem;

      SingletonRegister m_register;

      static void deregister( void *pObj );

   #include "cbo_all_inter_hpp.hpp"

};

#endif

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
// $Log:   Y:/VCS/iFastAWD/inc/statecountrylist.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:32:48   kovacsro
//Initial revision.
// 
//    Rev 1.4   Jul 20 2000 17:56:30   DT22388
// Performed sync-up of infra 1.7 with infra 1.9
// 
//    Rev 1.3   Mar 24 2000 12:39:54   DMUM
// Sync up with 1.7 changes for thread safety and usage
// of SingletonRegister
//
//    Rev 1.2   Jan 02 2000 07:23:48   DT29758
// Added  methods
// getStateCountryCodeByAbbreviation and
// getStateCountryCodeByName
//
//    Rev 1.1   Nov 11 1999 16:32:40   DT29758
// added unicode support and utilization of
// indexes for data object fields
//
//    Rev 1.0.1.0   Jul 22 1999 13:36:08   DT22388
// Performed code clean-up and added #undefs
// for the substitution string i.e. $strParentImplClass$.
// Also, added #includes for test classes.
//
//
//    Rev 1.0   Jun 22 1999 16:00:32   DT22388
//
//
//    Rev 1.1   Aug 12 1998 09:05:58   djoo
// Changed default formatted parameter on
// getForeignTaxRate.
//
//    Rev 1.0   29 Jul 1998 23:58:50   dt14596
// DLMG New Archives for TA2000NTDT
//
//    Rev 1.6   Jul 24 1998 09:38:04   DMGM
// added getListItemIndex method
//
//
//    Rev 1.5   Apr 09 1998 14:38:30   djoo
// Added string defines for tracing.
//
//    Rev 1.4   Dec 23 1997 10:55:28   dmxw
// Added method to retrieve foreign tax rate.
//
//
