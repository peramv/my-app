#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_no_dep_id_records_available : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_no_dep_id_records_available() { }
		~CIFast_IFast_ifastdbrkr_err_no_dep_id_records_available() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_DEP_ID_RECORDS_AVAILABLE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No Dep Id records available.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Keine Einträge für  Depot-ID verfügbar")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No hay registros de identificación de depósito disponibles")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucun enregistrement de code de dépôt n'est disponible.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er zijn geen records Deposito-ID beschikbaar")); }

        // Actions
	};
}



