#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resource_not_available : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resource_not_available() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resource_not_available() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESOURCE_NOT_AVAILABLE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("User has no access to the Sales Representative.  Secrecy Consent not held.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("L'utilisateur n'a pas accès à ce conseiller financier.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Benutzer hat keinen Zugriff auf Verkaufsvertreter.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El usuario no tiene acceso al representante de ventas")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'utilisateur n'a pas accès au représentant des ventes. Un accord de confidentialité est requis.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Gebruiker heeft geen toegang tot de vertegenwoordiger")); }

        // Actions
	};
}



