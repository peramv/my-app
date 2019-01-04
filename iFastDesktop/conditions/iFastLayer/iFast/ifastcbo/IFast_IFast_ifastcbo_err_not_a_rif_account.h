#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_not_a_rif_account : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_not_a_rif_account() { }
		~CIFast_IFast_ifastcbo_err_not_a_rif_account() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NOT_A_RIF_ACCOUNT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("RRIF/LIF/LRIF screen not found.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("RRIF/LIF/LRIF screen not found.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("RRIF / LIF / LRIF-Bildschirm nicht gefunden")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se encontró la pantalla RRIF/LIF/LRIF")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Écran FERR/FRV/FRRI introuvable")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Scherm RRIF/LIF/LRIF is niet gevonden")); }

        // Actions
	};
}



