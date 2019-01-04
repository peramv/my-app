#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_only_exclude_mch_for_thirdpartyfunds : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_only_exclude_mch_for_thirdpartyfunds() { }
		~CIFast_IFast_ifastcbo_err_only_exclude_mch_for_thirdpartyfunds() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ONLY_EXCLUDE_MCH_FOR_THIRDPARTYFUNDS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("MCH Flag should be EXCLUDE for Third Party Funds")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le signal MCH devrait être EXCLUS pour les fonds de tiers.")); }

        // Actions
	};
}



