#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_fees_waived : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_fees_waived() { }
		~CIFast_IFast_ifastdbrkr_err_fees_waived() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FEES_WAIVED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fees are waived for this account.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Auf Provisionen wurde für dieses Konto verzichtet.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Se exceptúan las comisiones para esta cuenta.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les frais sont exonérés pour ce compte.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er worden geen kosten berekend voor dit account")); }

        // Actions
	};
}



