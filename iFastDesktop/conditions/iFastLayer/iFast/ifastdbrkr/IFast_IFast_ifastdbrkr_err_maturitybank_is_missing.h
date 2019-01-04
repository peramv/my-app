#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_maturitybank_is_missing : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_maturitybank_is_missing() { }
		~CIFast_IFast_ifastdbrkr_err_maturitybank_is_missing() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_MATURITYBANK_IS_MISSING")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Bank information is missing.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Information bancaire manquante")); }

        // Actions
	};
}



