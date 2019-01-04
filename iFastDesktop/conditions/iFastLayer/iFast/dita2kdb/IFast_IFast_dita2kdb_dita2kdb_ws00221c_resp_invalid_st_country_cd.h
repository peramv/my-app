#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_st_country_cd : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_st_country_cd() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_st_country_cd() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_ST_COUNTRY_CD")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("A contract exists but is not effective until %ContractEffect%.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("A contract exists but is not effective until %ContractEffect%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ein Vertrag existiert, tritt aber nicht vor dem %ContractEffect%. in Kraft")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Existe un contrato pero no entrará en  vigencia hasta %ContractEffect%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Un contrat existe, mais il n'est pas en vigueur avant le %ContractEffect%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er bestaat een overeenkomst maar deze is pas van kracht op %ContractEffect%")); }

        // Actions
	};
}



