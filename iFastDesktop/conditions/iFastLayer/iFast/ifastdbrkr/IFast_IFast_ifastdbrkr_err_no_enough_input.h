#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_no_enough_input : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_no_enough_input() { }
		~CIFast_IFast_ifastdbrkr_err_no_enough_input() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_ENOUGH_INPUT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Input must either have All Fund Group Types or specific Fund Group Type.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Input must either have All Fund Group Types or specific Fund Group Type.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Eingabe muss entweder Gesamtfonds-Gruppenarten oder spezifische Fonds-Gruppenart beinhalten.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La información introducida debe tener Todos los tipos de grupos de fondos o un Tipo de grupo de fondo específico")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La saisie doit être tous les types de groupe de fonds ou un type de groupe de fonds spécifique.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("De invoer moet van het type Alle typen fondsgroepen of een bepaald Fondsgroeptype zijn")); }

        // Actions
	};
}



