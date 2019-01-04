#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_settlement_not_allowed_551 : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_settlement_not_allowed_551() { }
		~CIFast_IFast_ifastdbrkr_err_settlement_not_allowed_551() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SETTLEMENT_NOT_ALLOWED_551")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Settlements is not allowed in account.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Settlements is not allowed in account.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les règlements ne sont pas autorisés pour le compte.")); }

        // Actions
	};
}



