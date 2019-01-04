#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_didbrkr_didbrkr_no_path_to_properties_file : public CConditionObject
	{
	public:
		CBase_Ifds_didbrkr_didbrkr_no_path_to_properties_file() { }
		~CBase_Ifds_didbrkr_didbrkr_no_path_to_properties_file() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DIDBRKR_NO_PATH_TO_PROPERTIES_FILE")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("didbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_FR_FR() const { return DString(I_("La valeur %VALUE% est superieure a la valeur maximum autorisée, %MAX%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Der Wert %VALUE% ist größer als der erlaubte Maximalwert %MAX%.")); }

        // Actions
		virtual DString GetAction_FR_FR() const { return DString(I_("Saisissez une valeur inferieure a la valeur maximum autorisee.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Geben Sie einen Wert ein, der kleiner als der erlaubte Maximalwert ist.")); }
	};
}



