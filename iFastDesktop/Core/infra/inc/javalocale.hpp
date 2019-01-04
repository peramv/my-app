#ifndef JAVALOCALE_HPP
#define JAVALOCALE_HPP
#  pragma message( "including "__FILE__ )

/**
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


#ifndef DSTRING_HPP
   #include "dstring.hpp"
#endif

#ifndef COMMONPORT_H
   #include "commonport.h"
#endif

#ifndef LOCID_H
   #include <locid.h>
#endif

#ifndef CONFIGMANAGER_HPP
   #include "configmanager.hpp"
#endif

#ifndef SINGLETONREGISTER_HPP
   #include "singletonregister.hpp"
#endif

#ifndef ASSERT_H
  #include <assert.h>
#endif

#ifndef INCLUDED_MAP
#define INCLUDED_MAP
   #include <map>
#endif

#undef DICORE_LINKAGE
#ifdef DICORE_DLL
   #define DICORE_LINKAGE CLASS_EXPORT
#else
   #define DICORE_LINKAGE CLASS_IMPORT
#endif

class DICORE_LINKAGE JavaLocale
{

// Implementation
public:

   // Start with 1 (0 reserved)
   enum {
            JAVALOCALE_JNI_EXCEPTION_LOCATE = 1,
            JAVALOCALE_JNI_EXCEPTION_EXECUTE = 2,
            JAVALOCATE_ICU_ERROR = 3
        }
        ElementalCondition;

   /**
    * factory method for a US instance
    *
    * @return
    */
   static JavaLocale *getUSInstance( void );

   /**
    * factory method for a Japan instance
    *
    * @return
    */
   static JavaLocale *getJAPANInstance( void );

   /**
    * factory method for a Germany instance
    *
    * @return
    */
   static JavaLocale *getGERMANYInstance( void );

   /**
    * factory method for a French Canada instance
    *
    * @return
    */
   static JavaLocale *getCANADA_FRENCHInstance( void );

   /**
    * factory method for an English Canada instance
    *
    * @return
    */
   static JavaLocale *getCANADAInstance( void );

   /**
    * factory method for a UK instance
    *
    * @return
    */
   static JavaLocale *getUKInstance( void );

   /**
    * factory method for a France instance
    *
    * @return
    */
   static JavaLocale *getFRANCEInstance( void );

   /**
    * factory method for an Italy instance
    *
    * @return
    */
   static JavaLocale *getITALYInstance( void );

   /**
    * factory method for a Korea instance
    *
    * @return
    */
   static JavaLocale *getKOREAInstance( void );

   /**
    * factory method for a China instance
    *
    * @return
    */
   static JavaLocale *getCHINAInstance( void );

   /**
    * factory method for a Taiwan instance
    *
    * @return
    */
   static JavaLocale *getTAIWANInstance( void );

   /**
    * general factory method
    *
    * @param LCVstring ISO name for country, language, and optionally,
    *                  variant.
    * @return
    */
   static JavaLocale *getLocaleInstance( const DString & LCVstring );

   /**
    * general factory method
    *
    * @param language
    * @param country
    *
    * @return
    */
   static JavaLocale *getLocaleInstance( const DString & language,
                                          const DString & country);

   /**
    * general factory method
    *
    * @param language
    * @param country
    * @param variant
    *
    * @return
    */
   static JavaLocale *getLocaleInstance( const DString & language,
                                          const DString & country,
                                          const DString & variant);

   /**
    * returns the default JavaLocale, constructing it
    * on the first call
    *
    * @return
    */
   static JavaLocale *getDefaultInstance( void );

   /**
    * returns the current JavaLocale, constructing it
    * on the first call; if none is already set, it
    * will use the default JavaLocale
    *
    * @return
    */
   static JavaLocale *getCurrentInstance();

   /**
    * sets the parameter as the default JavaLocale
    *
    * @param JavaLocale
    *
    * @return
    */
   static JavaLocale *setCurrentInstance( JavaLocale * );

   /**
    * sets the parameter as the default locale
    *
    * @param localeString
    * e.g., I_("enUS") or a 6
    * character ISO string
    * containing llccvv
    * (language/
    * country/variant)
    * @return
    */
   static JavaLocale *setCurrentInstance( const DString & localeString );

   /**
    * returns the system default LCV (language/country/variant) string
    *
    * @param DString - where to store the return value.
    *
    * @return
    */
   static DString &getLCV( DString &dstrLCV );

   /**
    * This is used to clean up the Instance Map when
    * the process exits.
    */
   static void freeLocaleInstanceMap();

   /**
    * see Locale's method description in the ICU
    * documentation.
    *
    * @return reference to string passed in
    */
   DString &getISO3Language( DString &language ) const;

   /**
    * see Locale's method description in the ICU
    * documentation.
    *
    * @return reference to string passed in
    */
   DString &getISO3Country( DString &country ) const;

   /**
    * see Locale's method description in the ICU
    * documentation.
    *
    * @return reference to string passed in
    */
   DString &getLanguage( DString &language ) const;

   /**
    * see Locale's method description in the ICU
    * documentation.
    *
    * @return reference to string passed in
    */
   DString &getVariant( DString &variant ) const;

   /**
    * see Locale's method description in the ICU
    * documentation.
    *
    * @return
    */
   DString getDisplayVariant( void ) const;

   /**
    * see Locale's method description in the ICU
    * documentation.
    *
    * @return reference to string passed in
    */
   DString &getCountry( DString &country ) const;

   /**
    * see Locale's method description in the ICU
    * documentation.
    *
    * @return
    */
   DString getDisplayLanguage( void ) const;

   /**
    * see Locale's method description in the ICU
    * documentation.
    *
    * @return
    */
   DString getDisplayCountry( void ) const;

   /**
    * see Locale's method description in the ICU
    * documentation.
    *
    * @return
    */
   DString getDisplayName( void ) const;

   /**
    * returns the LCV (language/country/variant) string
    *
    * @return
    */
   const DString & getLCV( void ) const
   {
      return m_LCV;
   }

   /**
    * see Locale's method description in the ICU
    * documentation.
    *
    * @return
    */
   bool equals( JavaLocale * );

   /**
    * returns a pointer to the Locale object.
    *
    * @return
    */
   Locale * getLocale() { return m_loc; };

// Methods
private:
    JavaLocale( const DString & LCVstring );
    JavaLocale( const DString & jsLanguage,
                const DString & jsCountry );
    JavaLocale( const DString & jsLanguage,
                const DString & jsCountry,
                const DString & jsVariant );
    JavaLocale();

    virtual ~JavaLocale();

    void init( const DString & jsLanguage,
               const DString & jsCountry,
               const DString & jsVariant );

    void initLCV();

    static void setDefault( JavaLocale * );

    static void clearStatic( const JavaLocale * );
    static void releaseInstance( void * );

// Attributes
private:
   SingletonRegister m_register;
   Locale *m_loc;
   DString m_LCV;

// Static Attributes
private:
    static JavaLocale * s_pUSInstance;
    static JavaLocale * s_pJAPANInstance;
    static JavaLocale * s_pGERMANYInstance;
    static JavaLocale * s_pCANADA_FRENCHInstance;
    static JavaLocale * s_pCANADAInstance;
    static JavaLocale * s_pUKInstance;
    static JavaLocale * s_pFRANCEInstance;
    static JavaLocale * s_pITALYInstance;
    static JavaLocale * s_pKOREAInstance;
    static JavaLocale * s_pCHINAInstance;
    static JavaLocale * s_pTAIWANInstance;

    static JavaLocale * s_pCurrentInstance;
    static JavaLocale * s_pDefaultInstance;

    static DString s_currentLCV;

    typedef std::map< DString, JavaLocale *, std::less< DString > > InstanceMap;

    static InstanceMap s_InstanceMap;

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
// $Log:   Y:/VCS/iFastAWD/inc/javalocale.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:32:02   kovacsro
//Initial revision.
// 
//    Rev 1.29   May 18 2001 14:25:32   dt24433
// Changes for new ICU and switch to Guard/CriticalSectionLock from
// CriticalSection\MutexSemaphore.
// 
//    Rev 1.28   Feb 21 2001 16:28:48   DT21858
//  - Added SingletonRegister
//  - Some cleanup
//
//    Rev 1.27   Jun 06 2000 17:35:42   DT14177
// added javadoc comments.
//
//    Rev 1.26   Jun 02 2000 18:15:26   DT14177
// hid the destructor and made it virtual.  all instances should stay in the map until exit()
//
//    Rev 1.25   Jun 01 2000 17:32:46   DT14177
// added LCV string to private data
//
//    Rev 1.24   May 26 2000 20:26:36   DT14177
// Added ClientLocale support
//
//    Rev 1.23   Apr 11 2000 11:00:42   DT14177
// remove jni
//
//    Rev 1.22   Apr 10 2000 16:57:36   dtwk
// Change #includes of icu classes to <> instead of ""
//
//    Rev 1.21   10 Apr 2000 10:30:58   dt20842
// Switch to ICU and clean up error handling
//
//    Rev 1.20   06 Apr 2000 09:51:38   dt20842
// Change to ICU code
//
//    Rev 1.19   Oct 07 1999 15:43:56   DT14177
// Fixed more threading and memory leak issues.
//
//    Rev 1.18   Oct 05 1999 16:54:16   DT14177
// Added suppression and language severity enhancements; fixed multi-threading issues
//
//    Rev 1.17   Sep 28 1999 13:30:02   DT14177
// Multi-threading fix
//
//    Rev 1.16   Aug 05 1999 16:32:52   DT14177
// Performance improvement for getLCV()
//
//    Rev 1.15   Jul 08 1999 10:01:52   DT14177
// Fixed two memory leaks
//
//    Rev 1.14   Jun 18 1999 12:36:56   DT14177
// Fixed a bug where the default Locale wasn't being set.
//
//    Rev 1.13   Jun 15 1999 11:47:58   DT14177
// added setCurrentInstance()
//
//    Rev 1.12   Jun 10 1999 14:21:28   DT14177
// added comments
//
//    Rev 1.11   Jun 10 1999 11:28:40   DT14177
//
//
//    Rev 1.10   Jun 08 1999 14:17:18   DT14177
// added set,getInstance(); added comments; made some methods const
//
//    Rev 1.9   Jun 06 1999 13:24:00   DTWK
// Minor tweaks
//
//    Rev 1.8   Jun 01 1999 17:22:30   DTWK
//
//
//    Rev 1.7   May 12 1999 09:23:06   DT20842
// Added elemental conditions
//
//    Rev 1.6   Apr 23 1999 09:29:36   DT14177
// made method id's static and added work-around for 2-character Unicode getlanguage, country, and variant problem
//
//    Rev 1.5   Apr 14 1999 07:03:04   DT20842
// Added variant constructor
//
//    Rev 1.4   Apr 12 1999 16:14:16   DT20842
// Added getDefault
//
//    Rev 1.4   Apr 12 1999 16:11:02   DT20842
// Added getDefault
//
//    Rev 1.4   Apr 12 1999 16:03:34   DT20842
// Added getDefault
//
//    Rev 1.4   Apr 12 1999 16:02:12   DT20842
//
//
//    Rev 1.3   Apr 08 1999 13:02:24   DMUM
// Added import/export macros
//
//    Rev 1.2   Apr 02 1999 11:26:32   DT20842
// Removed java dependancy (compile/link) when using dicore
//
//    Rev 1.1   Mar 23 1999 09:41:26   DT20842
// Changes for merge dicore and dilocal
//
//    Rev 1.0   Mar 04 1999 14:41:10   DTWK
//
//
//    Rev 1.0   Mar 01 1999 13:50:48   MarkT
//
//
//
#endif