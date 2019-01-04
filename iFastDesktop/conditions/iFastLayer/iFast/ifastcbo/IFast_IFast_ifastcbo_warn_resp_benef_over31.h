#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_resp_benef_over31 : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_resp_benef_over31() { }
		~CIFast_IFast_ifastcbo_warn_resp_benef_over31() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_RESP_BENEF_OVER31")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Beneficiary %BENNAME% Age is over 31 and trade cannot be processed.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le bénéficiaire %BENNAME% a plus de 31 ans et la transaction ne peut pas être traitée.")); }

        // Actions
	};
}



