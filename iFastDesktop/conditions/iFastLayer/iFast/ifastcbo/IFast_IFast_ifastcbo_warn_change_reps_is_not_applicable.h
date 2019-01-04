#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_change_reps_is_not_applicable : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_change_reps_is_not_applicable() { }
		~CIFast_IFast_ifastcbo_warn_change_reps_is_not_applicable() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_CHANGE_REPS_IS_NOT_APPLICABLE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Changing sales representative is not applicable for %ACCOUNT_TYPE% accounts.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le changement de représentant des ventes ne s'applique pas aux comptes de type %ACCOUNT_TYPE%.")); }

        // Actions
	};
}



