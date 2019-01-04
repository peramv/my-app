#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastcbo_err_fund_not_rrsp_eligible : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastcbo_err_fund_not_rrsp_eligible() { }
		~CIFast_Infrastructure_ifastcbo_err_fund_not_rrsp_eligible() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FUND_NOT_RRSP_ELIGIBLE")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Object is not a valid type.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Object is not a valid type.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Das Objekt ist kein gültiger Typ.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El objeto no es un tipo válido.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'objet n'est pas une type valide.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Object is geen geldig type")); }

        // Actions
	};
}



