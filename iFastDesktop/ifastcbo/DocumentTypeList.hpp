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
//    Copyright 2002 by International financial data service.
//
//
//******************************************************************************
//
// ^FILE   : DocuemntTypeList.hpp
// ^AUTHOR : Yingbao Li
// ^DATE   : September 11, 2002
//
// ^CLASS    : DocuemntTypeList
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

class IFASTCBO_LINKAGE DocumentTypeList : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   DocumentTypeList( BFAbstractCBO &parent );
   virtual ~DocumentTypeList();
   // Initialize function
   SEVERITY init( const DString& dstrTrack = I_("N"),
                  const DString& dstrPageName = NULL_STRING );

   void getDocumentTypeSubstitute(DString& dstrDocTypeList,bool bEntity = false);
   void getDeliverySubstitute(DString& dstrDocType, DString& dstrDelList,DString& dstrDeliveryMethod);
protected:
   virtual void getStrKey( DString &strKey, const BFData *data  );
private:



};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//