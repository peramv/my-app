#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_invalid_isin_number : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_invalid_isin_number() { }
		~CIFast_IFast_ifastcbo_err_invalid_isin_number() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_ISIN_NUMBER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("ISIN does not exist on i-FAST.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("ISIN does not exist on i-FAST.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("ISIN inexistant dans iFAST")); }

        // Actions
	};
}



