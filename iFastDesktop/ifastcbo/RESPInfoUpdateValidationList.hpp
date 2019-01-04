#pragma once

//******************************************************************************
//
// COPYRIGHT:
//
// The computer systems, procedures, data bases and
// programs created and maintained by International Financial Data Services,
// are proprietary in nature and as such are confIdential.
// Any unauthorized use or disclosure of such information
// may result in civil liabilities.
//
// Copyright 2010 by International Financial Data Services.
//
//
//******************************************************************************
//
// ^FILE   : RESPInfoUpdateValidationList.hpp
// ^AUTHOR : 
// ^DATE   : Oct, 2010
//
// ^CLASS    : RESPInfoUpdateValidationList
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

#define EXTRACT_VALUE(s, val) \
      pos = s.find (I_(",")); \
      val = s.substr (0, pos);

#define CHOP_STRING(s) \
         pos = s.find (I_(",")); \
         pos = pos != DString::npos && pos + 1 <= s.length() ? pos + 1 : DString::npos; \
         if (pos != DString::npos) \
            s = s.substr (pos); \
         else \
            s = NULL_STRING;
            
class IFASTCBO_LINKAGE RESPInfoUpdateValidationList : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   RESPInfoUpdateValidationList( BFAbstractCBO &parent );
   virtual ~RESPInfoUpdateValidationList(void);

// Initialize function
   SEVERITY initNew( const BFDataGroupId& idDataGroup );
   SEVERITY init(const DString& strAccountNum,
                 const DString& strTransId,
                 const DString& strNewTaxJuris,
                 const DString& strNewSibling,
                 const DString& strValidateType,
                 const DString& strBenefIdList,
                 const BFDataGroupId& idDataGroup,
                 const DString& strTrack = I_("N"),
                 const DString& strPageName = NULL_STRING);
	SEVERITY displayAllRESPError(const BFDataGroupId &idDataGroup);

protected:
   virtual SEVERITY doCreateObject( const BFData& data, BFCBO *&pObjOut );
   virtual SEVERITY doCreateNewObject (BFCBO *& pBase, 
                                       DString &strKey, 
                                       const BFDataGroupId& idDataGroup );

private:
   
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/RESPInfoUpdateValidationList.hpp-arc  $
//
//   Rev 1.1   Nov 23 2010 09:05:04   kitticha
//PET165541_FN03_QESI_Phase3_Non_Finance - revise.
//
//   Rev 1.0   Oct 29 2010 04:01:12   kitticha
//Initial revision.
//
//
