#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_xparser_err_create_parser : public CConditionObject
	{
	public:
		CBase_Infrastructure_xparser_err_create_parser() { }
		~CBase_Infrastructure_xparser_err_create_parser() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CREATE_PARSER")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("xparser")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There is an internal problem. Cannot read configuration definition.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("There is an internal problem. Cannot read configuration definition.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Es gibt ein internes Problem. Die Konfigurationsdefinition kann nicht gelesen werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Hay un problema interno. No se puede leer la definición de la configuración.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a un problème interne. Impossible de lire la définition de la configuration.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is een intern probleem. Configuratiedefinitie kan niet worden gelezen")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a support representative to verify install configuration.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contact a support representative to verify install configuration.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Support-Mitarbeiter, um die Installationskonfiguration zu überprüfen.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Póngase en contacto con un representante de soporte técnico para verificar la configuración de instalación.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant technique pour vérifier la configuration de l'installation.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supportmedewerker om de installatieconfiguratie te controleren")); }
	};
}



