#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_reset_override_is_not_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_reset_override_is_not_allowed() { }
		~CIFast_IFast_ifastcbo_err_reset_override_is_not_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RESET_OVERRIDE_IS_NOT_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Cannot reset an overridden Access ID")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible de réinitialiser un code d'accès modifié.")); }

        // Actions
	};
}



