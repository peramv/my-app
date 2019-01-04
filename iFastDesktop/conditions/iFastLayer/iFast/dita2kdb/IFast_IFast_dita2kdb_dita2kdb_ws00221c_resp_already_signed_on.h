#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_already_signed_on : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_already_signed_on() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_already_signed_on() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_ALREADY_SIGNED_ON")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
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



