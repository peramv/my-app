﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_clearing_method_not_allowed_for_non_fundsettle_account : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_clearing_method_not_allowed_for_non_fundsettle_account() { }
		~CIFast_IFast_ifastcbo_err_clearing_method_not_allowed_for_non_fundsettle_account() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CLEARING_METHOD_NOT_ALLOWED_FOR_NON_FUNDSETTLE_ACCOUNT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Clearing Method not allowed for non Fund Settle Account.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Clearing Method not allowed for non Fund Settle Account.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Clearing Method not allowed for non Fund Settle Account.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La méthode de compensation n'est pas autorisée pour les comptes qui ne sont pas des compte de règlement de fonds.")); }

        // Actions
	};
}



