#include "stdafx.h"
#include ".\valuevariationdlg.h"

#include <bfproc\concretedialogcreator.hpp>
#include <ifastbp\HistoricalInfoProcess.hpp>

#include <uibase\dstedit.h>
namespace ifds
{
   extern CLASS_IMPORT const BFDateFieldId InitialDate;
   extern CLASS_IMPORT const BFDecimalFieldId InitialMarketValue;
   extern CLASS_IMPORT const BFDecimalFieldId NetTransAmt;
   extern CLASS_IMPORT const BFDateFieldId NetTransAmtAsOfDate;
}

namespace IFASTBP_PROC
{
   extern CLASS_IMPORT const BFContainerId MFACCOUNT;
}

namespace UAF
{
    extern CLASS_IMPORT I_CHAR * const VALUE_VARIATION;
}
namespace
{
   const I_CHAR *CLASSNAME = I_( "ValueVariationDlg" );
}

extern CLASS_IMPORT const I_CHAR* CMD_GUI_VALUE_VARIATION;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_HISTORICAL_INFO;

static ConcreteDialogCreator< ValueVariationDlg > dlgCreator( CMD_GUI_VALUE_VARIATION );

ValueVariationDlg::ValueVariationDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, 
      GenericInterface* pGIParent, const Command& rCommand)
      :BaseMainDlg(ValueVariationDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME)
{
   
}


BEGIN_MESSAGE_MAP(ValueVariationDlg, BaseMainDlg)
ON_BN_CLICKED(IDC_BTN_RESET, OnBtnReset)
END_MESSAGE_MAP()


ValueVariationDlg::~ValueVariationDlg(void)
{
}
 void ValueVariationDlg::OnPostInitDialog()
{
   SetUserAccesFunctionCode (UAF::VALUE_VARIATION);
   addControlGroupIDForPermissionCheck(0);

   AddControl( CTRL_DATE, IDC_DTP_INITIAL_DATE, IFASTBP_PROC::MFACCOUNT, ifds::InitialDate,  CTRLFLAG_DEFAULT );
   AddControl( CTRL_EDIT, IDC_EDT_INITIAL_MARKET_VALUE, IFASTBP_PROC::MFACCOUNT, ifds::InitialMarketValue,  CTRLFLAG_DEFAULT );
   dynamic_cast<DSTEdit *> (GetControl (IDC_EDT_INITIAL_MARKET_VALUE))->
         SetAllowedChars (I_(".0123456789"));
   AddControl( CTRL_EDIT, IDC_EDT_NET_TRANS_AMT, IFASTBP_PROC::MFACCOUNT, ifds::NetTransAmt,  CTRLFLAG_DEFAULT );
   dynamic_cast<DSTEdit *> (GetControl (IDC_EDT_NET_TRANS_AMT))->
         SetAllowedChars (I_(".0123456789"));
   AddControl( CTRL_DATE, IDC_DTP_NET_TRANS_AMT_AS_OF, IFASTBP_PROC::MFACCOUNT, ifds::NetTransAmtAsOfDate,  CTRLFLAG_DEFAULT );
   SetCaption(dstrCaption); 

   doRefresh(this, NULL_STRING);
}
void ValueVariationDlg::OnBtnReset()
{
   getParent()->reset(this, IFASTBP_PROC::MFACCOUNT);
   doRefresh(this, NULL);
}  

SEVERITY ValueVariationDlg::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "doInit" ) ); 

   getParent()->getParameter(I_("caption"), dstrCaption);

   return GETHIGHESTSEVERITY();
}

//******************************************************************************
bool ValueVariationDlg::doRefresh( GenericInterface *rpGICaller, const I_CHAR *szOriginalCommand )
{  
   ConnectControlsToData();
   LoadControls();
   return(true);
}