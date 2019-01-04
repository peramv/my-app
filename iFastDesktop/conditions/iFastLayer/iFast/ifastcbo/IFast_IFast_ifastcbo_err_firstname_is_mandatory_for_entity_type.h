#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_firstname_is_mandatory_for_entity_type : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_firstname_is_mandatory_for_entity_type() { }
		~CIFast_IFast_ifastcbo_err_firstname_is_mandatory_for_entity_type() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FIRSTNAME_IS_MANDATORY_FOR_ENTITY_TYPE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("First name is required for %ENTITY_TYPE%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("First name is required for %ENTITY_TYPE%.")); }

        // Actions
	};
}