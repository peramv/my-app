#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_didbrkr_didbrkr_not_a_dataelement_object : public CConditionObject
	{
	public:
		CBase_Ifds_didbrkr_didbrkr_not_a_dataelement_object() { }
		~CBase_Ifds_didbrkr_didbrkr_not_a_dataelement_object() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DIDBRKR_NOT_A_DATAELEMENT_OBJECT")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("didbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_DE_DE() const { return DString(I_("Arbeitsauftrag-CBE-Schlüssel nicht gefunden.")); }

        // Actions
		virtual DString GetAction_DE_DE() const { return DString(I_("Check system")); }
	};
}



