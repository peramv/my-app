#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_dita2kdb_dita2kdb_invalid_start_year : public CConditionObject
	{
	public:
		CIFast_Infrastructure_dita2kdb_dita2kdb_invalid_start_year() { }
		~CIFast_Infrastructure_dita2kdb_dita2kdb_invalid_start_year() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_INVALID_START_YEAR")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The system does not recognize start year.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("The system does not recognize start year.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Das System erkennt dieses Startjahr nicht.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El sistema no reconoce el año de inicio.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le système ne reconnaît pas l'année de début.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Het systeem herkent beginjaar niet")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Verify start year and re-enter.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verify start year and re-enter.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie das Startjahr und geben Sie es erneut ein.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verifique el año de inicio y vuelva a introducirlo.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez l'année de début et réessayez.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer het beginjaar en voer dit opnieuw in")); }
	};
}



