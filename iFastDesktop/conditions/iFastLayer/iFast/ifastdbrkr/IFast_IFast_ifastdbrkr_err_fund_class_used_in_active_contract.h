﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_fund_class_used_in_active_contract : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_fund_class_used_in_active_contract() { }
		~CIFast_IFast_ifastdbrkr_err_fund_class_used_in_active_contract() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FUND_CLASS_USED_IN_ACTIVE_CONTRACT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fund/Class is used in an active contract.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fund/Class is used in an active contract.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Fund/Class is used in an active contract.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le fonds/la classe est utilisé(e) dans un contrat actif.")); }

        // Actions
	};
}



