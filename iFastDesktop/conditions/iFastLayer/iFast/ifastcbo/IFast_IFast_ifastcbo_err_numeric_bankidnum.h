#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_numeric_bankidnum : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_numeric_bankidnum() { }
		~CIFast_IFast_ifastcbo_err_numeric_bankidnum() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NUMERIC_BANKIDNUM")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Bank ID must be numeric for this bank type.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Bank-ID für diese Bankart muss nummerisch sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La identificación de banco debe ser numérica para este tipo de banco.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code de la banque doit être numérique pour ce type de banque.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Bank-ID moet numeriek zijn voor dit banktype")); }

        // Actions
	};
}



