#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_address_code_not_effective : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_address_code_not_effective() { }
		~CIFast_IFast_ifastcbo_err_address_code_not_effective() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ADDRESS_CODE_NOT_EFFECTIVE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Address code %CODE% is no longer effective. Please assign another code, or create an effective address with this code.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Le code d'adresse %CODE% n'est plus en vigueur pour ce compte. Veuillez attribuer un autre code ou creer une adresse en vigueur avec ce code.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Der Adresscode %CODE% ist nicht mehr wirksam. Bitte weisen Sie einen anderen Code zu oder erstellen Sie eine wirksame Adresse mit diesem Code.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El código de dirección %CODE% ya no está vigente. Por favor asigne otro código o cree una nueva dirección vigente con este código.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code d'adresse %CODE% n'est plus en vigueur. Veuillez attribuer un autre code ou créer une adresse en vigueur avec ce code.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Adrescode %CODE% is niet langer van kracht. Wijs een andere code toe, of maak een nieuw geldig adres met deze code")); }

        // Actions
	};
}



