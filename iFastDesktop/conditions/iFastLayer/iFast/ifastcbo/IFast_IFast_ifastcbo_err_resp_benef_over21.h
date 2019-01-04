#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_resp_benef_over21 : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_resp_benef_over21() { }
		~CIFast_IFast_ifastcbo_err_resp_benef_over21() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RESP_BENEF_OVER21")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Beneficiary %BENNAME% is over 21 and trade cannot be processed.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le bénéficiaire %BENNAME% a plus de 21 ans et la transaction ne peut pas être traitée.")); }

        // Actions
	};
}



