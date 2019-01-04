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
//    Copyright 2005 by International financial data service.
//
//
//******************************************************************************
//
// ^FILE   : DefaultMailOptionList.hpp
// ^AUTHOR : Yingbao Li
// ^DATE   : September 1, 2005
//
// ^CLASS    : DefaultMailOptionList
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

class IFASTCBO_LINKAGE DefaultMailOptionList : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   DefaultMailOptionList( BFAbstractCBO &parent );
   virtual ~DefaultMailOptionList();

   // hold flag will be returned.
   DString  getDefaultHoldFlag( const DString& docType,
                                 const DString& fundGroup = NULL_STRING  );
   bool isObjectExit(const DString& fundGroup, 
                     const DString& docType );
   SEVERITY getDefaultDeliveryOptionFlags(DString& defOption, 
                                          const DString& docType,
                                          const DString& fundGroup = NULL_STRING);
protected:
private:
   // Initialize function
   SEVERITY init(  );
   SEVERITY init(const DString& fundGroup  );

   SEVERITY  getDefaultMailOptionListByFundGroup( 
                                    const DString& fundGroup,
                                    DefaultMailOptionList*& pDefaultMailOptionList  );
   SEVERITY  getDefaultMailOptionListForDocType(
                                    DefaultMailOptionList*& pDefaultMailOptionList  );
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//