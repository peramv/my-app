﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_redemption_code_is_not_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_redemption_code_is_not_allowed() { }
		~CIFast_IFast_ifastcbo_warn_redemption_code_is_not_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_REDEMPTION_CODE_IS_NOT_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Redemption Code is not allowed for transfers.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Code de rachat non autorisé pour les transferts")); }

        // Actions
	};
}



