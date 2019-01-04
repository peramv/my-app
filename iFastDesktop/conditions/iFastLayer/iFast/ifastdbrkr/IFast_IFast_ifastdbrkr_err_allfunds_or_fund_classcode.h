#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_allfunds_or_fund_classcode : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_allfunds_or_fund_classcode() { }
		~CIFast_IFast_ifastdbrkr_err_allfunds_or_fund_classcode() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ALLFUNDS_OR_FUND_CLASSCODE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Input must either have All funds or Fund and class code.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Input must either have All funds or Fund and class code.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Die Eingabe muss entweder Gesamtfonds- oder Fonds- und Klassencode beinhalten.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La información introducida debe tener Todos los fondos o Fondo y código de clase")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Vous devez saisir tous les fonds ou les codes de fonds et de classe.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Invoer moet Alle fondsen of Fonds en categoriecode bevatten")); }

        // Actions
	};
}



