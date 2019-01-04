#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_trade_is_thirty_old_older : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_trade_is_thirty_old_older() { }
		~CIFast_IFast_ifastdbrkr_err_trade_is_thirty_old_older() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TRADE_IS_THIRTY_OLD_OLDER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Trade is 30 days old or older.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Handel ist 30 Tage alt oder älter.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La operación tiene 30 días o más.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La transaction date de 30 jours ou plus.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Transactie is 30 dagen oud of ouder")); }

        // Actions
	};
}



