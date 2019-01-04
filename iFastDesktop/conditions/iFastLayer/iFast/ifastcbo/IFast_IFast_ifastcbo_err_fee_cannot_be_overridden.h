#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_fee_cannot_be_overridden : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_fee_cannot_be_overridden() { }
		~CIFast_IFast_ifastcbo_err_fee_cannot_be_overridden() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FEE_CANNOT_BE_OVERRIDDEN")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fee cannot be overridden, due to set-up.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fee cannot be overridden, due to set-up.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les frais ne peuvent être modifiés en raison du réglage.")); }

        // Actions
	};
}



