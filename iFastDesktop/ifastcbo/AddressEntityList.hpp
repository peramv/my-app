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
// ^FILE   : AddressEntityList.hpp
// ^AUTHOR : Yingbao Li
// ^DATE   : 09/06/99
//
// ^CLASS    : AddressEntityList
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

class EntityAddress;

class IFASTCBO_LINKAGE AddressEntityList : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   AddressEntityList( BFAbstractCBO &parent );
   virtual ~AddressEntityList( void );

   // Initialize function
   SEVERITY init();
   SEVERITY init( DString& entityID,
                  const DString& dstrTrack = I_("N"),
                  const DString& dstrPageName = NULL_STRING); 

   void setEntityId(DString strEntityId)
   { 
      strEntityId.strip().stripLeading('0');
      _entityId = strEntityId;  
   }

   DString getEntityId(){ return(_entityId);}

   bool doesAddressCodeExist(const DString& dstrAddrCode, const BFDataGroupId& idDataGroup );

   bool isDuplicateEntityAddress( EntityAddress *pEntityAddressToCheck,
	                              const BFDataGroupId& idDataGroup );

	virtual SEVERITY getMore();
	SEVERITY initSearch( const DString& strSearchType, 
								const DString& strSearchFirstName, 
								const DString& strSearchLastName, 
								const DString& strAddrId, 
								const DString& strSearchPSTL, 
								const DString& strSearchCountry,
								const DString& dstrTrack = I_("N"),
								const DString& dstrPageName = NULL_STRING,
								bool  bAddDataNotFoundError = true );

protected:
	virtual SEVERITY doCreateObject( const BFData& data, 
								     BFCBO *&pObjOut );
    virtual SEVERITY doCreateNewObject( BFCBO *& pBase, 
		                                DString & strKey, 
										const BFDataGroupId& idDataGroup );

private:
   //copy constructor
   DString  _entityId;
	BFData queryData;  
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AddressEntityList.hpp-arc  $
 * 
 *    Rev 1.13   Mar 10 2005 16:35:40   porteanm
 * PET 1171 FN01 - EUSD Entity Address Update support.
 * 
 *    Rev 1.12   Mar 08 2005 17:07:34   porteanm
 * PET 1171 FN01 - EUSD Entity Address Update support.
 * 
 *    Rev 1.11   Mar 08 2005 14:31:36   porteanm
 * PET 1171 FN01 - EUSD Entity Address Update support.
 * 
*/


