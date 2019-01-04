#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_invalid_ams_account : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_invalid_ams_account() { }
		~CIFast_IFast_ifastcbo_err_invalid_ams_account() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_AMS_ACCOUNT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid AMS Account.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültiges AMS-Konto.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Cuenta AMS no válida.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le compte de service de gestion de portefeuille est invalide.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldig BBD-account")); }

        // Actions
	};
}



