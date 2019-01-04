#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_invalid_mfr_payment : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_invalid_mfr_payment() { }
		~CIFast_IFast_ifastdbrkr_err_invalid_mfr_payment() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_MFR_PAYMENT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid payment period.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Période de paiement invalide")); }

        // Actions
	};
}



