#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_duplicate_key_ok : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_duplicate_key_ok() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_duplicate_key_ok() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_DUPLICATE_KEY_OK")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("At least two active Accountholder entities must be set up for this type of account.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Au moins deux entites de Titulaires de compte actives doivent être definies pour ce type de compte")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Für diese Kontoart müssen mindestens zwei Kontoinhaber-Objekte erstellt werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Deben configurarse al menos dos entidades de titular de cuenta activas para este tipo de cuenta.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Au moins deux entités titulaires de compte actives doivent être réglées pour ce type de compte.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er moeten ten minste twee actieve accounthouderseenheden zijn gemaakt voor dit type account")); }

        // Actions
	};
}



