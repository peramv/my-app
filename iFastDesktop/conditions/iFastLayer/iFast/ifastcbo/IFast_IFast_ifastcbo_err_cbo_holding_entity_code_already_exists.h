#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_cbo_holding_entity_code_already_exists : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_cbo_holding_entity_code_already_exists() { }
		~CIFast_IFast_ifastcbo_err_cbo_holding_entity_code_already_exists() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CBO_HOLDING_ENTITY_CODE_ALREADY_EXISTS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Holding Company Code already exists.")); }

        // Actions
	};
}



