#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_acct_grp_list_empty : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_acct_grp_list_empty() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_acct_grp_list_empty() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_ACCT_GRP_LIST_EMPTY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Parent/Legal Guardian has not been setup.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Parent/Legal Guardian has not been setup.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Eltern / Vormund wurde nicht erstellt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se ha configurado el padre/tutor legal")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le champ Parent/tuteur légal n'a pas été rempli.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ouder/Wettelijke voogd is niet ingesteld")); }

        // Actions
	};
}



