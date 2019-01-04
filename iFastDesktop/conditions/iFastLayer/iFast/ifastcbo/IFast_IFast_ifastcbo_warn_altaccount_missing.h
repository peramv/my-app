#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_altaccount_missing : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_altaccount_missing() { }
		~CIFast_IFast_ifastcbo_warn_altaccount_missing() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_ALTACCOUNT_MISSING")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Alternate Account value is missing")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Alternate Account value is missing")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La valeur de l'autre compte est manquante.")); }

        // Actions
	};
}



