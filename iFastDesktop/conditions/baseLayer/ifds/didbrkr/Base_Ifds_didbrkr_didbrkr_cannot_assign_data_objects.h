#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_didbrkr_didbrkr_cannot_assign_data_objects : public CConditionObject
	{
	public:
		CBase_Ifds_didbrkr_didbrkr_cannot_assign_data_objects() { }
		~CBase_Ifds_didbrkr_didbrkr_cannot_assign_data_objects() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DIDBRKR_CANNOT_ASSIGN_DATA_OBJECTS")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("didbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_DE_DE() const { return DString(I_("Die maximale Länge %MAX% des Feldes %TAG% wurde überschritten.")); }

        // Actions
		virtual DString GetAction_DE_DE() const { return DString(I_("Check input data")); }
	};
}



