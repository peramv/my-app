#ifndef INFRADATEFORMAT_HPP
#define INFRADATEFORMAT_HPP
#  pragma message( "including "__FILE__ )

/*
 *    COPYRIGHT:
 *
 *    The computer systems, procedures, data bases and
 *    programs created and maintained by DST Systems, Inc.,
 *    are proprietary in nature and as such are confidential.
 *    Any unauthorized use or disclosure of such information
 *    may result in civil liabilities.
 *
 *    Copyright 1999-2000 by DST Systems, Inc.
 */

/**@pkg DICORE */    

#ifndef TRACERCLIENT_HPP
   #include "tracerclient.hpp"
#endif

/**@#-*/  // forward declarations
namespace Infra
{
   class DateFormat;
   class DateHelper;
   class Locale;
   class ClientLocale;
};

class CriticalSectionLock;
namespace icu_3_6
{
   class DateFormat;
}
class DString;

/**@#+*/

#undef DICORE_LINKAGE
#ifdef DICORE_DLL
   #define DICORE_LINKAGE CLASS_EXPORT
#else
   #define DICORE_LINKAGE CLASS_IMPORT
#endif

/**
 * A DateFormat creates a locale-specific child object.
 * Currently, SimpleDateFormat is the only child class
 * available for use.
 */

class DICORE_LINKAGE Infra::DateFormat
{

// Implementation
public:

   // Start with 1 (0 reserved)
   enum {
            ICU_ERROR = 1
        } ElementalCondition;

   virtual ~DateFormat();

   /**
    * Creates a dateTime formatter that uses the
    * short style for both the date (MM/DD/YY) and the time
    * with the default locale from the host system
    * 
    * @return a DateFormat object
    */
   static DateFormat getInstance( bool = false );
   
   /**
    * Creates a  date formatter that uses the
    * medium style for both the date (e.g., Jan 3, 1990) and the
    * time with the default locale from the host system
    * 
    * @return a DateFormat object
    */
   static DateFormat getDateInstance( bool = false );
   
   /**
    * Creates a  date formatter that uses the
    * medium style for both the date (e.g., Jan 3, 1990) and the
    * time
    * 
    * @param loc    - the locale with which to initialize the 
    *                 DateFormat object
    *
    * @return a DateFormat object
    */
   static DateFormat getDateInstance( Infra::Locale * loc,
                                      bool = false );
   
   
   /**
    * Creates a  dateTime formatter that uses the
    * medium style for both the date (e.g., Jan 3, 1990) and the
    * time
    * 
    * @param loc    - the locale with which to initialize the 
    *                 DateFormat object
    *
    * @return a DateFormat object
    */
   static DateFormat getDateInstance( Infra::ClientLocale * loc,
                                      bool = false );

   /**
    * Creates a dateTime formatter that uses the
    * medium style for both the date (e.g., Jan 3, 1990) and the
    * time with the default locale from the host system
    * 
    * @return a DateFormat object
    */
   static DateFormat getDateTimeInstance( bool = false );

   /**
    * compares this DateFormat with the parameter
    * 
    * @param DateFormat
    *
    * @return - true, if equal
    *           false, otherwise
    */
   bool equals( DateFormat & );
   
   /**
    * checks whether the isLenient flag is set to allow
    * flexible interpretation of date formats
    * 
    * @return - true, if the lenient flag is set
    *           false, otherwise
    */
   bool isLenient( void );

   /**
    * sets the isLenient flag
    * 
    * @param lenient
    */
   void setLenient( bool lenient );
   friend Infra::DateHelper;

// Methods   
private:
   // we don' wan' no steenkeen' shallow copies
    DateFormat( DateFormat & );
    DateFormat & operator=( DateFormat & );

    DateFormat( );
    DateFormat( icu_3_6::DateFormat * dateFormatIn,
                bool );

    const DString format( double dateToFormat );
    double parse( const DString & );

// Attributes
private:
   ::DateFormat   * _dateFormat;
   UErrorCode       errorConstruct;
   CriticalSectionLock *_lock;
   
   /*static */TRACER_CLASS_VARIABLE;
};

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
// $Log:   Y:/VCS/iFastAWD/inc/infradateformat.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:31:44   kovacsro
//Initial revision.
//
//   Rev 1.1   May 18 2001 14:23:46   dt24433
//Changes to sync with Java* changes for new ICU.
//
//   Rev 1.0   28 Dec 2000 08:58:44   dt14177
// 
// 
//    Rev 1.10   Jun 01 2000 14:39:22   DT14177
// added & edited didoc comments
// 
//    Rev 1.9   Jun 01 2000 12:13:30   DT14177
// added didoc comments
// 
//    Rev 1.8   May 26 2000 20:26:32   DT14177
// Added ClientLocale support
// 
//    Rev 1.7   Apr 10 2000 16:57:32   dtwk
// Change #includes of icu classes to <> instead of ""
// 
//    Rev 1.6   10 Apr 2000 10:30:54   dt20842
// Switch to ICU and clean up error handling
// 
//    Rev 1.5   Jun 08 1999 14:12:32   DT14177
// Added stuff needed by dDate.
// 
//    Rev 1.4   Jun 01 1999 17:22:10   DTWK
//  
// 
//    Rev 1.3   May 12 1999 09:22:00   DT20842
// Added elemental conditions
// 
//    Rev 1.2   Apr 08 1999 13:02:16   DMUM
// Added import/export macros
//
//    Rev 1.1   Apr 02 1999 11:26:24   DT20842
// Removed di dependancy (compile/link) when using dicore
//
//    Rev 1.0   Mar 04 1999 14:40:22   DTWK
//
//
//    Rev 1.0   Mar 01 1999 13:50:48   MarkT
//
//
//
#endif