#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_no_holdings_for_date : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_no_holdings_for_date() { }
		~CIFast_IFast_ifastcbo_err_no_holdings_for_date() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_HOLDINGS_FOR_DATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No fund holdings exist on this date.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Zu diesem Datum existieren keine Fonds-Beteiligungen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No existen inversiones en la cuenta a esta fecha.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucun portefeuille de fonds existant à cette date")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er bestaan geen fondsvermogens op deze datum")); }

        // Actions
	};
}



