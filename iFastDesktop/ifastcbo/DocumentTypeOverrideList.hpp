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
// ^FILE   : DocumentTypeOverrideList.hpp
// ^AUTHOR : Yingbao Li
// ^DATE   : April 17, 2003
//
// ^CLASS    : DocumentTypeOverrideList
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

class IFASTCBO_LINKAGE DocumentTypeOverrideList : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   DocumentTypeOverrideList( BFAbstractCBO &parent );
   virtual ~DocumentTypeOverrideList();
   // Initialize function
	SEVERITY init(const DString& dstrGroupCode, const DString& dstrTrack = I_("N"),
                                  const DString& dstrPageName = NULL_STRING  );

   void getDocumentTypeSubstitute(DString& dstrDocTypeList );
   void getDocumentTypeSubstituteByCategory(
                               DString& dstrDocTypeList,
                               int iMatchType,
                               DString category                               
                               );
protected:


private:
	void linkSubstituteSet();

	DString m_strGroupCode;

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//