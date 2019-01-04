#ifndef AWD23KEY_HPP
#define AWD23KEY_HPP

#pragma message( "including "__FILE__ )

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

/**@pkg DIAWD23 */    

#ifndef COMMONPORT_H
   #include "commonport.h"
#endif
#ifndef AWDKEY_HPP
   #include "awdkey.hpp"
#endif
#ifndef AWDSTRCT_H
   #include "awdstrct.h"
#endif

class AWDBase;
class AWDObjectFactory;

#undef DIAWD23_LINKAGE
#ifdef DIAWD23_DLL
   #define DIAWD23_LINKAGE CLASS_EXPORT
#else
   #define DIAWD23_LINKAGE CLASS_IMPORT
#endif

class DIAWD23_LINKAGE Awd23Key : public AwdKey
{
   // Public Enumerations
   public:
      enum
      {
         CRDATTIM_LEN = 26,
         RECORDCD_LEN = 1,
         CRNODE_LEN   = 2,
      };

   public:
      /**
       * Default constructor
       */
      Awd23Key();
      
      /**
       * Destructor
       */
      virtual ~Awd23Key();

   // Public methods inherited from AwdKey
   public:
      /**
       * Getter for the key
       * 
       * @return 
       */
      virtual bool isKey() const;
      
      /**
       * Makes a copy of the key
       * 
       * @return 
       */
      virtual AwdKey * makeCopy() const;

      /**
       * Getter for the date/time string
       * 
       * @return 
       */
      virtual DString getCreateDateTime() const;

      /**
       * Getter for the numeric code string
       * 
       * @return 
       */
      virtual DString getRecordCode() const;

      /**
       * Getter for the node string
       * 
       * @return 
       */
      virtual DString getCreateNode() const;

      /**
       * Assignment operator
       * 
       * @param key
       * @return 
       */
      virtual bool operator ==( const AwdKey &key ) const;

   // Public methods for use by Awd23Interface
   public:
      /**
       * Constructor
       * 
       * @param key
       */
      Awd23Key( AWDOBJKEY & key );

      /**
       * Constructor
       * 
       * @param pObj
       */
      Awd23Key( AWDBase * pObj );

      /**
       * Copy constructor
       * 
       * @param pKey
       */
      Awd23Key( const Awd23Key * pKey );

      /**
       * Getter for the key
       * 
       * @return 
       */
      const AWDOBJKEY & getKey() const { return m_key; };

      /**
       * Getter for the object
       * 
       * @return 
       */
      AWDBase * getAwdBaseObj() const { return m_pObj; };

      /**
       * Getter for the AWD object struct
       * 
       * @return 
       */
      AWDOBJ getAwdObjStruct() const;

   // private methods
   private:
      void copyKey( const Awd23Key *pOriginal );
      void retrieveObject();
      void getStruct();
      AWDBase *copyObject( AWDBase *pCopy );

   // Private members
   private:
      AWDOBJKEY  m_key;
      AWDBase   *m_pObj;
      bool       m_isKey;
};




//******************************************************************************
//              Revision Control Entries
//******************************************************************************
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
// $Log:   Y:/VCS/iFastAWD/diawd23/awd23key.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:16:28   kovacsro
//Initial revision.
// 
//    Rev 1.6   05 Dec 2000 13:58:10   dt14177
// cleanup and documentation
// 
//    Rev 1.5   Apr 09 1999 13:50:38   DMUM
// Sync up with 1.6.x
//
//    Rev 1.3.1.0   Mar 31 1999 13:20:54   DMUM
// Sync up with Infra 1.6.x
//
//    Rev 1.0.1.1   Jan 20 1999 16:41:58   DMUM
// Development for TA2000 NT rel 3.4
//
//    Rev 1.0.1.0   Sep 29 1998 14:37:06   DTWK
//
//
//    Rev 1.1   Sep 09 1998 08:01:08   DMUM
// Added == operator
//
//    Rev 1.0   29 Jul 1998 20:28:16   DT14596
// DLMG New Archives for TA2000NTDT
//
//    Rev 1.4   Jul 23 1998 07:36:42   dmum
// Cleanup
//
//    Rev 1.3   Dec 30 1997 12:25:52   dmum
//
//
//    Rev 1.2   Dec 16 1997 11:21:16   dmum
// No longer interfaces with AWD32.EXE
//
// Now uses AWD 2.3.0b directly through SOM and APIs
//
//    Rev 1.1   10 Nov 1997 15:20:06   dmum
// Added redundancy guards and export/import guards
//
//    Rev 1.0   03 Sep 1997 14:21:24   dmum
//
//
//
//

#endif // AWD23KEY_HPP
