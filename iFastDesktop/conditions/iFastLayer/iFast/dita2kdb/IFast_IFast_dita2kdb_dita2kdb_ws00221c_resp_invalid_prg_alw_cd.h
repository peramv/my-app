#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_prg_alw_cd : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_prg_alw_cd() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_prg_alw_cd() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_PRG_ALW_CD")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No Contract-Mstr record found.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("No Contract-Mstr record found.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Contract-Mstr-Eintrag nicht gefunden")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se encontró el registro Contract-Mstr")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucun enregistrement de l'original du contrat n'a été trouvé.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Record Contract-Mstr is niet gevonden")); }

        // Actions
	};
}



