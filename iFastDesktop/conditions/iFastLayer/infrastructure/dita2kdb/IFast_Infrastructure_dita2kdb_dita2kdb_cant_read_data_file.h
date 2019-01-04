#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_dita2kdb_dita2kdb_cant_read_data_file : public CConditionObject
	{
	public:
		CIFast_Infrastructure_dita2kdb_dita2kdb_cant_read_data_file() { }
		~CIFast_Infrastructure_dita2kdb_dita2kdb_cant_read_data_file() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_CANT_READ_DATA_FILE")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Unable to read data file SIGNON2.DAT")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Unable to read data file SIGNON2.DAT")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Datei SIGNON2.DAT kann nicht geöffnet werden")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Imposible leer el archivo de datos SIGNON2.DAT")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible de lire le fichier de données SIGNON2.DAT.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Gegevensbestand SIGNON2.DAT kan niet worden gelezen")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Check system")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verifiez le systeme.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie das System")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verifique el sistema")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez le système.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer het systeem")); }
	};
}



