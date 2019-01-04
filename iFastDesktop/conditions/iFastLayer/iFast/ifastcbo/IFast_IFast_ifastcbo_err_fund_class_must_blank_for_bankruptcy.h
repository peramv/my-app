#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_fund_class_must_blank_for_bankruptcy : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_fund_class_must_blank_for_bankruptcy() { }
		~CIFast_IFast_ifastcbo_err_fund_class_must_blank_for_bankruptcy() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FUND_CLASS_MUST_BLANK_FOR_BANKRUPTCY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fund and Class must be blank for bankruptcy reason code.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fonds und Klasse müssen leer sein wegen des Konkurs-Begründungscodes.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El fondo y la clase deben estar en blanco para el código de motivo de quiebra")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les champs Fonds et Classe doivent être vides pour le code de raison de la faillite.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Fonds en categorie moeten leeg zijn voor redencode faillissement")); }

        // Actions
	};
}



