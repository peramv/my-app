﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_transaction_not_found : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_transaction_not_found() { }
		~CIFast_IFast_ifastdbrkr_err_transaction_not_found() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TRANSACTION_NOT_FOUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Transaction not found.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Transaction not found.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Transaktion nicht gefunden")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se encontró la transacción")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Transaction introuvable")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Transactie is niet gevonden")); }

        // Actions
	};
}



