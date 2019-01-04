#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_multiple_clearing_platfrom_id_not_allowed_for_clearing_platform : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_multiple_clearing_platfrom_id_not_allowed_for_clearing_platform() { }
		~CIFast_IFast_ifastcbo_err_multiple_clearing_platfrom_id_not_allowed_for_clearing_platform() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_MULTIPLE_CLEARING_PLATFROM_ID_NOT_ALLOWED_FOR_CLEARING_PLATFORM")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("More then one clearing platform id for the same clearing platform entity is not allowed.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Avoir plus d'un code de plateforme de compensation pour la même entité de plateforme de compensation n'est pas autorisé.")); }

        // Actions
	};
}



