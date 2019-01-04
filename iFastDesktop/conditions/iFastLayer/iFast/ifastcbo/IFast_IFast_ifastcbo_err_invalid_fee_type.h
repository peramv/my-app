#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_invalid_fee_type : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_invalid_fee_type() { }
		~CIFast_IFast_ifastcbo_err_invalid_fee_type() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_FEE_TYPE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid Fee Type.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Type de frais invalide")); }

        // Actions
	};
}



