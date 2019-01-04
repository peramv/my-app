#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_loi_eff_dte : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_loi_eff_dte() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_loi_eff_dte() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_LOI_EFF_DTE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Broker name empty.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Broker name empty.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Brokername ist nicht eingetragen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Nombre de corredor vacío.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le nom du courtier est vide.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Makelaarsnaam is leeg")); }

        // Actions
	};
}



