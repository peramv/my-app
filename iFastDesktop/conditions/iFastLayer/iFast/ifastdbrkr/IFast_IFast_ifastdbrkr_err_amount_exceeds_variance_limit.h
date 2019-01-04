#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_amount_exceeds_variance_limit : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_amount_exceeds_variance_limit() { }
		~CIFast_IFast_ifastdbrkr_err_amount_exceeds_variance_limit() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AMOUNT_EXCEEDS_VARIANCE_LIMIT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Amount exceeds variance limit")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Amount exceeds variance limit")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le montant excède la limite d'écart.")); }

        // Actions
	};
}



