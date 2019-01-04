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
//******************************************************************************
//
// ^FILE   : DeductionDetails.hpp
// ^AUTHOR : Zijian Ying
// ^DATE   : 8/16/1999
//
// ^CLASS    : DeductionDetails
// ^SUBCLASS :
//******************************************************************************


#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>
///#endif

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE DeductionDetails : public MFCanBFCbo, private boost::noncopyable
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

   static DString getUniqueKey( DString& TransId );

   DeductionDetails( BFAbstractCBO &parent );
   virtual ~DeductionDetails();

   void init( BFData &data, DString& currency);

   void getField( const BFFieldId& idField,
                  DString& strFieldValue,
                  const BFDataGroupId& idDataGroup,
                  bool formattedReturn = false ) const;

private:
   bool _AlreadyGotDetails;
   DString _currency;

};

///#endif
