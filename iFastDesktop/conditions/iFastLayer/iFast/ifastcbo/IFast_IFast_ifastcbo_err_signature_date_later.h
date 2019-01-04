#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_signature_date_later : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_signature_date_later() { }
		~CIFast_IFast_ifastcbo_err_signature_date_later() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SIGNATURE_DATE_LATER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Signature Date %DATE1% later than the PAC Effective Date %DATE2%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Date de signature %DATE1% postérieure à la date d’effet de la PAC %DATE2%.")); }

        // Actions
	};
}



