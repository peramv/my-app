#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_cap_gains_code : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_cap_gains_code() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_cap_gains_code() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_CAP_GAINS_CODE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("ITF Entity should be setup.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("ITF Entity should be setup.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("ITF-Objekt sollte erstellt sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Debe configurarse la entidad ITF")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'entité EFP doit être créée.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("ITF-eenheid moet worden ingesteld")); }

        // Actions
	};
}



