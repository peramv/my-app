#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_lockedin_to_non_registed_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_lockedin_to_non_registed_allowed() { }
		~CIFast_IFast_ifastcbo_warn_lockedin_to_non_registed_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_LOCKEDIN_TO_NON_REGISTED_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Allowed Transfer is from Locked-IN to Non Registered")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le transfert autorisé est un transfert d'immobilisé à non enregistré.")); }

        // Actions
	};
}



