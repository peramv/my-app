#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_trfx_age_diff_not_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_trfx_age_diff_not_allowed() { }
		~CIFast_IFast_ifastcbo_err_trfx_age_diff_not_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TRFX_AGE_DIFF_NOT_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Transfer from one account to another account whose annuitant's ages are different, is not allowed.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le transfert d'un compte à un autre lorsque l'âge des crédirentiers est différent n'est pas autorisé.")); }

        // Actions
	};
}



