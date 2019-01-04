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
//    Copyright 2003 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : AMSSearchCriteria.hpp
// ^AUTHOR : May Lin
// ^DATE   : Aug. 21,  2003
//
// ^CLASS    : AMSSearchCriteria
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
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

class IFASTCBO_LINKAGE AMSSearchCriteria : public MFCanBFCbo, private boost::noncopyable
{
public:
   //TODO: enter specific field enumerations
   AMSSearchCriteria( BFAbstractCBO &parent );
   virtual ~AMSSearchCriteria();
   SEVERITY init( const BFDataGroupId& idDataGroup,
				  const DString& dstrTrack = I_("N"), 
				  const DString& dstrPageName = NULL_STRING);
   void clearUpdateFlags(const BFDataGroupId& idDataGroup);
protected:
   virtual SEVERITY doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );

private:
    void SearchTypeRelatedChanges(const BFDataGroupId& idDataGroup );
	void setFieldsAsRequired( const BFFieldId idField[], const BFDataGroupId& idDataGroup,bool bReqired );
	void clearFieldsValue( const BFFieldId idField[], const BFDataGroupId& idDataGroup);
	void getAMSTypeList(DString &dstrAMSTypeList);
	
	DString _dstrAmsType;
	DString _dstrCurDate;
};
/******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AMSSearchCriteria.hpp-arc  $
//
//   Rev 1.0   Aug 22 2003 11:23:58   linmay
//Initial Revision
//
*/
///#endif
