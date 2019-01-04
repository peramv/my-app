#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_invalid_wkn_number : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_invalid_wkn_number() { }
		~CIFast_IFast_ifastcbo_err_invalid_wkn_number() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_WKN_NUMBER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("WKN does not exist on i-FAST.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("WKN does not exist on i-FAST.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("WKN inexistant dans iFAST")); }

        // Actions
	};
}



