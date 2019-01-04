#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_reset_exceed_max : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_reset_exceed_max() { }
		~CIFast_IFast_ifastcbo_err_reset_exceed_max() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RESET_EXCEED_MAX")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The number of resets exceed the maximum allowed.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("The number of resets exceed the maximum allowed.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("The number of resets exceed the maximum allowed.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le nombre de revalorisations excède le maximum autorisé.")); }

        // Actions
	};
}



