#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_no_rif_setup_info : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_no_rif_setup_info() { }
		~CIFast_IFast_ifastdbrkr_err_no_rif_setup_info() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_RIF_SETUP_INFO")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
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



