#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_multiple_same_clearing_platform_entity_not_allowed_for_account : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_multiple_same_clearing_platform_entity_not_allowed_for_account() { }
		~CIFast_IFast_ifastcbo_err_multiple_same_clearing_platform_entity_not_allowed_for_account() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_MULTIPLE_SAME_CLEARING_PLATFORM_ENTITY_NOT_ALLOWED_FOR_ACCOUNT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Linking more then once the same clearing platform entity is not allowed for the account.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Relier plus d'une fois la même entité de plateforme de compensation n'est pas autorisé pour le compte.")); }

        // Actions
	};
}



