#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_connect_internal_error : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_connect_internal_error() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_connect_internal_error() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_CONNECT_INTERNAL_ERROR")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Shareholder number already exists in the database.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Le numero d'actionnaire existe deja dans la base de donnees")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Aktionärs-Nummer existiert bereits in der Datenbank.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El número de accionista ya existe en la base de datos")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le numéro d'actionnaire existe déjà dans la base de données.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Aandeelhoudersnummer bestaat al in de database")); }

        // Actions
	};
}



