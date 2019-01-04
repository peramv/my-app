#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_holding_comp_code_is_required : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_holding_comp_code_is_required() { }
		~CIFast_IFast_ifastcbo_err_holding_comp_code_is_required() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_HOLDING_COMP_CODE_IS_REQUIRED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Holding Company Code is Required.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Code de société de portefeuille requis.")); }

        // Actions
	};
}



