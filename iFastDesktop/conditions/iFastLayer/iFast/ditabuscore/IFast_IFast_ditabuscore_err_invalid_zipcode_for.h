#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ditabuscore_err_invalid_zipcode_for : public CConditionObject
	{
	public:
		CIFast_IFast_ditabuscore_err_invalid_zipcode_for() { }
		~CIFast_IFast_ditabuscore_err_invalid_zipcode_for() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_ZIPCODE_FOR")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ditabuscore")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The Field is required for record update.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("La zone %FieldName% doit être renseignee pour la mise a jour de l'enregistrement. Veuillez saisir une valeur.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Das Feld ist für die Aktualisierung des Eintrags erforderlich. Bitte geben Sie einen Wert ein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El campo es obligatorio para la actualización del registro. Por favor introduzca un valor.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Ce champ doit être rempli pour la mise à jour de l'enregistrement.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Het veld is vereist voor het bijwerken van het record. Vul een waarde in")); }

        // Actions
	};
}



