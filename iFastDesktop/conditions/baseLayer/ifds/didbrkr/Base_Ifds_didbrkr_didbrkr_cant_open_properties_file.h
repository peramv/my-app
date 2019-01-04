#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_didbrkr_didbrkr_cant_open_properties_file : public CConditionObject
	{
	public:
		CBase_Ifds_didbrkr_didbrkr_cant_open_properties_file() { }
		~CBase_Ifds_didbrkr_didbrkr_cant_open_properties_file() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DIDBRKR_CANT_OPEN_PROPERTIES_FILE")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("didbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_FR_FR() const { return DString(I_("La valeur %VALUE% est inferieure a la valeur minimum autorisée, %MIN%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Der Wert %VALUE% ist kleiner als der erlaubte Minimalwert %MIN%.")); }

        // Actions
		virtual DString GetAction_FR_FR() const { return DString(I_("Saisissez une valeur superieure a la valeur minimum autorisee.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Geben Sie einen Wert ein, der größer als der erlaubte Minimalwert ist.")); }
	};
}



