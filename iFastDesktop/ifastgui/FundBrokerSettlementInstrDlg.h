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
//    Copyright 2004 by International Financial Data Service
//
//******************************************************************************
//
// ^FILE   : FundBrokerSettlementInstrDlg.h
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : FundBrokerSettlementInstrDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : 
//
// -----------------------------------------------------------------------------
//
//******************************************************************************

#include <ifastgui\ifasthistoricalinfo.hpp>
#include <ifastgui\settlementinstrdlg.h>

#ifndef BASEMAINDLG_H
   #include <ifastgui\BaseMainDlg.h>
#endif


class FundBrokerSettlementInstrDlg : public SettlementInstrDlg
{
public:
   /**
    * Standard dialog constructor for DSTC
    */
   FundBrokerSettlementInstrDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);
   ~FundBrokerSettlementInstrDlg();

		
protected:
	virtual BOOL OnInitDialog();   	
public:	

private:
	virtual void setSettlementInstructionsControls();
};


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastgui/FundBrokerSettlementInstrDlg.h-arc  $
//
//   Rev 1.2   Nov 26 2004 16:56:34   aguilaam
//PET1117_FN21: settlement instructions
//
//   Rev 1.1   Nov 19 2004 17:33:30   aguilaam
//PET117_FN21: settlement instructions enhancement (temporary check-in for build)
//
//   Rev 1.0   Oct 19 2004 13:17:24   AGUILAAM
//Initial Revision
//
//   Rev 1.0   Oct 13 2004 15:39:22   VADEANUM
//Initial revision.
//
