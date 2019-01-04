#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_rrifamountcannotbelessequalzero : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_rrifamountcannotbelessequalzero() { }
		~CIFast_IFast_ifastcbo_err_rrifamountcannotbelessequalzero() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RRIFAmountCannotBeLessEqualZero")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Gross payment can not be less or equal to 0.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Brutto-Zahlung darf nicht weniger oder gleich 0,0 sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El pago bruto no puede ser inferior o igual a 0.0")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le paiement brut ne peut être inférieur ou égal à zéro.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Bruto betaling kan niet minder zijn dan of gelijk zijn aan 0,0")); }

        // Actions
	};
}



