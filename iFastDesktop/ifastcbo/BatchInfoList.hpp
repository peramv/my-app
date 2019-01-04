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
//    Copyright 1999 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : BatchInfoList.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : BatchInfoList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION : The associated accounts for the selected entity
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

//Forward declarations
class WhereUsed;
static DString _empty;

class IFASTCBO_LINKAGE BatchInfoList : public MFCanBFCbo, private boost::noncopyable
{
public:
   BatchInfoList( BFAbstractCBO &parent );

   virtual ~BatchInfoList();

   SEVERITY init( const DString& dstrTrack = I_("N"),
                  const DString& dstrPageName = NULL_STRING);

   SEVERITY init( const BFData& data );
   
   SEVERITY validateBatch (const DString& dstrBatchName, 
                           const BFDataGroupId& idDataGroup);
   void getSubstitionList(DString& dstrBatchSubList, 
                          const DString &dstrOriginalBatchName, 
                          const BFDataGroupId& idDataGroup,
   DString& firstBatch = _empty);
   void getStrKey (DString &strKey, const BFData *data);

protected:
   virtual SEVERITY doCreateObject(const BFData& data, BFCBO *&pObjOut);
   virtual SEVERITY doCreateNewObject(BFCBO *& pBase, DString & strKey, const BFDataGroupId& idDataGroup );

private:
   BFData	_requestData;
   DString	_originalBatch;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/BatchInfoList.hpp-arc  $
//
//   Rev 1.2   Apr 13 2012 12:52:20   popescu
//Incident 2900100 - fixed bulk/cancelation issues related to the batch field being mandatory
// 
*/