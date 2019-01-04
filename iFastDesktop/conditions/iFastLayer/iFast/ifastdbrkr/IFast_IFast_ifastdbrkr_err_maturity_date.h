#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_maturity_date : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_maturity_date() { }
		~CIFast_IFast_ifastdbrkr_err_maturity_date() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_MATURITY_DATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Incorrect calculation of Maturity Date.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Incorrect calculation of Maturity Date.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Falsche Berechnung des Fälligkeitsdatums.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Cálculo incorrecto de la fecha de vencimiento")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Calcul incorrect de la date d'échéance")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Onjuiste berekening van vervaldatum")); }

        // Actions
	};
}



