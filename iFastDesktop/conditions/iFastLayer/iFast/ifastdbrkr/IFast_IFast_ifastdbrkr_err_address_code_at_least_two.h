#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_address_code_at_least_two : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_address_code_at_least_two() { }
		~CIFast_IFast_ifastdbrkr_err_address_code_at_least_two() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ADDRESS_CODE_AT_LEAST_TWO")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Address code must be at least two characters long.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Address code must be at least two characters long.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Adresscode muss aus mindestens zwei Zeichen bestehen")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El código de dirección debe tener al menos 2 caracteres")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code d'adresse doit contenir au moins 2 caractères.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Adrescode moet ten minste twee tekens lang zijn")); }

        // Actions
	};
}



