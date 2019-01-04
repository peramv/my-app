#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastcbo_err_primary_benef_percent_should_add_up_to_100 : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastcbo_err_primary_benef_percent_should_add_up_to_100() { }
		~CIFast_Infrastructure_ifastcbo_err_primary_benef_percent_should_add_up_to_100() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PRIMARY_BENEF_PERCENT_SHOULD_ADD_UP_TO_100")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("^'.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("^'.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("^'.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("^'.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("^'.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("^'")); }

        // Actions
	};
}



