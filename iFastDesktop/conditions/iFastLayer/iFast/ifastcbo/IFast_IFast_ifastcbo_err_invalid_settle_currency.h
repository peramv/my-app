#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_invalid_settle_currency : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_invalid_settle_currency() { }
		~CIFast_IFast_ifastcbo_err_invalid_settle_currency() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_SETTLE_CURRENCY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Settle Currency is mandatory.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Abrechnungswährung ist obligatorisch")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La divisa de liquidación es obligatoria")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La monnaie de règlement est requise.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Betalingsvaluta is verplicht")); }

        // Actions
	};
}



