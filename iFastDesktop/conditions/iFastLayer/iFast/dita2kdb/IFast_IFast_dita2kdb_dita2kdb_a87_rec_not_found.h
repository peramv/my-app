#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_a87_rec_not_found : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_a87_rec_not_found() { }
		~CIFast_IFast_dita2kdb_dita2kdb_a87_rec_not_found() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_A87_REC_NOT_FOUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Record is locked.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Record is locked.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Eintrag ist gesperrt")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El registro está bloqueado")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'enregistrement est verrouillé.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Record is vergrendeld")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Try later")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Try later")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Versuchen Sie es später noch einmal")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Try later")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Essayez plus tard.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Probeer het later opnieuw")); }
	};
}



