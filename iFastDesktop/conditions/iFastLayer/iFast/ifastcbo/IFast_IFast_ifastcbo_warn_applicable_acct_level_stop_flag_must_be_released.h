#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_applicable_acct_level_stop_flag_must_be_released : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_applicable_acct_level_stop_flag_must_be_released() { }
		~CIFast_IFast_ifastcbo_warn_applicable_acct_level_stop_flag_must_be_released() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_APPLICABLE_ACCT_LEVEL_STOP_FLAG_MUST_BE_RELEASED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Please review and update applicable stop flag at account level.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Veuillez réviser et mettre à jour le signal d'arrêt applicable au niveau du compte.")); }

        // Actions
	};
}



