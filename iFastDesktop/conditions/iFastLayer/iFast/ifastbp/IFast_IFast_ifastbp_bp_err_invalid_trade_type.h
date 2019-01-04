#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastbp_bp_err_invalid_trade_type : public CConditionObject
	{
	public:
		CIFast_IFast_ifastbp_bp_err_invalid_trade_type() { }
		~CIFast_IFast_ifastbp_bp_err_invalid_trade_type() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("BP_ERR_INVALID_TRADE_TYPE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastbp")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid Trades Transaction Type.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültiger Handels-Transaktionsart.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Tipo de transacción de operaciones no válido.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Type de transaction des transactions invalide")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldig handelstransactietype")); }

        // Actions
	};
}



