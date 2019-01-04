#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_settlement_value_date : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_settlement_value_date() { }
		~CIFast_IFast_ifastcbo_err_settlement_value_date() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SETTLEMENT_VALUE_DATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Value date is not equal to %DATE%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Valutatag ist nicht gleich %DATE% .")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La fecha de valuación no es igual a %DATE%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date de valeur n'est pas identique au %DATE%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Waardedatum is niet gelijk aan %DATE%")); }

        // Actions
	};
}



