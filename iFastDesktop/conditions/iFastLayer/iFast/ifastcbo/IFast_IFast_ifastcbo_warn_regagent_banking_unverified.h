#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_regagent_banking_unverified : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_regagent_banking_unverified() { }
		~CIFast_IFast_ifastcbo_warn_regagent_banking_unverified() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_REGAGENT_BANKING_UNVERIFIED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Reg Agent Banking Instructions not Verified")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les instruction bancaire de l'agent d'enregistrement ne sont pas vérifiées.")); }

        // Actions
	};
}



