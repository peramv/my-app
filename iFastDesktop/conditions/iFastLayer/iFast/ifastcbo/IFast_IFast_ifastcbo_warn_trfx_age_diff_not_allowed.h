#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_trfx_age_diff_not_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_trfx_age_diff_not_allowed() { }
		~CIFast_IFast_ifastcbo_warn_trfx_age_diff_not_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_TRFX_AGE_DIFF_NOT_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Transfer from one account to another account whose annuitant's ages are different, may not be allowed.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le transfert d'un compte à un autre lorsque l'âge des crédirentiers est différent pourrait ne pas être autorisé.")); }

        // Actions
	};
}



