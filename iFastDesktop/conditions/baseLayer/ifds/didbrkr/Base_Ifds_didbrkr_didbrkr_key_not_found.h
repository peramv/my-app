#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_didbrkr_didbrkr_key_not_found : public CConditionObject
	{
	public:
		CBase_Ifds_didbrkr_didbrkr_key_not_found() { }
		~CBase_Ifds_didbrkr_didbrkr_key_not_found() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DIDBRKR_KEY_NOT_FOUND")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("didbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_DE_DE() const { return DString(I_("Feld %TAG% wurde nicht gültig gesetzt.")); }

        // Actions
		virtual DString GetAction_DE_DE() const { return DString(I_("Check input data")); }
	};
}



