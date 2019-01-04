#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_address_line45 : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_address_line45() { }
		~CIFast_IFast_ifastcbo_err_address_line45() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ADDRESS_LINE45")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Address line 4 and 5 are required.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Les lignes 4 et 5 de l'adresse sont requises, veuillez ressaisir")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Die Adresszeilen 4 und 5 sind erforderlich, bitte geben Sie neu ein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La línea de dirección 4 y 5 son obligatorias; por favor vuelva a introducir los datos.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les lignes d'adresse 4 et 5 doivent être remplies.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Adresregel 4 en 5 zijn vereist, vul deze opnieuw in")); }

        // Actions
	};
}



