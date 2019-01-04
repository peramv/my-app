#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_fund_class_must_both_be_blank : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_fund_class_must_both_be_blank() { }
		~CIFast_IFast_ifastcbo_err_fund_class_must_both_be_blank() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FUND_CLASS_MUST_BOTH_BE_BLANK")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fund and Class must both be blank or both be entered.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fonds und Klasse müssen entweder beide leer oder beide eingegeben sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El fondo y la clase deben estar en blanco o deben introducirse ambos.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les champs Fonds et Classe doivent être tous deux vides ou tous deux remplis.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Fonds en categorie moeten beide leeg zijn of beide zijn ingevuld")); }

        // Actions
	};
}



