#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_dita2kdb_dita2kdb_data_not_found : public CConditionObject
	{
	public:
		CIFast_Infrastructure_dita2kdb_dita2kdb_data_not_found() { }
		~CIFast_Infrastructure_dita2kdb_dita2kdb_data_not_found() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_DATA_NOT_FOUND")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Information not found.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Information not found.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Information wurde nicht gefunden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se encontró la información.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Information introuvable")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Informatie is niet gevonden")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Verify search criteria.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verify search criteria.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Bestätigen Sie die Suchkriterien.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verify search criteria.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez les données saisies.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer de zoekcriteria")); }
	};
}



