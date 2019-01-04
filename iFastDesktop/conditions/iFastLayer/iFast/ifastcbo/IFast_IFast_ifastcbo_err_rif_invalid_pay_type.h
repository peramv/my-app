#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_rif_invalid_pay_type : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_rif_invalid_pay_type() { }
		~CIFast_IFast_ifastcbo_err_rif_invalid_pay_type() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RIF_INVALID_PAY_TYPE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Only \"E\", \"S\", \"M\" and \"X\" are valid values.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Only \"E\", \"S\", \"M\" and \"X\" are valid values.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Nur \"E\", \"S\", \"M\" und \"X\" sind gültige Werte.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Sólo \"E\", \"S\", \"M\" y \"X\" son valores válidos.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les seules valeurs valides sont E, S, M et X.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Alleen  'E, 'S', 'M' en 'X' zijn geldige waarden")); }

        // Actions
	};
}



