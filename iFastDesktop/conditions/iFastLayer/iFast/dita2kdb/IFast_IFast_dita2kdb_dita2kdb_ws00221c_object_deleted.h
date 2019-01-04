#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_object_deleted : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_object_deleted() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_object_deleted() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_OBJECT_DELETED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Database error.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Database error.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Datenbankfehler.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Error de la base de datos.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Erreur de la base de données")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Databasefout")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact System Administrator. See logs.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contact System Administrator. See logs.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an den Systemadministrator. Siehe Protokolle.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Contact System Administrator. See logs.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec l'administrateur du système. Voir les journaux de marche.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een systeembeheerder. Raadpleeg de logboeken")); }
	};
}



