#ifndef REPOSITORYDATASOURCE_HPP
#define REPOSITORYDATASOURCE_HPP

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
 *    Copyright 1996-2000 by DST Systems, Inc.
 */

/**@pkg DIDBRKR */    

#ifndef INCLUDED_FSTREAM
#define INCLUDED_FSTREAM
   #include <fstream>
#endif

#ifndef INCLUDED_MAP
#define INCLUDED_MAP
   #include <map>
#endif

#ifndef COMMONTEMPLATES_H
   #include "commontemplates.h"
#endif

#ifndef COMMONPORT_H
   #include "commonport.h"
#endif

#ifndef SYMBOLS_H
   #include "symbols.h"
#endif

#ifndef DSTRING_HPP
   #include "dstring.hpp"
#endif

#ifndef DATAELEMENTPROPERTIES_HPP
   #include "dataelementproperties.hpp"
#endif

#ifndef DATAPROPERTIES_HPP
   #include "dataproperties.hpp"
#endif

#undef DIDBRKR_LINKAGE
#ifdef DIDBRKR_DLL
   #define DIDBRKR_LINKAGE CLASS_EXPORT
#else
   #define DIDBRKR_LINKAGE CLASS_IMPORT
#endif

class ClientLocale;

class DIDBRKR_LINKAGE RepositoryDataSource
{
public:
   /**
    * constructor
    */
   RepositoryDataSource();
   /**
    * destructor
    */
   virtual ~RepositoryDataSource();

   virtual SEVERITY getDataSet( const DString &dataSetName,
                                const ClientLocale& clientLocale,
                                unsigned long &dataSetId,
                                string_vector &fieldList,
                                DString &dstrType ) = 0;

   virtual SEVERITY getDataSet( unsigned long dataSetId,
                                const ClientLocale& clientLocale,
                                DString &dataSetName,
                                string_vector &fieldList,
                                DString &dstrType ) = 0;

   virtual DataElementProperties * getField( unsigned long fieldId,
                                             const ClientLocale& clientLocale,
                                             bool fExactMatch ) = 0;
   virtual void getMask( unsigned long maskID, DString &maskString,
                         unsigned long &numLanguages,
                         const ClientLocale *pClientLocale = 0,
                         bool fExactMatch = false ) = 0;

   virtual void getSubstitutionSet( unsigned long setID, DString &subSetString,
                                    unsigned long &numLanguages,
                                    const ClientLocale *pClientLocale = 0,
                                    bool fExactMatch = false ) = 0;

   virtual DString getVersionNumber() = 0;
   virtual DString getClient() { return m_client.c_str(); }

protected:
   DString m_client;

private:
   virtual bool readDataProperties( unsigned long dataSetID,
                            const ClientLocale *pClientLocale = 0 ) = 0;
   virtual bool readDataElementProperties( unsigned long elementID,
                                   const ClientLocale *pClientLocale = 0 ) = 0;

   virtual bool readMask( unsigned long maskID, const ClientLocale *pClientLocale = 0 ) = 0;
   virtual bool readSubstitutionMap( unsigned long maskID,
                             const ClientLocale *pClientLocale = 0 ) = 0;

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

