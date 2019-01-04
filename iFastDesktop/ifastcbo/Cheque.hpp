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
//    Copyright 2004, By International Financial Data Service
//
//
//******************************************************************************
//
// ^FILE   : Cheque.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : Cheque
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class ChequeDetailsList;

class IFASTCBO_LINKAGE Cheque : public MFCanBFCbo
{
	public:

		Cheque( BFAbstractCBO &parent );
		virtual ~Cheque();

		SEVERITY init( const BFData& data );
		SEVERITY init(const BFDataGroupId& idDataGroup );
		SEVERITY getDetailsList( ChequeDetailsList *&pDetailsList, const BFDataGroupId& idDataGroup );

	protected:

	    SEVERITY doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );

  	private:

	SEVERITY setChequeSubstitionList (const DString &dstrCheque, const BFDataGroupId& idDataGroup);
    DString m_dstrCheque;

};

/* $Log::
 */