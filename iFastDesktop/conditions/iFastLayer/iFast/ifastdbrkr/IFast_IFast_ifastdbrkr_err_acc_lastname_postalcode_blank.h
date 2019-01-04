#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_acc_lastname_postalcode_blank : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_acc_lastname_postalcode_blank() { }
		~CIFast_IFast_ifastdbrkr_err_acc_lastname_postalcode_blank() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACC_LASTNAME_POSTALCODE_BLANK")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account Number, Last Name and Postal Code cannot be blank.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Kontonummer, Nachname und Postleitzahl können nicht leer sein")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Los campos de número de cuenta, apellido y código postal no pueden estar en blanco")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le numéro de compte, le nom de famille et le code postal sont requis.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Accountnummer, achternaam en postcode mogen niet leeg zijn")); }

        // Actions
	};
}



