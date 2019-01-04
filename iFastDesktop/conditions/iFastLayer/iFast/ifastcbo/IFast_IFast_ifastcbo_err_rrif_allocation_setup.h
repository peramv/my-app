#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_rrif_allocation_setup : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_rrif_allocation_setup() { }
		~CIFast_IFast_ifastcbo_err_rrif_allocation_setup() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RRIF_ALLOCATION_SETUP")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("RRIF Allocation has not been set up.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("RRIF-Zuweisung wurde nicht erstellt!")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se han configurado las asignaciones RRIF.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La répartition FERR n'a pas été réglée.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("RRIF-allocatie is niet ingesteld!")); }

        // Actions
	};
}



