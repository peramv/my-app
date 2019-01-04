#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_dita2kdb_dita2kdb_record_already_exist : public CConditionObject
	{
	public:
		CIFast_Infrastructure_dita2kdb_dita2kdb_record_already_exist() { }
		~CIFast_Infrastructure_dita2kdb_dita2kdb_record_already_exist() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_RECORD_ALREADY_EXIST")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Record already exists.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Record already exists.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Dieser Eintrag existiert bereits.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El registro ya existe.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Enregistrement déjà existant")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Record bestaat al")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Verify data entered.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verify data entered.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie die eingegebenen Daten.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verifique los datos introducidos.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez les données saisies.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer de ingevoerde gegevens")); }
	};
}



