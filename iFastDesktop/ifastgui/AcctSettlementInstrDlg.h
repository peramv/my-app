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
// ^FILE   : AcctSettlementInstrDlg.h
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : AcctSettlementInstrDlg
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


class AcctSettlementInstrDlg : public SettlementInstrDlg
{
public:
   /**
    * Standard dialog constructor for DSTC
    */
   AcctSettlementInstrDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);
	~AcctSettlementInstrDlg();

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
// $Log:   Y:/VCS/BF iFAST/ifastgui/AcctSettlementInstrDlg.h-arc  $
//
//   Rev 1.1   Nov 26 2004 16:56:34   aguilaam
//PET1117_FN21: settlement instructions
//
//   Rev 1.0   Oct 13 2004 15:39:22   VADEANUM
//Initial revision.
//
