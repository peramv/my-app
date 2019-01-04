#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_didbrkr_didbrkr_file_seek_failed : public CConditionObject
	{
	public:
		CBase_Ifds_didbrkr_didbrkr_file_seek_failed() { }
		~CBase_Ifds_didbrkr_didbrkr_file_seek_failed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DIDBRKR_FILE_SEEK_FAILED")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("didbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_FR_FR() const { return DString(I_("There is an internal problem.  Object does not support field group processing.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Es gibt ein internes Problem.  Das Objekt unterstützt Feldgruppenverarbeitung nicht.")); }

        // Actions
		virtual DString GetAction_FR_FR() const { return DString(I_("Contactez un representant en assitance technique et communiquez-lui ce message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Support-Mitarbeiter und teilen Sie ihm die Meldung mit.")); }
	};
}



