#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_dita2kdb_dita2kdb_systran_instr_exist : public CConditionObject
	{
	public:
		CBase_Infrastructure_dita2kdb_dita2kdb_systran_instr_exist() { }
		~CBase_Infrastructure_dita2kdb_dita2kdb_systran_instr_exist() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_SYSTRAN_INSTR_EXIST")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("SYSTRAN instructions exist.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("SYSTRAN instructions exist.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("SYSTRAN-Anweisungen existieren.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Existen instrucciones SYSTRAN.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Instructions SYSTRAN existantes")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er bestaan SYSTRAN-instructies")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Review account options.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Review account options.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie die Kontooptionen.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Review account options.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Passez en revue les options du compte.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Herzie de accountmogelijkheden")); }
	};
}



