#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_guarantee_adjust_need_cancellation : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_guarantee_adjust_need_cancellation() { }
		~CIFast_IFast_ifastdbrkr_err_guarantee_adjust_need_cancellation() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_GUARANTEE_ADJUST_NEED_CANCELLATION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Guarantee adjustments need to be cancelled before DOB change due to reduction age impact.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Guarantee adjustments need to be cancelled before DOB change due to reduction age impact.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les ajustements de garantie doivent être annulés avant le changement de date de naissance en raison de l'impact de la réduction d'âge.")); }

        // Actions
	};
}



