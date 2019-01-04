#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_dfhresp_disabled : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_dfhresp_disabled() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_dfhresp_disabled() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_DFHRESP_DISABLED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Trade belongs to previous tax year.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("L'operation est comprise dans l'exercice fiscal precedent")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Handel gehört zum vorigen Steuerjahr.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La operación pertenece al año fiscal anterior")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La transaction appartient à l'année d'imposition précédente.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Handel behoort bij voorgaande belastingjaar")); }

        // Actions
	};
}



