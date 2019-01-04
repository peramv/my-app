#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_house_account : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_house_account() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_house_account() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_HOUSE_ACCOUNT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Federal jurisdiction is not permitted for this Tax Type.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Federal jurisdiction is not permitted for this Tax Type.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Bundeszuständigkeit ist für diese Steuerart nicht zulässig.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se permite la jurisdicción federal para este tipo tributario")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La juridiction fédérale n'est pas autorisée pour ce type d'imposition.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Federaal rechtsgebied is niet toegestaan voor dit belastingtype")); }

        // Actions
	};
}



