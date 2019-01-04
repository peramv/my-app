#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_didbrkr_didbrkr_data_has_no_repeats : public CConditionObject
	{
	public:
		CIFast_Infrastructure_didbrkr_didbrkr_data_has_no_repeats() { }
		~CIFast_Infrastructure_didbrkr_didbrkr_data_has_no_repeats() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DIDBRKR_DATA_HAS_NO_REPEATS")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("didbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Data %props% has no repeats.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Data %props% has no repeats.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Daten %props% haben keine Wiederholungen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Los datos %props% no tienen repeticiones.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les données %props% n'ont aucune répétition.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Gegeven %props% heeft geen herhalingen")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Check system")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verifiez le systeme.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie das System")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verifique el sistema")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez le système.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer het systeem")); }
	};
}



