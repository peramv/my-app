#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_address_code_not_setup : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_address_code_not_setup() { }
		~CIFast_IFast_ifastcbo_err_address_code_not_setup() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ADDRESS_CODE_NOT_SETUP")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Address code %CODE% has not been set up for this account. Please assign another code, or create a new address with this code.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Le code d'adresse %CODE% na pas ete defini pour ce compte. Veuillez attribuer un autre code ou creer une nouvelle adresse avec ce code.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Der Adresscode %CODE% wurde nicht für dieses Konto erstellt. Bitte weisen Sie einen anderen Code zu oder erstellen Sie eine neue Adresse mit diesem Code.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se ha configurado el código de dirección %CODE% para esta cuenta. Por favor asigne otro código o cree una nueva dirección con este código.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code d'adresse %CODE% n'a pas été réglé pour ce compte. Veuillez attribuer un autre code ou créer une adresse en vigueur avec ce code.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Adrescode %CODE% is niet ingesteld voor dit account. Wijs een andere code toe, of maak een nieuw adres met deze code")); }

        // Actions
	};
}



