#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_manual_dividend_not_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_manual_dividend_not_allowed() { }
		~CIFast_IFast_ifastcbo_err_manual_dividend_not_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_MANUAL_DIVIDEND_NOT_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Manual dividend posting for this fund is not allowed.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Manual dividend posting for this fund is not allowed.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Manual dividend posting for this fund is not allowed.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'enregistrement manuel des dividendes n'est pas autorisé pour ce fonds.")); }

        // Actions
	};
}



