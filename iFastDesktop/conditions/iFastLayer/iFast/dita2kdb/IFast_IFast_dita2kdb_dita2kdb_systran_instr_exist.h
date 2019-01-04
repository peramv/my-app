#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_systran_instr_exist : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_systran_instr_exist() { }
		~CIFast_IFast_dita2kdb_dita2kdb_systran_instr_exist() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_SYSTRAN_INSTR_EXIST")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No work type was selected.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("No work type was selected.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Es wurde kein Arbeitstyp ausgewählt. Wählen Sie einen Arbeitstyp.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se seleccionó un tipo de tarea. Seleccione un tipo de tarea.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucun type de travail n'a été sélectionné.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is geen werktype geselecteerd. Selecteer een werktype")); }

        // Actions
	};
}



