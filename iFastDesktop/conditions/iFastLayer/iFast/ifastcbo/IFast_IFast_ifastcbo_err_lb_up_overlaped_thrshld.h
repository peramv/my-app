#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_lb_up_overlaped_thrshld : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_lb_up_overlaped_thrshld() { }
		~CIFast_IFast_ifastcbo_err_lb_up_overlaped_thrshld() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_LB_UP_OVERLAPED_THRSHLD")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fee threshold upper bound and lower bound overlapped for %THRSHLD%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les limites supérieure et inférieure du seuil de frais se chevauchent pour %THRSHLD%.")); }

        // Actions
	};
}



