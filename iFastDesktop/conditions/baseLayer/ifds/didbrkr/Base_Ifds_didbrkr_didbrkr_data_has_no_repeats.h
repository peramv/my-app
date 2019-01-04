#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_didbrkr_didbrkr_data_has_no_repeats : public CConditionObject
	{
	public:
		CBase_Ifds_didbrkr_didbrkr_data_has_no_repeats() { }
		~CBase_Ifds_didbrkr_didbrkr_data_has_no_repeats() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DIDBRKR_DATA_HAS_NO_REPEATS")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("didbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_DE_DE() const { return DString(I_("%STRING%")); }

        // Actions
		virtual DString GetAction_DE_DE() const { return DString(I_("Check system")); }
	};
}



