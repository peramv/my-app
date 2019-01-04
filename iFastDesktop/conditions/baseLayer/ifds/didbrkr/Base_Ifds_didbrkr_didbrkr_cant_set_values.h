#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_didbrkr_didbrkr_cant_set_values : public CConditionObject
	{
	public:
		CBase_Ifds_didbrkr_didbrkr_cant_set_values() { }
		~CBase_Ifds_didbrkr_didbrkr_cant_set_values() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DIDBRKR_CANT_SET_VALUES")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("didbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_FR_FR() const { return DString(I_("Unable to retrieve data for %LABEL%")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Daten für %LABEL% können nicht ausgelesen werden.")); }

        // Actions
		virtual DString GetAction_FR_FR() const { return DString(I_("Verify CBO code.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie den CBO-Code.")); }
	};
}



