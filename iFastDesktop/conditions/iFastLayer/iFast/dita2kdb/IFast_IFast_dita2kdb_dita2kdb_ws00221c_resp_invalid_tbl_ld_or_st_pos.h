﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_tbl_ld_or_st_pos : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_tbl_ld_or_st_pos() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_tbl_ld_or_st_pos() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_TBL_LD_OR_ST_POS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Close Account redemption code entered without full redemption.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Close Account redemption code entered without full redemption.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Konto-Abschluss-Tilgungscode mit voller Tilgung eingegeben")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Se introdujo el código de rescate con cierre de cuenta sin rescate total.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code de rachat de fermeture du compte a été saisi sans rachat total.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Aflossingscode voor sluiten account is ingevoerd zonder volledige aflossing")); }

        // Actions
	};
}



