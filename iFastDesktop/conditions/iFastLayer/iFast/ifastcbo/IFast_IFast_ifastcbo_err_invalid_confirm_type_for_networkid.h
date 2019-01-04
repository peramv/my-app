#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_invalid_confirm_type_for_networkid : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_invalid_confirm_type_for_networkid() { }
		~CIFast_IFast_ifastcbo_err_invalid_confirm_type_for_networkid() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_CONFIRM_TYPE_FOR_NETWORKID")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid other confirm type for the Delivery Network.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Autre type de confirmation invalide pour l'ordre de réseau")); }

        // Actions
	};
}



