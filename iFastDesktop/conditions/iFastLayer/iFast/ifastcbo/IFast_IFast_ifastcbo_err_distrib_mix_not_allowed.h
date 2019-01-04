#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_distrib_mix_not_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_distrib_mix_not_allowed() { }
		~CIFast_IFast_ifastcbo_err_distrib_mix_not_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DISTRIB_MIX_NOT_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account level distribution option percentage mixes are not allowed.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les compositions de pourcentage d'option de distribution au niveau du compte ne sont pas autorisées.")); }

        // Actions
	};
}



