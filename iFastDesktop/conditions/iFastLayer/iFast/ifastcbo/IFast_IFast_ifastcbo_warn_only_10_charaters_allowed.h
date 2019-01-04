#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_only_10_charaters_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_only_10_charaters_allowed() { }
		~CIFast_IFast_ifastcbo_warn_only_10_charaters_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_ONLY_10_CHARATERS_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Only ten characters are allowed for wire order number.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Only ten characters are allowed for wire order number.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le numéro de l'ordre électronique ne peut être composé de plus de dix caractères.")); }

        // Actions
	};
}



