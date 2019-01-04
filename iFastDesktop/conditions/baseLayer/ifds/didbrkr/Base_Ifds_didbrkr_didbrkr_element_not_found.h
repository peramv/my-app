#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_didbrkr_didbrkr_element_not_found : public CConditionObject
	{
	public:
		CBase_Ifds_didbrkr_didbrkr_element_not_found() { }
		~CBase_Ifds_didbrkr_didbrkr_element_not_found() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DIDBRKR_ELEMENT_NOT_FOUND")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("didbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_FR_FR() const { return DString(I_("Field %TAG% has an invalid type - expecting %TYPE%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Das Feld %TAG% hat einen ungültigen Typ - %TYPE% wird erwartet")); }

        // Actions
		virtual DString GetAction_FR_FR() const { return DString(I_("Make sure the correct type is used.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Vergewissern Sie sich, dass der richtige Typ verwendet wird.")); }
	};
}



