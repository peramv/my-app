#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_no_a53_for_verify_dte : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_no_a53_for_verify_dte() { }
		~CIFast_IFast_dita2kdb_dita2kdb_no_a53_for_verify_dte() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_NO_A53_FOR_VERIFY_DTE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Not enough input information for record selection.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Not enough input information for record selection.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Nicht genügend Informationen zur Auswahl eines Eintrags eingegeben")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se introdujo suficiente información para la selección de un registro")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'information saisie est insuffisante à la sélection d'enregistrement.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Onvoldoende invoergegevens voor recordselectie")); }

        // Actions
	};
}



