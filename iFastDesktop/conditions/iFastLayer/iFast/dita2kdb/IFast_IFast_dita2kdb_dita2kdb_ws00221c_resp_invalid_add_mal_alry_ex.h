#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_add_mal_alry_ex : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_add_mal_alry_ex() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_add_mal_alry_ex() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_ADD_MAL_ALRY_EX")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Only one Parent/Legal Guardian Entity is allowed.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Only one Parent/Legal Guardian Entity is allowed.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Nur ein Eltern / Vormund-Objekt ist zugelassen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Sólo se permite una entidad Padre/Tutor legal")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Une seule entité parent/tuteur légal est autorisée.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is slechts één eenheid Ouder/Wettelijke voogd toegestaan")); }

        // Actions
	};
}



