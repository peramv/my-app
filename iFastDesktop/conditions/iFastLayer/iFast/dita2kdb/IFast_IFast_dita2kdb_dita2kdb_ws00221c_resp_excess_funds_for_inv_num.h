#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_excess_funds_for_inv_num : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_excess_funds_for_inv_num() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_excess_funds_for_inv_num() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_EXCESS_FUNDS_FOR_INV_NUM")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Batch search type is invalid.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Batch search type is invalid.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Batch-Suchart ist ungültig.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El tipo de búsqueda por lotes no es válido")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Type de recherche de lot invalide")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Zoektype batch is ongeldig")); }

        // Actions
	};
}



