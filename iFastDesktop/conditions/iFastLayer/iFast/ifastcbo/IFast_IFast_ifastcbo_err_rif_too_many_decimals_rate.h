#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_rif_too_many_decimals_rate : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_rif_too_many_decimals_rate() { }
		~CIFast_IFast_ifastcbo_err_rif_too_many_decimals_rate() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RIF_TOO_MANY_DECIMALS_RATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Rate must have only two decimal digits.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Rate must have only two decimal digits.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Satz darf nur zwei Dezimalstellen haben.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La tasa sólo debe tener dos dígitos decimales.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le taux ne doit avoir que deux caractères numériques décimaux.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Tarief mag slechts twee cijfers achter de komma hebben")); }

        // Actions
	};
}



