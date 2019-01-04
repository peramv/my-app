#pragma once
//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2005 by International Financial Data Services
//
//
//******************************************************************************
//
// ^FILE   : EntityAddress.hpp
// ^AUTHOR : Yingbao Li
// ^DATE   : October, 99
//
// ^CLASS    : Address
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************


#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>
///#endif

class AddressEntityList;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE EntityAddress : public MFCanBFCbo, private boost::noncopyable
{
public:
   EntityAddress( BFAbstractCBO &parent );
   virtual ~EntityAddress();

   SEVERITY init( const BFData& InstData );
   SEVERITY init( const BFDataGroupId& idDataGroup );
   SEVERITY getFormattedAddress(DString& dstrAddress, const BFDataGroupId& idDataGroup);

 protected:
	virtual void doInitWithDefaultValues (const BFDataGroupId &idDataGroup);
	virtual SEVERITY doValidateField( const BFFieldId& idField, 
					                  const DString& strValue, 
									  const BFDataGroupId& idDataGroup );
	virtual SEVERITY doApplyRelatedChanges ( const BFFieldId &idField, 
                                             const BFDataGroupId &idDataGroup);	

	virtual SEVERITY doValidateAll( const BFDataGroupId &idDataGroup, 
                                    long lValidateGroup);
private:
   	SEVERITY commonInit( const BFDataGroupId& idDataGroup );
	SEVERITY applyCountryCodeRelatedChanges( const BFDataGroupId& idDataGroup );
	bool isFirstShareholder(const BFDataGroupId& idDataGroup);
	SEVERITY updateMailingInfoByRetmailForAddrCode(const DString &dstrHoldFlag, const BFDataGroupId &idDataGroup);

	DString _dstrAddrLine1, 
		    _dstrAddrLine2, 
			_dstrAddrLine3,
			_dstrCity, 
			_dstrPostal, 
			_dstrHoldMail, 
			_dstrCountry, 
			_dstrProvince; 			
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/EntityAddress.hpp-arc  $
 * 
 *    Rev 1.12   Mar 15 2005 11:20:46   porteanm
 * PET 1171 FN01 - EUSD Entity Address Update support.
 * 
 *    Rev 1.11   Mar 08 2005 17:09:04   porteanm
 * PET 1171 FN01 - EUSD Entity Address Update support.
 * 
 *    Rev 1.10   Mar 08 2005 14:32:56   porteanm
 * PET 1171 FN01 - EUSD Entity Address Update support.
 * 
 *    Rev 1.9   Mar 02 2005 16:42:38   porteanm
 * PET 1171 FN01 - EUSD Entity Address Update support - work in progress.
*/ 
