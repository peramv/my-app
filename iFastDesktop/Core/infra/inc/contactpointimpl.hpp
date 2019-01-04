// %BEGIN_INTERFACE%

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

/**@pkg DITABUSCORE */    

#ifndef CONTACTPOINTIMPL_HPP
#define CONTACTPOINTIMPL_HPP

#ifndef CBOINSTANCEFIELDINFO_HPP
#include "CBOInstanceFieldInfo.hpp"
#endif

#ifndef CBOBASEIMPL_HPP
#include "CBOBaseImpl.hpp"
#endif

//use namespace std for the Standard C++ library
using namespace std;

//forward declares
class Data;

//defines for identifying subclasses using substitution at compile time
#undef  $ParentImplClass$
#define $ParentImplClass$  CBOBaseImpl

#undef  $ImplClass$
#define $ImplClass$  ContactPointImpl

// Import/Export resolution
#undef DITABUSCORE_LINKAGE
#ifdef DITABUSCORE_DLL
   #define DITABUSCORE_LINKAGE CLASS_EXPORT
#else
   #define DITABUSCORE_LINKAGE CLASS_IMPORT
#endif

/*
 * Class: ContactPointImpl
 *
 * Description : Generic container for a customer's point of
 *               contact, for example, a mailing address.
 */
 
class DITABUSCORE_LINKAGE ContactPointImpl : public CBOBaseImpl
{
public:
        // %BEGIN_INTERFACE%

         enum FIELD
         {
            CONTACT_POINT_ID1,
            CONTACT_POINT_ID2,
            MAX_FIELDS
         };

         enum OBJECT
         {
            UNUSED_OBJECT,
            MAX_OBJECTS
         };

         /**
          * default constructor
          */
         ContactPointImpl();

         /**
          * copy constructor
          * 
          * @param copy
          */
         ContactPointImpl( const ContactPointImpl& copy );

         /**
          * destructor
          */
         virtual ~ContactPointImpl();

         /**
          * assignment operator
          * 
          * @param copy
          * @return 
          */
         ContactPointImpl& operator=( const ContactPointImpl& copy );

         /**
          * initializing method
          * 
          * @return 
          */
         SEVERITY init();

         /**
          * initializing method from a Data object
          * 
          * @param dataContactPoint
          * @return 
          */
         SEVERITY init( Data& dataContactPoint );

         /**
          * equals operator
          * 
          * @param rContactPointImpl
          * @return true, if equal
          *         false, otherwise
          */
         virtual bool operator==( const ContactPointImpl& rContactPointImpl );

         // %END_INTERFACE%
         
         /**
          * set Id fields of ContactPointImpl 
          * to zeroes.
          * 
          * @return highest severity
          */
         SEVERITY zapContactPointIds( void );

        #include "Common_Impl_hpp.hpp"
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
