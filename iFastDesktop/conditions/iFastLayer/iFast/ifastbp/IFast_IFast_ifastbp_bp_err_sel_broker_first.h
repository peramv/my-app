#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastbp_bp_err_sel_broker_first : public CConditionObject
	{
	public:
		CIFast_IFast_ifastbp_bp_err_sel_broker_first() { }
		~CIFast_IFast_ifastbp_bp_err_sel_broker_first() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("BP_ERR_SEL_BROKER_FIRST")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastbp")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Please select a broker first.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Please select a broker first.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Wählen Sie zuerst einen Broker.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Por favor seleccione un corredor primero.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Veuillez d'abord sélectionner un courtier.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Selecteer eerst een makelaar")); }

        // Actions
	};
}



