#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_system_down : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_system_down() { }
		~CIFast_IFast_dita2kdb_dita2kdb_system_down() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_SYSTEM_DOWN")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("This account does not invest in any fund.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Ce compte n'investit pas dans un fonds.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Dieses Konto investiert nicht in einen Fonds.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Esta cuenta no invierte en ningún fondo.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Ce compte n'investit dans aucun fonds.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Dit account belegt in geen enkel fonds")); }

        // Actions
	};
}



