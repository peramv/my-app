#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_xparser_err_delete_parser : public CConditionObject
	{
	public:
		CBase_Infrastructure_xparser_err_delete_parser() { }
		~CBase_Infrastructure_xparser_err_delete_parser() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DELETE_PARSER")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("xparser")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There is an internal problem. Cannot open file: %PATH%")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("There is an internal problem. Cannot open file: %PATH%")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Es gibt ein internes Problem. Folgende Datei kann nicht geöffnet werden: %PATH%")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Hay un problema interno. No se puede abrir el archivo: %PATH%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a un problème interne. Impossible d'ouvrir le fichier : %PATH%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is een intern probleem. Bestand kan niet worden geopend: %PATH%")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a support representative to verify this file or check install configuration.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contact a support representative to verify this file or check install configuration.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Support-Mitarbeiter, um diese Datei und die Installationskonfiguration zu überprüfen.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Póngase en contacto con un representante de soporte técnico para verificar este archivo o verificar la configuración de instalación.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant technique pour vérifier ce fichier ou la configuration de l'installation.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supportmedewerker om dit bestand te controleren of controleer de installatieconfiguratie")); }
	};
}



