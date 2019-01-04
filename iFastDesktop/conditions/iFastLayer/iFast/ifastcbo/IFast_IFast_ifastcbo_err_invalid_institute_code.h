#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_invalid_institute_code : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_invalid_institute_code() { }
		~CIFast_IFast_ifastcbo_err_invalid_institute_code() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_INSTITUTE_CODE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Institution code does not exist.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Ce code d'etablissement n'existe pas. Veuillez ressaisir un code ou appuyer sur F4 pour obtenir une liste de banques valides.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Instituts-Code existiert nicht. Bitte geben Sie neu ein oder drücken Sie F4, um eine Liste mit gültigen Banken einzusehen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El código de institución no existe. Por favor vuelva a introducir los datos o presione F4 para ver una lista de bancos válidos.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Code d'institution inexistant")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Instellingscode bestaat niet. Vul deze opnieuw in of druk op F4 voor een lijst met geldige banken")); }

        // Actions
	};
}



