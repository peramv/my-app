#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_program_name_not_in_plan : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_program_name_not_in_plan() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_program_name_not_in_plan() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_PROGRAM_NAME_NOT_IN_PLAN")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Corresponding account entity joint record not found.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Corresponding account entity joint record not found.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Entsprechender Gemeinschafts-Eintrag für das Konto-Objekt nicht gefunden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se encontró el registro conjunto de entidad de cuenta correspondiente")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'enregistrement conjoint de l'entité du compte correspondant est introuvable.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Bijbehorende gezamenlijk record voor accounteenheid is niet gevonden")); }

        // Actions
	};
}



