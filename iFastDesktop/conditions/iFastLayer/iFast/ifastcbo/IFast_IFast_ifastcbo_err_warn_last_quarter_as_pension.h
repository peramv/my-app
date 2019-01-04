#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_warn_last_quarter_as_pension : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_warn_last_quarter_as_pension() { }
		~CIFast_IFast_ifastcbo_err_warn_last_quarter_as_pension() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_WARN_LAST_QUARTER_AS_PENSION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("This is the last quarter of AS Pension Plan.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Dies ist das letzte Quartal des AS-Rentenplans.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Éste es el último trimestre del plan de jubilación AS")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("C'est le dernier trimestre de x.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Dit is het laatste kwartaal van AS-pensioenplan")); }

        // Actions
	};
}



