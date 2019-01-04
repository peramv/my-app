#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_comm_shares_not_found : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_comm_shares_not_found() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_comm_shares_not_found() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_COMM_SHARES_NOT_FOUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Maximum must be greater than Mandatory Annual Amount.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Maximum must be greater than Mandatory Annual Amount.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Maximum muss größer als der obligatorische Jahresbetrag sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El máximo debe ser superior al monto anual obligatorio.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le maximum doit être supérieur au montant annuel requis.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Maximum moet groter zijn dan verplicht jaarbedrag")); }

        // Actions
	};
}



