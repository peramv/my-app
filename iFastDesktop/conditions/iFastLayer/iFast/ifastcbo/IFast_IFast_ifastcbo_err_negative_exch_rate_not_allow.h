#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_negative_exch_rate_not_allow : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_negative_exch_rate_not_allow() { }
		~CIFast_IFast_ifastcbo_err_negative_exch_rate_not_allow() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NEGATIVE_EXCH_RATE_NOT_ALLOW")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Negative exchange rate is not allowed.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Negativer Wechselkurs ist nicht erlaubt")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se permite un tipo de cambio negativo")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Un taux de change négatif n'est pas autorisé.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Negatieve wisselkoers is niet toegestaan")); }

        // Actions
	};
}



