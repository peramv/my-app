#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_a90_info_unavail : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_a90_info_unavail() { }
		~CIFast_IFast_dita2kdb_dita2kdb_a90_info_unavail() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_A90_INFO_UNAVAIL")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Registered Address not available for the account.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Registered Address not available for the account.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Registrierte Adresse für das Konto nicht verfügbar")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La dirección registrada no está disponible para la cuenta")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'adresse enregistrée n'est pas disponible pour le compte.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Geregistreerd adres is niet beschikbaar voor het account")); }

        // Actions
	};
}



