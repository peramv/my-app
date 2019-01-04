#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_criteria_limit_exceeded : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_criteria_limit_exceeded() { }
		~CIFast_IFast_ifastcbo_err_criteria_limit_exceeded() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CRITERIA_LIMIT_EXCEEDED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The criteria %CRITERIA% cannot occur more than %MAX% times.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Die Kriterien %CRITERIA% können nicht öfter als %MAX% Mal vorkommen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Los criterios %CRITERIA% no se pueden producir más de %MAX% veces.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le critère %CRITERIA% ne peut apparaître plus de %MAX% fois.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("De criteria %CRITERIA% kunnen niet meer dan %MAX% keer voorkomen")); }

        // Actions
	};
}



