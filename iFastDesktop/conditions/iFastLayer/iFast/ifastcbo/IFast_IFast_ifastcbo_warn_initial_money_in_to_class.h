#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_initial_money_in_to_class : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_initial_money_in_to_class() { }
		~CIFast_IFast_ifastcbo_warn_initial_money_in_to_class() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_INITIAL_MONEY_IN_TO_A_CLASS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Initial money-in to a class.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Fonds entrants initiaux dans une catégorie.")); }

        // Actions
	};
}



