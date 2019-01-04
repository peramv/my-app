﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_account_entity_not_found : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_account_entity_not_found() { }
		~CIFast_IFast_ifastdbrkr_err_account_entity_not_found() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCOUNT_ENTITY_NOT_FOUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account entity not found.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Account entity not found.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Kontoobjekt nicht gefunden")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se encontró la entidad de la cuenta")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Entité du compte introuvable")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Accounteenheid is niet gevonden")); }

        // Actions
	};
}



