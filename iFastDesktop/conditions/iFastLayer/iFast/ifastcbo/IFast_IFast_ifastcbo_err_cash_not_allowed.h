#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_cash_not_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_cash_not_allowed() { }
		~CIFast_IFast_ifastcbo_err_cash_not_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CASH_NOT_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Distribution can only be re-invested.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Verteilung kann nur reinvestiert sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La distribución sólo puede reinvertirse.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La distribution peut seulement être réinvestie.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Distributie kan alleen opnieuw worden belegd")); }

        // Actions
	};
}



