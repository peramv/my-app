#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastcbo_err_address_code_not_effective : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastcbo_err_address_code_not_effective() { }
		~CIFast_Infrastructure_ifastcbo_err_address_code_not_effective() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ADDRESS_CODE_NOT_EFFECTIVE")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Field %FIELD% is required.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Field '^' is required.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Das Feld %FIELD% ist notwendig.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El campo %FIELD% es obligatorio.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le champ %FIELD% est requis.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Veld %FIELD% is vereist")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Required fields cannot be set to blank or null.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Les zones obligatoires ne peuvent pas etre vides ou renseignees avec 0.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Notwendige Felder können nicht auf leer oder null eingestellt werden.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Required fields cannot be set to blank or null.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Les champs requis ne peuvent être laissés vides ou réglés à zéro.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Vereiste velden mogen niet leeg zijn of de waarde null bevatten")); }
	};
}



