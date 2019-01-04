#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_xparser_err_no_request_name : public CConditionObject
	{
	public:
		CBase_Infrastructure_xparser_err_no_request_name() { }
		~CBase_Infrastructure_xparser_err_no_request_name() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_REQUEST_NAME")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("xparser")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There is an internal problem. Cannot persist an undefined persistence.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("There is an internal problem. Cannot persist an undefined persistence.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Es gibt ein internes Problem. Nicht definierte Fortdauer kann nicht eingehalten werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Hay un problema interno. No se puede persistir una persistencia no definida.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a un problème interne. Impossible de poursuivre une persistance non définie.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is een intern probleem. Ongedefinieerde persistentie kan niet worden doorgezet")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a support representative to verify install configuration.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contact a support representative to verify install configuration.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Support-Mitarbeiter, um die Installationskonfiguration zu überprüfen.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Póngase en contacto con un representante de soporte técnico para verificar la configuración de instalación.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant technique pour vérifier la configuration de l'installation.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supportmedewerker om de installatieconfiguratie te controleren")); }
	};
}



