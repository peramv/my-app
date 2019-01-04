#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_apo_fpo_reg_fmt : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_apo_fpo_reg_fmt() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_apo_fpo_reg_fmt() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_APO_FPO_REG_FMT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Annuitant Entity should be setup and only one entry is allowed.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Annuitant Entity should be setup and only one entry is allowed.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Rentenempfänger-Objekt sollte erstellt sein und nur ein Eintrag ist zugelassen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Debe configurarse la entidad Titular de la anualidad y sólo se permite una entrada")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le crédirentier doit être créé; un seul crédirentier est autorisé.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Eenheid lijfrentetrekker moet worden ingesteld en er is slechts één eenheid toegestaan")); }

        // Actions
	};
}



