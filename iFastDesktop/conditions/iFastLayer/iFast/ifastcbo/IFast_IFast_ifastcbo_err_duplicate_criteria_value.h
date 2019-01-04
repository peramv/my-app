#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_duplicate_criteria_value : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_duplicate_criteria_value() { }
		~CIFast_IFast_ifastcbo_err_duplicate_criteria_value() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DUPLICATE_CRITERIA_VALUE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Duplicate criteria (%CRITERIA%) with value (%VALUE%).")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Doppelte Kriterien (%CRITERIA%) mit Wert (%VALUE%).")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Criterios repetidos (%CRITERIA%) con valor (%VALUE%).")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Copie du critère (%CRITERIA%) avec la valeur (%VALUE%)")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Dubbele criteria (%CRITERIA%) met waarde (%VALUE%)")); }

        // Actions
	};
}



