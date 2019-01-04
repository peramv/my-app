#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_no_rif_allocation_info : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_no_rif_allocation_info() { }
		~CIFast_IFast_ifastdbrkr_err_no_rif_allocation_info() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_RIF_ALLOCATION_INFO")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No RIF Allocation Information.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("No RIF Allocation Information.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Keine RIF-Zuweisungs-Informationen")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No hay información de asignación RIF")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucune information sur la répartition FRR")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er zijn geen RIF-allocatiegegevens")); }

        // Actions
	};
}



