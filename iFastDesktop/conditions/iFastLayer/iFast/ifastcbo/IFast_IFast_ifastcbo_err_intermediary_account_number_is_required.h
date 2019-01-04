#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_intermediary_account_number_is_required : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_intermediary_account_number_is_required() { }
		~CIFast_IFast_ifastcbo_err_intermediary_account_number_is_required() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INTERMEDIARY_ACCOUNT_NUMBER_IS_REQUIRED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Intermediary account number is a required field for record update.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Intermediary account number is a required field for record update.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Mittler (Intermediary)-Kontonummer ist ein notwendiges Feld für die Aktualisierung des Eintrags Bitte geben Sie einen Wert ein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El número de cuenta de intermediario es un campo obligatorio para la actualización del registro. Por favor introduzca un valor.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le numéro de compte intermédiaire est requis pour la mise à jour de l'enregistrement.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Accountnummer tussenpersoon is een verplicht veld voor het bijwerken van het record. Vul een waarde in")); }

        // Actions
	};
}



