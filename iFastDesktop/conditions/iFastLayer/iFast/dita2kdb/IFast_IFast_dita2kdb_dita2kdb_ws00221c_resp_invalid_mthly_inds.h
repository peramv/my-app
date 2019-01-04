#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_mthly_inds : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_mthly_inds() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_mthly_inds() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_MTHLY_INDS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account was not active.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Account was not active.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Konto war nicht aktiv.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La cuenta no estaba activa.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le compte était inactif.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Account was niet actief")); }

        // Actions
	};
}



