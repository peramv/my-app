#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_entity_cannot_be_used_with_redemption_code : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_entity_cannot_be_used_with_redemption_code() { }
		~CIFast_IFast_ifastcbo_err_entity_cannot_be_used_with_redemption_code() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ENTITY_CANNOT_BE_USED_WITH_REDEMPTION_CODE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The entity (%entityid%) cannot be used with redemption code (%redcode%).")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("The entity (%entityid%) cannot be used with redemption code (%redcode%).")); }

        // Actions
	};
}



