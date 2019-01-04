#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_signature_date_later : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_signature_date_later() { }
		~CIFast_IFast_ifastcbo_warn_signature_date_later() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_SIGNATURE_DATE_LATER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Signature Date %DATE1% later than the PAC Effective Date %DATE2%.")); }

        // Actions
	};
}



