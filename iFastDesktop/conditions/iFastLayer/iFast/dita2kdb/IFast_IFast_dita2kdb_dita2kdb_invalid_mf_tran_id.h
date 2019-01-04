#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_invalid_mf_tran_id : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_invalid_mf_tran_id() { }
		~CIFast_IFast_dita2kdb_dita2kdb_invalid_mf_tran_id() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_INVALID_MF_TRAN_ID")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No RIF Setup Information.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("No RIF Setup Information.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Keine RIF-Setup-Informationen")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No hay información de configuración RIF")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucune information sur le réglage FRR")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er zijn geen RIF-instellingsgegevens")); }

        // Actions
	};
}



