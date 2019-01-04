#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_invalid_holding_comp_code : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_invalid_holding_comp_code() { }
		~CIFast_IFast_ifastcbo_err_invalid_holding_comp_code() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_HOLDING_COMP_CODE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid Holding Company Code.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Code de société de portefeuille invalide.")); }

        // Actions
	};
}



