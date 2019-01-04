#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_didbrkr_didbrkr_properties_dont_match : public CConditionObject
	{
	public:
		CBase_Ifds_didbrkr_didbrkr_properties_dont_match() { }
		~CBase_Ifds_didbrkr_didbrkr_properties_dont_match() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DIDBRKR_PROPERTIES_DONT_MATCH")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("didbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_FR_FR() const { return DString(I_("There is an internal problem. Object %OBJECT% marked as private use.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Es gibt ein internes Problem. Objekt %OBJECT% als Privatnutzung gekennzeichnet.")); }

        // Actions
		virtual DString GetAction_FR_FR() const { return DString(I_("Contactez un representant en assitance technique et communiquez-lui ce message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Support-Mitarbeiter und teilen Sie ihm die Meldung mit.")); }
	};
}



