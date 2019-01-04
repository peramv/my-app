#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_two_decimal_point_only : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_two_decimal_point_only() { }
		~CIFast_IFast_ifastcbo_err_two_decimal_point_only() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TWO_DECIMAL_POINT_ONLY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Please enter only two decimal points.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Veuillez saisir deux decimales uniquement.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Bitte geben Sie nur zwei Dezimalstellen ein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Por favor introduzca sólo dos decimales.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Veuillez ne saisir que deux signes décimaux.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Vul slechts twee cijfers achter de komma in")); }

        // Actions
	};
}



