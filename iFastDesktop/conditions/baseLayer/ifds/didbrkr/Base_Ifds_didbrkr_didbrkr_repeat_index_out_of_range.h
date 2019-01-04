#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_didbrkr_didbrkr_repeat_index_out_of_range : public CConditionObject
	{
	public:
		CBase_Ifds_didbrkr_didbrkr_repeat_index_out_of_range() { }
		~CBase_Ifds_didbrkr_didbrkr_repeat_index_out_of_range() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DIDBRKR_REPEAT_INDEX_OUT_OF_RANGE")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("didbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_DE_DE() const { return DString(I_("Arbeitsauftrag-CBE bereits registriert.")); }

        // Actions
		virtual DString GetAction_DE_DE() const { return DString(I_("Check system")); }
	};
}



