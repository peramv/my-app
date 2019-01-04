#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_didbrkr_didbrkr_cannot_assign_dataelement_objects : public CConditionObject
	{
	public:
		CBase_Ifds_didbrkr_didbrkr_cannot_assign_dataelement_objects() { }
		~CBase_Ifds_didbrkr_didbrkr_cannot_assign_dataelement_objects() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DIDBRKR_CANNOT_ASSIGN_DATAELEMENT_OBJECTS")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("didbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_DE_DE() const { return DString(I_("Arbeitsauftrag-CBE-Schlüssel dupliziert.")); }

        // Actions
		virtual DString GetAction_DE_DE() const { return DString(I_("Check system")); }
	};
}



