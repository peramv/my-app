#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_account_inactive : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_account_inactive() { }
		~CIFast_IFast_ifastdbrkr_err_account_inactive() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCOUNT_INACTIVE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account is not active.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Konto ist nicht aktiv.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La cuenta no está activa")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Compte inactif")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Account is niet actief")); }

        // Actions
	};
}



