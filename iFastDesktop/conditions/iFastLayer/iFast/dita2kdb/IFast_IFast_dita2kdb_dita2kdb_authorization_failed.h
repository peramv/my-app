#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_authorization_failed : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_authorization_failed() { }
		~CIFast_IFast_dita2kdb_dita2kdb_authorization_failed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_AUTHORIZATION_FAILED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid Group.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Invalid Group.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültige Gruppe")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Grupo no válido")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Groupe invalide")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldige groep")); }

        // Actions
	};
}



