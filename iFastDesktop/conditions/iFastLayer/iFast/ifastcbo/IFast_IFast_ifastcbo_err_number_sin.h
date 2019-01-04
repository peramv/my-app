#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_number_sin : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_number_sin() { }
		~CIFast_IFast_ifastcbo_err_number_sin() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NUMBER_SIN")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Social insurance number must be 9 digits.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Social insurance number must be 9 digits.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Die Sozialversicherungsnummer muss aus 9 Ziffern bestehen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El número de Seguro Social debe tener 9 dígitos")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le numéro d'assurance sociale doit être composé de 9 caractères numériques.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Sofi-nummer moet uit 9 cijfers bestaan")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("please re-enter")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("please re-enter")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Bitte geben Sie neu ein.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("please re-enter")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Veuillez recommencer la saisie.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("vul opnieuw in")); }
	};
}



