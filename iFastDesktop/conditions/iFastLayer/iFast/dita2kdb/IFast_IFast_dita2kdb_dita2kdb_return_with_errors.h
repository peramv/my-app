#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_return_with_errors : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_return_with_errors() { }
		~CIFast_IFast_dita2kdb_dita2kdb_return_with_errors() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_RETURN_WITH_ERRORS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Client Account can not have a Nominee Owner.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Client Account can not have a Nominee Owner.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Kunden-Konto kann keinen Bevollmächtigten Inhaber haben")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La cuenta de cliente no puede tener un propietario nominatario")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Un compte client ne peut avoir de propriétaire nominé.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Klantaccount mag geen gevolmachtigde eigenaar hebben")); }

        // Actions
	};
}



