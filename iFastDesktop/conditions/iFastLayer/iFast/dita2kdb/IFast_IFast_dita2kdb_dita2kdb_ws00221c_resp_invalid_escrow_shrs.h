#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_escrow_shrs : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_escrow_shrs() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_escrow_shrs() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_ESCROW_SHRS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Rate must be smaller or equal to 100.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Rate must be smaller or equal to 100.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Satz muss kleiner oder gleich 100 sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La tasa debe ser inferior o igual a 100.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le taux doit être inférieur ou égal à 100.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Tarief moet kleiner zijn dan of gelijk aan 100")); }

        // Actions
	};
}



