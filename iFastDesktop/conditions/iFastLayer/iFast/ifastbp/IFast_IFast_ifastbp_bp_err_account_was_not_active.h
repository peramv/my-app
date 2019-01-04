#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastbp_bp_err_account_was_not_active : public CConditionObject
	{
	public:
		CIFast_IFast_ifastbp_bp_err_account_was_not_active() { }
		~CIFast_IFast_ifastbp_bp_err_account_was_not_active() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("BP_ERR_ACCOUNT_WAS_NOT_ACTIVE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastbp")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account was not active.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Account was not active.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Konto war nicht aktiv.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La cuenta no estaba activa.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le compte était inactif.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Account was niet actief")); }

        // Actions
	};
}



