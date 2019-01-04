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
// FILE   : RDSPTransfer.hpp
// AUTHOR : 
// DATE   : 
//
// CLASS    : RDSPTransfer
// SUBCLASS :
//
// CLASS DESCRIPTION :
//
//******************************************************************************

#include <boost\utility.hpp>
#include <ifastcbo\mfcancbo.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class EntityIdsList;

class IFASTCBO_LINKAGE RDSPTransfer : public MFCanBFCbo, private boost::noncopyable
{
public:   
   RDSPTransfer (BFAbstractCBO &parent);
   virtual ~RDSPTransfer();

   SEVERITY initNew (const BFDataGroupId &idDataGroup,
					 const DString &accountNum,
					 const DString &transNum,                  
					 const DString &transType,
					 const DString &tradeDate,
					 const DString &depositType,
					 const DString &redCode);

   SEVERITY init (const DString &accountNum,
                  const DString &transNum,                  
                  const DString &transType,
                  const DString &tradeDate,
                  const DString &depositType,
                  const DString &redCode,                   
                  const DString &tradeType = I_("Pend"),                
                  const DString &dstrTrack = I_("N"),
                  const DString &dstrPageName = NULL_STRING);
   
protected:
   virtual void doInitWithDefaultValues (const BFDataGroupId& idDataGroup);
   virtual SEVERITY doValidateField (const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup);
   virtual SEVERITY doApplyRelatedChanges (const BFFieldId& idField, const BFDataGroupId& idDataGroup);
   virtual SEVERITY doValidateAll (const BFDataGroupId &idDataGroup, long lValidateGroup);	   

private:  
   SEVERITY commonInit (const BFDataGroupId& idDataGroup);     
   
};

