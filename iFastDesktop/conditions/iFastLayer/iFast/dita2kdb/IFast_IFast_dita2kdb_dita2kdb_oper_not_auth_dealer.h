#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_oper_not_auth_dealer : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_oper_not_auth_dealer() { }
		~CIFast_IFast_dita2kdb_dita2kdb_oper_not_auth_dealer() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_OPER_NOT_AUTH_DEALER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Registered address default not found.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Registered address default not found.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Registrierter Adressenstandard nicht gefunden")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se encontró la dirección registrada predeterminada")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'adresse enregistrée par défaut est introuvable.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Standaard geregistreerd adres is niet gevonden")); }

        // Actions
	};
}



