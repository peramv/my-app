#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_invalid_tradeindate : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_invalid_tradeindate() { }
		~CIFast_IFast_ifastcbo_err_invalid_tradeindate() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_TRADEINDATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Trade In Date is before Trade Out Date.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("rade In Date is before Trade Out Date.")); }

        // Actions
	};
}



