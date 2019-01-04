#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_missing_future_default_settl_instr : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_missing_future_default_settl_instr() { }
		~CIFast_IFast_ifastcbo_warn_missing_future_default_settl_instr() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_MISSING_FUTURE_DEFAULT_SETTL_INSTR")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The current active default settlement instruction will expire on  %DATE%. There are no default instructions set up past this date.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les instructions de règlement par défaut actives actuellement expireront le %DATE%. Aucune instruction par défaut n'a été réglée après cette date.")); }

        // Actions
	};
}



