#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_warn_escrow_units_excess_holding : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_warn_escrow_units_excess_holding() { }
		~CIFast_IFast_ifastcbo_err_warn_escrow_units_excess_holding() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_WARN_ESCROW_UNITS_EXCESS_HOLDING")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Escrow/Assigned units exceed current settled units balance:  %SETTLEUNIT%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Treuhand-Anteile überschreiten aktuellen abgerechneten Anteil-Saldo :  %SETTLEUNIT%")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Las unidades en custodia exceden el saldo de unidades liquidadas actuales:  %SETTLEUNIT%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les unités de la mise en garantie excèdent le solde actuel d'unités réglées : %SETTLEUNIT%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Pandeenheden overschrijden huidig saldo betaalde eenheden:  %SETTLEUNIT%")); }

        // Actions
	};
}



