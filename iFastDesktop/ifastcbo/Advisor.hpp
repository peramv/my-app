#pragma once
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
//    Copyright 1997 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : Advisor.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : Address
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class AdvisorList;

class IFASTCBO_LINKAGE Advisor : public MFCanBFCbo, private boost::noncopyable
{
public:
   //TODO: enter specific field enumerations
   enum FIELD
   {
      UNUSED_FIELD,
      MAX_FIELDS
   };

   //TODO: enter specific contained object enumerations
   enum OBJECT
   {
      UNUSED_OBJECT,
      MAX_OBJECTS
   };

   Advisor( BFAbstractCBO &parent );
   virtual ~Advisor();

   SEVERITY init( AdvisorList* advisorList, const BFData& InstData );

   SEVERITY init(AdvisorList* advisorList, const BFDataGroupId& idDataGroup);

   SEVERITY doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup );
   SEVERITY doPreValidateAll( const BFDataGroupId& idDataGroup );
/**
    * virtual function. Should be overwritten in order to do special processing in setField before the actual value is 
    * filled in into the CBO
    * @param idField      - the identifier of the field to be set
    * @param strValue      - the value to be set
    * @param idDataGroup  - the identifier of the data group with which the field should be set
    * @param bFormatted    - strValue is formatted or not
   */
   SEVERITY doPreSetField( const BFFieldId& idField, DString & strValue, const BFDataGroupId& idDataGroup, bool bFormatted );
   //virtual SEVERITY doPreValidateAll( const BFDataGroupId& idDataGroup );
   void setObjectUpdated(const BFDataGroupId& idDataGroup);
   virtual void doInitWithDefaultValues( const BFDataGroupId& idDataGroup );
private:
   SEVERITY setDefault();
   AdvisorList * pAdvisorList_;
   DString strEmail, strPhonenum;
};
///#endif
