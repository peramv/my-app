#ifndef AWDLOOKUPRESULT_HPP
#define AWDLOOKUPRESULT_HPP

#pragma message( "including "__FILE__ )

/** 
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

/**@pkg DIAWDI */    

#ifndef COMMONPORT_H
   #include "commonport.h"
#endif
#ifndef DSTRING_HPP
   #include "dstring.hpp"
#endif

#undef DIAWDI_LINKAGE
#ifdef DIAWDI_DLL
   #define DIAWDI_LINKAGE CLASS_EXPORT
#else
   #define DIAWDI_LINKAGE CLASS_IMPORT
#endif

/**
 * This class is used to return the results of a lookup on the AWD server.
 *
 * A single AwdLookupResult object represents either a single AWD work or
 * a single AWD source object.
 *
 * @see CriteriaVector
 */
class DIAWDI_LINKAGE AwdLookupResult
{
   public:
      /**
       * Default constructor.
       */
      AwdLookupResult();

      /**
       * Copy constructor.
       *
       * @param copy - The AwdLookupResult object to copy.
       */
      AwdLookupResult( const AwdLookupResult &copy );

      /**
       * Destructor.
       */
      virtual ~AwdLookupResult();

   public:
      /**
       * Returns the business area.
       *
       * @return The business area.
       */
      DString getBusinessArea() const;

      /**
       * Returns the work type, if the object is an AWD work (transaction or
       * case) object.
       *
       * @return The work type.
       */
      DString getWorkType() const;

      /**
       * Returns the source type, if the object is an AWD source object.
       *
       * @return The source type.
       */
      DString getSourceType() const;

      /**
       * Returns the status, if the object is an AWD work (transaction or case)
       * object.
       *
       * @return The status.
       */
      DString getStatus() const;

      /**
       * Returns the queue, if the object is an AWD work (transaction or case)
       * object.
       *
       * @return The queue.
       */
      DString getQueue() const;

      /**
       * Returns the creation date and time. This is one of the three elements
       * of a key to an AWD object on an AWD server.  This is needed for an
       * AwdKey object.
       *
       * @return The creation date and time.
       */
      DString getCreateDateTime() const;

      /**
       * Returns the record code. This is one of the three elements of a key to
       * an AWD object on an AWD server.  This is needed for an AwdKey object.
       *
       * @return The record code.
       */
      DString getRecordCode() const;

      /**
       * Returns the creation node. This is one of the three elements of a key
       * to an AWD object on an AWD server.  This is needed for an AwdKey
       * object.
       *
       * @return The creation node.
       */
      DString getCreateNode() const;

      /**
       * Assignment operator.
       *
       * @param copy - The AwdLookupResult object to copy.
       *
       * @return Reference to self.
       */
      AwdLookupResult &operator=( const AwdLookupResult &copy );

   protected:
      DString m_unit;
      DString m_wrkt;
      DString m_objt;
      DString m_stat;
      DString m_queu;
      DString m_crda;
      DString m_reco;
      DString m_crno;
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
// $Log:   Y:/VCS/iFastAWD/inc/awdlookupresult.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:29:48   kovacsro
//Initial revision.
// 
//    Rev 1.3   23 Oct 2000 11:44:32   dt14177
// cleanup
// 
//    Rev 1.2   Apr 24 2000 10:38:34   DMUM
//  
//
//    Rev 1.1   Apr 09 1999 13:26:22   DMUM
// Sync up with 1.6.x
//
//    Rev 1.0.2.0   Mar 31 1999 13:14:54   DMUM
// Sync up with Infra 1.6.x
//
//    Rev 1.0.1.1   Feb 19 1999 07:47:32   DMUM
// Added lookupSource() and fixed AwdTemplates
//
//    Rev 1.0.1.0   Feb 09 1999 10:23:30   DMUM
// Added documentation
//
//    Rev 1.0   Jan 20 1999 09:08:50   DMUM
//
//
//

#endif // AWDLOOKUPRESULT_HPP

