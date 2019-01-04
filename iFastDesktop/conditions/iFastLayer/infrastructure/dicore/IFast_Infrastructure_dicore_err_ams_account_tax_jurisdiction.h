#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_dicore_err_ams_account_tax_jurisdiction : public CConditionObject
	{
	public:
		CIFast_Infrastructure_dicore_err_ams_account_tax_jurisdiction() { }
		~CIFast_Infrastructure_dicore_err_ams_account_tax_jurisdiction() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AMS_ACCOUNT_TAX_JURISDICTION")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dicore")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The account tax jurisdiction has not been set up for the AMS portfolio.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("The account tax jurisdiction has not been set up for the AMS portfolio.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("The account tax jurisdiction has not been set up for the AMS portfolio.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La juridiction fiscale du compte n'a pas été réglée pour le portefeuille de service de gestion de portefeuille.")); }

        // Actions
	};
}



