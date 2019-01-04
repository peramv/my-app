#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_dicore_dicore_persist_registry_fail : public CConditionObject
	{
	public:
		CIFast_Infrastructure_dicore_dicore_persist_registry_fail() { }
		~CIFast_Infrastructure_dicore_dicore_persist_registry_fail() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DICORE_PERSIST_REGISTRY_FAIL")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dicore")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There is an internal problem. Cannot persist to registry.  %GENERIC%")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("There is an internal problem. Cannot persist to registry.  %GENERIC%")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Es gibt ein internes Problem. Verbindung zur Registrierung kann nicht aufrechterhalten werden.  %GENERIC%")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("There is an internal problem. Cannot persist to registry.  %GENERIC%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a un problème interne. Impossible de poursuivre jusqu'au registre. %GENERIC%")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is een intern probleem. Cannot persist to registry.  %GENERIC%")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a support representative to verify install configuration and operator registry privileges.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contact a support representative to verify install configuration and operator registry privileges.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Support-Mitarbeiter, um die Installationskonfiguration und die Registrierungsberechtigungen des Operators zu überprüfen.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Póngase en contacto con un representante de soporte técnico para verificar la configuración de instalación y los privilegios de registro del operador.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant technique pour vérifier la configuration de l'installation et les privilèges de connexion de l'opérateur.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supportmedewerker om de installatieconfiguratie en de registerbevoegdheden van de operator te controleren")); }
	};
}



