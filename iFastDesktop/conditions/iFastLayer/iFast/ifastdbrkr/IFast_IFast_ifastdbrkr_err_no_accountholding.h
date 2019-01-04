#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_no_accountholding : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_no_accountholding() { }
		~CIFast_IFast_ifastdbrkr_err_no_accountholding() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_ACCOUNTHOLDING")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No Account holdings exist at this date.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("No Account holdings exist at this date.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Zu diesem Datum existiert keine Konto-Beteiligung.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No existen inversiones en la cuenta a esta fecha")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucun portefeuille de compte existant à ce jour")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er bestaan geen accountvermogens op deze datum")); }

        // Actions
	};
}



