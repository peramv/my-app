#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_matching_key_not_found : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_matching_key_not_found() { }
		~CIFast_IFast_ifastcbo_warn_matching_key_not_found() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_MATCHING_KEY_NOT_FOUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The Matching Key does not exist for F50 record.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La clé correspondante n'existe pas pour l'enregistrement F50.")); }

        // Actions
	};
}
