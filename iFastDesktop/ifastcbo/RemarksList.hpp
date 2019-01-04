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
//******************************************************************************
//
// ^FILE   : RemarksList.hpp
// ^AUTHOR : Yakov Prager
// ^DATE   : March 22, 1999
//
// ^CLASS  : RemarksList
// ^PARENT : ListBase
//
// ^CLASS DESCRIPTION :
//    ements a map from the STL to hold fully instantiated BFBase objects
//    that are created from Data objects stored in the inherited ListBase class 
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

class IFASTCBO_LINKAGE RemarksList : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   RemarksList( BFAbstractCBO &parent );
   virtual ~RemarksList();
   //used to initialize from the shareholder object, when shareholder is new,
   //the param here is passed for convenience
   SEVERITY initNew(const DString& shrNum, const BFDataGroupId& idDataGroup = BF::HOST);
   // Initialize function
   SEVERITY init(const DString& shrNum, 
      const DString& dstrTrack= I_("N"), const DString& dstrPageName = NULL_STRING);
   SEVERITY getMore();
   void refreshMe (bool bRefreshMe);
   virtual bool needsRefresh (const BFDataGroupId& idDataGroup) const;

protected:
   virtual SEVERITY doCreateObject( const BFData& data, BFCBO *&pObjOut );
	virtual void  getStrKey(DString &strKey, const BFData *data);

   SEVERITY doCreateNewObject(BFCBO *& pBase, DString &strKey , const BFDataGroupId& idDataGroup);
private:
   BFData _requestData;
   bool _bRefresh;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/RemarksList.hpp-arc  $
 * 
 *    Rev 1.14   May 21 2012 14:22:20   dchatcha
 * Fix revision contorl entry.
 * 
 *    Rev 1.13   May 21 2012 14:15:52   dchatcha
 * P0186479 FN10 -Gap 14G - Block Service Unit Transfers, revise code.
 */ 
