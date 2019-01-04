#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_invalid_age : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_invalid_age() { }
		~CIFast_IFast_ifastcbo_warn_invalid_age() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_INVALID_AGE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Age not valid for tax type")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Âge invalide pour le type d'imposition")); }

        // Actions
	};
}



