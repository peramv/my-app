//
//  ContactPoint.hpp
//
//  This header file was automatically generated!
//  **** DO NOT MODIFY THIS FILE!!! ****
//
//  Generation timestamp
//     Date:  
//     Time:  
//

#ifndef CONTACTPOINT_HPP
#define CONTACTPOINT_HPP


//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1998 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : ContactPoint.hpp
// ^AUTHOR : Cory Root
// ^DATE   : 
//
// ^CLASS    : ContactPoint
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION : Generic container for a customer's point of contact, 
//                      for example, a mailing address.
// 
// ----------------------------------------------------------
//                PUBLIC MEMBER FUNCTIONS
// ----------------------------------------------------------
//
// ^METHOD      : ContactPoint();
//
// ^DESCRIPTION : Public constructor for creating a ContactPoint object
//
// ^PARAMETERS  : N/A
//
// ^RETURNS     : Reference to an ContactPoint Object
//
// ^THROWS      : N/A
//
// ^EXAMPLE     :
// ----------------------------------------------------------
//
// ^METHOD      : ContactPoint( const ContactPoint& );
//
// ^DESCRIPTION : Copy constructor for ContactPoint object
//
// ^PARAMETERS  : const reference to a ContactPoint object
//
// ^RETURNS     : Reference to a new ContactPoint Object
//
// ^THROWS      : N/A
//
// ^EXAMPLE     :
// ----------------------------------------------------------
//
// ^METHOD      : init()
//
// ^DESCRIPTION : initializes a ContactPoint object to it's 
//                default values
//
// ^PARAMETERS  : N/A
//
// ^RETURNS     : SEVERITY
//
// ^THROWS      : N/A
//
// ^EXAMPLE     :
// ----------------------------------------------------------
//
// ^METHOD      : init( Data& )
//
// ^DESCRIPTION : initializes a ContactPoint object to the values
//                specified by the Data object
//
// ^PARAMETERS  : Data&
//
// ^RETURNS     : SEVERITY
//
// ^THROWS      : N/A
//
// ^EXAMPLE     :
// ----------------------------------------------------------
#ifndef COMMONPORT_H
#include "CommonPort.h"
#endif

#ifndef CBOBASE_HPP
#include "CBOBase.hpp"
#endif

//use namespace std for the Standard C++ library
using namespace std;

//forward declares
// Forward declaration of implementation class
class ContactPointImpl;

//defines for identifying subclasses using substitution at compile time
#undef  $ParentClass$
#define $ParentClass$    CBOBase

#undef  $ThisClass$
#define $ThisClass$      ContactPoint

#undef  $ThisClassImpl$
#define $ThisClassImpl$  ContactPointImpl

#undef  $ParentClassStr$
#define $ParentClassStr$    I_("CBOBase")

#undef  $ThisClassStr$
#define $ThisClassStr$      I_("ContactPoint")

#undef  $ThisClassImplStr$
#define $ThisClassImplStr$  I_("ContactPointImpl")

// Import/Export resolution
#undef DITABUSCORE_LINKAGE
#ifdef DITABUSCORE_DLL
   #define DITABUSCORE_LINKAGE CLASS_EXPORT
#else
   #define DITABUSCORE_LINKAGE CLASS_IMPORT
#endif

class DITABUSCORE_LINKAGE ContactPoint : public CBOBase
{
   public:
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

      ContactPoint();
      ContactPoint( const ContactPoint& copy );
      virtual ~ContactPoint();
      ContactPoint& operator=( const ContactPoint& copy );
      SEVERITY init();
      SEVERITY init( Data& dataContactPoint );
      virtual bool operator==( const ContactPoint& rContactPoint );





   // include common declarations
   #include "Common_Inter_hpp.hpp"

};


#endif
