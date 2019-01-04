#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_re_blc_excl_cd : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_re_blc_excl_cd() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_re_blc_excl_cd() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_RE_BLC_EXCL_CD")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No Cot-Contract-ShGroup record found.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("No Cot-Contract-ShGroup record found.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Contract-ShGroup-Eintrag nicht gefunden")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se encontró el registro Cot-Contract-ShGroup")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucun enregistrement du groupe de l'actionnaire du contrat x n'a été trouvé.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Record Cot-Contract-ShGroup is niet gevonden")); }

        // Actions
	};
}



