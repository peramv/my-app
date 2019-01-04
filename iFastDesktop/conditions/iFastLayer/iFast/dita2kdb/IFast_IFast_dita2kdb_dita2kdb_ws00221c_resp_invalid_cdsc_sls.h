#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_cdsc_sls : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_cdsc_sls() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_cdsc_sls() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_CDSC_SLS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("RRIF-Detail recid is invalid.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("RRIF-Detail recid is invalid.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("RRIF-Detaileintrags-ID ist ungültig")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La identificación de registro RRIF-Detail no es válida.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code d'enregistrement de détail FERR est invalide.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Record-ID RRIF-Detail is ongeldig")); }

        // Actions
	};
}



