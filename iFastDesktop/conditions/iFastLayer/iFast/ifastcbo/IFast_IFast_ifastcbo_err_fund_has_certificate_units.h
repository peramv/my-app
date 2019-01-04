#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_fund_has_certificate_units : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_fund_has_certificate_units() { }
		~CIFast_IFast_ifastcbo_err_fund_has_certificate_units() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FUND_HAS_CERTIFICATE_UNITS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fund has certificate units.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a des unités de certificat au fonds.")); }

        // Actions
	};
}



